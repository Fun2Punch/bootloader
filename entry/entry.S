;this is entry code for start vmm
.intel_syntax noprefix

.section .text

.global entry

entry:
        hlt
        nop
        ret

.att_syntax prefix
