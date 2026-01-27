#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Library/BaseMemoryLib.h>
#include <Include/Protocol/DebugSupport.h>

#include "memory.h"
#include "bits.h"

#include "snapshot.h"

UINT8 EFIAPI trans_linear_addr(IN UINTN cr3)
{
  UINTN pml4;
  Print(L"cr3 = 0x%lx\r\n", cr3);

  pml4 = cr3 & 0x000FFFFFFFFFF000;
  Print(L"PML4 = 0x%lx\r\n", pml4);

  return 0;
}

// R0.PG = 1, CR4.PAE = 1, IA32_EFER.LME = 1, and //////////////////// CR4.LA57 = 0. 5 - level paging
void EFIAPI paging_mode(struct system_regs_x64 *registers)
{
  current_registers_snapshot(registers);
}

UINTN EFIAPI save_memory_map(void)
{
  EFI_MEMORY_DESCRIPTOR *memory_desc = NULL;
  vmm_memory_map *memory_map = NULL;
  UINTN map_size, map_key, desc_size;
  UINT32 desc_version;

  gBS->AllocatePool(EfiRuntimeServicesCode, sizeof(vmm_memory_map), (void **)&memory_map);

  map_size = 0;
  map_key = 0;
  desc_size = sizeof(EFI_MEMORY_DESCRIPTOR);
  ZeroMem(memory_map, sizeof(vmm_memory_map));
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
