#ifndef BUILDING_CARANVASERAI_H
#define BUILDING_CARANVASERAI_H

#include "building/building.h"

#define TRADE_POLICY_COST 500

typedef enum {
    NO_POLICY,
    TRADE_POLICY_1,
    TRADE_POLICY_2,
    TRADE_POLICY_3
} trade_policy;

int building_caravanserai_enough_foods(building *caravanserai);
int building_caravanserai_get_storage_destination(building *caravanserai);

#endif // BUILDING_CARANVASERAI_H