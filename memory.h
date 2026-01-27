#ifndef _PAGING_H
#define _PAGING_H

typedef struct _memory_map {
  UINT32               type;
  EFI_PHYSICAL_ADDRESS physical_addr_start;
  EFI_VIRTUAL_ADDRESS  virtual_addr_start;
  UINT64               pages_num;
  UINT64               attribute;
} vmm_memory_map;

EFI_STATUS EFIAPI paging_mode(void);
UINTN EFIAPI save_memory_map(void);
UINT8 EFIAPI trans_linear_addr(IN UINTN cr3);

#endif
