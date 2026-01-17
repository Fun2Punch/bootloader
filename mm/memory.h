#ifndef _MEMORY_H_
#define _MEMORY_H_

#define BASE_ADDR 0x100000
#define MAX_PAGES 512
#define PAGING_SIZE_4096 4096

struct special_registers {
        unsigned long cr0;
        unsigned long cr3;
        unsigned long cr4;
        unsigned long msr_gs_base;
        unsigned long ldtr;
        unsigned long debug_control;
        unsigned short tr;
};

struct memory_map {
        unsigned long base_addr;
        unsigned long state;
        unsigned long size;
        unsigned long capacity;
};



void mm_init(void);

unsigned long alloc_page();

extern void memset(void *dest, int data, unsigned int len);

#endif
