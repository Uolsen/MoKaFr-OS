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
#include "timer/system_timer.h"

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

    DEBUG_F("trng:");
    int64_t params0[] = {(uint64_t)rand(10, 1000)};
    printk("num 1: %u\r\n", params0);
    int64_t params1[] = {(uint64_t)rand(10, 1000)};
    printk("num 2: %u\r\n", params1);
    int64_t params3[] = {(uint64_t)rand(10, 1000)};
    printk("num 3: %u\r\n", params3);

    init_interrupt_controller();
    init_interrupt_controller();
    enable_irq();
    DEBUG_F("enable_irq();");
    // local_timer_init();
    // local_timer_reset();
    DEBUG_F("local_timer_reset();");
    system_timer_init();
    DEBUG_F("system_timer_init();");




    // // handle_irq();

    // DEBUG_F("After INIT");

    // // local_timer_init();

    // DEBUG_F("TIMER INIT");

    // delay(500000000);
    // DEBUG_F("DELAY");

    fb_init();

//    drawRect(150,150,400,400,0x03,0);
//    drawRect(300,300,350,350,0x2e,1);
//
//    for (uint32_t i = 0; i < 16; i++) {
//        drawRect(1400, 150 + (i*(20+5)), 20, 20, 0x03, 0);
//    }
//
//    drawCircle(960,540,250,0x0e,0);
//    drawCircle(960,540,50,0x13,1);
//
//    drawPixel(250,250,0x0e);

    drawChar('O',500,500,0x05);
    drawString(40,40,"Welcome to MoKaFr OS!",0x0f);

//    drawLine(100,500,350,700,0x0c);

    // local_timer_init();

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