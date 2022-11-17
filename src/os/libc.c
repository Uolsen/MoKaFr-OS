#include "libc.h"
#include "intdef.h"

void mmio_write(int64_t reg, uint32_t val) {
    *(volatile uint32_t *) reg = val;
}

uint32_t mmio_read(int64_t reg) {
    return *(volatile uint32_t *) reg;
}