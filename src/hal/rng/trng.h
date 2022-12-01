#ifndef _TRNG_H
#define _TRNG_H
#include "lib.h"

#define RANDOM_BASE_ADDR    0xfe104000UL

#define RNG_CTRL            ((volatile uint32_t*) (RANDOM_BASE_ADDR + 0x00UL))
#define RNG_STATUS          ((volatile uint32_t*) (RANDOM_BASE_ADDR + 0x04UL))
#define RNG_DATA            ((volatile uint32_t*) (RANDOM_BASE_ADDR + 0x08UL))
#define RNG_FF_THRESHOLD    ((volatile uint32_t*) (RANDOM_BASE_ADDR + 0x0cUL))
#define RNG_INT_MASK        ((volatile uint32_t*) (RANDOM_BASE_ADDR + 0x10UL))

void init_rand();
uint64_t rand(uint64_t min, uint64_t max);

#endif
