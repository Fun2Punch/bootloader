#ifndef __SNAP_SHOT_H__
#define __SNAP_SHOT_H__

// Intel x64 General purpose registers.
struct general_registers {
  unsigned long rax;
  unsigned long rbx;
  unsigned long rcx;
  unsigned long rdx;
  unsigned long rdi;
  unsigned long rsi;
  unsigned long rbp;
  unsigned long rsp;
  unsigned long r8;
  unsigned long r9;
  unsigned long r10;
  unsigned long r11;
  unsigned long r12;
  unsigned long r13;
  unsigned long r14;
  unsigned long r15;
};

// Intel x64 Segment registers
struct segment_registers {
  unsigned long cs;
  unsigned long ds;
  unsigned long es;
  unsigned long ss;
  unsigned long fs;
  unsigned long gs;
};

struct status_flags {
  unsigned char cf;
  unsigned char pf;
  unsigned char af;
  unsigned char zf;
  unsigned char sf;
  unsigned char of;
};

/*
* 47(79)                      16 15             0
* +-----------------------------|---------------+
* 32(64)-bit Linear Base Address| 16-Bit Table Limit
*/

#pragma pack(2) // Alignment of 2bytes
struct gdtr {
  unsigned short limit;
  unsigned long long base_addr;
};
#pragma pack()

#endif
