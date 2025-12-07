
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Turdefs.h"

int TgetVersionInfo(char* output, int output_buff_size);
int TgetShellCmdRunnerName(char* output, int output_buff_size);
int TgetLanguage(char* output, int output_buff_size);

int TgetPid(pid_t* output);
int TgetTmuxPid(pid_t* output);
int TgetLastCmdExecutedPath(char* output, int output_buff_size);

int TgetSEInfo(char* output, int output_buff_size);
int TgetPackageName(char* output, int output_buff_size);
int TgetSessionCountSinceBoot(TUint* output);

int TgetApkRelease(char* output, int output_buff_size);
int TgetAndroidSdkVersion(TUint* output);
int TgetTmuxSdkVersion(TUint* output);



#ifdef __cplusplus
}
#endif