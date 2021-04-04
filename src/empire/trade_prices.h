#ifndef EMPIRE_TRADE_PRICES_H
#define EMPIRE_TRADE_PRICES_H

#include "core/buffer.h"
#include "game/resource.h"

/**
 * @file
 * Trade prices.
 */

/**
 * Reset trade prices to the default
 */
void trade_prices_reset(void);

/**
 * Get the buy price for the resource
 * @param resource Resource
 * @param land_trader 1 if land_trader 0 else sea_trader
 */
int trade_price_buy(resource_type resource, int land_trader);

/**
 * Get the sell price for the resource
 * @param resource Resource
 * @param land_trader 1 if land_trader 0 else sea_trader
 */
int trade_price_sell(resource_type resource, int land_trader);

/**
 * Return the factor to apply when selling resource
 * @param factor default is 1
 * @param land_trader 1 if land_trader 0 else sea_trader
 * @return 1 if not factor to apply else other value
 */
double trade_factor_sell(double factor, int land_trader);

/**
 * Return the factor to apply when buying resource
 * @param factor default is 1
 * @param land_trader 1 if land_trader 0 else sea_trader
 * @return 1 if not factor to apply else other value
 */
double trade_factor_buy(double factor, int land_trader);

/**
 * Return the factor to apply depending caravanserai food stock vs food consumption
 * @return 0 if no factor to apply else 0.01 to 0.1 if caravanserai is active depending workers in it
 */
double trade_get_caravanserai_factor();

/**
 * Change the trade price for resource by amount
 * @param resource Resource to change
 * @param amount Amount to change, can be positive or negative
 * @return True if the price has been changed
 */
int trade_price_change(resource_type resource, int amount);

/**
 * Save trade prices to buffer
 * @param buf Buffer
 */
void trade_prices_save_state(buffer *buf);

/**
 * Load trade prices from buffer
 * @param buf Buffer
 */
void trade_prices_load_state(buffer *buf);

#endif // EMPIRE_TRADE_PRICES_H
