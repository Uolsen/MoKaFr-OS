#include "stdlib/stdstring.h"
#include "lib.h"
#include "debug/debug.h"

const char char_conv_arr[] = "0123456789ABCDEF";
static char split [32][1024];

/**
 * Attempt to convert the given int to string.
 * @param input
 * @param output
 * @param base
 */
void itoa(unsigned int input, char* output, unsigned int base) {
    int i = 0;

    while (input > 0) {
        output[i] = char_conv_arr[input % base];
        input /= base;
        i++;
    }

    if (i == 0)
    {
        output[i] = char_conv_arr[0];
        i++;
    }

    output[i] = '\0';
    i--;

    for (int j = 0; j <= i/2; j++)
    {
        char c = output[i - j];
        output[i - j] = output[j];
        output[j] = c;
    }
}

/**
 * Attempt to convert the given string to an int.
 *
 * @param input
 * @return
 */
int atoi(const char* input) {
    int output = 0;

    while (*input != '\0')
    {
        output *= 10;
        if (*input > '9' || *input < '0')
            break;

        output += *input - '0';

        input++;
    }

    return output;
}

/**
 * Copies the given string (src) to another string (dest).
 *
 * @param dest
 * @param src
 * @param size
 * @return
 */
char* strncpy(char* dest, const char *src, int size) {
    int i;

    for (i = 0; i < size && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < size; i++)
        dest[i] = '\0';

    return dest;
}

/**
 * Add the given string (src) at the end of another string (dest).
 *
 * @param dest
 * @param src
 * @param size
 * @return
 */
// add to end of dest string src
char* stradd(char* dest, const char *src, int size) {

    uint32_t dest_len = strlen(dest);

    for (uint32_t i = dest_len, s = 0; s < size; i++, s++)
    {
        dest[i] = src[s];
    }

    return dest;
}

/**
 * Compare whether two strings match.
 *
 * @param s1
 * @param s2
 * @param size
 * @return
 */
int strncmp(const char *s1, const char *s2, int size) {
    unsigned char u1, u2;
    while (size-- > 0)
    {
        u1 = (unsigned char) *s1++;
        u2 = (unsigned char) *s2++;
        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }

    return 0;
}

/**
 * Get the length of the specified string.
 *
 * @param s
 * @return
 */
int strlen(const char* s) {
    int i = 0;

    while (s[i] != '\0')
        i++;

    return i;
}

/**
 * Adds the given string (src) at the end of another string (dest).
 *
 * @param src
 * @param dest
 */
void stradd2(char* src, char* dest) {
//    int j = 0;
    for (int i = strlen(dest), j = 0; j < strlen(src); j++, i++) {
        dest[i] = src[j];
    }

//    return dest;
}

/**
 * Add the given string (target) at the beginning of another string (src).
 * @param src
 * @param target
 */
void straddtostart(char *src, char * target) {

    // /root/home/admin
    // ""
    // admin
    // home
    // root
    // stradd2("", "admin") => /admin
    //stradd2("admin", "home") => /home/admin
    //stradd2("home/admin", "root") => root/home/admnin

    char tmp[1024] = {0};
    strncpy(tmp, src, strlen(src));
    stradd2(target, tmp);
    strncpy(target, tmp, strlen(tmp));

}

/**
 * Clear the memory at the specified address and length.
 *
 * @param memory
 * @param length
 */
void bzero(void* memory, int length) {
    char* mem = (char*)(memory);

    for (int i = 0; i < length; i++)
        mem[i] = 0;
}

/**
 * Split the specified string using the given delimiter and offset.
 *
 * @param src The source string to split
 * @param znak The character to split by (delimiter)
 * @param offset Set 0 to split the whole string.
 * @return Array of splitted values
 */
uint32_t ** strsplit(uint8_t * src, uint8_t znak, uint32_t offset) {
    bzero(split, 32 * 1024);
    char token[32];
    uint32_t token_i = 0;
    uint32_t tokens_i = 0;

    for (uint32_t i = offset; i <= strlen(src); i++) {
        if (src[i] == znak || src[i] == '\0' || src[i] == '\n') {
            strncpy(split[tokens_i], token, strlen(token));
            tokens_i++;
            bzero(token, strlen(token));
            token_i = 0;
        } else {
            token[token_i] = src[i];
            token_i++;
        }
    }

//    for (uint32_t i = 0; i < 32; i++) {
//        DEBUG_P("00 hex: %x", split[i]);
//        DEBUG_P("00 string: %s", split[i]);
//    }

    return &split;
}

/**
 * Returns a part of the specified splitted string (array) at the given index.
 *
 * Ex: to get the second part of a splitted string, use get_split(<split>, 2)
 *
 * @param split Result of the strsplit function the s
 * @param index Index of the splitted part to get
 * @return
 */
uint8_t * get_split(uint8_t * split, uint32_t index) {
    return split + (1024 * index);
}


