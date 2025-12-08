
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include "Turdefs.h"

int T_MoveCharBuffer(const char* input  , char* output , int output_size);
void T_ClearCharBuffer(char* buffer , int buffer_size);
int T_Getenv(const char* Envname, const char** output, int* get_output_size);

int T_MemAlloc(TPtr* allocator_Ptr , TUint alloc_size);
int T_MemFree(TPtr* allocated_Ptr);
int T_SendSignalToPid(pid_t pid, int signal);


// int T_ReadFileD(const char* filepath, int remove_newline, char* output, int output_buff_size);
int T_FReadBufferD(FILE* fp , char** output);
int T_GetParentPgid(pid_t* output);


#ifdef __cplusplus
}
#endif

