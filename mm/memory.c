#include <stddef.h>
#include <stdint.h>

#include "memory.h"

struct memory_map *mem_map;

void mm_init(void)
{
        memset((void*)mem_map, 0, sizeof(struct memory_map));
}

unsigned long alloc_page()
{
        unsigned long addr = 0;
        

        return addr;
}
