#include "depot.h"

#include "building/granary.h"
#include "building/industry.h"
#include "building/storage.h"
#include "building/warehouse.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/config.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "map/road_access.h"
#include "map/road_network.h"
#include "map/routing.h"
#include "map/routing_terrain.h"
#include "figure/image.h"

#define FIGURE_REROUTE_DESTINATION_TICKS 120

static const int CART_OFFSET_MULTIPLE_LOADS_FOOD[] = { 0, 0, 8, 16, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static const int CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[] = { 0, 0, 0, 0, 0, 8, 0, 16, 24, 32, 40, 48, 56, 64, 72, 80 };
static const int CART_OFFSET_8_LOADS_FOOD[] = { 0, 40, 48, 56, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static int cartpusher_speed();
static void update_image(figure *f);
static void set_cart_graphic(figure *f);
static int get_storage_road_access(building *b, map_point *point);
static void dump_goods(figure *f);
static int is_order_condition_satisfied(building *depot, order *order);
static int storage_remove_resource(building *b, int resource, int amount);
static int storage_add_resource(building *b, int resource, int amount);

void figure_depot_cartpusher_action(figure *f)
{
    figure_image_increase_offset(f, 12);
    f->cart_image_id = 0;
    int speed_factor = cartpusher_speed();
    int percentage_speed = 0;
    int road_network_id = map_road_network_get(f->grid_offset);
    f->terrain_usage = TERRAIN_USAGE_ROADS;
    building *b = building_get(f->building_id);

    switch (f->action_state) {
    case FIGURE_ACTION_150_ATTACK:
        figure_combat_handle_attack(f);
        break;
    case FIGURE_ACTION_149_CORPSE:
        figure_combat_handle_corpse(f);
        break;
    case FIGURE_ACTION_231_DEPOT_CART_PUSHER_INITIAL:
        set_cart_graphic(f);
        if (!map_routing_citizen_is_passable(f->grid_offset)) {
            f->state = FIGURE_STATE_DEAD;
        }
        if (b->state != BUILDING_STATE_IN_USE || b->figure_id != f->id) {
            f->state = FIGURE_STATE_DEAD;
        }

        f->current_order = b->data.depot.order1;
        if (is_order_condition_satisfied(b, &f->current_order)) {
            building *src = building_get(f->current_order.src_storage_id);
            map_point road_access;
            get_storage_road_access(src, &road_access);
            f->action_state = FIGURE_ACTION_232_DEPOT_CART_PUSHER_HEADING_TO_SOURCE;
            f->destination_building_id = f->current_order.src_storage_id;
            f->destination_x = road_access.x;
            f->destination_y = road_access.y;
        } else {
            f->state = FIGURE_STATE_DEAD;
        }

        f->image_offset = 0;
        break;
    case FIGURE_ACTION_232_DEPOT_CART_PUSHER_HEADING_TO_SOURCE:
        set_cart_graphic(f);
        figure_movement_move_ticks_with_percentage(f, speed_factor, percentage_speed);
        if (f->direction == DIR_FIGURE_AT_DESTINATION) {
            f->action_state = FIGURE_ACTION_233_DEPOT_CART_PUSHER_AT_SOURCE;
            f->wait_ticks = 0;
        } else if (f->direction == DIR_FIGURE_LOST) {
            f->action_state = FIGURE_ACTION_237_DEPOT_CART_PUSHER_CANCEL_ORDER;
            f->wait_ticks = 0;
        } else if (f->direction == DIR_FIGURE_REROUTE) {
            figure_route_remove(f);
            f->wait_ticks = 0;
        }
        break;
    case FIGURE_ACTION_233_DEPOT_CART_PUSHER_AT_SOURCE:
        set_cart_graphic(f);
        f->wait_ticks++;
        if (f->wait_ticks > 10) {
            building *src = building_get(f->current_order.src_storage_id);

            // TODO upgradable?
            int capacity = resource_is_food(f->current_order.resource_type) ? 8 : 4;
            int remaining_capacity = storage_remove_resource(src, f->current_order.resource_type, capacity);
            if (remaining_capacity == capacity) {
                // no available goods, wait at the building
            } else {
                f->resource_id = f->current_order.resource_type;
                f->loads_sold_or_carrying = capacity - remaining_capacity;

                building *dst = building_get(f->current_order.dst_storage_id);
                map_point road_access;
                get_storage_road_access(dst, &road_access);
                f->action_state = FIGURE_ACTION_234_DEPOT_CART_HEADING_TO_DESTINATION;
                f->destination_building_id = f->current_order.dst_storage_id;
                f->destination_x = road_access.x;
                f->destination_y = road_access.y;
                figure_route_remove(f);
            }
        }
        f->image_offset = 0;
        break;
    case FIGURE_ACTION_234_DEPOT_CART_HEADING_TO_DESTINATION:
        set_cart_graphic(f);
        figure_movement_move_ticks_with_percentage(f, speed_factor, percentage_speed);
        if (f->direction == DIR_FIGURE_AT_DESTINATION) {
            f->action_state = FIGURE_ACTION_235_DEPOT_CART_PUSHER_AT_DESTINATION;
            f->wait_ticks = 0;
        } else if (f->direction == DIR_FIGURE_LOST) {
            f->action_state = FIGURE_ACTION_237_DEPOT_CART_PUSHER_CANCEL_ORDER;
            f->wait_ticks = 0;
        } else if (f->direction == DIR_FIGURE_REROUTE) {
            figure_route_remove(f);
            f->wait_ticks = 0;
        }
        break;
    case FIGURE_ACTION_235_DEPOT_CART_PUSHER_AT_DESTINATION:
        set_cart_graphic(f);
        f->wait_ticks++;
        if (f->wait_ticks > 10) {
            building *dst = building_get(f->current_order.dst_storage_id);

            f->loads_sold_or_carrying = storage_add_resource(dst, f->resource_id, f->loads_sold_or_carrying);
            if (f->loads_sold_or_carrying) {
                // loads remaining
                set_cart_graphic(f);
            } else {
                f->action_state = FIGURE_ACTION_236_DEPOT_CART_PUSHER_RETURNING;
                f->loads_sold_or_carrying = 0;
                f->resource_id = RESOURCE_NONE;
                f->destination_building_id = f->building_id;
                f->destination_x = b->road_access_x;
                f->destination_y = b->road_access_y;
                figure_route_remove(f);
            }
            f->wait_ticks = 0;
        }
        break;
    case FIGURE_ACTION_236_DEPOT_CART_PUSHER_RETURNING:
        set_cart_graphic(f);
        figure_movement_move_ticks_with_percentage(f, speed_factor, percentage_speed);
        if (f->direction == DIR_FIGURE_AT_DESTINATION) {
            f->action_state = FIGURE_ACTION_231_DEPOT_CART_PUSHER_INITIAL;
            f->state = FIGURE_STATE_DEAD;
        } else if (f->direction == DIR_FIGURE_LOST) {
            f->state = FIGURE_STATE_DEAD;
        }
        break;
    case FIGURE_ACTION_237_DEPOT_CART_PUSHER_CANCEL_ORDER:
        dump_goods(f);
        f->action_state = FIGURE_ACTION_236_DEPOT_CART_PUSHER_RETURNING;
        f->destination_building_id = f->building_id;
        f->destination_x = b->road_access_x;
        f->destination_y = b->road_access_y;
        figure_route_remove(f);
        break;
    }

    if (b->state != BUILDING_STATE_IN_USE) {
        f->state = FIGURE_STATE_DEAD;
    }

    update_image(f);
}

static void set_cart_graphic(figure *f)
{
    if (f->loads_sold_or_carrying == 0) {
        f->cart_image_id = image_group(GROUP_FIGURE_CARTPUSHER_CART);
    } else if (f->loads_sold_or_carrying == 1) {
        f->cart_image_id = image_group(GROUP_FIGURE_CARTPUSHER_CART) +
            8 * f->resource_id + resource_image_offset(f->resource_id, RESOURCE_IMAGE_CART);
    } else if (f->loads_sold_or_carrying < 8) {
        if (resource_is_food(f->resource_id)) {
            f->cart_image_id = image_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_MULTIPLE_LOADS_FOOD[f->resource_id];
            f->cart_image_id += resource_image_offset(f->resource_id, RESOURCE_IMAGE_FOOD_CART);
        } else {
            f->cart_image_id = image_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_RESOURCE) + CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[f->resource_id];
            f->cart_image_id += resource_image_offset(f->resource_id, RESOURCE_IMAGE_CART);
        }
    } else {
        f->cart_image_id = image_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) +
            CART_OFFSET_8_LOADS_FOOD[f->resource_id];
        f->cart_image_id += resource_image_offset(f->resource_id, RESOURCE_IMAGE_FOOD_CART);
    }
}

static int cartpusher_speed()
{
    return 1;
}

static void update_image(figure *f)
{
    int dir = figure_image_normalize_direction(
        f->direction < 8 ? f->direction : f->previous_tile_direction);

    if (f->action_state == FIGURE_ACTION_149_CORPSE) {
        f->image_id = image_group(GROUP_FIGURE_MIGRANT) + figure_image_corpse_offset(f) + 96;
        f->cart_image_id = 0;
    }
    else {
        f->image_id = image_group(GROUP_FIGURE_MIGRANT) + dir + 8 * f->image_offset;
    }
    if (f->cart_image_id) {
        f->cart_image_id += dir;
        figure_image_set_cart_offset(f, dir);
        if (f->loads_sold_or_carrying >= 8) {
            f->y_offset_cart -= 40;
        }
    }
}

static int is_order_condition_satisfied(building *depot, order *order)
{
    if (!order->src_storage_id || !order->dst_storage_id || !order->resource_type) {
        return 0;
    }

    if (order->condition.condition_type == ORDER_CONDITION_NEVER) {
        return 0;
    }

    building *src = building_get(order->src_storage_id);
    building *dst = building_get(order->dst_storage_id);
    if (!src || !dst) {
        return 0;
    }

    if (src->state != BUILDING_STATE_IN_USE || dst->state != BUILDING_STATE_IN_USE) {
        return 0;
    }

    if (src->type != BUILDING_GRANARY && src->type != BUILDING_WAREHOUSE) {
        return 0;
    }
    if (dst->type != BUILDING_GRANARY && dst->type != BUILDING_WAREHOUSE) {
        return 0;
    }

    // fail if no path
    // if we decide to use a different terrain type for the cart, this needs to be updated as well
    map_point src_access_point;
    map_point dst_access_point;
    get_storage_road_access(src, &src_access_point);
    get_storage_road_access(dst, &dst_access_point);
    if (!map_routing_citizen_can_travel_over_road_garden(depot->road_access_x, depot->road_access_y, src_access_point.x, src_access_point.y) ||
        !map_routing_citizen_can_travel_over_road_garden(src_access_point.x, src_access_point.y, dst_access_point.x, dst_access_point.y)) {
        return 0;
    }

    int src_amount = src->type == BUILDING_GRANARY ?
        building_granary_resource_amount(order->resource_type, src) / RESOURCE_GRANARY_ONE_LOAD :
        building_warehouse_get_amount(src, order->resource_type);
    int dst_amount = dst->type == BUILDING_GRANARY ?
        building_granary_resource_amount(order->resource_type, dst) / RESOURCE_GRANARY_ONE_LOAD :
        building_warehouse_get_amount(dst, order->resource_type);
    if (src_amount == 0) {
        return 0;
    }

    switch (order->condition.condition_type) {
    case ORDER_CONDITION_SOURCE_HAS_MORE_THAN:
        return src_amount >= order->condition.threshold;
    case ORDER_CONDITION_DESTINATION_HAS_LESS_THAN:
        return dst_amount < order->condition.threshold;
    default:
        return 1;
    }
}

static int get_storage_road_access(building *b, map_point *point)
{
    if (b->type == BUILDING_GRANARY) {
        map_point_store_result(b->x + 1, b->y + 1, point);
        return 1;
    } else if (b->type == BUILDING_WAREHOUSE) {
        if (b->has_road_access == 1) {
            map_point_store_result(b->x, b->y, point);
            return 1;
        }
        else if (!map_has_road_access_rotation(b->subtype.orientation, b->x, b->y, 3, point)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        point->x = b->road_access_x;
        point->y = b->road_access_y;
        return b->has_road_access;
    }
}

static void dump_goods(figure *f)
{
    if (f->loads_sold_or_carrying > 0) {
        // TODO maybe add a dump goods animation?
        f->loads_sold_or_carrying = 0;
        f->resource_id = RESOURCE_NONE;
        set_cart_graphic(f);
    }
}

static int storage_remove_resource(building *b, int resource, int amount)
{
    if (b->type == BUILDING_GRANARY) {
        return building_granary_remove_resource(b, resource, amount * 100) / 100;
    } else if (b->type == BUILDING_WAREHOUSE) {
        return building_warehouse_remove_resource(b, resource, amount);
    } else {
        return amount;
    }
}

static int storage_add_resource(building *b, int resource, int amount)
{
    if (b->type == BUILDING_GRANARY) {
        while (amount > 0) {
            if (!building_granary_add_resource(b, resource, 0)) {
                return amount;
            }
            amount--;
        }
    } else if (b->type == BUILDING_WAREHOUSE) {
        while (amount > 0) {
            if (!building_warehouse_add_resource(b, resource)) {
                return amount;
            }
            amount--;
        }
    }
    return amount;
}

void figure_depot_recall(figure *f)
{
    f->action_state = FIGURE_ACTION_237_DEPOT_CART_PUSHER_CANCEL_ORDER;
}
