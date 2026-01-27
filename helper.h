#ifndef _HELPER_H
#define _HELPER_H

struct desc_table_reg_x64;
struct system_registers_x64;

void (*create_new_gdt_t)(desc_table_reg_x64 *buffer);


#endif
