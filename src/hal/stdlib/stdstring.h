#ifndef _STDSTRING_H
#define _STDSTRING_H

void itoa(unsigned int input, char* output, unsigned int base);
int atoi(const char* input);
char* strncpy(char* dest, const char *src, int size);
char* stradd(char* dest, const char *src, int size);
void stradd2(char* dest, char* src);
int strncmp(const char *s1, const char *s2, int size);
int strlen(const char* s);
void straddtostart(char *src, char * target);
void bzero(void* memory, int length);

#endif