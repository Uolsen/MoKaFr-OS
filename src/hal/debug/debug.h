#ifndef DEBUG_H
#define DEBUG_H

#include "print/print.h"

#define DEBUG_E(e) do {                  \
    if (!(e))                           \
        error_check(__FILE__, __LINE__);\
} while (0)

#define DEBUG_F(e) do {     \
    print_debug(e);         \
} while (0)

void error_check(char *file, uint64_t line);
void print_debug(char *string);


#endif
