#ifndef _HELPER_H
#define _HELPER_H

#define NULL_DESCRIPTOR               0x0000000000000000
#define KERNEL_MODE_CODE_SEGMENT      0x00000000000FFFFF
#define KERNEL_MODE_DATA_SEGMENT      0x0000000000000000
#define USER_MODE_DATA_SEGMENT        0x0000000000000000
#define USER_MODE_CODE_SEGMENT        0x0000000000000000
#define TASK_STATE_SEGMENT            0x0000000000000000


///
/// FXSAVE_STATE.
/// FP / MMX / XMM registers (see fxrstor instruction definition).
///
struct fx_save_state_x64 {
  UINT16    fcw;
  UINT16    fsw;
  UINT16    ftw;
  UINT16    opcode;
  UINT64    rip;
  UINT64    data_offset;
  UINT8     reserved0[8];
  UINT8     st0Mm0[10];
  UINT8     reserved1[6];
  UINT8     st1_mm1[10];
  UINT8     reserved2[6];
  UINT8     st2_mm2[10];
  UINT8     reserved3[6];
  UINT8     st3Mm3[10];
  UINT8     reserved4[6];
  UINT8     st4Mm4[10];
  UINT8     reserved5[6];
  UINT8     st5Mm5[10];
  UINT8     reserved6[6];
  UINT8     st6Mm6[10];
  UINT8     reserved7[6];
  UINT8     st7Mm7[10];
  UINT8     reserved8[6];
  UINT8     xmm0[16];
  UINT8     xmm1[16];
  UINT8     xmm2[16];
  UINT8     xmm3[16];
  UINT8     xmm4[16];
  UINT8     xmm5[16];
  UINT8     xmm6[16];
  UINT8     xmm7[16];
  //
  // NOTE: UEFI 2.0 spec definition as follows.
  //
  UINT8     reserved9[14 * 16];
};

///
///  x64 processor context definition.
/// 
/*
* 47(79)                      16 15             0
* +-----------------------------|---------------+
* 32(64)-bit Linear Base Address| 16-Bit Table Limit
*/
struct desc_table_reg_x64 {
  UINT16 limit;
  UINT64 base;
};

typedef struct _system_context_x64 {
  UINT64 rax;
  UINT64 rbx;
  UINT64 rcx;
  UINT64 rdx;
  UINT64 rsi;
  UINT64 rdi;
  UINT64 rbp;
  UINT64 rsp;
  UINT64 r8;
  UINT64 r9;
  UINT64 r10;
  UINT64 r11;
  UINT64 r12;
  UINT64 r13;
  UINT64 r14;
  UINT64 r15;
  UINT64 rip;
  UINT64 rflags;
  UINT64 cs;
  UINT64 ss;
  UINT64 ds;
  UINT64 es;
  UINT64 fs;
  UINT64 gs;
  UINT64 fs_base;
  UINT64 gs_base;
  UINT64 tr;
  UINT64 ldt;
  UINT64 cs_access_rights;
  UINT64 ss_access_rights;
  UINT64 ds_access_rights;
  UINT64 es_access_rights;
  UINT64 fs_access_rights;
  UINT64 gs_access_rights;
  UINT64 cs_limit;
  UINT64 ss_limit;
  UINT64 ds_limit;
  UINT64 es_limit;
  UINT64 fs_limit;
  UINT64 gs_limit;
  UINT64 cr0;
  UINT64 cr2;
  UINT64 cr3;
  UINT64 cr4;
  UINT64 cr8;
  UINT64 efer;
  UINT64 dr0;
  UINT64 dr1;
  UINT64 dr2;
  UINT64 dr3;
  UINT64 dr6;
  UINT64 dr7;
  struct desc_table_reg_x64 gdtr;
  UINT64 idt_base;
  UINT64 idt_limit;
  struct fx_save_state_x64 fx_save_state;
  UINT64 exception_data;
  UINT64 cpu_count;
  UINT64 ap_entry_page;
  UINT64 un_cached;
} system_context_x64;

void EFIAPI init_cpu_snapshot(system_context_x64 *system_context);
UINTN get_cpu_count();

#endif
