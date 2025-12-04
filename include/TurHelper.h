
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Turdefs.h"

int T_MoveCharBuffer(const char* input  , char* output , const int output_size);
void T_ClearCharBuffer(char* buffer , const int buffer_size);
int T_Getenv(const char* Envname, char** output);

int T_MemAlloc(TPtr* allocator_Ptr , const TUint alloc_size);
int T_MemFree(TPtr* allocated_Ptr);

#ifdef __cplusplus
}
#endif

