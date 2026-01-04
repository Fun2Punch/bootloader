#ifndef _PAGING_H
#define _PAGING_H

BOOLEAN EFIAPI long_mode_enabled(void);
UINTN EFIAPI level4_paging(void);

UINT8 EFIAPI trans_linear_addr(IN UINTN cr3);

#endif
