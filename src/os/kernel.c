#include "uart/uart.h"
#include "print/print.h"
// #include "debug.h"
#include "lib.h"
// #include "handler.h"
#include "timer/system_timer.h"
#include "timer/arm_timer.h"
#include "timer/local_timer.h"
#include "debug/debug.h"

void main()
{
    init_uart();
    print("Hello, Raspberry pi\r\n");
    int64_t params2[] = {(uint64_t)get_el()};
    printk("We are at EL %u\r\n", params2);
    DEBUG_F("Hello, Raspberry PI 4!!!");
    DEBUG_K("Vypis s parametrem %u", params2);
    DEBUG_E(0);
    local_timer_init();

    // arm_timer_init();

    // // system_timer_init();
    // for (uint32_t i = 0; i < 100000; i++)
    // {
            
    // }
    
    // system_timer_init();

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