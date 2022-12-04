#ifndef _STDSTRING_H
#define _STDSTRING_H

#include "intdef.h"

typedef struct Token {
    char value[32];
} Token;

void itoa(unsigned int input, char* output, unsigned int base);
int atoi(const char* input);
char* strncpy(char* dest, const char *src, int size);
char* stradd(char* dest, const char *src, int size);
void stradd2(char* dest, char* src);
int strncmp(const char *s1, const char *s2, int size);
int strlen(const char* s);
void straddtostart(char *src, char * target);
void bzero(void* memory, int length);
uint32_t ** strsplit(uint8_t * src, uint8_t znak, uint32_t offset);
uint8_t * get_split(uint8_t * split, uint32_t index);

#endif