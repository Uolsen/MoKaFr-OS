#ifndef _LIBC_H
#define _LIBC_H

void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);

#endif