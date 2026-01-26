.intel_syntax noprefix

.global set_new_gdt

set_new_gdt:
        
        push rax
        retfq
