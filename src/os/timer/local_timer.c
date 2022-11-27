#include "timer/local_timer.h"
#include "lib.h"
#include "debug/debug.h"

void local_timer_init(){
	DEBUG_F("local_timer_init1");
	uint32_t peri = (0x01 << 24);
	peri |= 0;
	mmio_write(PERI_IRQ_ROUTE0, peri);
	DEBUG_F("local_timer_init2");

	// uint32_t load = 0b111111111111111111111111111;
	uint32_t load = 200;
	load |= 1 << 28;
	load |= 1 << 29;
	mmio_write(LOCAL_TIMER_CONTROL, load);
	DEBUG_F("local_timer_init3");
	
	uint32_t currVal = mmio_read(LOCAL_TIMER_CONTROL);
	int64_t data[] = {(currVal)};
	DEBUG_K("Timer value: %u", data);
}

void local_timer_reset(){
	uint32_t rst = (1 << 30);
	rst |= (1 << 31);
	mmio_write(LOCAL_TIMER_IRQ, rst);
}
