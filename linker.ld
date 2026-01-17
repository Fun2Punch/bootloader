ENTRY(_start)

PHDRS {
    text PT_LOAD FLAGS(5);
    data PT_LOAD FLAGS(6);
}

SECTIONS
{
    /* load address */
    base = 0x100000;

    .text : {
        *(.text*)
    } :text

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    } :data

    .bss : {
        __bss_start = base;
        *(COMMON)
        *(.bss*)
        __bss_end = base;
    }

    .stack (NOLOAD) : {
        __stack_botoom = base;
        base = base + 0x8000;
        __stack_top = base;
    }
}

