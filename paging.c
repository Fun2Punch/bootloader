#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Library/BaseMemoryLib.h>

#include "include/paging.h"
#include "include/bits.h"

UINT8 EFIAPI trans_linear_addr(IN UINTN cr3)
{
  UINTN pml4;
  Print(L"cr3 = 0x%lx\r\n", cr3);

  pml4 = cr3 & 0x000FFFFFFFFFF000;
  Print(L"PML4 = 0x%lx\r\n", pml4);

  return 0;
}

BOOLEAN EFIAPI long_mode_enabled(UINTN cr0, UINTN cr4)
{
  UINT64 efer;
  BOOLEAN status;

  efer = AsmReadMsr64(0xC0000080);
  status = 0;

  if ((efer & BIT8) == 0 && (efer & BIT10) == 0) {
    goto long_mode_disabled;
  }

  if ((cr0 & BIT31) == 0 && (cr4 & BIT5) == 0) {
    goto long_mode_disabled;
  }

  status = 1;
long_mode_disabled:
  return status;
}

// R0.PG = 1, CR4.PAE = 1, IA32_EFER.LME = 1, and //////////////////// CR4.LA57 = 0. 5 - level paging
UINTN EFIAPI paging_mode(void)
{
  UINTN status, cr0, cr4, and_mask;
  BOOLEAN long_mode;

  status = 0;
  and_mask = 0;
  cr0 = AsmReadCr0();
  cr4 = AsmReadCr4();

  Print(L"CR4 = 0x%llu\r\n", cr4);
  long_mode = long_mode_enabled(cr0, cr4);
  if (long_mode) {
    Print(L"long mode enabled\n");
  } else {
                    Print(L"level4 paging disabled, long mode disabled\n");
    goto disabled_level4;
  }

  if ((cr4 & BIT12) == 0) {
    Print(L"CR4.LA57 = 0\r\n");
  } else {
    Print(L"level5 enabled, CR4.LA57 = 1\r\n");
  }

  if ((cr4 & BIT17)) {
    Print(L"level4 enabled, CR4.PCIDE = 1\r\n");
  } else {
    Print(L"level5 enabled, CR4.PCIDE = 0\n");
  }

  status = 1;
disabled_level4:
  return status;
}

UINTN EFIAPI save_memory_map(void)
{
  EFI_MEMORY_DESCRIPTOR *memory_desc = NULL;
  custom_memory_map *memory_map = NULL;
  UINTN map_size, map_key, desc_size;
  UINT32 desc_version;

  gBS->AllocatePool(EfiRuntimeServicesCode, sizeof(custom_memory_map), (void **)&memory_map);

  map_size = 0;
  map_key = 0;
  desc_size = sizeof(EFI_MEMORY_DESCRIPTOR);
  ZeroMem(memory_map, sizeof(custom_memory_map));
  desc_version = 0;

  gBS->GetMemoryMap(&map_size, NULL, &map_key, &desc_size, &desc_version);
  gBS->AllocatePool(EfiLoaderCode, map_size, (void **)&memory_desc);
  gBS->GetMemoryMap(&map_size, memory_desc, &map_key, &desc_size, &desc_version);

  Print(L"map_size = %llu, map_key = %llu, desc_size = %llu\n", map_size, map_key, desc_size);
  Print(L"PhysicalAddress = 0x%lx\n", memory_desc->PhysicalStart);
  Print(L"VirtualStart = 0x%lx\n", memory_desc->VirtualStart);
  Print(L"NumberOfPages = 0x%lx\n", memory_desc->NumberOfPages);
  Print(L"Attribute = %llu\n", memory_desc->Attribute);

  return map_key;
}
