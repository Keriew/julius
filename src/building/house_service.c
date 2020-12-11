#include "house_service.h"

#include "building/building.h"
#include "building/monument.h"
#include "city/culture.h"
#include "core/calc.h"

static void decay(unsigned char *value)
{
    if (*value > 0) {
        *value = *value - 2;
    } else {
        *value = 0;
    }
}

void house_service_decay_culture(void)
{
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_IN_USE || !b->house_size) {
            continue;
        }
        decay(&b->data.house.theater);
        decay(&b->data.house.amphitheater_actor);
        decay(&b->data.house.amphitheater_gladiator);
        decay(&b->data.house.colosseum_gladiator);
        decay(&b->data.house.colosseum_lion);
        decay(&b->data.house.hippodrome);
        decay(&b->data.house.school);
        decay(&b->data.house.library);
        decay(&b->data.house.academy);
        decay(&b->data.house.barber);
        decay(&b->data.house.clinic);
        decay(&b->data.house.bathhouse);
        decay(&b->data.house.hospital);
        decay(&b->data.house.temple_ceres);
        decay(&b->data.house.temple_neptune);
        decay(&b->data.house.temple_mercury);
        decay(&b->data.house.temple_mars);
        decay(&b->data.house.temple_venus);
        decay(&b->house_pantheon_access);
        if (b->days_since_offering < 125) {
            ++b->days_since_offering;
        }
    }
}

void house_service_decay_tax_collector(void)
{
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_IN_USE && b->house_tax_coverage) {
            b->house_tax_coverage--;
        }
    }
}

void house_service_decay_houses_covered(void)
{
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_UNUSED && b->type != BUILDING_TOWER) {
            if (b->houses_covered <= 1) {
                b->houses_covered = 0;
            } else {
                b->houses_covered--;
            }
        }
    }
}

void house_service_calculate_culture_aggregates(void)
{
    int base_entertainment = city_culture_coverage_average_entertainment() / 5;
    int venus_module2 = building_monument_gt_module_is_active(VENUS_MODULE_2_DESIRABILITY_ENTERTAINMENT);
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_IN_USE || !b->house_size) {
            continue;
        }

        // entertainment
        b->data.house.entertainment = base_entertainment;
        if (b->data.house.theater) {
            b->data.house.entertainment += 10;
        }
        if (b->data.house.amphitheater_actor) {
            if (b->data.house.amphitheater_gladiator) {
                b->data.house.entertainment += 15;
            } else {
                b->data.house.entertainment += 10;
            }
        }
        if (b->data.house.colosseum_gladiator) {
            if (b->data.house.colosseum_lion) {
                b->data.house.entertainment += 25;
            } else {
                b->data.house.entertainment += 15;
            }
        }
        if (b->data.house.hippodrome) {
            b->data.house.entertainment += 30;
        }

        // Venus Module 2 Entertainment Bonus
        if (venus_module2 && b->data.house.temple_venus) {
            b->data.house.entertainment += 10;
        }

        // education
        b->data.house.education = 0;
        if (b->data.house.school || b->data.house.library) {
            b->data.house.education = 1;
            if (b->data.house.school && b->data.house.library) {
                b->data.house.education = 2;
                if (b->data.house.academy) {
                    b->data.house.education = 3;
                }
            }
        }
        
        if (b->house_population > 0) {
			if (b->data.house.theater) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.theater_accessibility = 100;
				} else {
					b->data.house.theater_accessibility = calc_bound( (b->data.house.theater / b->house_population) * 100, 0, 100);
				}
			}
			if (b->data.house.amphitheater_actor) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.amphitheater_accessibility = 100;
				} else {
					b->data.house.amphitheater_accessibility = calc_bound( (b->data.house.amphitheater_actor / b->house_population) * 100, 0, 100);
				}
			}
			if (b->data.house.colosseum_gladiator) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.colosseum_accessibility = 100;
				} else {
					b->data.house.colosseum_accessibility = calc_bound( (b->data.house.colosseum_gladiator / b->house_population) * 100, 0, 100);
				}
			}
			if (b->data.house.hippodrome) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.hippodrome_accessibility = 100;
				} else {
					b->data.house.hippodrome_accessibility = calc_bound( (b->data.house.hippodrome / b->house_population) * 100, 0, 100);
				}
			}
            if (b->data.house.school) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.school_accessibility = 100;
				} else {
					b->data.house.school_accessibility = calc_bound( (b->data.house.school / b->house_population) * 100, 0, 100);
				}
			}
            if (b->data.house.library) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.library_accessibility = 100;
				} else {
					b->data.house.library_accessibility = calc_bound( (b->data.house.library / b->house_population) * 100, 0, 100);
				}
			}
            if (b->data.house.academy) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.academy_accessibility = 100;
				} else {
					b->data.house.academy_accessibility = calc_bound( (b->data.house.academy / b->house_population) * 100, 0, 100);
				}
			}
            if (b->data.house.hospital) {
				if (b->subtype.house_level >= HOUSE_SMALL_PALACE) {
					b->data.house.hospital_accessibility = 100;
				} else {
					b->data.house.hospital_accessibility = calc_bound( (b->data.house.hospital / b->house_population) * 100, 0, 100);
				}
			}
		}

        // religion
        b->data.house.num_gods = 0;
        if (b->data.house.temple_ceres) {
            ++b->data.house.num_gods;
        }
        if (b->data.house.temple_neptune) {
            ++b->data.house.num_gods;
        }
        if (b->data.house.temple_mercury) {
            ++b->data.house.num_gods;
        }
        if (b->data.house.temple_mars) {
            ++b->data.house.num_gods;
        }
        if (b->data.house.temple_venus) {
            ++b->data.house.num_gods;
        }

        // health
        b->data.house.health = 0;
        if (b->data.house.clinic) {
            ++b->data.house.health;
        }
        if (b->data.house.hospital) {
            ++b->data.house.health;
        }
    }
}
