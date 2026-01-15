#include <stdint.h>
#include <stddef.h>

extern void init(void);
extern void vmm_init(void);
extern void mm_init(void);

int entry_vmm(void)
{
        mm_init(void);
        
        
        return 0;
}