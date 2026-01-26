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



  Print(L"init current cpu state snapshot done!\n");
}

void init_gdt()
{
  

  
}
