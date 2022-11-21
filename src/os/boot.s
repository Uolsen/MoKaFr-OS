.section ".text.boot"  // Make sure the linker puts this at the start of the kernel image

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

    // Clean the BSS section
    ldr     x1, =__bss_start     // Start address
    ldr     w2, =__bss_size      // Size of the section
3:  cbz     w2, 4f               // Quit loop if zero
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b               // Loop if non-zero

    ldr x0, =vector_table
    msr vbar_el1, x0

    // Jump to our main() routine in C (make sure it doesn't return)
4:  bl      main
    // In case it does return, halt the master core too
    bl       end