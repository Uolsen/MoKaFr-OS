#include "interrupt/irq.h"
#include "timer/system_timer.h"
#include "debug/debug.h"
#include "timer/local_timer.h"
#include "lib.h"

void enable_interrupt_controller()
{
	// REGS_IRQ->irq0_enable_0 = UART_IRQ;
	// REGS_IRQ->irq0_enable_1 = UART_IRQ;
	mmio_write(IRQ_REG_IRQ0_SET_EN_0, AUX_IRQ);
	// mmio_write(IRQ_REG_IRQ0_SET_EN_1, UART_IRQ);
	// mmio_write(IRQ_REG_IRQ0_SET_EN_1, 0);
	// mmio_write(IRQ_REG_IRQ0_SET_EN_2, (1 << 31));
}

void disable_interrupt_controller()
{
	// REGS_IRQ->irq0_enable_0 = 0;
	// mmio_write(IRQ_REG_IRQ0_CLR_EN_0, ARM_IRQ);
	// mmio_write(IRQ_REG_IRQ0_CLR_EN_1, UART_IRQ);
}

void handle_irq()
{
	// int64_t pend0 = mmio_read(IRQ_REG_IRQ0_PENDING0);
	// int64_t pend1 = mmio_read(IRQ_REG_IRQ0_PENDING1);
	// int64_t pend2 = mmio_read(IRQ_REG_IRQ0_PENDING2);
	// uint64_t pend2 = mmio_read(LOCAL_TIMER_CONTROL);
	// int64_t data[] = {(pend2)};
	// DEBUG_K("INTERUPT: %u", data);

	DEBUG_F("INTERUPT");
	// printk("INTERUPT: %u", data);

	// local_timer_reset();

	// unsigned int irq = REGS_IRQ->irq0_pending_0;

	// while(irq) {
	//     if (irq & SYS_TIMER_IRQ_1) {
	//         irq &= ~SYS_TIMER_IRQ_1;

	//         handle_timer_1();
	//     }

	//     if (irq & SYS_TIMER_IRQ_3) {
	//         irq &= ~SYS_TIMER_IRQ_3;

	//         handle_timer_3();
	//     }
	// }
}
