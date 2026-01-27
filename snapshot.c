#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/MpService.h>

#include "include/snapshot.h"
#include "include/bits.h"

UINT64 EFIAPI get_cpu_count()
{
  EFI_MP_SERVICES_PROTOCOL *mp = NULL;
  UINT64 num_processor, num_enabled_processor;

  gBS->LocateProtocol(&gEfiMpServiceProtocolGuid, NULL, (void **)&mp);
  mp->GetNumberOfProcessors(mp, &num_processor, &num_enabled_processor);

  Print(L"cpu count done!\n");

  return num_enabled_processor;
}

system_registers_x64 EFIAPI init_cpu_snapshot()
{
  gBS->AllocatePool(EfiRuntimeServicesData, sizeof(system_registers_x64), (void **)&system_registers);
  if (EFI_ERROR(status)) {
    Print(L"system_context_x64 allocate failed = %r\r\n", status);
  }

  ZeroMem(system_registers, sizeof(system_registers_x64));

  Print(L"init current cpu state snapshot done!\n");
}
