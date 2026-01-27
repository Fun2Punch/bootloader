#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/LoadedImage.h>

#include "bootloader.h"
#include "memory.h"

#include "snapshot.h"
#include "bits.h"

// xor eax, eax | mov eax, cr0 | and eax, 0x7FFFFFFF | cmp eax, 1 je PagingOn(function addr)

void EFIAPI *init_fs(IN EFI_HANDLE image_handle, file_system *fs)
{
  EFI_STATUS status;

  status = gBS->AllocatePool(EfiBootServicesData, sizeof(file_system), (void **)&fs);
  if (EFI_ERROR(status)) {
    Print(L"failed file_system allocete = %r\r\n", status);
  }

  status = gBS->HandleProtocol(image_handle, &gEfiLoadedImageProtocolGuid, (void**) & fs->loaded_img);
  if (EFI_ERROR(status)) {
    Print(L"failed to HandleProtocol = %r\r\n", status);
  }

  status = gBS->HandleProtocol(loaded_img->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**) & fs->simple_fs);
  if (EFI_ERROR(status)) {
    Print(L"failed to Simple file system protocol = %r\r\n", status);
  }

  status = simple_fs->OpenVolume(simple_fs, &fs->root);
  if (EFI_ERROR(status)) {
    Print(L"failed to OpenVolume = %r\r\n", status);
  }
}

EFI_STATUS EFIAPI load_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name)
{
  EFI_STATUS status = EFI_SUCCESS;
  EFI_FILE_PROTOCOL *vm_img;
  UINTN buf_size, *vm_img_buf = NULL;

  status = root->Open(root, &vm_img, img_name, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
  if (EFI_ERROR(status)) {
    Print(L"Failed to root fs open = %r\r\n", status);
    status = EFI_NOT_FOUND;
    goto failed_status;
  }

  buf_size = 4096;
  vm_img->SetPosition(vm_img, 0);
  status = vm_img->Read(vm_img, &buf_size, vm_img_buf);
  if (EFI_ERROR(status)) {
    Print(L"Failed to vm image read = %r\r\n", status);
    goto failed_status;
  }

  status = EFI_SUCCESS;

failed_status:
  return status;
}

void EFIAPI start_bootloader(EFI_HANDLE image_handle)
{
  EFI_STATUS status;
  file_system *fs;
  EFI_PHYSICAL_ADDRESS phy_addr;
  system_registers_x64 system_registers;

  if (paging_mode()) {
    Print(L"paging enabled\r\n");
  }

  status = gBS->AllocatePages(AllocateAnyPages, EfiRuntimeServicesData, 2, &phy_addr);
  if (EFI_ERROR(status)) {
    Print(L"Failed AllocatePages = %r\r\n", status);
  }

  system_registers = init_cpu_snapshot();
}


void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table)
{
  gST = system_table;
  gBS = system_table->BootServices;
}

EFI_STATUS EFIAPI efi_main(IN EFI_HANDLE image_handle, IN EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status = EFI_SUCCESS;

  init_system_table(system_table);
  start_bootloader(image_handle);

  return status;
}
