#include "mmu.h"
#include "mm/mm.h"
#include "sysregs.h"
#include "base.h"
//#include "kernel"

.section .initsys.start
// .section ".text.boot"  // Make sure the linker puts this at the start of the kernel image

.global _start  // Execution starts here
_start:
    // Check processor ID is zero (executing on main core), else hang
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cmp     x1, #0
    beq     kernel_entry
    
    // We're not on the main core, so hang in an infinite wait loop
end:  
    wfe
    bl       end

kernel_entry:  // We're on the main core!

    // Swith to EL1
    mrs x0, CurrentEL
    lsr x0, x0, #2              // Getting current level -> shifting by 2
    cmp x0, #2                  // compare it with 2
    bne end

    msr sctlr_el1, xzr
    mov x0, #(1<<31)
    msr hcr_el2, x0

    mov x0, 0b1111000101
    msr spsr_el2, x0

    adr x0, el1_entry
    msr elr_el2, x0

    eret

el1_entry:
    // Set stack to start below our code
    ldr     x1, =_start
    mov     sp, x1

    bl     =main

    // Clean the BSS section
    ldr     x1, =__bss_start     // Start address
    ldr     x2, =__bss_size      // Size of the section
3:  cbz     w2, 4f               // Quit loop if zero
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b               // Loop if non-zero

    //ldr x0, =vector_table
    //msr vbar_el1, x0
4:  ldr     x1, =irq_vector_init
    br      x1

    // Jump to our main() routine in C (make sure it doesn't return)
    ldr     x1, =main
    br      x1
    // In case it does return, halt the master core too
    bl       end

    .macro	create_pgd_entry, tbl, virt, tmp1, tmp2
	create_table_entry \tbl, \virt, PGD_SHIFT, \tmp1, \tmp2
	create_table_entry \tbl, \virt, PUD_SHIFT, \tmp1, \tmp2
	.endm

	.macro	create_table_entry, tbl, virt, shift, tmp1, tmp2
	lsr	\tmp1, \virt, #\shift
	and	\tmp1, \tmp1, #PTRS_PER_TABLE - 1			// table index
	add	\tmp2, \tbl, #PAGE_SIZE
	orr	\tmp2, \tmp2, #MM_TYPE_PAGE_TABLE	
	str	\tmp2, [\tbl, \tmp1, lsl #3]
	add	\tbl, \tbl, #PAGE_SIZE					// next level table page
	.endm

	.macro	create_block_map, tbl, phys, start, end, flags, tmp1
	lsr	\start, \start, #SECTION_SHIFT
	and	\start, \start, #PTRS_PER_TABLE - 1			// table index
	lsr	\end, \end, #SECTION_SHIFT
	and	\end, \end, #PTRS_PER_TABLE - 1				// table end index
	lsr	\phys, \phys, #SECTION_SHIFT
	mov	\tmp1, #\flags
	orr	\phys, \tmp1, \phys, lsl #SECTION_SHIFT			// table entry
9999:	str	\phys, [\tbl, \start, lsl #3]				// store the entry
	add	\start, \start, #1					// next entry
	add	\phys, \phys, #SECTION_SIZE				// next block
	cmp	\start, \end
	b.ls	9999b
	.endm

/*
__create_page_tables:
	mov	x29, x30						// save return address

	adrp	x0, pg_dir
	mov	    x1, #PG_DIR_SIZE
	// bl 	memzero
6:  cbz     w2, 7f               // Quit loop if zero
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 6b               // Loop if non-zero

7:	adrp	x0, pg_dir
	mov	x1, #VA_START 
	create_pgd_entry x0, x1, x2, x3

	/* Mapping kernel and init stack *\/
	mov 	x1, xzr							// start mapping from physical offset 0
	mov 	x2, #VA_START						// first virtual address
	ldr	x3, =(VA_START + DEVICE_BASE - SECTION_SIZE)		// last virtual address
	create_block_map x0, x1, x2, x3, MMU_FLAGS, x4

	/* Mapping device memory*\/
	mov 	x1, #DEVICE_BASE					// start mapping from device base address 
	ldr 	x2, =(VA_START + DEVICE_BASE)				// first virtual address
	ldr	x3, =(VA_START + PHYS_MEMORY_SIZE - SECTION_SIZE)	// last virtual address
	create_block_map x0, x1, x2, x3, MMU_DEVICE_FLAGS, x4

	mov	x30, x29						// restore return address
	ret

.section .initsys.data
data:
    b   data */
