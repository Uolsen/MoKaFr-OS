#ifndef _UART_H
#define _UART_H

#include "lib.h"

#define IO_BASE_ADDR    0xfe200000

#define UART0_DR        IO_BASE_ADDR + 0x1000
#define UART0_FR        IO_BASE_ADDR + 0x1018
#define UART0_CR        IO_BASE_ADDR + 0x1030
#define UART0_LCRH      IO_BASE_ADDR + 0x102c
#define UART0_FBRD      IO_BASE_ADDR + 0x1028
#define UART0_IBRD      IO_BASE_ADDR + 0x1024
#define UART0_IMSC      IO_BASE_ADDR + 0x1038
#define UART0_MIS       IO_BASE_ADDR + 0x1040
#define UART0_ICR       IO_BASE_ADDR + 0x1044
#define UART0_IFLS      IO_BASE_ADDR + 0x1034
#define UART0_RIS       IO_BASE_ADDR + 0x103C

#define UART5_DR        IO_BASE_ADDR + 0x1a00
#define UART5_FR        IO_BASE_ADDR + 0x1a18
#define UART5_CR        IO_BASE_ADDR + 0x1a30
#define UART5_LCRH      IO_BASE_ADDR + 0x1a2c
#define UART5_FBRD      IO_BASE_ADDR + 0x1a28
#define UART5_IBRD      IO_BASE_ADDR + 0x1a24
#define UART5_IMSC      IO_BASE_ADDR + 0x1a38
#define UART5_MIS       IO_BASE_ADDR + 0x1a40
#define UART5_ICR       IO_BASE_ADDR + 0x1a44
#define UART5_IFLS      IO_BASE_ADDR + 0x1a34
#define UART5_RIS       IO_BASE_ADDR + 0x1a3C

#define MAX_BUFFER_SIZE	64

void get_buffer(uint8_t * str);
unsigned char read_char(void);
void write_char(unsigned char c);
void write_string(const char *string);
void init_uart(void);
void uart_handler(void);

#endif
