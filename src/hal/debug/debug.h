#ifndef DEBUG_H
#define DEBUG_H

#include "print/print.h"

// chybovy vypis DEBUG_E(0)
#define DEBUG_E(e) do {                 \
    if (!(e))                           \
        error_check(__FILE__, __LINE__);\
} while (0)

// vypis bez parametru DEBUG_F(string)
#define DEBUG_F(e) do {     \
    print_debug(e);         \
} while (0)

// vypis s parametrem DEBUG_K(string, param)
#define DEBUG_K(string, params) do {    \
    printk_debug(string, params);       \
} while (0)

void error_check(char *file, uint64_t line);
void print_debug(char *string);
void printk_debug(char *string, int64_t params[]);

#endif
