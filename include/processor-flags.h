#ifndef _PROCESSOR_FLAGS_H
#define _PROCESSOR_FLAGS_H

#include <include/bits.h>

// EFLAGS REGISTER
#define X86_EFLAGS_CF_BIT          0 /* Carry Flag */
#define X86_EFLAGS_CF              _BIT_LEFT(X86_EFLAGS_CF_BIT)
#define X86_EFLAGS_FIXED_BIT       1
#define X86_EFLAGS_FIXED           _BIT_LEFT(X86_EFLAGS_FIXED_BIT)
#define X86_EFLAGS_PF_BIT          2
#define X86_EFLAGS_PF              _BIT_LEFT(X86_EFLAGS_PF_BIT)
#define X86_EFLAGS_AF_BIT          4
#define X86_EFLAGS_AF              _BIT_LEFT(X86_EFLAGS_AF_BIT)
#define X86_EFLAGS_ZF_BIT          6
#define X86_EFLAGS_ZF              _BIT_LEFT(X86_EFLAGS_ZF_BIT)
#define X86_EFLAGS_SF_BIT          7
#define X86_EFLAGS_SF              _BIT_LEFT(X86_EFLAGS_SF_BIT)
#define X86_EFLAGS_TF_BIT          8
#define X86_EFLAGS_TF              _BIT_LEFT(X86_EFLAGS_TF_BIT)
#define X86_EFLAGS_IF_BIT          9
#define X86_EFLAGS_IF              _BIT_LEFT(X86_EFLAGS_IF_BIT)
#define X86_EFLAGS_DF_BIT          10
#define X86_EFLAGS_DF              _BIT_LEFT(X86_EFLAGS_DF_BIT)
#define X86_EFLAGS_OF_BIT          11
#define X86_EFLAGS_OF              _BIT_LEFT(X86_EFLAGS_OF_BIT)
#define X86_EFLAGS_IOPL_BIT        12
//#define X86_EFLAGS_IOPL            _

#endif
