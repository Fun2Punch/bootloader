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

void EFIAPI init_cpu_snapshot(system_context_x64 *system_context)
{
  ZeroMem(system_context, sizeof(system_context_x64));
  Print(L"Registers allocated = 0x%lx\r\n", system_context);

  system_context->cr0 = AsmReadCr0();
  system_context->cr2 = AsmReadCr2();
  system_context->cr3 = AsmReadCr3();
  system_context->cr4 = AsmReadCr4();
  system_context->dr7 = AsmReadDr7();
  system_context->cpu_count = get_cpu_count();
  system_context->efer = AsmReadMsr64(0xC0000080);



  Print(L"init current cpu state snapshot done!\n");
}
