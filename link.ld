MEMORY {
    initsys_base : ORIGIN = 0x80000, LENGTH = 0x10000
    kernel : ORIGIN = 0xFF000000, LENGTH = 0x1000000
}

SECTIONS
{
    .initsys :
    {
        *(.initsys.start*)
        *(.initsys*)
    } > initsys_base
    
    .initsys.data :
    {
        *(.initsys.data*)
    } > initsys_base

    __kernel_high_code = ALIGN(4k);
	_virt_code_start = 0xFF000000;

	/* KERNEL - sekce pro jaderny kod a data; zacatek zarovnany na nasobek 4k */

    .text (__kernel_high_code + _virt_code_start) : AT(__kernel_high_code)
	{
		*(.text*)
	} > kernel

	.rodata : {
		*(.rodata*)
	} > kernel

	.data : {
		*(.data .data.*)
	} > kernel

    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    } > kernel

    
    .pg_dir : {
        . = ALIGN(16);
        pg_dir = .;
    } > kernel 

    /* . = 0x80000;     /* Kernel load address for AArch64 *\/
    .text : { KEEP(*(.text.boot)) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    PROVIDE(_data = .);
    .data : { *(.data .data.*) }
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }
    _end = .; */

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start)>>3;