#include "trade_prices.h"
#include "city/buildings.h"
#include "core/calc.h"
#include "building/model.h"

struct trade_price {
    int32_t buy;
    int32_t sell;
};

static const struct trade_price DEFAULT_PRICES[RESOURCE_MAX] = {
    {0, 0}, {28, 22}, {38, 30}, {38, 30}, // wheat, vegetables, fruit
    {42, 34}, {44, 36}, {44, 36}, {215, 160}, // olives, vines, meat, wine
    {180, 140}, {60, 40}, {50, 35}, {40, 30}, // oil, iron, timber, clay
    {200, 140}, {250, 180}, {200, 150}, {180, 140} // marble, weapons, furniture, pottery
};

static struct trade_price prices[RESOURCE_MAX];

void trade_prices_reset(void)
{
    for (int i = 0; i < RESOURCE_MAX; i++) {
        prices[i] = DEFAULT_PRICES[i];
    }
}

int trade_price_buy(resource_type resource)
{
    return (int)(prices[resource].buy * trade_factor_buy(1));
}

int trade_price_sell(resource_type resource)
{
    return (int)(prices[resource].sell * trade_factor_sell(1));
}

double trade_factor_sell(double factor)
{
    if(city_buildings_has_caravanserai()) {
        factor += trade_sub_factor();
    }
    return factor;
}

double trade_factor_buy(double factor)
{
    if(city_buildings_has_caravanserai()) {
        factor -= trade_sub_factor();
    }
    return factor;
}

double trade_sub_factor() {
    double sub_factor = 0;
    for (int i = 1; i < MAX_BUILDINGS ; i++) {
        building *b = building_get(i);
        if (b->type == BUILDING_CARAVANSERAI) {
            int pct_workers = calc_percentage(b->num_workers, model_get_building(b->type)->laborers);
            if (pct_workers >= 100) {
                sub_factor = 0.1;
            } else if (pct_workers >= 75) {
                sub_factor = 0.075;
            } else if (pct_workers >= 50) {
                sub_factor = 0.05;
            } else if (pct_workers >= 25) {
                sub_factor = 0.025;
            } else if (pct_workers > 0) {
                sub_factor = 0.01;
            }
        }
    }
    return sub_factor;
}

int trade_price_change(resource_type resource, int amount)
{
    if (amount < 0 && prices[resource].sell <= 0) {
        // cannot lower the price to negative
        return 0;
    }
    if (amount < 0 && prices[resource].sell <= -amount) {
        prices[resource].buy = 2;
        prices[resource].sell = 0;
    } else {
        prices[resource].buy += amount;
        prices[resource].sell += amount;
    }
    return 1;
}

void trade_prices_save_state(buffer *buf)
{
    for (int i = 0; i < RESOURCE_MAX; i++) {
        buffer_write_i32(buf, prices[i].buy);
        buffer_write_i32(buf, prices[i].sell);
    }
}

void trade_prices_load_state(buffer *buf)
{
    for (int i = 0; i < RESOURCE_MAX; i++) {
        prices[i].buy = buffer_read_i32(buf);
        prices[i].sell = buffer_read_i32(buf);
    }
}
