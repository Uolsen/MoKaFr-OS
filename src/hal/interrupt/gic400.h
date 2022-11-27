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
 

void init_interrupt_controller(void);
void enable_irq(void);
void disable_irq(void);

#endif
