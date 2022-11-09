#include "random_generator/trng.h"
#include "print/print.h"

uint64_t rand(uint64_t min, uint64_t max) {
    uint64_t ctrl_value = in_word(RNG_CTRL);

    if (!(ctrl_value =& 1)) {           // initialize on first call
   //     RNG_STATUS = 0x40000;          // not sure why is this important, but linux does it this way
 //       RNG_INT_MASK |= 1;             // mask interrupt
        ctrl_value |= 1;                 // enable the generator

        out_word(RNG_CTRL, ctrl_value);

        while (!(in_word(RNG_STATUS) >> 24)){
            uint64_t status = in_word(RNG_STATUS);
            status = status >> 24;
            out_word(RNG_STATUS, status);
        } ; // wait until it's entropy good enough
    }
    return ((((uint64_t)in_word(RNG_DATA) << 32) | in_word(RNG_DATA)) % (max - min)) + min;
}

