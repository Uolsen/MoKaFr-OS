#include "uart/uart.h"
#include "print/print.h"
// #include "debug.h"
#include "lib.h"
// #include "handler.h"

void main()
{
    init_uart();

    print("Hello, Raspberry pi\r\n");
    int64_t params2[] = {(uint64_t)get_el()};
    printk("We are at EL %u\r\n", params2);
    // char buffer[1024];
    // int buffer_size = 0;
    // decimal_to_string(buffer, 0, (uint64_t)get_el());
    // printk(buffer);

    //init_timer();
    // init_interrupt_controller();
    // enable_irq();
    
    while (1) {
        ;
    }
}