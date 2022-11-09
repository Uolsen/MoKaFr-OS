#include "timer/local_timer.h"
#include "lib.h"
#include "print/print.h"

void local_timer_init(){

	print("LOCAL timer\n");

	uint32_t load = 100000;
	load |= 1 << 28;
	out_word(LOCAL_TIMER_CONTROL, load);

	for (uint32_t i = 0; i < 1000; i++)
	{
			
	}
	
	uint32_t currVal = in_word(LOCAL_TIMER_CONTROL);
	currVal &= ~(15 << 28);

	int64_t data[] = {(currVal)};

	printk("Timer value: %u\n", data);
}
