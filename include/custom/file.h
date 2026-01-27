

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Turdefs.h"


int T_ReadFile(const char* filepath,  char* output, int output_buff_size);
int T_FReadBufferD(TFile* fp , char** output);

int T_OpenFileDescriptor(const char* filepath, char* mode, TFile** output, TFile_Mode open_mode);
int T_CloseFileDescriptor(TFile* file_handle, TFile_Mode close_mode, int* returncode);
int T_HaveAccess(const char* filepath, int flags);



#ifdef __cplusplus
}
#endif

