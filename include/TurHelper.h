
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


int T_GetParentPgid(pid_t* output);
int T_ReadFile(const char* filepath,  char* output, int output_buff_size);
int T_FReadBufferD(TFile* fp , char** output);

int T_OpenFileDescriptor(const char* filepath, char* mode, TFile** output, TFile_Mode open_mode);
int T_CloseFileDescriptor(TFile* file_handle, TFile_Mode close_mode, int* returncode);
int T_HaveAccess(const char* filepath, int flags);


int T_GetEnvOrDefault(const char* Envname, char* output, int output_buff_size);


#ifdef __cplusplus
}
#endif

