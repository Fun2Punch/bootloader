#ifndef __BOOT_LOADER_H__
#define __BOOT_LOADER_H__

#include "snapshot.h"

struct system_regs_x64;

struct system_settings {
  struct system_regs_x64 (EFIAPI *get_current_regs)(void);
};

EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE image_handle, IN EFI_SYSTEM_TABLE *system_table);
void EFIAPI start_bootloader(EFI_HANDLE image_handle);

struct system_regs_x64 EFIAPI current_regs(void);

EFI_STATUS EFIAPI load_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name);

EFI_PHYSICAL_ADDRESS EFIAPI alloc_vmm(void);

#endif
