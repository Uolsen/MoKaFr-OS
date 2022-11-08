#ifndef _PRINT_H
#define _PRINT_H

#include "lib.h"

int printk(const char *format, int64_t data[]);
int print(const char *format);

#endif