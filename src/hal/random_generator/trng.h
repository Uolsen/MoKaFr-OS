#ifndef _TRNG_H
#define _TRNG_H
#include "lib.h"

#define RANDOM_BASE_ADDR    0xFE104000UL

#define RNG_CTRL            RANDOM_BASE_ADDR + 0x00UL
#define RNG_STATUS          RANDOM_BASE_ADDR + 0x04UL
#define RNG_DATA            RANDOM_BASE_ADDR + 0x08UL
#define RNG_FF_THRESHOLD    RANDOM_BASE_ADDR + 0x0cUL
#define RNG_INT_MASK        RANDOM_BASE_ADDR + 0x10UL

uint64_t rand(uint64_t min, uint64_t max);

#endif
