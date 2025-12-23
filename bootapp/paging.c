#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "include/Library/paging.h"
#include "x86/include/asm/bits.h"

UINT8 EFIAPI trans_linear_addr(IN UINTN *entry)
{
  Print(L"Directory Pointer = 0x%x\r\n", entry[0]);
  Print(L"Page Directory    = 0x%x\r\n", entry[1]);

}

BOOLEAN EFIAPI long_mode_enabled(void)
{
  UINT64 efer;

  efer = AsmReadMsr64(0xC0000080);
  Print(L"efer = %x\r\n", efer);
  if ((efer & 0x500) != 0x500) {
    return 0;
  }

  return 1;
}

// R0.PG = 1, CR4.PAE = 1, IA32_EFER.LME = 1, and //////////////////// CR4.LA57 = 0. 5 - level paging
UINTN EFIAPI level4_paging(void)
{
  UINTN cr0, cr4, and_mask;
  BOOLEAN long_mode;

  cr0 = AsmReadCr0();
  cr4 = AsmReadCr4();

  long_mode = long_mode_enabled();
  if (!long_mode) {
    Print(L"long mode disabled\r\n");
    return 0;
  }

  Print(L"CR0 = 0x%x\r\n", cr0);
  and_mask = _BIT_LEFT(31);
  if ((cr0 & and_mask) == 0) {
    Print(L"CR0.PG = 0\r\n");
    return 0;
  } else {
    Print(L"CR0.PG = 1\r\n");
  }

  Print(L"CR4 = 0x%x\r\n", cr4);
  and_mask = _BIT_LEFT(5);
  if ((cr4 & and_mask) == 0) {
    Print(L"CR4.PAE = 0\r\n");
    return 0;
  } else {
    Print(L"CR4.PAE = 1\r\n");
  }

  and_mask = _BIT_LEFT(12);
  if ((cr4 & and_mask) == 1) {
    Print(L"CR4.LA57 = 1\r\n");
    return 0;
  } else {
    Print(L"CR4.LA57 = 0\r\n");
  }

  return 1;
}
