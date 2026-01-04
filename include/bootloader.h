#ifndef __BOOT_LOADER_H__
#define __BOOT_LOADER_H__

#include "snapshot.h"

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


#endif
