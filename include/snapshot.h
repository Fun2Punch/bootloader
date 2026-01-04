#ifndef _HELPER_H
#define _HELPER_H

#include <Library/BaseLib.h>

#pragma pack(1)
typedef struct _x64_registers_state {
  UINT64    rax;
  UINT64    rbx;
  UINT64    rcx;
  UINT64    rdx;
  UINT64    rsi;
  UINT64    rdi;
  UINT64    rip;
  UINT64    rbp;
  UINT64    rsp;
  UINT64    r8;
  UINT64    r9;
  UINT64    r10;
  UINT64    r11;
  UINT64    r12;
  UINT64    r13;
  UINT64    r14;
  UINT64    r15;

  UINT64    cr0;
  UINT64    cr2;
  UINT64    cr3;
  UINT64    cr4;
  UINT64    dr7;

  UINT64    cpu_count;
  UINT64    efer;
  UINT64    lme;
  UINT64    idt_base;
  UINT64    idt_limit;
  UINT64    gdt_base;
  UINT64    gdt_limit;

  UINT64    rflags;
  UINT64    cs;
  UINT64    ss;
  UINT64    ds;
  UINT64    es;
  UINT64    fs;
  UINT64    gs;
  UINT64    tr;
  UINT64    ldt;

  UINT64    cs_access_rights;
  UINT64    ss_access_rights;
  UINT64    ds_access_rights;
  UINT64    es_access_rights;
  UINT64    fs_access_rights;
  UINT64    gs_access_rights;

  UINT64    cs_limit;
  UINT64    ss_limit;
  UINT64    ds_limit;
  UINT64    es_limit;
  UINT64    fs_limit;
  UINT64    gs_limit;

  UINT64    fs_base;
  UINT64    gs_base;
  UINT64    ap_entry_page; //Physical address in the lower 1MB memory used for AP bootup
  UINT64    un_cached;
} x64_registers_state;


/*
* 47(79)                      16 15             0
* +-----------------------------|---------------+
* 32(64)-bit Linear Base Address| 16-Bit Table Limit
*/

typedef struct _segments_desc {
  UINT64 segment_desc;
} segment_desc;

void init_gdt();

/*
PUBLIC get_cr0
PUBLIC get_cr2
PUBLIC get_cr3
PUBLIC get_cr4

;PUBLIC get_ss
;PUBLIC get_cs
;PUBLIC get_ds
;PUBLIC get_es
;PUBLIC get_fs
;PUBLIC get_gs

;PUBLIC get_gdt
;PUBLIC get_idt
;PUBLIC get_ldt
;PUBLIC get_tr

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

PUBLIC memset

.code

get_cr0 PROC
  mov rax, cr0
  ret
get_cr0 ENDP

get_cr2 PROC
  mov rax, cr2
  ret
get_cr2 ENDP

get_cr3 PROC
  mov rax, cr3
  ret
get_cr3 ENDP

get_cr4 PROC
  mov rax, cr4
  ret
get_cr4 ENDP

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

memset PROC
  cld
  xor eax, eax
  mov rcx, rdx
  rep stosb
memset ENDP


END


*/

//extern void init_cpu_state(x64_registers_state *registers);
//extern UINT64 memset(OUT x64_registers_state *registers);
//
//extern UINT64 get_cr0(void);
//extern UINT64 get_cr2(void);
//extern UINT64 get_cr3(void);
//extern UINT64 get_cr4(void);
//
//extern UINT16 get_ss(void);
//extern UINT16 get_cs(void);
//extern UINT16 get_ds(void);
//extern UINT16 get_es(void);
//extern UINT16 get_fs(void);
//extern UINT16 get_gs(void);
//
//extern UINT16 get_gdt(void);
//extern UINT16 get_idt(void);
//extern UINT16 get_ldt(void);
//extern UINT16 get_tr(void);
//
//extern UINT64 get_rax(void);
//extern UINT64 get_rbx(void);
//extern UINT64 get_rcx(void);
//extern UINT64 get_rdx(void);
//extern UINT64 get_rsp(void);
//extern UINT64 get_rbp(void);
//extern UINT64 get_rsi(void);
//extern UINT64 get_rdi(void);
//
//extern UINT64 get_r8(void);
//extern UINT64 get_r9(void);
//extern UINT64 get_r10(void);
//extern UINT64 get_r11(void);
//extern UINT64 get_r12(void);
//extern UINT64 get_r13(void);
//extern UINT64 get_r14(void);
//extern UINT64 get_r15(void);

#endif
