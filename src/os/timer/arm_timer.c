#include "timer/arm_timer.h"
#include "sched/sched.h"
#include "debug/debug.h"
#include "lib.h"

void init_timer(void)
{
    DEBUG_F("ARM Timer INIT\n");

    mmio_write(ARM_TIMER_PREDIV, 0x7d);
    mmio_write(ARM_TIMER_LOAD, 40000000);
    mmio_write(ARM_TIMER_CONTROL, 0b10100010);
}

void timer_interrupt_handler(void)
{
    DEBUG_F("timer_interrupt_handler");

    // timer_tick();

    uint32_t mask = mmio_read(ARM_TIMER_MSKIRQ);

    DEBUG_P("timer_interrupt_handler mask: %u", mask);

    if (mask & 1) {
        DEBUG_F("timer_interrupt_handler MASK");
        // timer_tick();

        mmio_write(ARM_TIMER_IRQCNTL, 1);
    }

    // init_timer();
}