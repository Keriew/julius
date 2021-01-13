#include "dock.h"

#include "building/market.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "empire/city.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/routing.h"
#include "map/terrain.h"
#include "scenario/map.h"
#include "empire/empire.h"
#include "figuretype/trader.h"

int building_dock_count_idle_dockers(const building *dock)
{
    int num_idle = 0;
    for (int i = 0; i < 3; i++) {
        if (dock->data.dock.docker_ids[i]) {
            figure *f = figure_get(dock->data.dock.docker_ids[i]);
            if (f->action_state == FIGURE_ACTION_132_DOCKER_IDLING ||
                f->action_state == FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE) {
                num_idle++;
            }
        }
    }
    return num_idle;
}

void building_dock_update_open_water_access(void)
{
    map_point river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry.x, river_entry.y);
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_IN_USE && !b->house_size && b->type == BUILDING_DOCK) {
            if (map_terrain_is_adjacent_to_open_water(b->x, b->y, 3)) {
                b->has_water_access = 1;
            } else {
                b->has_water_access = 0;
            }
        }
    }
}

int building_dock_is_connected_to_open_water(int x, int y)
{
    map_point river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry.x, river_entry.y);
    if (map_terrain_is_adjacent_to_open_water(x, y, 3)) {
        return 1;
    } else {
        return 0;
    }
}

int building_dock_accepts_ship(int ship_id, int dock_id)
{
    building* dock = building_get(dock_id);
    figure* f = figure_get(ship_id);
    empire_city* city = empire_city_get(f->empire_city_id);
    for (int resource = RESOURCE_WHEAT; resource < RESOURCE_MAX; resource++) {
        if (city->sells_resource[resource] || city->buys_resource[resource]) {
            if (is_good_accepted(resource - 1, dock)) {
                return 1;
            }
        }
    }
    return 0;
}

int building_dock_can_import_from_ship(building *dock, int ship_id) {
    figure *ship = figure_get(ship_id);
    if (ship->loads_sold_or_carrying <= 0) {
        return 0;
    }
    
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX; r++) {
        if (is_good_accepted(r - 1, dock) && empire_can_import_resource_from_city(ship->empire_city_id, r)) {
            return 1;
        }
    }
    return 0;
}

int building_dock_can_export_to_ship(building *dock, int ship_id) {
    figure *ship = figure_get(ship_id);
    if (ship->trader_amount_bought >= figure_trade_sea_trade_units()) {
        return 0;
    }
    
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX; r++) {
        if (is_good_accepted(r - 1, dock) && empire_can_export_resource_to_city(ship->empire_city_id, r)) {
            return 1;
        }
    }
    return 0;
}

int building_dock_get_dock_accepting_ship(int ship_id) {
    if (!city_buildings_has_working_dock()) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id) continue;
        if (building_dock_accepts_ship(ship_id,dock_id)) {
            return dock_id;
        }
    }
    return 0;
}

int building_dock_get_free_destination(int ship_id, map_point *tile)
{
    if (!city_buildings_has_working_dock()) {
        return 0;
    }
    figure *ship = figure_get(ship_id);
    int importing_dock_id = 0;
    int exporting_dock_id = 0;
    int dock_id = 0;
    
    for (int i = 0; i < 10; i++) {
        dock_id = city_buildings_get_working_dock(i);
        if (!dock_id) continue;
        if (!building_dock_accepts_ship(ship_id, dock_id)) continue;
        if (figure_trader_ship_docked_once(ship, dock_id)) continue;

        building* dock = building_get(dock_id);
        if (dock->data.dock.trade_ship_id == ship_id) {
            if (ship->action_state == FIGURE_ACTION_112_TRADE_SHIP_MOORED && ship->destination_building_id == dock_id) {
                continue;
            } else {
                importing_dock_id = exporting_dock_id = dock_id;
                break;
            }
        }

        if (!dock->data.dock.trade_ship_id) {
            
            if (ship->action_state == FIGURE_ACTION_110_TRADE_SHIP_CREATED) {
                importing_dock_id = dock_id;
                break;
            }

            if (building_dock_can_import_from_ship(dock, ship_id)) {
                importing_dock_id = dock_id;
                // prioritize imports
                break;
            } else if (building_dock_can_export_to_ship(dock, ship_id)) {
                exporting_dock_id = dock_id;
            } else if (ship->action_state == FIGURE_ACTION_114_TRADE_SHIP_ANCHORED && map_figure_at(ship->grid_offset) == ship->id) {
                importing_dock_id = exporting_dock_id = dock_id;
                break;
            }
        }
    }
    
    dock_id = importing_dock_id ? importing_dock_id : exporting_dock_id;     
    if (dock_id <= 0) {
        return 0;
    }

    building *dock = building_get(dock_id);
    int dx, dy;
    switch (dock->data.dock.orientation) {
        case 0: dx = 1; dy = -1; break;
        case 1: dx = 3; dy = 1; break;
        case 2: dx = 1; dy = 3; break;
        default: dx = -1; dy = 1; break;
    }
    map_point_store_result(dock->x + dx, dock->y + dy, tile);
    dock->data.dock.trade_ship_id = ship_id;
    figure_trader_ship_record_dock(ship, dock_id);
    return dock_id;
}

int building_dock_get_queue_destination(int ship_id, map_point *tile)
{
    if (!city_buildings_has_working_dock()) {
        return 0;
    }
    figure *ship = figure_get(ship_id);
    int importing_dock_id = 0;
    int exporting_dock_id = 0;
    int first_queue_available_dock = 0;
    int second_queue_available_dock = 0;
    // first queue position
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id) continue;
        if (!building_dock_accepts_ship(ship_id, dock_id))
        {
            dock_id = 0;
            continue;
        }
        if (figure_trader_ship_docked_once(ship, dock_id)) continue;
        building *dock = building_get(dock_id);
        int dx, dy;
        switch (dock->data.dock.orientation) {
            case 0: dx = 2; dy = -2; break;
            case 1: dx = 4; dy = 2; break;
            case 2: dx = 2; dy = 4; break;
            default: dx = -2; dy = 2; break;
        }
        map_point_store_result(dock->x + dx, dock->y + dy, tile);
        if (!map_has_figure_at(map_grid_offset(tile->x, tile->y))) {
            if (!first_queue_available_dock) first_queue_available_dock = dock_id;
            if (figure_trader_ship_can_queue_for_import(ship) && building_dock_can_import_from_ship(dock, ship_id)) {
                importing_dock_id = dock_id;
                // prioritize imports
                break;
            } else if (figure_trader_ship_can_queue_for_export(ship) && building_dock_can_export_to_ship(dock, ship_id)) {
                exporting_dock_id = dock_id;
            }
        }
    }

    if (importing_dock_id) {
        return importing_dock_id;
    } else if (exporting_dock_id) {
        return exporting_dock_id;
    }

    // second queue position
    importing_dock_id = exporting_dock_id = 0;
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id) continue;
        if (!building_dock_accepts_ship(ship_id, dock_id))
        {
            dock_id = 0;
            continue;
        }
        if (figure_trader_ship_docked_once(ship, dock_id)) continue;
        building *dock = building_get(dock_id);
        int dx, dy;
        switch (dock->data.dock.orientation) {
            case 0: dx = 2; dy = -3; break;
            case 1: dx = 5; dy = 2; break;
            case 2: dx = 2; dy = 5; break;
            default: dx = -3; dy = 2; break;
        }
        map_point_store_result(dock->x + dx, dock->y + dy, tile);
        if (!map_has_figure_at(map_grid_offset(tile->x, tile->y))) {
            if (!second_queue_available_dock) second_queue_available_dock = dock_id;
            if (figure_trader_ship_can_queue_for_import(ship) && building_dock_can_import_from_ship(dock, ship_id)) {
                importing_dock_id = dock_id;
                // prioritize imports
                break;
            } else if (figure_trader_ship_can_queue_for_export(ship) && building_dock_can_export_to_ship(dock, ship_id)) {
                exporting_dock_id = dock_id;
                break;
            }
        }
    }


    if (importing_dock_id) {
        return importing_dock_id;
    } else if (exporting_dock_id) {
        return exporting_dock_id;
    }

    if (ship->action_state == FIGURE_ACTION_110_TRADE_SHIP_CREATED) {
        return first_queue_available_dock ? first_queue_available_dock : second_queue_available_dock;
    }
    return 0;
}
