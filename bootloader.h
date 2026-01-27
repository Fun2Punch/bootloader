#ifndef __BOOT_LOADER_H__
#define __BOOT_LOADER_H__

#include "snapshot.h"

typedef struct _file_system {
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_fs;
  EFI_LOADED_IMAGE_PROTOCOL *loaded_img;
  EFI_FILE_PROTOCOL *root;
  CHAR16 *vmm_name;
} file_system;

typedef struct _system_management {
  system_architecture_x64 x64_system;
  file_system fs;
} system_management;

void EFIAPI start_bootloader(EFI_HANDLE image_handle);

void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE image_handle, IN EFI_SYSTEM_TABLE *system_table);

void EFIAPI *init_fs(IN EFI_HANDLE image_handle, file_system *fs);
void free_fs(file_system *fs);
EFI_STATUS EFIAPI load_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name);


#endif
