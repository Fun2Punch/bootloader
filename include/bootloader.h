#ifndef _BOOTLOADER_H
#define _BOOTLOADER_H

#include "snapshot.h"

void EFIAPI init_cpu_snapshot(x64_registers_state *registers);
UINT64 EFIAPI get_cpu_count();

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


#endif
