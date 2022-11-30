#include "drivers/gpio/gpio.h"
#include "timer/arm_timer.h"
#include "uart/uart.h"
#include "sched/sched.h"
#include "lib.h"
#include "debug/debug.h"
#include "stdlib/stdstring.h"

int length = 0;
int rows = 0;
int font_width = 8;
int line_height = 20;
int x_base = 50;
int y_base = 60;
int crln = 0;

static uint8_t buffer[MAX_BUFFER_SIZE];
static uint32_t buff_len = 0;

void load_char(unsigned char c)

{
    buffer[buff_len] = c;
    buff_len++;
}

void get_buffer(uint8_t * str){
    strncpy(str, buffer, MAX_BUFFER_SIZE);
    for (uint32_t i = 0; i < MAX_BUFFER_SIZE; i++)
    {
        buffer[i] = '\0';
    }
    buff_len = 0;
    
    DEBUG_P("BUFFER: %s", str);
}

void write_char(unsigned char c)
{
    while (mmio_read(UART0_FR) & (1 << 3))
    {
    }
    mmio_write(UART0_DR, c);

    // Draw on screen
    int x = x_base + (length * font_width);

    if (c == '\r' || c == '\n') {
        if (crln == 0) {
            rows += 1;
            length = 0;
            crln = 1;
        }
    } else {
        crln = 0;
    }
//        if (crln == 0) {
//            crln = 1;
//            length = 0;
//            rows += 1;
//        } else {
//            crln = 0;
//        }
//    } else {
        drawChar(c, x, y_base + (rows * line_height), 0x05);

        length += 1;
        if (length >= 226) {
            length = 0;
            rows += 1;

            if (rows >= 48) {
                rows = 0;
                fb_clear();
            }
        }
//    }
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
            timer_tick();
            return;
        }
        else
        {
            // write_char(ch);
            load_char(ch);
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

void init_uart_5(void)
{
    gpio_set_function(12, Alt_4);
    gpio_set_function(13, Alt_4);

    out_word(UART5_CR, 0);
    out_word(UART5_IBRD, 26);
    out_word(UART5_FBRD, 0);
    out_word(UART5_LCRH, (1 << 5) | (1 << 6));
    out_word(UART5_IMSC, (1 << 4));
    out_word(UART5_CR, (1 << 0) | (1 << 8) | (1 << 9));
}
