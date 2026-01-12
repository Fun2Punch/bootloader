#ifndef __BOOT_LOADER_H__
#define __BOOT_LOADER_H__

#include "snapshot.h"

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE image_handle, IN EFI_SYSTEM_TABLE *system_table);
EFI_STATUS EFIAPI start_bootloader(EFI_HANDLE image_handle);

EFI_FILE_PROTOCOL *init_fs(IN EFI_HANDLE image_handle);
EFI_STATUS EFIAPI load_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name);


#endif
