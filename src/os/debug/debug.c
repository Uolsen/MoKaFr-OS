#include "debug/debug.h"
#include "print/print.h"

void error_check(char *file, uint64_t line) {
    #ifdef DEBUG
    int64_t params[] = {(int64_t) file};
    printk("DEBUG ERROR [%s : ", params);
    int64_t params2[] = {line};
    printk("%u]\r\n", params2);

    while (1) {;}
    #endif
}

void print_debug(char *string) {
    #ifdef DEBUG
    int64_t params[] = {(int64_t) string};
    printk("DEBUG INFO: %s\r\n", params);
    #endif
}

void printk_debug(char *string, int64_t params[]) {
    #ifdef DEBUG
    print("DEBUG INFO: ");
    printk(string, params);
    print("\r\n");
    #endif
}
