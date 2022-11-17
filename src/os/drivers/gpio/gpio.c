#include "lib.h"
#include "drivers/gpio/gpio.h"
#include "print/print.h"

unsigned int gpio_call(unsigned int pin_number, unsigned  int value, unsigned int reg, unsigned int field_size) {
    unsigned int field_mask = (1 << field_size) - 1;

    unsigned int num_fields = 32 / field_size;
    unsigned int shift = (pin_number % num_fields) * field_size;

    unsigned int cur_value = mmio_read(reg);

    int64_t params[] = {(uint64_t)cur_value};

    cur_value &= ~(field_mask << shift);
    cur_value |= value << shift;

    mmio_write(reg, cur_value);
    int64_t params2[] = {(uint64_t)cur_value};

    return 1;
}

unsigned int gpio_set(unsigned int pin_number) {
    GpioRegister reg = GPSET0;

    // Get register for given pin
    switch (pin_number / 32) {
        case 0: reg = GPSET0; break;
        case 1: reg = GPSET1; break;
    }

    return gpio_call(pin_number, 1,reg, 1);
}

unsigned int gpio_clear(unsigned int pin_number) {
    GpioRegister reg = GPCLR0;

    // Get register for given pin
    switch (pin_number / 32) {
        case 0: reg = GPCLR0; break;
        case 1: reg = GPCLR1; break;
    }

    return gpio_call(pin_number, 1,reg, 1);
}

unsigned int gpio_set_function(unsigned int pin_number, GpioFunction gpio_function) {
    GpioRegister reg = GPFSEL0;

    // Get register for given pin
    switch (pin_number / 10) {
        case 0: reg = GPFSEL0; break;
        case 1: reg = GPFSEL1; break;
        case 2: reg = GPFSEL2; break;
        case 3: reg = GPFSEL3; break;
        case 4: reg = GPFSEL4; break;
        case 5: reg = GPFSEL5; break;
    }

    return gpio_call(pin_number, gpio_function, reg, 3);

//    // Calculate the bit index for given pin
//    unsigned int bit = (pin_number % 10) * 3;
//
//    unsigned int cur_value = mmio_read(reg);
//
////    int64_t params[] = {(uint64_t)cur_value};
////    printk("old gpio %u\r\n", params);
//
//    cur_value &= (~(7 << bit));
//    cur_value |= (gpio_function << bit);
//
//    mmio_write(reg, cur_value);
////    int64_t params2[] = {(uint64_t)cur_value};
////    printk("new gpio %u\r\n", params2);

    return 1;
}

//unsigned int gpio_pull(unsigned int pin_number) {
//    return gpio_call(pin_number, 1, GPPUPPDN0, 2, GPIO_MAX_PIN);
//}
//
//unsigned int gpio_function(unsigned int pin_number) {
//    return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN);
//}