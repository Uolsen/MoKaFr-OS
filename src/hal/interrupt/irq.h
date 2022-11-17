#ifndef _IRQ_H
#define _IRQ_H
#include "drivers/gpio/gpio.h"
#include "lib.h"

struct arm_irq_regs_2711 {
    volatile uint64_t irq0_pending_0;
    volatile uint64_t irq0_pending_1;
    volatile uint64_t irq0_pending_2;
    volatile uint64_t res0;
    volatile uint64_t irq0_enable_0;
    volatile uint64_t irq0_enable_1;
    volatile uint64_t irq0_enable_2;
    volatile uint64_t res1;
    volatile uint64_t irq0_disable_0;
    volatile uint64_t irq0_disable_1;
    volatile uint64_t irq0_disable_2;
};

typedef struct arm_irq_regs_2711 arm_irq_regs;

#define REGS_IRQ ((arm_irq_regs *)(GPIO_BASE_ADDR + 0x0000B200))

enum irqs {
    SYS_TIMER_IRQ_0 = 1,
    SYS_TIMER_IRQ_1 = 2,
    SYS_TIMER_IRQ_2 = 4,
    SYS_TIMER_IRQ_3 = 8,
    AUX_IRQ = (1 << 29),
    UART_IRQ = 153,
};

void irq_init_vectors();
void irq_enable();
void irq_disable();
void enable_interrupt_controller();
void disable_interrupt_controller();

#endif
