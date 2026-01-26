#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/LoadedImage.h>

#include "include/bootloader.h"
#include "include/memory.h"

#include "include/snapshot.h"
#include "include/bits.h"

// xor eax, eax | mov eax, cr0 | and eax, 0x7FFFFFFF | cmp eax, 1 je PagingOn(function addr)

EFI_FILE_PROTOCOL *init_fs(IN EFI_HANDLE image_handle)
{
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_fs = NULL;
  EFI_LOADED_IMAGE_PROTOCOL *loaded_img = NULL;
  EFI_FILE_PROTOCOL *root = NULL;
  EFI_STATUS status;

  status = gBS->HandleProtocol(image_handle, &gEfiLoadedImageProtocolGuid, (void**) & loaded_img);
  if (EFI_ERROR(status)) {
    Print(L"Failed to HandleProtocol = %r\r\n", status);
  }

  status = gBS->HandleProtocol(loaded_img->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**) & simple_fs);
  if (EFI_ERROR(status)) {
    Print(L"Failed to Simple file system protocol = %r\r\n", status);
  }

  status = simple_fs->OpenVolume(simple_fs, &root);
  if (EFI_ERROR(status)) {
    Print(L"Faild to OpenVolume = %r\r\n", status);
  }

  return root;
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
  // UINTN map_key;
  UINTN paging;
  EFI_PHYSICAL_ADDRESS *hypervisor_image;
  x64_registers_state *registers;
  EFI_FILE_PROTOCOL *root;
  CHAR16 *img_name = L"vmm.img";

  paging = paging_mode();
  if (paging) {
    Print(L"paging enabled\r\n");
  }

  gBS->AllocatePool(EfiRuntimeServicesCode, 4096, (void **)&hypervisor_image);

  gBS->AllocatePool(EfiRuntimeServicesData, sizeof(x64_registers_state), (void **)&registers);

  init_cpu_snapshot(registers);
  save_memory_map();

  root = init_fs(image_handle);
  load_img(root, img_name);
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
