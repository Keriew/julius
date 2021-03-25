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
 */
int trade_price_buy(resource_type resource);

/**
 * Get the sell price for the resource
 * @param resource Resource
 */
int trade_price_sell(resource_type resource);

/**
 * Return the factor to apply when selling resource
 * @param factor default is 1
 * @return 1 if not factor to apply else other value
 */
double trade_factor_sell(double factor);

/**
 * Return the factor to apply when buying resource
 * @param factor default is 1
 * @return 1 if not factor to apply else other value
 */
double trade_factor_buy(double factor);

/**
 * Return the factor to apply depending caravanserai labor worker
 * Exemple
 * if laborworker is 100%, then applying 10% bonus
 * if laborworker is 50%, then applying 5% bonus
 * etc.
 * @return 1 if not factor to apply else other value
 */
double trade_sub_factor();

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
