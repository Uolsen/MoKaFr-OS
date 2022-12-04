#ifndef _GPIO_H
#define _GPIO_H

#define GPIO_BASE_ADDR 0xFE000000

typedef enum {
    // function set
    GPFSEL0     = GPIO_BASE_ADDR + 0x200000,
    GPFSEL1     = GPIO_BASE_ADDR + 0x200004,
    GPFSEL2     = GPIO_BASE_ADDR + 0x200008,
    GPFSEL3     = GPIO_BASE_ADDR + 0x20000c,
    GPFSEL4     = GPIO_BASE_ADDR + 0x200010,
    GPFSEL5     = GPIO_BASE_ADDR + 0x200014,

    // set
    GPSET0      = GPIO_BASE_ADDR + 0x20001C,
    GPSET1      = GPIO_BASE_ADDR + 0x200020,

    // clear
    GPCLR0      = GPIO_BASE_ADDR + 0x200028,
    GPCLR1      = GPIO_BASE_ADDR + 0x20002c,

    GPPUPPDN0   = GPIO_BASE_ADDR + 0x2000E4
} GpioRegister;

enum {
    GPIO_MAX_PIN = 53,
};

typedef enum {
    Input   = 0, // 000 - input
    Output  = 1, // 001 - output
    Alt_5   = 2, // 010 - alt. function 5
    Alt_4   = 3, // 011 - alt. function 4
    Alt_0   = 4, // 100 - alt. function 0
    Alt_1   = 5, // 101 - alt. function 1
    Alt_2   = 6, // 110 - alt. function 2
    Alt_3   = 7, // 111 - alt. function 3
} GpioFunction;

unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size);

unsigned int gpio_set(unsigned int pin_number);

unsigned int gpio_clear(unsigned int pin_number);

//unsigned int gpio_pull(unsigned int pin_number);
//

unsigned int gpio_set_function(unsigned int pin_number, GpioFunction gpio_function);

#endif