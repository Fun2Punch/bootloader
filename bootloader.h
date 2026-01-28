#ifndef __BOOT_LOADER_H__
#define __BOOT_LOADER_H__

#include "snapshot.h"

struct system_regs_x64;

struct file_system {
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_fs;
  EFI_LOADED_IMAGE_PROTOCOL *loaded_img;
  EFI_FILE_PROTOCOL *root;
  CHAR16 *vmm_name;
};

struct system_management {
  struct system_regs_x64 *registers;
  struct file_system fs;
};

struct system_settings {
  struct system_regs_x64 (EFIAPI *get_current_regs)(void);
};

EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE image_handle, IN EFI_SYSTEM_TABLE *system_table);
void EFIAPI start_bootloader(EFI_HANDLE image_handle);

// initialize
void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
void EFIAPI init_fs(IN EFI_HANDLE image_handle, struct file_system *fs);
void EFIAPI init_settings(OUT struct system_settings *setting);
struct system_management EFIAPI *init_system_management();

struct system_regs_x64 EFIAPI current_regs();

EFI_STATUS EFIAPI load_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name);

EFI_PHYSICAL_ADDRESS EFIAPI alloc_vmm();

#endif