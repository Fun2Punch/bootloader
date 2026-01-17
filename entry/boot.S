.intel_syntax noprefix

.section .text

.global _start
.global entry_vmm

.global __bss_start
.global __bss_end

_start:
        push rsp
        lea rsp, [rip + __stack_top]

        xor rax, rax
        mov rax, __bss_end
        sub rax, __bss_start

        mov rcx, rax
        xor rax, rax
        rep stosb

        jmp entry_vmm

        pop rsp

.att_syntax prefix
