#include "random_generator/trng.h"
#include "print/print.h"
#include "debug/debug.h"

/*uint64_t rand(uint64_t min, uint64_t max) {
    uint64_t ctrl_value = in_word(RNG_CTRL);

    ctrl_value = ctrl_value & 1;

    if (!(ctrl_value)) {           // initialize on first call
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
}*/

uint64_t rand(uint64_t min, uint64_t max) {
    uint64_t ctrl_value = mmio_read(RNG_CTRL);
   // if (ctrl_value & 1) {
        DEBUG_F("trng 1");
        mmio_write(RNG_STATUS, 0x40000);
        uint64_t mask_value = mmio_read(RNG_INT_MASK);
        mask_value |= 1;
        mmio_write(RNG_INT_MASK, mask_value);
        ctrl_value |= 1;
        out_word(RNG_CTRL, ctrl_value);
        DEBUG_F("trng 2");
//        while (!(mmio_read(RNG_STATUS) >> 24)) {
//            int64_t params0[] = {(uint64_t)mmio_read(RNG_STATUS)};
//            DEBUG_K("status: %u", params0);
//            uint64_t status = mmio_read(RNG_STATUS);
//            status = status >> 24;
//            mmio_write(RNG_STATUS, status);
        //}
  //  }
//    DEBUG_F("trng 3");
    //return ((((uint64_t)mmio_read(RNG_DATA) << 32) | mmio_read(RNG_DATA)) % (max - min)) + min;
    // vypisuje 0 :(
    return mmio_read(RNG_DATA);
}
