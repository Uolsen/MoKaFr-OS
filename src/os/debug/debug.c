#include "debug/debug.h"
#include "print/print.h"

/**
 * Checks for errors and stops execution and shows file and line where error occured.
 *
 * @param file File where the error occurred
 * @param line Line where the error occurred
 */
void error_check(char *file, uint64_t line) {
    #ifdef DEBUG
    int64_t params[] = {(int64_t) file};
    printk("DEBUG ERROR [%s : ", params);
    int64_t params2[] = {line};
    printk("%u]\r\n", params2);

    while (1) {;}
    #endif
}

/**
 * If debug mode is enabled, prints a debug message.
 *
 * @param string String to print
 */
void print_debug(char *string) {
    #ifdef DEBUG
    int64_t params[] = {(int64_t) string};
    printk("DEBUG INFO: %s\r\n", params);
    #else
    print("");
    #endif
}

/**
 * If debug mode is enabled, prints a debug message with specified parameters.
 *
 * @param string String to print
 * @param params
 */
void printk_debug(char *string, int64_t params[]) {
    #ifdef DEBUG
    print("DEBUG INFO: ");
    printk(string, params);
    print("\r\n");
    #endif
}

/**
 * If debug mode is enabled, prints a debug message with one parameter.
 *
 * @param string string to print
 * @param param
 */
void printk_debug_p(char *string, int64_t param) {
    #ifdef DEBUG
    print("DEBUG INFO: ");
    printp(string, param);
    print("\r\n");
    #endif
}
