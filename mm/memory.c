#include <stddef.h>
#include <stdint.h>

#include "memory.h"

unsigned char mem_map[512*1024*1024];

void mm_init(void)
{

}

unsigned long alloc_page()
{
        unsigned long addr;
        for(int i = 0; i <= MAX_PAGES; ++i) {
                if(mem_map[i] == 0) {
                        mem_map[i] = 1;
                        addr = BASE_ADDR + (i << 12);
                        memset((void*)addr, 0, 4096);
                        return addr;
                }
        }

        return 0;
}
