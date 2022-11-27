.section .text
.global vector_table

.balign 0x800
vector_table:
current_el_sp0_sync:
    b error

.balign 0x80
current_el_sp0_irq:
    b error

.balign 0x80
current_el_sp0_fiq:
    b error

.balign 0x80
current_el_sp0_serror:
    b error

.balign 0x80
current_el_spn_sync:
    b sync_handler

.balign 0x80
current_el_spn_irq:
    b irq_handler

.balign 0x80
current_el_spn_fiq:
    b error

.balign 0x80
current_el_spn_serror:
    b error

.balign 0x80
lower_el_aarch64_sync:
    b error

.balign 0x80
lower_el_aarch64_irq:
    b error

.balign 0x80
lower_el_aarch64_fiq:
    b error

.balign 0x80
lower_el_aarch64_serror:
    b error

.balign 0x80
lower_el_aarch32_sync:
    b error

.balign 0x80
lower_el_aarch32_irq:
    b error

.balign 0x80
lower_el_aarch32_fiq:
    b error

.balign 0x80
lower_el_aarch32_serror:
    b error


sync_handler:
    sub sp, sp, #(32 * 8)
    stp x0, x1, [sp]
    stp x2, x3, [sp, #(16 * 1)]
    stp x4, x5, [sp, #(16 * 2)]
    stp	x6, x7, [sp, #(16 * 3)]
	stp	x8, x9, [sp, #(16 * 4)]
	stp	x10, x11, [sp, #(16 * 5)]
	stp	x12, x13, [sp, #(16 * 6)]
	stp	x14, x15, [sp, #(16 * 7)]
	stp	x16, x17, [sp, #(16 * 8)]
	stp	x18, x19, [sp, #(16 * 9)]
	stp	x20, x21, [sp, #(16 * 10)]
	stp	x22, x23, [sp, #(16 * 11)]
	stp	x24, x25, [sp, #(16 * 12)]
	stp	x26, x27, [sp, #(16 * 13)]
	stp	x28, x29, [sp, #(16 * 14)]
    str x30, [sp, #(16 * 15)]

    mov x0, #1
    mrs x1, esr_el1
    mrs x2, elr_el1
    bl handler

    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #(16 * 1)]
    ldp x4, x5, [sp, #(16 * 2)]
    ldp	x6, x7, [sp, #(16 * 3)]
	ldp	x8, x9, [sp, #(16 * 4)]
	ldp	x10, x11, [sp, #(16 * 5)]
	ldp	x12, x13, [sp, #(16 * 6)]
	ldp	x14, x15, [sp, #(16 * 7)]
	ldp	x16, x17, [sp, #(16 * 8)]
	ldp	x18, x19, [sp, #(16 * 9)]
	ldp	x20, x21, [sp, #(16 * 10)]
	ldp	x22, x23, [sp, #(16 * 11)]
	ldp	x24, x25, [sp, #(16 * 12)]
	ldp	x26, x27, [sp, #(16 * 13)]
	ldp	x28, x29, [sp, #(16 * 14)]
    ldr x30, [sp, #(16 * 15)]

    add sp, sp, #(32 * 8)
    eret

irq_handler:
    sub sp, sp, #(32 * 8)
    stp x0, x1, [sp]
    stp x2, x3, [sp, #(16 * 1)]
    stp x4, x5, [sp, #(16 * 2)]
    stp	x6, x7, [sp, #(16 * 3)]
	stp	x8, x9, [sp, #(16 * 4)]
	stp	x10, x11, [sp, #(16 * 5)]
	stp	x12, x13, [sp, #(16 * 6)]
	stp	x14, x15, [sp, #(16 * 7)]
	stp	x16, x17, [sp, #(16 * 8)]
	stp	x18, x19, [sp, #(16 * 9)]
	stp	x20, x21, [sp, #(16 * 10)]
	stp	x22, x23, [sp, #(16 * 11)]
	stp	x24, x25, [sp, #(16 * 12)]
	stp	x26, x27, [sp, #(16 * 13)]
	stp	x28, x29, [sp, #(16 * 14)]
    str x30, [sp, #(16 * 15)]

    mov x0, #2
    mrs x1, esr_el1
    mrs x2, elr_el1
    bl handler

    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #(16 * 1)]
    ldp x4, x5, [sp, #(16 * 2)]
    ldp	x6, x7, [sp, #(16 * 3)]
	ldp	x8, x9, [sp, #(16 * 4)]
	ldp	x10, x11, [sp, #(16 * 5)]
	ldp	x12, x13, [sp, #(16 * 6)]
	ldp	x14, x15, [sp, #(16 * 7)]
	ldp	x16, x17, [sp, #(16 * 8)]
	ldp	x18, x19, [sp, #(16 * 9)]
	ldp	x20, x21, [sp, #(16 * 10)]
	ldp	x22, x23, [sp, #(16 * 11)]
	ldp	x24, x25, [sp, #(16 * 12)]
	ldp	x26, x27, [sp, #(16 * 13)]
	ldp	x28, x29, [sp, #(16 * 14)]
    ldr x30, [sp, #(16 * 15)]

    add sp, sp, #(32 * 8)
    eret

error:
    sub sp, sp, #(32 * 8)
    stp x0, x1, [sp]
    stp x2, x3, [sp, #(16 * 1)]
    stp x4, x5, [sp, #(16 * 2)]
    stp	x6, x7, [sp, #(16 * 3)]
	stp	x8, x9, [sp, #(16 * 4)]
	stp	x10, x11, [sp, #(16 * 5)]
	stp	x12, x13, [sp, #(16 * 6)]
	stp	x14, x15, [sp, #(16 * 7)]
	stp	x16, x17, [sp, #(16 * 8)]
	stp	x18, x19, [sp, #(16 * 9)]
	stp	x20, x21, [sp, #(16 * 10)]
	stp	x22, x23, [sp, #(16 * 11)]
	stp	x24, x25, [sp, #(16 * 12)]
	stp	x26, x27, [sp, #(16 * 13)]
	stp	x28, x29, [sp, #(16 * 14)]
    str x30, [sp, #(16 * 15)]

    mov x0, #0
    bl handler

    ldp x0, x1, [sp]
    ldp x2, x3, [sp, #(16 * 1)]
    ldp x4, x5, [sp, #(16 * 2)]
    ldp	x6, x7, [sp, #(16 * 3)]
	ldp	x8, x9, [sp, #(16 * 4)]
	ldp	x10, x11, [sp, #(16 * 5)]
	ldp	x12, x13, [sp, #(16 * 6)]
	ldp	x14, x15, [sp, #(16 * 7)]
	ldp	x16, x17, [sp, #(16 * 8)]
	ldp	x18, x19, [sp, #(16 * 9)]
	ldp	x20, x21, [sp, #(16 * 10)]
	ldp	x22, x23, [sp, #(16 * 11)]
	ldp	x24, x25, [sp, #(16 * 12)]
	ldp	x26, x27, [sp, #(16 * 13)]
	ldp	x28, x29, [sp, #(16 * 14)]
    ldr x30, [sp, #(16 * 15)]

    add sp, sp, #(32 * 8)
    eret
    
.global enable_irq
enable_irq:
    msr daifclr, #2
    ret

.global disable_irq
disable_irq:
	msr	daifset, #2
	ret
    