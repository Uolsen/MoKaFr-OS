#include "stdlib/stdstring.h"

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

// vynulovani pameti
void bzero(void* memory, int length) {
    char* mem = (char*)(memory);

    for (int i = 0; i < length; i++)
        mem[i] = 0;
}
