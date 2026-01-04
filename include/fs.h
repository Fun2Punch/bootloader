#ifndef _FS_H
#define _FS_H

EFI_FILE_PROTOCOL *init_fs(IN EFI_HANDLE image_handle);
EFI_STATUS EFIAPI open_img(IN EFI_FILE_PROTOCOL *root, IN CHAR16 *img_name);

#endif
