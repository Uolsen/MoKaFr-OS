#define THREAD_CPU_CONTEXT			0 		// offset of cpu_context in task_struct 

.global cpu_switch_to
cpu_switch_to:

	mov	x10, #THREAD_CPU_CONTEXT
	add	x8, x0, x10
	
	mov	x9, sp
	//mov	x7, x30

	//mrs x0, CurrentEL // current exception level
    //lsr x0, x0, #2
	//cmp		x0, #1
	//bne     cpu_skip

	//MSR 	SPSEL, #0

//cpu_skip:

	stp	x19, x20, [x8], #16		// store callee-saved registers
	stp	x21, x22, [x8], #16
	stp	x23, x24, [x8], #16
	stp	x25, x26, [x8], #16
	stp	x27, x28, [x8], #16
	stp	x29, x9, [x8], #16
	str	x30, [x8]

	add	x8, x1, x10


	ldp	x19, x20, [x8], #16		// restore callee-saved registers
	ldp	x21, x22, [x8], #16
	ldp	x23, x24, [x8], #16
	ldp	x25, x26, [x8], #16
	ldp	x27, x28, [x8], #16
	ldp	x29, x9, [x8], #16
	ldr	x30, [x8]
	//ldr	x7, [x8]
	
	mov	sp, x9

	b preempt_enable

	// msr elr_el1, x7
	
	//MSR 	SPSEL, #1
	//mov	x30, x7
	// Instrukce na to abych nebyl v IRQ

	ret