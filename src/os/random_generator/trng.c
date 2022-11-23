#include "random_generator/trng.h"
#include "print/print.h"
#include "debug/debug.h"

/*
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
*/

void init_rand() {
    mmio_write(RNG_STATUS, 0x40000);
    uint64_t mask_value = mmio_read(RNG_INT_MASK);
    mask_value |= 1;
    mmio_write(RNG_INT_MASK, mask_value);
    uint64_t ctrl_value = mmio_read(RNG_CTRL);
    ctrl_value |= 1;
    mmio_write(RNG_CTRL, ctrl_value);
    DEBUG_F("RAND INIT OK");
}

uint64_t rand(uint64_t min, uint64_t max) {
    uint64_t status_value = mmio_read(RNG_STATUS);
    while(!(status_value >> 24)) ;
    return mmio_read(RNG_DATA) % (max-min) + min;
}