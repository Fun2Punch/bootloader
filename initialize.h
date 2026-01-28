#ifndef _INITIALIZE_H
#define _INITIALIZE_H


// initialize
void EFIAPI init_system_table(IN EFI_SYSTEM_TABLE *system_table);
void EFIAPI init_fs(IN EFI_HANDLE image_handle, struct file_system *fs);
void EFIAPI init_settings(OUT struct system_settings *setting);
struct system_management EFIAPI *init_system_management(void);

#endif
