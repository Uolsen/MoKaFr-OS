#include "src/os/uart/uart.h"
#include "src/os/print/print.h"
// #include "debug.h"
#include "src/os/lib.h"
// #include "handler.h"

void main()
{
    init_uart();
    printk("Hello, Raspberry pi\r\n");
    printk("We are at EL %u\r\n", (uint64_t)get_el());

    //init_timer();
    // init_interrupt_controller();
    // enable_irq();
    
    while (1) {
        ;
    }
}