#include "stdlib/stdfile.h"

uint32_t getpid() {
    uint32_t pid;

    asm volatile("svc #172");
    asm volatile("mov %0, x0" : "=r" (pid));

    return pid;
}

uint32_t open(const char* filename, Open_mode mode) {
    uint32_t file;

    asm volatile("mov x0, %0" : : "r" (filename));
    asm volatile("mov x1, %0" : : "r" (mode));
    asm volatile("svc #56");
    asm volatile("mov %0, x0" : "=r" (file));

    return file;

}

uint32_t read(uint32_t file, const char* buffer, uint32_t size) {
    uint32_t rdnum;

    asm volatile("mov x0, %0" : : "r" (file));
    asm volatile("mov x1, %0" : : "r" (buffer));
    asm volatile("mov x2, %0" : : "r" (size));
    asm volatile("svc #63");
    asm volatile("mov %0, x0" : "=r" (rdnum));

    return rdnum;
}

uint32_t write(uint32_t file, const char* buffer, uint32_t size) {
    uint32_t wrnum;

    asm volatile("mov x0, %0" : : "r" (file));
    asm volatile("mov x1, %0" : : "r" (buffer));
    asm volatile("mov x2, %0" : : "r" (size));
    asm volatile("svc #64");
    asm volatile("mov %0, x0" : "=r" (wrnum));

    return wrnum;
}

void close(uint32_t file) {
    asm volatile("mov x0, %0" : : "r" (file));
    asm volatile("svc #57");
}


// ioctl - svc #29