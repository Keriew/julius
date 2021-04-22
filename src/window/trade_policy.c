#include "trade_policy.h"

#include "assets/assets.h"
#include "building/caravanserai.h"
#include "building/monument.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "sound/speech.h"
#include "translation/translation.h"
#include "window/action_popup.h"

const option_menu_item caravanserai_policy_options[3] = {
        {
                0, TR_BUILDING_CARAVANSERAI_POLICY_1_TITLE, TR_BUILDING_CARAVANSERAI_POLICY_1,
                0, "Areldir", "Econ_Logistics", "Trade Policy 1", 0
        },
        {
                0, TR_BUILDING_CARAVANSERAI_POLICY_2_TITLE, TR_BUILDING_CARAVANSERAI_POLICY_2,
                0, "Areldir", "Econ_Logistics", "Trade Policy 2", 0
        },
        {
                0, TR_BUILDING_CARAVANSERAI_POLICY_3_TITLE, TR_BUILDING_CARAVANSERAI_POLICY_3,
                0, "Areldir", "Econ_Logistics", "Trade Policy 3", 0
        }
};

void window_building_draw_caravanserai_action(building_info_context *c)
{

    int policy = building_monument_module_type(BUILDING_CARAVANSERAI);
    int policy_title = TR_BUILDING_CARAVANSERAI_NO_POLICY;

    if (policy) {
        policy_title = caravanserai_policy_options[policy - 1].header;
    }

    text_draw_multiline(translation_for(policy_title), c->x_offset + 160, c->y_offset + 160,
                        260, FONT_NORMAL_BLACK, 0);

    if (policy) {
        text_draw_multiline(translation_for(policy_title + 1), c->x_offset + 160, c->y_offset + 185,
                            260, FONT_NORMAL_BLACK, 0);

        int policy_image = assets_get_image_id(assets_get_group_id((char *) caravanserai_policy_options[policy - 1].asset_author, (char *) caravanserai_policy_options[policy - 1].asset_name),
                                               (char *) caravanserai_policy_options[policy - 1].asset_image_id);

        image_draw(policy_image, c->x_offset + 32, c->y_offset + 150);
    } else {
        int policy_image = assets_get_image_id(assets_get_group_id("Areldir", "Econ_Logistics"), "Trade Policy");
        image_draw(policy_image, c->x_offset + 32, c->y_offset + 150);
    }
}

static void caravanserai_policy(int selection)
{
    if (!selection) {
        return;
    }

    sound_speech_play_file("wavs/market4.wav");
    building *b = building_get(city_buildings_get_caravanserai());

    city_finance_process_construction(TRADE_POLICY_COST);
    building_monument_add_module(b, selection);
}

void window_policy_show()
{
    building *b = building_get(city_buildings_get_caravanserai());
    int current_policy = b->data.monument.upgrades;
    window_action_popup_show(TR_BUILDING_CARAVANSERAI_POLICY_TITLE, TR_BUILDING_CARAVANSERAI_POLICY_TEXT,
                             caravanserai_policy_options, caravanserai_policy, current_policy);
}
