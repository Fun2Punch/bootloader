#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/LoadedImage.h>

#include "include/bootloader.h"
#include "include/paging.h"
#include "include/fs.h"

#include "include/snapshot.h"
#include "include/bits.h"

// xor eax, eax | mov eax, cr0 | and eax, 0x7FFFFFFF | cmp eax, 1 je PagingOn(function addr)

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table)
{
  gST = system_table;
  gBS = system_table->BootServices;
}

EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS status;
  UINTN paging;
  EFI_PHYSICAL_ADDRESS *hypervisor_image = NULL;
  x64_registers_state *registers = NULL;

  init_system_table(SystemTable);
  paging = level4_paging();
  if (paging) {
    Print(L"Level4 paging enabled\r\n");
  }

  status = gBS->AllocatePool(EfiRuntimeServicesCode, 1024, (void**) & hypervisor_image);
  if (EFI_ERROR(status)) {
    Print(L"Failed to AllocatePool for Hypervisor image = %r\r\n", status);
  }

  status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(x64_registers_state), (void**) & registers);
  init_cpu_snapshot(registers);

  return EFI_SUCCESS;
}
