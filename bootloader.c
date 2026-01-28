#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include "bootloader.h"
#include "memory.h"
#include "snapshot.h"
#include "bits.h"
#include "initialize.h"

// xor eax, eax | mov eax, cr0 | and eax, 0x7FFFFFFF | cmp eax, 1 je PagingOn(function addr)

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

EFI_PHYSICAL_ADDRESS EFIAPI alloc_vmm(void)
{
  EFI_PHYSICAL_ADDRESS vmm_addr;
  EFI_STATUS status;

  status = gBS->AllocatePages(AllocateAnyPages, EfiRuntimeServicesData, 2, &vmm_addr);
  if (EFI_ERROR(status)) {
    Print(L"failed allocate pages for vmm addr = %r\r\n", status);
  }

  return vmm_addr;
}

void EFIAPI start_bootloader(EFI_HANDLE image_handle)
{
  EFI_PHYSICAL_ADDRESS vmm_addr;
  struct system_management *data;
  struct system_settings *settings = NULL;

  vmm_addr = alloc_vmm();
  Print(L"vmm address = 0x%lx\r\n", vmm_addr);

  init_settings(settings);
  Print(L"settings = 0x%lx\r\n", settings);
  data = init_system_management();
  data->registers = init_cpu_snapshot();
}

struct system_regs_x64 EFIAPI current_regs(void)
{
  struct system_regs_x64 regs;

  gBS->AllocatePool(EfiBootServicesData, sizeof(struct system_regs_x64), (void**)&regs);

  return regs;
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
