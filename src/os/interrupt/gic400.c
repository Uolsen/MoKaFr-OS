#include "interrupt/gic400.h"
#include "timer/arm_timer.h"
#include "uart/uart.h"
#include "debug/debug.h"
#include "sched/sched.h"
#include "lib.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

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

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	DEBUG_P("%s, ", entry_error_messages[type]);
	DEBUG_P("ESR: %x, ", esr);
	DEBUG_P("address: %x\r\n", address);
}

void handle(void)
{
    uint32_t irq = get_irq_number();

    // DEBUG_P("handler() irq: %u", irq);

    mmio_write(ICC_EOI, irq);

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

    // mmio_write(ICC_EOI, irq);
}