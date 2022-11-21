#ifndef _LIBC_H
#define _LIBC_H

#include "lib.h"

#define PERIPHERAL_BASE 0xFE000000

void mmio_write(uint64_t reg, uint32_t val);
unsigned int mmio_read(uint64_t reg);

#endif