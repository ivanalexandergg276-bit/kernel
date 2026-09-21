/*
 * openKRN - Linker Script
 * Copyright (C) 2026 Reliable Kernel Corp.
 */

ENTRY(start)

SECTIONS
{
    /* Los kernels de 32 bits tradicionales suelen arrancar en la dirección 1 Megabyte */
    . = 1M;

    .text : {
        *(.multiboot)
        *(.text)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}