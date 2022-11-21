#include "libc.h"

void mmio_write(uint64_t reg, uint32_t val){
    *(volatile uint32_t *) reg = val;
}

unsigned int mmio_read(uint64_t reg) {
    return *(volatile uint32_t *) reg;
}