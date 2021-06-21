#include "depot.h"

#include "building/building.h"
#include "building/storage.h"
#include "building/warehouse.h"
#include "figure/figure.h"
#include "graphics/generic_button.h"
#include "graphics/image.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/scrollbar.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "translation/translation.h"
#include "window/building_info.h"

static void order_set_source(int index, int param2);
static void order_set_destination(int index, int param2);
static void order_set_resource(int index, int param2);
static void order_set_condition_type(int index, int param2);
static void order_set_condition_threshold(int index, int param2);
static void set_order_source(int depot_building_id, int building_id);
static void set_order_destination(int depot_building_id, int building_id);
static void set_order_resource(int depot_building_id, int resource_id);

static struct {
    int focus_button_id;
    int orders_focus_button_id;
    int resource_focus_button_id;
    int storage_building_focus_button_id;
    int depot_resource_focus_button_id;
} data;

static const translation_key TRANSLATION_KEY_ORDER_CONDITION[4] = {
    TR_ORDER_CONDITION_NEVER,
    TR_ORDER_CONDITION_ALWAYS,
    TR_ORDER_CONDITION_SOURCE_HAS_MORE_THAN,
    TR_ORDER_CONDITION_DESTINATION_HAS_LESS_THAN
};

#define DEPOT_BUTTONS_X_OFFSET 32
#define DEPOT_BUTTONS_Y_OFFSET 204
static generic_button depot_order_buttons[] = {
    {100, 0, 26, 26, order_set_resource, button_none, 1, 0},
    {100, 56, 284, 22, order_set_source, button_none, 2, 0},
    {100, 82, 284, 22, order_set_destination, button_none, 3, 0},
    {100, 30, 284, 22, order_set_condition_type, button_none, 4, 0},
    {384, 30, 32, 22, order_set_condition_threshold, button_none, 5, 0},
};

static int storage_buildings_count() {
    int count = 0;
    for (int i = 1; i < building_count(); i++) {
        building *b = building_get(i);
        if (b->type == BUILDING_GRANARY || b->type == BUILDING_WAREHOUSE) {
            count++;
        }
    }
    return count;
}

#define ROW_HEIGHT 22
#define MAX_VISIBLE_ROWS 15
static void on_scroll(void);
static scrollbar_type scrollbar = { 0, 0, ROW_HEIGHT * MAX_VISIBLE_ROWS, on_scroll, 4 };
void window_building_depot_init()
{
    int total = storage_buildings_count();
    scrollbar_init(&scrollbar, 0, total - MAX_VISIBLE_ROWS);
}

static void on_scroll(void)
{
    window_request_refresh();
}

void window_building_draw_depot(building_info_context *c)
{
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 4);
    text_draw_centered(translation_for(TR_BUILDING_DEPOT),
        c->x_offset, c->y_offset + 12, 16 * c->width_blocks, FONT_LARGE_BLACK, 0);
    text_draw_multiline(translation_for(TR_BUILDING_DEPOT_DESC),
        c->x_offset + 32, c->y_offset + 76, 16 * (c->width_blocks - 4), FONT_NORMAL_BLACK, 0);
    window_building_draw_employment(c, 138);
}

void window_building_draw_depot_foreground(building_info_context *c)
{
    building *b = building_get(c->building_id);
    building *src = building_get(b->data.depot.order1.src_storage_id);
    building *dst = building_get(b->data.depot.order1.dst_storage_id);

    if (!b->data.depot.order1.resource_type) {
        b->data.depot.order1.resource_type = RESOURCE_WHEAT;
    }

    int x_offset = c->x_offset + DEPOT_BUTTONS_X_OFFSET;
    int y_offset = c->y_offset + DEPOT_BUTTONS_Y_OFFSET;

    text_draw(translation_for(TR_FIGURE_INFO_DEPOT_DELIVER), x_offset, y_offset + 8, FONT_SMALL_PLAIN, 0);
    depot_order_buttons[0].x = 100;
    int image_id = image_group(GROUP_RESOURCE_ICONS) + b->data.depot.order1.resource_type +
        resource_image_offset(b->data.depot.order1.resource_type, RESOURCE_IMAGE_ICON);
    button_border_draw(x_offset + depot_order_buttons[0].x, y_offset + depot_order_buttons[0].y,
        depot_order_buttons[0].width, depot_order_buttons[0].height, data.focus_button_id == 1);
    image_draw(image_id, x_offset + depot_order_buttons[0].x + 2, y_offset + depot_order_buttons[0].y + 2);

    order_condition_type condition_type = b->data.depot.order1.condition.condition_type;
    text_draw(translation_for(TR_BUILDING_INFO_DEPOT_CONDITION), x_offset, y_offset + depot_order_buttons[3].y + 6, FONT_SMALL_PLAIN, 0);
    button_border_draw(x_offset + depot_order_buttons[3].x, y_offset + depot_order_buttons[3].y,
        depot_order_buttons[3].width, depot_order_buttons[3].height, data.focus_button_id == 4);
    text_draw_centered(translation_for(TRANSLATION_KEY_ORDER_CONDITION[condition_type]),
        x_offset + depot_order_buttons[3].x, y_offset + depot_order_buttons[3].y + 6, depot_order_buttons[3].width, FONT_SMALL_PLAIN, 0);
    if (condition_type != ORDER_CONDITION_ALWAYS && condition_type != ORDER_CONDITION_NEVER) {
        button_border_draw(x_offset + depot_order_buttons[4].x, y_offset + depot_order_buttons[4].y,
            depot_order_buttons[4].width, depot_order_buttons[4].height, data.focus_button_id == 5);
        text_draw_number_centered(b->data.depot.order1.condition.threshold,
            x_offset + depot_order_buttons[4].x, y_offset + depot_order_buttons[4].y + 6, depot_order_buttons[4].width, FONT_SMALL_PLAIN);
    }

    text_draw(translation_for(TR_BUILDING_INFO_DEPOT_SOURCE), x_offset, y_offset + depot_order_buttons[1].y + 6, FONT_SMALL_PLAIN, 0);
    button_border_draw(x_offset + depot_order_buttons[1].x, y_offset + depot_order_buttons[1].y,
        depot_order_buttons[1].width, depot_order_buttons[1].height, data.focus_button_id == 2);
    text_draw_label_and_number_centered(translation_for(building_translation_key(src)),
        src->id, "", x_offset + depot_order_buttons[1].x, y_offset + depot_order_buttons[1].y + 6,
        depot_order_buttons[1].width, FONT_SMALL_PLAIN, 0);

    text_draw(translation_for(TR_BUILDING_INFO_DEPOT_DESTINATION), x_offset, y_offset + depot_order_buttons[2].y + 6, FONT_SMALL_PLAIN, 0);
    button_border_draw(x_offset + depot_order_buttons[2].x, y_offset + depot_order_buttons[2].y,
        depot_order_buttons[2].width, depot_order_buttons[2].height, data.focus_button_id == 3);
    text_draw_label_and_number_centered(translation_for(building_translation_key(dst)),
        dst->id, "", x_offset + depot_order_buttons[2].x, y_offset + depot_order_buttons[2].y + 6,
        depot_order_buttons[2].width, FONT_SMALL_PLAIN, 0);
}

int window_building_handle_mouse_depot(const mouse *m, building_info_context *c)
{
    return generic_buttons_handle_mouse(m, c->x_offset + DEPOT_BUTTONS_X_OFFSET, c->y_offset + DEPOT_BUTTONS_Y_OFFSET,
        depot_order_buttons, 5, &data.focus_button_id);
}

static void order_set_source(int index, int param2)
{
    window_building_info_depot_select_source();
}

static void order_set_destination(int index, int param2)
{
    window_building_info_depot_select_destination();
}

static void order_set_condition_type(int index, int param2)
{
    window_building_info_depot_toggle_condition_type();
}

static void order_set_condition_threshold(int index, int param2)
{
    window_building_info_depot_toggle_condition_threshold();
}

void draw_order_source_destination_background(building_info_context *c, uint8_t *title)
{
    int y_offset = window_building_get_vertical_offset(c, 28);
    c->help_id = 0;
    outer_panel_draw(c->x_offset, y_offset, 29, 28);
    text_draw_centered(title, c->x_offset, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK, 0);
    inner_panel_draw(c->x_offset + 16, y_offset + 42, c->width_blocks - 2, 21);
}

void window_building_draw_depot_select_source(building_info_context *c)
{
    draw_order_source_destination_background(c, translation_for(TR_BUILDING_INFO_DEPOT_SELECT_SOURCE_TITLE));
}

// field values will be overwritten in draw_depot_select_source_destination
static generic_button depot_select_storage_buttons[] = {
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
    {0, 0, 0, ROW_HEIGHT, button_none, button_none, 0, 0},
};

void draw_depot_select_source_destination(building_info_context *c) {
    int y_offset = window_building_get_vertical_offset(c, 28);

    scrollbar.x = c->x_offset + 16 * (c->width_blocks - 2) - 26;
    scrollbar.y = y_offset + 46;
    scrollbar_draw(&scrollbar);

    int index = 0, offset = scrollbar.scroll_position;
    for (int i = 1; i < building_count(); i++) {
        building *b = building_get(i);
        if (b->type == BUILDING_GRANARY || b->type == BUILDING_WAREHOUSE) {
            if (index == MAX_VISIBLE_ROWS) {
                break;
            }
            if (offset > 0) {
                offset--;
            }
            else {
                button_border_draw(c->x_offset + 18, y_offset + 46 + ROW_HEIGHT * index,
                    16 * (c->width_blocks - 2) - 4 - (scrollbar.max_scroll_position > 0 ? 39 : 0),
                    22, data.storage_building_focus_button_id == index + 1);
                text_draw_label_and_number_centered(translation_for(building_translation_key(b)),
                    b->id, "", c->x_offset + 32, y_offset + 52 + ROW_HEIGHT * index,
                    16 * (c->width_blocks - 2) - 4 - (scrollbar.max_scroll_position > 0 ? 39 : 0),
                    FONT_SMALL_PLAIN, 0);
                index++;
            }
        }
    }
}

void window_building_draw_depot_select_source_foreground(building_info_context *c)
{
    draw_depot_select_source_destination(c);
}

int handle_mouse_depot_select_source_destination(const mouse *m, building_info_context *c, int is_source)
{
    if (scrollbar_handle_mouse(&scrollbar, m)) {
        return 1;
    }

    int y_offset = window_building_get_vertical_offset(c, 28);
    int index = 0, offset = scrollbar.scroll_position;
    for (int i = 0; i < MAX_VISIBLE_ROWS; i++) {
        depot_select_storage_buttons[i].x = 0;
        depot_select_storage_buttons[i].y = 22 * i;
        depot_select_storage_buttons[i].width = 16 * (c->width_blocks - 2) - 4 -
            (scrollbar.max_scroll_position > 0 ? 39 : 0);
        depot_select_storage_buttons[i].height = ROW_HEIGHT;
        depot_select_storage_buttons[i].left_click_handler = button_none;
        depot_select_storage_buttons[i].parameter1 = 0;
        depot_select_storage_buttons[i].parameter2 = 0;
    }
    for (int i = 1; i < building_count(); i++) {
        building *b = building_get(i);
        if (b->type == BUILDING_GRANARY || b->type == BUILDING_WAREHOUSE) {
            if (index == MAX_VISIBLE_ROWS) {
                break;
            }
            if (offset > 0) {
                offset--;
            }
            else {
                depot_select_storage_buttons[index].left_click_handler = is_source ? set_order_source : set_order_destination;
                depot_select_storage_buttons[index].parameter1 = c->building_id;
                depot_select_storage_buttons[index].parameter2 = i;
                index++;
            }
        }
    }

    return generic_buttons_handle_mouse(m, c->x_offset + 18, y_offset + 46, depot_select_storage_buttons,
        MAX_VISIBLE_ROWS, &data.storage_building_focus_button_id);
}

int window_building_handle_mouse_depot_select_source(const mouse *m, building_info_context *c)
{
    return handle_mouse_depot_select_source_destination(m, c, 1);
}

static void set_order_source(int depot_building_id, int building_id)
{
    building *b = building_get(depot_building_id);
    b->data.depot.order1.src_storage_id = building_id;
    window_building_info_depot_return_to_main_window();
}

static void set_order_destination(int depot_building_id, int building_id)
{
    building *b = building_get(depot_building_id);
    b->data.depot.order1.dst_storage_id = building_id;
    window_building_info_depot_return_to_main_window();
}

void window_building_draw_depot_select_destination(building_info_context *c)
{
    draw_order_source_destination_background(c, translation_for(TR_BUILDING_INFO_DEPOT_SELECT_DESTINATION_TITLE));
}

void window_building_draw_depot_select_destination_foreground(building_info_context *c)
{
    draw_depot_select_source_destination(c);
}

int window_building_handle_mouse_depot_select_destination(const mouse *m, building_info_context *c)
{
    return handle_mouse_depot_select_source_destination(m, c, 0);
}

static void order_set_resource(int index, int param2)
{
    window_building_info_depot_select_resource();
}

static generic_button depot_select_resource_buttons[] = {
    {18, 0, 214, 26, set_order_resource, button_none, 0, 1},
    {232, 0, 214, 26, set_order_resource, button_none, 0, 2},
    {18, 26, 214, 26, set_order_resource, button_none, 0, 3},
    {232, 26, 214, 26, set_order_resource, button_none, 0, 4},
    {18, 52, 214, 26, set_order_resource, button_none, 0, 5},
    {232, 52, 214, 26, set_order_resource, button_none, 0, 6},
    {18, 78, 214, 26, set_order_resource, button_none, 0, 7},
    {232, 78, 214, 26, set_order_resource, button_none, 0, 8},
    {18, 104, 214, 26, set_order_resource, button_none, 0, 9},
    {232, 104, 214, 26, set_order_resource, button_none, 0, 10},
    {18, 130, 214, 26, set_order_resource, button_none, 0, 11},
    {232, 130, 214, 26, set_order_resource, button_none, 0, 12},
    {18, 156, 214, 26, set_order_resource, button_none, 0, 13},
    {232, 156, 214, 26, set_order_resource, button_none, 0, 14},
    {18, 182, 214, 26, set_order_resource, button_none, 0, 15},
};

void window_building_draw_depot_select_resource(building_info_context *c)
{
    int y_offset = window_building_get_vertical_offset(c, 28);
    c->help_id = 0;
    outer_panel_draw(c->x_offset, y_offset, 29, 28);
    text_draw_centered(translation_for(TR_BUILDING_INFO_DEPOT_SELECT_RESOURCE_TITLE),
        c->x_offset, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK, 0);
    inner_panel_draw(c->x_offset + 16, y_offset + 42, c->width_blocks - 2, 21);
}

void window_building_draw_depot_select_resource_foreground(building_info_context *c)
{
    int y_offset = window_building_get_vertical_offset(c, 28);
    for (int i = RESOURCE_MIN; i < RESOURCE_MAX; i++) {
        int index = i - RESOURCE_MIN;

        int image_id = image_group(GROUP_RESOURCE_ICONS) + i + resource_image_offset(i, RESOURCE_IMAGE_ICON);
        button_border_draw(c->x_offset + depot_select_resource_buttons[index].x,
            y_offset + 46 + depot_select_resource_buttons[index].y,
            214, 26, data.depot_resource_focus_button_id == index + 1);
        image_draw(image_id, c->x_offset + depot_select_resource_buttons[index].x + 3,
            y_offset + 46 + depot_select_resource_buttons[index].y + 3);
        lang_text_draw(23, i, c->x_offset + depot_select_resource_buttons[index].x + 33,
            y_offset + 46 + depot_select_resource_buttons[index].y + 10, FONT_SMALL_PLAIN);
    }
}

int window_building_handle_mouse_depot_select_resource(const mouse *m, building_info_context *c)
{
    for (int i = 0; i < sizeof(depot_select_resource_buttons) / sizeof(generic_button); i++) {
        depot_select_resource_buttons[i].parameter1 = c->building_id;
    }
    return generic_buttons_handle_mouse(m, c->x_offset, c->y_offset, depot_select_resource_buttons,
        15, &data.depot_resource_focus_button_id);
}

static void set_order_resource(int depot_building_id, int resource_id)
{
    building *b = building_get(depot_building_id);
    b->data.depot.order1.resource_type = resource_id;
    window_building_info_depot_return_to_main_window();
}
