#include "uart/uart.h"
#include "print/print.h"
#include "lib.h"
#include "debug/debug.h"
#include "timer/arm_timer.h"
#include "interrupt/gic400.h"

void process(char *array)
{
	while (1){
		for (int i = 0; i < 5; i++){
			write_char(array[i]);
			delay(100000);
		}
	}
}

void main()
{
    init_uart();
    fb_init();
    init_interrupt_controller();
    enable_irq();
    print("Hello, Raspberry pi\r\n");
    int64_t params[] = {(uint64_t)get_el()};
    printk("We are at EL %u\r\n", params);

    init_timer();
    DEBUG_F("init_timer();");


    // uint32_t res = copy_process((uint64_t)&process, (uint64_t)"12345");

    // DEBUG_P("process res: %u", res);

    // if (res != 0) {
    //     print("error while starting process 1");
    //     return;
    // }
    // res = copy_process((uint64_t)&process, (uint64_t)"abcde");

    // DEBUG_P("process res: %u", res);
    // if (res != 0) {
    //     print("error while starting process 2");
    //     return;
    // }

    while (1){
    //     schedule();
    }
}