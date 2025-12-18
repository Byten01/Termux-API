#define _GNU_SOURCE


#include "Termux.h"
#include <stdio.h>

__attribute__((constructor))
void INIT_DYNAMIC_LINK(void)
{
    printf("dynamic linker loaded .so file\n");
    InitPaths();
}