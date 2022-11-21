#include "timer/system_timer.h"
#include "lib.h"
#include "print/print.h"

void system_timer_init(){
	mmio_write(SYS_TIMER_CS, 0);
	uint32_t currVal = mmio_read(SYS_TIMER_CLO);

	// mmio_write(SYS_TIMER_C3, currVal + 4000000000);
	mmio_write(SYS_TIMER_C3, currVal + 200000);

	int64_t data[] = {currVal};
	printk("Timer value: %u\n", data);
}
