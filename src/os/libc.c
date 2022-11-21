#include "libc.h"
#include "intdef.h"

void mmio_write(uint64_t reg, uint32_t val){
    *(volatile uint32_t *) reg = val;
}

uint64_t mmio_read(uint64_t reg) {
    return *(volatile unsigned int *) reg;
}