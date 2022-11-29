#ifndef _PRINT_H
#define _PRINT_H

#include "lib.h"

int printk(const char *format, int64_t data[]);
int printp(const char *format, int64_t param);
int print(const char *format);

#endif