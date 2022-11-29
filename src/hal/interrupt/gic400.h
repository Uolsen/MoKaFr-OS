#ifndef _GIC400_H
#define _GIC400_H

#define GIC_BASE  0xff840000
#define BASE_ADDR 0xfe000000

#define DISTRIBUTOR               	GIC_BASE + 0x1000
#define ICD_TYPE            		DISTRIBUTOR + 0x4
#define ICD_ICENABLE        		DISTRIBUTOR + 0x180
#define ICD_ISENABLE        		DISTRIBUTOR + 0x100
#define ICD_SET_PENDING     		DISTRIBUTOR + 0x200
#define ICD_SET_ACTIVE      		DISTRIBUTOR + 0x300
#define ICD_PR              		DISTRIBUTOR + 0x400
#define ICD_PTR             		DISTRIBUTOR + 0x800
#define ICD_GROUP           		DISTRIBUTOR + 0x80
#define ICD_ICFGR           		DISTRIBUTOR + 0xc00

#define CPU_INTERFACE       GIC_BASE + 0x2000
#define ICC_PR              CPU_INTERFACE + 0x4
#define ICC_ACK             CPU_INTERFACE + 0xc
#define ICC_EOI             CPU_INTERFACE + 0x10




#define IRQ_BASIC_PENDING	(BASE_ADDR+0x0000B200)
#define IRQ_PENDING_1		(BASE_ADDR+0x0000B204)
#define IRQ_PENDING_2		(BASE_ADDR+0x0000B208)
#define FIQ_CONTROL			(BASE_ADDR+0x0000B20C)
#define ENABLE_IRQS_1		(BASE_ADDR+0x0000B210)
#define ENABLE_IRQS_2		(BASE_ADDR+0x0000B214)
#define ENABLE_BASIC_IRQS	(BASE_ADDR+0x0000B218)
#define DISABLE_IRQS_1		(BASE_ADDR+0x0000B21C)
#define DISABLE_IRQS_2		(BASE_ADDR+0x0000B220)
#define DISABLE_BASIC_IRQS	(BASE_ADDR+0x0000B224)

#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)
#define AUX_IRQ				(1 << 29)
#define UART_IRQ			(1 << (57-32))

void init_interrupt_controller(void);

#endif
