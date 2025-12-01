
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int TgetVersionInfo(char* output, const int output_buff_size);
int TgetShellCmdRunnerName(char* output, const int output_buff_size);
int TgetLanguage(char* output, const int output_buff_size);
int TgetPid(int* output);
int TgetLastCmdExecutedPath(char* output, const int output_buff_size);





#ifdef __cplusplus
}
#endif