#ifndef _ARM_TIMER_H
#define _ARM_TIMER_H

// #define ARM_TIMER_BASE_ADDR    0x7e00b000UL
#define ARM_TIMER_BASE_ADDR    0xfe20b000UL
// #define SYS_TIMER_BASE_ADDR    0x20003000UL

#define ARM_TIMER_LOAD		ARM_TIMER_BASE_ADDR + 0x400UL
#define ARM_TIMER_VALUE		ARM_TIMER_BASE_ADDR + 0x404UL
#define ARM_TIMER_CONTROL	ARM_TIMER_BASE_ADDR + 0x08UL
#define ARM_TIMER_IRQCNTL	ARM_TIMER_BASE_ADDR + 0x0CUL
#define ARM_TIMER_RAWIRQ	ARM_TIMER_BASE_ADDR + 0x10UL
#define ARM_TIMER_MSKIRQ	ARM_TIMER_BASE_ADDR + 0x04UL
#define ARM_TIMER_RELOAD	ARM_TIMER_BASE_ADDR + 0x08UL
#define ARM_TIMER_PREDIV	ARM_TIMER_BASE_ADDR + 0x08UL
#define ARM_TIMER_FREECNT	ARM_TIMER_BASE_ADDR + 0x08UL

void arm_timer_init();

#endif
