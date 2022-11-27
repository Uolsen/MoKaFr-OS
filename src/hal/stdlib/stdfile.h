#ifndef _STDFILE_H
#define _STDFILE_H

#include "intdef.h"

typedef enum {
    ReadOnly,
    WriteOnly,
    ReadWrite,
} FileMode;

uint32_t getpid();
uint32_t open(const char* filename, FileMode mode);
uint32_t read(uint32_t file, const char* buffer, uint32_t size);
uint32_t write(uint32_t file, const char* buffer, uint32_t size);
void close(uint32_t file);

#endif
