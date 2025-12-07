
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include "Turdefs.h"

int T_MoveCharBuffer(const char* input  , char* output , int output_size);
void T_ClearCharBuffer(char* buffer , int buffer_size);
int T_Getenv(const char* Envname, char** output);

int T_MemAlloc(TPtr* allocator_Ptr , TUint alloc_size);
int T_MemFree(TPtr* allocated_Ptr);
int T_sendSignalToPid(pid_t pid, int signal);


#ifdef __cplusplus
}
#endif

