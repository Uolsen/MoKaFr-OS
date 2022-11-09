#include "timer/arm_timer.h"
#include "lib.h"
#include "print/print.h"

void arm_timer_init(){
	print("ARM Timer INIT\n");

	out_word(ARM_TIMER_LOAD, 0x20000);
	uint32_t currVal = in_word(ARM_TIMER_VALUE);
	int64_t data[] = {currVal};

	// out_word(SYS_TIMER_C3, currVal + 200000);

	printk("ARM Timer value: %u\n", data);
}
