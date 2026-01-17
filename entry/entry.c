#include <stdint.h>
#include <stddef.h>

extern void mm_init(void);

int entry_vmm(void)
{
        mm_init();
        
        
        return 0;
}
