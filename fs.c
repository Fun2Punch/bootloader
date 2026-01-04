#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>

#include <Library/DevicePathLib.h>

#include "include/bits.h"
#include "include/fs.h"

#include "include/snapshot.h"

EFI_FILE_PROTOCOL *init_fs(IN EFI_HANDLE image_handle)
{
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_fs = NULL;
  EFI_LOADED_IMAGE_PROTOCOL *loaded_img = NULL;
  EFI_FILE_PROTOCOL *root = NULL;
  EFI_STATUS status;

  status = gBS->HandleProtocol(image_handle, &gEfiLoadedImageProtocolGuid, &loaded_img);
  if (EFI_ERROR(status)) {
    Print(L"Failed to HandleProtocol = %r\r\n", status);
  }

  status = gBS->HandleProtocol(loaded_img->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, &simple_fs);
  if (EFI_ERROR(status)) {
    Print(L"Failed to Simple file system protocol = %r\r\n", status);
  }

  status = simple_fs->OpenVolume(simple_fs, &root);
  if (EFI_ERROR(status)) {
    Print(L"Faild to OpenVolume = %r\r\n", status);
  }
  
  return root;
}

EFI_STATUS EFIAPI open_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name)
{
  EFI_STATUS status = EFI_SUCCESS;
  //EFI_FILE_PROTOCOL *vm_img;
  //UINTN buf_size, *vm_img_buf = NULL;

  /*status = root->Open(root, &vm_img, img_name, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
  if (EFI_ERROR(status)) {
    Print(L"Failed to root fs open = %r\r\n", status);
  }*/

  //buf_size = 4096;
  //vm_img->SetPosition(vm_img, 0);
  /*status = vm_img->Read(vm_img, &buf_size, vm_img_buf);
  if (EFI_ERROR(status)) {
    Print(L"Failed to vm image read = %r\r\n", status);
  }*/
  
  return status;
}
