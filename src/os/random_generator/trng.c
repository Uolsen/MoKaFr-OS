#include "random_generator/trng.h"
#include "print/print.h"

uint64_t rand(uint64_t min, uint64_t max) {
    if (!((*RNG_CTRL) & 1)) {           // initialize on first call
        *RNG_STATUS = 0x40000;          // not sure why is this important, but linux does it this way
 //       *RNG_INT_MASK |= 1;             // mask interrupt
        *RNG_CTRL |= 1;                 // enable the generator
        while (!((*RNG_STATUS) >> 24)); // wait until it's entropy good enough
    }
    return ((((uint64_t)(*RNG_DATA) << 32) | *RNG_DATA) % (max - min)) + min;
}

