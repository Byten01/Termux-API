
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Turdefs.h"

int TgetVersionInfo(char* output, const int output_buff_size);
int TgetShellCmdRunnerName(char* output, const int output_buff_size);
int TgetLanguage(char* output, const int output_buff_size);

int TgetPid(TUint* output);
int TgetTmuxPid(TUint* output);
int TgetLastCmdExecutedPath(char* output, const int output_buff_size);

int TgetSEInfo(char* output, const int output_buff_size);
int TgetPackageName(char* output, const int output_buff_size);
int TgetSessionCountSinceBoot(TUint* output);

int TgetApkRelease(char* output, const int output_buff_size);
int TgetAndroidSdkVersion(TUint* output);

#ifdef __cplusplus
}
#endif