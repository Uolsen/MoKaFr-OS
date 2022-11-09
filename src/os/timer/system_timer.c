#include "timer/system_timer.h"
#include "lib.h"
#include "print/print.h"

void system_timer_init(){
	out_word(SYS_TIMER_CS, 0);
	uint32_t currVal = in_word(SYS_TIMER_CLO);
	int64_t data[] = {currVal};

	out_word(SYS_TIMER_C3, currVal + 200000);

	printk("Timer value: %u\n", data);
}
