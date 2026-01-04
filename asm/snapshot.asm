PUBLIC get_rax
PUBLIC get_rbx
PUBLIC get_rcx
PUBLIC get_rdx
PUBLIC get_rsp
PUBLIC get_rbp
PUBLIC get_rsi
PUBLIC get_rdi

PUBLIC get_r8
PUBLIC get_r9
PUBLIC get_r10
PUBLIC get_r11
PUBLIC get_r12
PUBLIC get_r13
PUBLIC get_r14
PUBLIC get_r15

.code

get_rax PROC
  ret
get_rax ENDP

get_rbx PROC
  mov rax, rbx
  ret
get_rbx ENDP

get_rcx PROC
  mov rax, rcx
  ret
get_rcx ENDP

get_rdx PROC
  mov rax, rdx
  ret
get_rdx ENDP

get_rsp PROC
  mov rax, rsp
  ret
get_rsp ENDP

get_rbp PROC
  mov rax, rbp
  ret
get_rbp ENDP

get_rdi PROC
  mov rax, rdi
  ret
get_rdi ENDP

get_rsi PROC
  mov rax, rsi
  ret
get_rsi ENDP

get_r8 PROC
  mov rax, r8
  ret
get_r8 ENDP

get_r9 PROC
  mov rax, r9
  ret
get_r9 ENDP

get_r10 PROC
  mov rax, r10
  ret
get_r10 ENDP

get_r11 PROC
  mov rax, r11
  ret
get_r11 ENDP

get_r12 PROC
  mov rax, r12
  ret
get_r12 ENDP

get_r13 PROC
  mov rax, r13
  ret
get_r13 ENDP

get_r14 PROC
  mov rax, r14
  ret
get_r14 ENDP

get_r15 PROC
  mov rax, r15
  ret
get_r15 ENDP

END
