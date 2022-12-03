#include "stdlib/stdstring.h"
#include "lib.h"
#include "debug/debug.h"

const char char_conv_arr[] = "0123456789ABCDEF";

// int to string
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

// string to int
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

// copy string
char* strncpy(char* dest, const char *src, int size) {
    int i;

    for (i = 0; i < size && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < size; i++)
        dest[i] = '\0';

    return dest;
}

// add to end of dest string src
char* stradd(char* dest, const char *src, int size) {

    uint32_t dest_len = strlen(dest);

    for (uint32_t i = dest_len, s = 0; s < size; i++, s++)
    {
        dest[i] = src[s];
    }

    return dest;
}

// compare strings
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

// string length
int strlen(const char* s) {
    int i = 0;

    while (s[i] != '\0')
        i++;

    return i;
}

void stradd2(char* src, char* dest) {
//    int j = 0;
    for (int i = strlen(dest), j = 0; j < strlen(src); j++, i++) {
        dest[i] = src[j];
    }

//    return dest;
}

// add to begin of dest string src
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

// vynulovani pameti
void bzero(void* memory, int length) {
    char* mem = (char*)(memory);

    for (int i = 0; i < length; i++)
        mem[i] = 0;
}

char ** strsplit(char * src, char znak, int offset) {
    bzero(split, 32*1024);
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

    return split;
}

