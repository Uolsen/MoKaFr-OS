#include "timer/local_timer.h"
#include "lib.h"
#include "debug/debug.h"

void local_timer_init(){
	uint32_t peri = (0x01 << 24);
	peri |= 0;
	mmio_write(PERI_IRQ_ROUTE0, peri);

	// uint32_t load = 0b111111111111111111111111111;
	uint32_t load = 500000000;
	load |= 1 << 28;
	load |= 1 << 29;
	mmio_write(LOCAL_TIMER_CONTROL, load);
	
	uint32_t currVal = mmio_read(LOCAL_TIMER_CONTROL);
	int64_t data[] = {(currVal)};
	DEBUG_K("Timer value: %u", data);

	local_timer_reset();
}

void local_timer_reset(){
	uint32_t rst = (1 << 30);
	rst |= (1 << 31);
	mmio_write(LOCAL_TIMER_IRQ, rst);
}
