#include "uart/uart.h"
#include "print/print.h"
// #include "debug.h"
#include "lib.h"
// #include "handler.h"
#include "timer/system_timer.h"
#include "timer/arm_timer.h"
#include "timer/local_timer.h"
#include "interrupt/irq.h"
#include "debug/debug.h"

void main()
{
    init_uart();
    print("Hello, Raspberry pi\r\n");
    int64_t params2[] = {(uint64_t)get_el()};
    printk("We are at EL %u\r\n", params2);
    DEBUG_F("Hello, Raspberry PI 4!!!");

    irq_init_vectors();
    enable_interrupt_controller();
    irq_enable();

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