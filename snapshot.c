#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/SimpleFileSystem.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/MpService.h>

#include "snapshot.h"
#include "bits.h"
#include "memory.h"

#include "helper.h"

UINT64 EFIAPI get_cpu_count()
{
  EFI_MP_SERVICES_PROTOCOL *mp = NULL;
  UINT64 num_processor, num_enabled_processor;

  gBS->LocateProtocol(&gEfiMpServiceProtocolGuid, NULL, (void **)&mp);
  mp->GetNumberOfProcessors(mp, &num_processor, &num_enabled_processor);

  Print(L"cpu count done!\n");

  return num_enabled_processor;
}

struct system_regs_x64 EFIAPI *init_cpu_snapshot()
{
  EFI_STATUS status;
  struct system_regs_x64 *registers;

  status = gBS->AllocatePool(EfiRuntimeServicesData, sizeof(struct system_regs_x64), (void **)&registers);
  if (EFI_ERROR(status)) {
    Print(L"system_registers_x64 allocate failed = %r\r\n", status);
  }

  ZeroMem(registers, sizeof(struct system_regs_x64));

  paging_mode(registers);

  Print(L"init current cpu state snapshot done!\n");

  return registers;
}

void EFIAPI current_registers_snapshot(struct system_regs_x64 *registers)
{
  registers->cr0 = AsmReadCr0();
  registers->cr3 = AsmReadCr3();
  registers->cr4 = AsmReadCr4();
  registers->efer = AsmReadMsr64(0xC0000080);
}
