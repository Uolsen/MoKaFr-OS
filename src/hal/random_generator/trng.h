#ifndef _TRNG_H
#define _TRNG_H
#include "lib.h"

#define RANDOM_BASE_ADDR    0xFE104000

#define RNG_CTRL            (volatile uint32_t*) (RANDOM_BASE_ADDR + 0x00)
#define RNG_STATUS          (volatile uint32_t*) (RANDOM_BASE_ADDR + 0x04)
#define RNG_DATA            (volatile uint32_t*) (RANDOM_BASE_ADDR + 0x08)
#define RNG_FF_THRESHOLD    (volatile uint32_t*) (RANDOM_BASE_ADDR + 0x0c)
#define RNG_INT_MASK        (volatile uint32_t*) (RANDOM_BASE_ADDR + 0x10)

uint64_t rand(uint64_t min, uint64_t max);

#endif
