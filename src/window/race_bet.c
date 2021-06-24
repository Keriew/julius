
#include "assets/assets.h"
#include "city/data_private.h"
#include "city/race_bet.h"
#include "core/calc.h"
#include "graphics/arrow_button.h"
#include "graphics/generic_button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "race_bet.h"
#include "translation/translation.h"


static void arrow_button_bet(int is_down, int param2);
static void button_horse_selection(int option, int param2);

static generic_button buttons[] = {
        {34, 145, 81, 91, button_horse_selection, button_none, BLUE_HORSE, 0},
        {144, 145, 81, 91, button_horse_selection, button_none, RED_HORSE, 0},
        {254, 145, 81, 91, button_horse_selection, button_none, WHITE_HORSE, 0},
        {364, 145, 81, 91, button_horse_selection, button_none, GREEN_HORSE, 0}
};

static arrow_button bet_buttons[] = {
        {106, 269, 17, 24, arrow_button_bet, 1, 0},
        {130, 269, 15, 24, arrow_button_bet, 0, 0}
};

static struct {
    int bet_value;
    int bet_amount;
    int focus_button_id;
    int focus_button_id2;
    int width_blocks;
    int height_blocks;
} data;

static int init()
{
    if (window_is(WINDOW_RACE_BET)) {
        // don't show popup over popup
        return 0;
    }
    data.bet_value = city_data.games.bet_value ? city_data.games.bet_value : NO_BET;
    data.bet_amount = city_data.games.bet_amount ? city_data.games.bet_amount: 0;
    data.width_blocks = 30;
    data.height_blocks = 20;

    return 1;
}


static void draw_background(void)
{
    window_draw_underlying_window();

    graphics_in_dialog_with_size(16 * data.width_blocks, 16 * data.height_blocks);

    outer_panel_draw(0, 0, data.width_blocks, data.height_blocks);

    image_draw(image_group(GROUP_RESOURCE_ICONS) + RESOURCE_DENARII, 20, 20);

    text_draw_centered(translation_for(TR_WINDOW_RACE_BET_TITLE), 0, 20, 16 * data.width_blocks, FONT_LARGE_BLACK, 0);

    text_draw_multiline(translation_for(TR_WINDOW_RACE_BET_DESCRIPTION), 25, 65, 438, FONT_NORMAL_BLACK, 0);

    inner_panel_draw(18, 265, 28, 2);
    text_draw_centered(translation_for(TR_WINDOW_RACE_BET_AMOUNT), 18, 275, 80, FONT_NORMAL_WHITE, 0);
    int width = text_draw_number(data.bet_amount, '@', " ", 165, 275, FONT_NORMAL_WHITE);
    width += lang_text_draw(50, 15, 165 + width, 275, FONT_NORMAL_WHITE);
    text_draw_with_money(translation_for(TR_PERSONAL_SAVINGS), city_emperor_personal_savings(), " ", "", 284, 275, 175,  FONT_NORMAL_WHITE, 0);

    graphics_reset_dialog();
}

static void draw_foreground(void)
{
    graphics_in_dialog_with_size(16 * data.width_blocks, 16 * data.height_blocks);

    int image_id = assets_get_image_id("UI_Elements", "Hipp_Blues_UH");
    int image_id_focus = assets_get_image_id("UI_Elements", "Hipp_Blues_H");

    for (int i = 0; i < 4; i++) {
        int slice_id = (2 * i);
        int id = data.focus_button_id == (i+1) || data.bet_value == (i+1) ? image_id_focus : image_id;
        image_draw(id + slice_id, 34 + i * 110, 145);
    }

    arrow_buttons_draw(0, 0, bet_buttons, 2);
    graphics_reset_dialog();
    window_request_refresh();
}

static void handle_input(const mouse *m, const hotkeys *h)
{
    const mouse *m_dialog = mouse_in_dialog_with_size(m, data.width_blocks * 16, data.height_blocks * 16);
    if (input_go_back_requested(m, h)) {
        city_data.games.bet_value = data.bet_value;
        if (city_data.games.bet_value) {
            city_data.games.bet_amount = data.bet_amount;
        }
        window_go_back();
    }

    if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons, 4, &data.focus_button_id) ||
        arrow_buttons_handle_mouse(m_dialog, 0, 0, bet_buttons, 2, &data.focus_button_id2)) {
        return;
    }
}

static void arrow_button_bet(int is_down, int param2)
{
    int amount = data.bet_amount;
    amount += is_down ? -10 : 10;
    data.bet_amount = calc_bound(amount, 0, city_data.emperor.personal_savings);

    window_request_refresh();
}

static void button_horse_selection(int option, int param2)
{
    data.bet_value = option;
}

void window_race_bet_show()
{
    if (init()) {
        window_type window = {
                WINDOW_RACE_BET,
                draw_background,
                draw_foreground,
                handle_input
        };
        window_show(&window);
    }
}
