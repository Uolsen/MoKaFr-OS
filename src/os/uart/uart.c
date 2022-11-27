#include "drivers/gpio/gpio.h"
#include "timer/arm_timer.h"
#include "uart/uart.h"
#include "lib.h"

void write_char(unsigned char c)
{
    while (in_word(UART0_FR) & (1 << 3))
    {
    }
    out_word(UART0_DR, c);
}

unsigned char read_char(void)
{
    return in_word(UART0_DR);
}

void write_string(const char *string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        write_char(string[i]);
    }
}

void uart_handler(void)
{
    uint32_t status = in_word(UART0_MIS);

    if (status & (1 << 4))
    {
        char ch = read_char();

        if (ch == '\r')
        {
            write_string("\r\n");
        }
        else if (ch == '\\')
        {
            // timer_interrupt_handler();
            return;
        }
        else
        {
            write_char(ch);
        }

        out_word(UART0_ICR, (1 << 4));
    }
}

void init_uart(void)
{
    gpio_set_function(14, Alt_0);
    gpio_set_function(15, Alt_0);

    out_word(UART0_CR, 0);
    out_word(UART0_IBRD, 26);
    out_word(UART0_FBRD, 0);
    out_word(UART0_LCRH, (1 << 5) | (1 << 6));
    out_word(UART0_IMSC, (1 << 4));
    out_word(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}
