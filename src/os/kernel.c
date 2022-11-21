#include "uart/uart.h"
#include "print/print.h"
// #include "debug.h"
#include "lib.h"
// #include "handler.h"
// #include "timer/system_timer.h"
// #include "timer/arm_timer.h"
// #include "timer/local_timer.h"
#include "interrupt/irq.h"
#include "debug/debug.h"
#include "timer/qemu_timer.h"
#include "timer/local_timer.h"

void main()
{
    init_uart();
    print("Hello, Raspberry pi\r\n");
    int64_t params2[] = {(uint64_t)get_el()};
    printk("We are at EL %u\r\n", params2);
    DEBUG_F("Hello, Raspberry PI 4!!!");

    // irq_init_vectors();
    // DEBUG_F("irq_init_vectors INIT");
    // enable_interrupt_controller();
    // DEBUG_F("enable_interrupt_controller INIT");
    // irq_enable();
    // DEBUG_F("irq_enable INIT");

    init_interrupt_controller();
    enable_irq();
    DEBUG_F("enable_irq();");
    local_timer_init();
    local_timer_reset();
    DEBUG_F("local_timer_reset();");


    // // handle_irq();

    // DEBUG_F("After INIT");

    // // local_timer_init();

    // DEBUG_F("TIMER INIT");

    // delay(500000000);
    // DEBUG_F("DELAY");


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

void timer_core()
{
    delay(500000000);
    init_uart();
    // print("TIMER CORE Hello, Raspberry pi\r\n");

    DEBUG_F("TIMER CORE !!!!!!");
    
    while (1) {
        ;
    }
}