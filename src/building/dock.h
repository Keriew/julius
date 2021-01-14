#ifndef BUILDING_DOCK_H
#define BUILDING_DOCK_H

#include "building/building.h"
#include "map/point.h"

int building_dock_count_idle_dockers(const building *dock);

void building_dock_update_open_water_access(void);

int building_dock_is_connected_to_open_water(int x, int y);

int building_dock_get_free_destination(int ship_id, map_point *tile);

int building_dock_get_queue_destination(int ship_id, map_point *tile);

int building_dock_get_dock_accepting_ship(int ship_id);

int building_dock_get_can_trade_with_route(int route_id, int dock_id);

void building_dock_set_can_trade_with_route(int route_id, int dock_id, int can_trade);
#endif // BUILDING_DOCK_H
