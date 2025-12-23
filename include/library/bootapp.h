#ifndef __BOOTAPP_H__
#define __BOOTAPP_H__

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


#endif
