#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>

#include "initialize.h"
#include "snapshot.h"


void EFIAPI init_fs(IN EFI_HANDLE image_handle, struct file_system *fs)
{
  EFI_STATUS status;

  status = gBS->AllocatePool(EfiBootServicesData, sizeof(struct file_system), (void **)&fs);
  if (EFI_ERROR(status)) {
    Print(L"failed file_system allocete = %r\r\n", status);
  }

  status = gBS->HandleProtocol(image_handle, &gEfiLoadedImageProtocolGuid, (void **)&fs->loaded_img);
  if (EFI_ERROR(status)) {
    Print(L"failed to HandleProtocol = %r\r\n", status);
  }

  status = gBS->HandleProtocol(fs->loaded_img->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void **)&fs->simple_fs);
  if (EFI_ERROR(status)) {
    Print(L"failed to Simple file system protocol = %r\r\n", status);
  }

  status = fs->simple_fs->OpenVolume(fs->simple_fs, &fs->root);
  if (EFI_ERROR(status)) {
    Print(L"failed to OpenVolume = %r\r\n", status);
  }
}


struct system_management EFIAPI *init_system_management(void)
{
  struct system_management *sys;

  gBS->AllocatePool(EfiBootServicesData, sizeof(struct system_management), (void **)&sys);

  return sys;
}

void EFIAPI init_settings(OUT struct system_settings *setting)
{
  gBS->AllocatePool(EfiBootServicesData, sizeof(struct system_settings), (void **)&setting);

  ZeroMem(setting, sizeof(struct system_settings));

  setting->get_current_regs = current_regs;
}
