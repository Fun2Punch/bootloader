#ifndef _PAGING_H
#define _PAGING_H

typedef struct _memory_map {
  UINT32               type;
  EFI_PHYSICAL_ADDRESS physical_addr_start;
  EFI_VIRTUAL_ADDRESS  virtual_addr_start;
  UINT64               pages_num;
  UINT64               attribute;
} custom_memory_map;

typedef struct _pml4_table {
  unsigned char p;
} pml4_table;

BOOLEAN EFIAPI long_mode_enabled(UINTN cr0, UINTN cr4);
UINTN EFIAPI level4_paging(void);

UINTN EFIAPI save_memory_map(void);

UINT8 EFIAPI trans_linear_addr(IN UINTN cr3);

#endif
