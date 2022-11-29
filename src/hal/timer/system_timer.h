#ifndef _SYSTEM_TIMER_H
#define _SYSTEM_TIMER_H

#define BASE_ADDR 0xfe000000

#define TIMER_CS        (BASE_ADDR+0x00003000)
#define TIMER_CLO       (BASE_ADDR+0x00003004)
#define TIMER_CHI       (BASE_ADDR+0x00003008)
#define TIMER_C0        (BASE_ADDR+0x0000300C)
#define TIMER_C1        (BASE_ADDR+0x00003010)
#define TIMER_C2        (BASE_ADDR+0x00003014)
#define TIMER_C3        (BASE_ADDR+0x00003018)

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

void system_timer_init();

#endif
