#include "timer/arm_timer.h"
#include "debug/debug.h"
#include "lib.h"

void init_timer(void)
{
    DEBUG_F("ARM Timer INIT\n");

    mmio_write(ARM_TIMER_PREDIV, 0x7d);
    mmio_write(ARM_TIMER_LOAD, 4000000);
    mmio_write(ARM_TIMER_CONTROL, 0b10100010);
}

void timer_interrupt_handler(void)
{
	uint64_t ticks = 0;
    uint32_t mask = mmio_read(ARM_TIMER_MSKIRQ);

    if (mask & 1) {
		uint64_t data[] = {{ticks}};
		DEBUG_K("timer %u\r\n", data);

        ticks++;
        mmio_write(ARM_TIMER_IRQCNTL, 1);

    }
}