.intel_syntax noprefix

.section .text

.global _start

_start:
        hlt
        nop
        jmp entry_vmm

.att_syntax prefix
