#include "interrupt/gic400.h"
#include "timer/arm_timer.h"
#include "uart/uart.h"
#include "debug/debug.h"
#include "lib.h"

void init_interrupt_controller(void)
{
    mmio_write(DISTRIBUTOR, 0);
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

    mmio_write(DISTRIBUTOR, 1);
    mmio_write(CPU_INTERFACE, 1);
}


static uint32_t get_irq_number(void)
{
    return mmio_read(ICC_ACK);
}

void handler(uint64_t numid, uint64_t esr, uint64_t elr)
{
    // uint32_t irq = get_irq_number();
    uint32_t irq;

	// int64_t data[] = {irq, numid};

	DEBUG_P("handler() numid: %u", numid);

    switch (numid) {
        case 1:
            // printk("sync error at %x: %x\r\n", elr, esr);
            DEBUG_P("handler() esr: %u", esr);
            DEBUG_P("handler() elr: %u", elr);
            while (1) { }
            break;

        case 2:
            irq = get_irq_number();

            DEBUG_P("handler() irq: %u", irq);

            if (irq == 64) {
                timer_interrupt_handler();
                // init_timer();
            }
            else if (irq == 96 + 57) {
                uart_handler();
            }
            else {
                DEBUG_F("unknown irq\r\n");
                while (1) { }
            }

            mmio_write(ICC_EOI, irq);
            break;    

        default:
            // printk("unknown exception\r\n");
            while (1) { }
    }
}