#include "timer/system_timer.h"
#include "lib.h"
#include "sched/sched.h"
#include "print/print.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void system_timer_init ( void )
{
	curVal = mmio_read(TIMER_CLO);
	curVal += interval;
	mmio_write(TIMER_C1, curVal);
}

void handle_timer_irq( void ) 
{
	curVal += interval;
	mmio_write(TIMER_C1, curVal);
	mmio_write(TIMER_CS, TIMER_CS_M1);
	timer_tick();
}
