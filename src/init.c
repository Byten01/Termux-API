#define _GNU_SOURCE



#include <stdio.h>
#include <sys/prctl.h>

#include "Termux.h"

__attribute__((constructor))
void INIT_DYNAMIC_LINK(void)
{
    
    #ifdef LIB_NODBG
        DBG_INFO("Dynamic lib set to non debugable");        
        prctl(PR_SET_DUMPABLE, 0);
        prctl(PR_SET_PTRACER, 0);         
    #endif 
    
    InitPaths();
}