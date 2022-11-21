#ifndef _IRQ_H
#define _IRQ_H
#include "drivers/gpio/gpio.h"
#include "lib.h"

#define GIC_BASE  0xff840000

#define IRQ_REG_IRQ0_PENDING0		GPIO_BASE_ADDR + 0x200UL
#define IRQ_REG_IRQ0_PENDING1		GPIO_BASE_ADDR + 0x204UL
#define IRQ_REG_IRQ0_PENDING2		GPIO_BASE_ADDR + 0x208UL
#define IRQ_REG_IRQ0_SET_EN_0		GPIO_BASE_ADDR + 0x210UL
#define IRQ_REG_IRQ0_SET_EN_1		GPIO_BASE_ADDR + 0x214UL
#define IRQ_REG_IRQ0_SET_EN_2		GPIO_BASE_ADDR + 0x218UL
#define IRQ_REG_IRQ0_CLR_EN_0		GPIO_BASE_ADDR + 0x220UL
#define IRQ_REG_IRQ0_CLR_EN_1		GPIO_BASE_ADDR + 0x224UL
#define IRQ_REG_IRQ0_CLR_EN_2		GPIO_BASE_ADDR + 0x228UL

enum vc_irqs1 {
    SYS_TIMER_IRQ_0 = 1,
    SYS_TIMER_IRQ_1 = 2,
    SYS_TIMER_IRQ_2 = 4,
    SYS_TIMER_IRQ_3 = 8,
    AUX_IRQ = (1 << 29),
    ARM_IRQ = (1 << 30),
};

enum vc_irqs2 {
    UART_IRQ = (1 << (57-32)),
};

void irq_init_vectors();
void irq_enable();
void irq_disable();
void enable_interrupt_controller();
void disable_interrupt_controller();

#endif
