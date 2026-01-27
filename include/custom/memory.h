


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Turdefs.h"


int T_MemAlloc(TPtr* allocator_Ptr , TUint alloc_size);
int T_MemFree(TPtr* allocated_Ptr);

#ifdef __cplusplus
}
#endif

