
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int TgetVersionInfo(char* output, const int output_buff_size);
int TgetShellCmdRunnerName(char* output, const int output_buff_size);
int TgetLanguage(char* output, const int output_buff_size);

int TgetPid(unsigned int* output);
int TgetTmuxPid(unsigned int* output);
int TgetLastCmdExecutedPath(char* output, const int output_buff_size);

int TgetSEInfo(char* output, const int output_buff_size);
int TgetPackageName(char* output, const int output_buff_size);
int TgetSessionCountSinceBoot(unsigned int* output);

#ifdef __cplusplus
}
#endif