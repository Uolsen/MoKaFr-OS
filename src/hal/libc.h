#ifndef _LIBC_H
#define _LIBC_H

#include "lib.h"

#define PERIPHERAL_BASE 0xFE000000

void mmio_write(uint64_t reg, uint32_t val);
uint64_t mmio_read(uint64_t reg);

void wait_ms(uint32_t ms);

#endif