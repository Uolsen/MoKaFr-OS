#include "lib.h"
#include "drivers/gpio/gpio.h"
#include "print/print.h"

/**
 * Set the value of the gpio registers.
 *
 * @param pin_number Index of the pin: 0 - 57
 * @param value Value to write to
 * @param base Base address of the GPIO register
 * @param field_size Size of a single field (for example 1 bit, 3 bits, etc)
 * @return
 */
uint32_t gpio_call(uint32_t pin_number, uint32_t value, uint32_t reg, uint32_t field_size) {
    uint32_t field_mask = (1 << field_size) - 1;

    uint32_t num_fields = 32 / field_size;
    uint32_t shift = (pin_number % num_fields) * field_size;

    uint32_t cur_value = mmio_read(reg);

    cur_value &= ~(field_mask << shift);
    cur_value |= value << shift;

    mmio_write(reg, cur_value);

    return 1;
}

/**
 * Sets the specified pin high (1).
 *
 * If the specified pin is set to be an input pin, the call has no effect.
 *
 * @param pin_number Pin index from 0 - 57
 * @return
 */
uint32_t gpio_set(uint32_t pin_number) {
    GpioRegister reg = GPSET0;

    // Get register for given pin
    switch (pin_number / 32) {
        case 0: reg = GPSET0; break;
        case 1: reg = GPSET1; break;
    }

    return gpio_call(pin_number, 1, reg, 1);
}

/**
 * Sets the specified pin low (0).
 *
 * If the specified pin is set to be an input pin, the call has no effect.
 *
 * @param pin_number Pin index from 0 - 57
 * @return
 */
uint32_t gpio_clear(uint32_t pin_number) {
    GpioRegister reg = GPCLR0;

    // Get register for given pin
    switch (pin_number / 32) {
        case 0: reg = GPCLR0; break;
        case 1: reg = GPCLR1; break;
    }

    return gpio_call(pin_number, 1,reg, 1);
}

/**
 * Set the function of the GPIO pin.
 *
 * @param pin_number Index of the pin: 0 - 57
 * @param gpio_function GPIO Function Enum
 *
 * @see GpioFunction
 * @return
 */
uint32_t gpio_set_function(uint32_t pin_number, GpioFunction gpio_function) {
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
}