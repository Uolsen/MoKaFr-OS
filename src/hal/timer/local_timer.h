#ifndef _LOCAL_TIMER_H
#define _LOCAL_TIMER_H

// #define LOCAL_TIMER_BASE_ADDR    0x4c000000UL
// #define LOCAL_TIMER_BASE_ADDR    0xff800000UL
#define LOCAL_TIMER_BASE_ADDR    0xff840000UL

#define CORE_IRQ_CONTROL			LOCAL_TIMER_BASE_ADDR + 0x0cUL
#define PERI_IRQ_ROUTE0				LOCAL_TIMER_BASE_ADDR + 0x24UL
#define LOCAL_TIMER_CONTROL			LOCAL_TIMER_BASE_ADDR + 0x34UL
#define LOCAL_TIMER_IRQ				LOCAL_TIMER_BASE_ADDR + 0x38UL

void local_timer_init();
void local_timer_reset();

#endif
