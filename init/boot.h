#ifndef _BOOT_H
#define _BOOT_H

struct vmm_context;
struct uefi_state_struct;
struct vmm_parameters;

struct screen_coordinate {
	UINTN x, y, width, height, delta;
};

void EFIAPI init_services(EFI_HANDLE image_handle,
			  EFI_SYSTEM_TABLE *system_table);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle,
			   IN EFI_SYSTEM_TABLE *SystemTable);

void EFIAPI __create_painting(void);

extern void enter_vmm(struct vmm_context *context,
		      struct uefi_state_struct *uefi_state);

extern void exit_vmm(void);

#endif
