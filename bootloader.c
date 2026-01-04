#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/MpService.h>

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

void EFIAPI init_cpu_snapshot(x64_registers_state *registers)
{
  ZeroMem(registers, sizeof(x64_registers_state));
  Print(L"Registers allocated = 0x%lx\r\n", registers);

  registers->cr0 = AsmReadCr0();
  registers->cr2 = AsmReadCr2();
  registers->cr3 = AsmReadCr3();
  registers->cr4 = AsmReadCr4();
  registers->dr7 = AsmReadDr7();
  registers->cpu_count = get_cpu_count();
  registers->efer = AsmReadMsr64(0xC0000080);
  registers->lme = registers->efer & (_BIT_LEFT(3));
}

UINT64 EFIAPI get_cpu_count()
{
  EFI_MP_SERVICES_PROTOCOL *mp = NULL;
  UINT64 num_processor, num_enabled_processor;

  gBS->LocateProtocol(&gEfiMpServiceProtocolGuid, NULL, (void**)&mp);
  mp->GetNumberOfProcessors(mp, &num_processor, &num_enabled_processor);

  return num_enabled_processor;
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

  status = gBS->AllocatePool(EfiRuntimeServicesCode, 1024, (void**)&hypervisor_image);
  if (EFI_ERROR(status)) {
    Print(L"Failed to AllocatePool for Hypervisor image = %r\r\n", status);
  }

  status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(x64_registers_state), (void**)&registers);
  init_cpu_snapshot(registers);

  return EFI_SUCCESS;
}
