#include "timer/qemu_timer.h"
#include "timer/local_timer.h"
#include "debug/debug.h"
#include "lib.h"

static uint64_t ticks = 0;

void init_interrupt_controller(void)
{
    mmio_write(DIST, 0);
    mmio_write(CPU_INTERFACE, 0);

    mmio_write(ICC_PR, 0xff);

    mmio_write(ICD_PR + 64, 0);
    mmio_write(ICD_PR + 38*4, 0);

    mmio_write(ICD_PTR + 64, 1);
    mmio_write(ICD_PTR + 38*4, 0x100);

    mmio_write(ICD_ICFGR + 16, 2);
    mmio_write(ICD_ICFGR + 36, 0x80000);
    
    mmio_write(ICD_ISENABLE + 8, 1);
    mmio_write(ICD_ISENABLE + 16, (1 << 25));

    mmio_write(DIST, 1);
    mmio_write(CPU_INTERFACE, 1);
}

void init_timer(void)
{
    mmio_write(TIMER_PREDIV, 0x7d);
    mmio_write(TIMER_LOAD, 19841);
    mmio_write(TIMER_CTL, 0b10100010);
}

static uint32_t get_irq_number(void)
{
    return mmio_read(ICC_ACK);
}

static void timer_interrupt_handler(void)
{
    uint32_t mask = mmio_read(TIMER_MSKIRQ);

    if (mask & 1) {
        if (ticks % 100 == 0) {
            printk("timer %u\r\n", ticks);
        }

        ticks++;
        mmio_write(TIMER_ACK, 1);
    }
}

void handler(uint64_t numid, uint64_t esr, uint64_t elr)
{
    uint32_t irq;

	int64_t data[] = {irq, numid};

	DEBUG_K("handler() %u %u", data);

	// local_timer_reset();

    switch (numid) {
        case 1:
            // printk("sync error at %x: %x\r\n", elr, esr);
			local_timer_reset();
            while (1) { }
            break;

        case 2:
            irq = get_irq_number();

            if (irq == 64) {
                timer_interrupt_handler();
            }
            else if (irq == 96 + 57) {
				local_timer_reset();
                uart_handler();
            }
            else {
                // printk("unknown irq\r\n");
                while (1) { }
            }

            mmio_write(ICC_EOI, irq);
            break;    

        default:
            // printk("unknown exception\r\n");
            while (1) { }
    }
}