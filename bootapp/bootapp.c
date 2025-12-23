#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "include/library/bootapp.h"

// xor eax, eax | mov eax, cr0 | and eax, 0x7FFFFFFF | cmp eax, 1 je PagingOn(function addr)

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table)
{
  gST = system_table;
  gBS = system_table->BootServices;
}

EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  UINTN paging;

  init_system_table(SystemTable);
  paging = level4_paging();
  if (paging) {
    Print(L"Level4 paging enabled\r\n");
  }

  return EFI_SUCCESS;
}
