#include "libc.h"
#include "intdef.h"

void mmio_write(uint64_t reg, uint32_t val) {
    *(volatile uint32_t *) reg = val;
}

uint64_t mmio_read(uint64_t reg) {
    return *(volatile unsigned int *) reg;
}

void wait_ms(uint32_t ms) {
    register uint64_t f, t, r;

    // Get the current counter frequency
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));

    // Read the current counter
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));

    // Calculate expire value for counter
    t += ((f / 1000) * ms) / 1000;
    do {
        asm volatile ("mrs %0, cntpct_el0" : "=r"(r));
    } while (r < t);
}