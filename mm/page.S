.intel_syntax noprefix

.global memset

.section .text

memset:
        cld
        mov rdi, rdx
        xor rax, rax
        mov rcx, 512
        rep stosq


.att_syntax prefix
