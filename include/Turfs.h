
#pragma once


#ifdef __cplusplus
extern "C" {
#endif


int TgetHomeDir(char* output , const int output_buff_size);
int TgetCurrentDir(char* output, const int output_buff_size);
int TgetTempDir(char* output , const int output_buff_size);
int TgetPrefixDir(char* output, const int output_buff_size);
int TgetBinDir(char* output , const int output_buff_size);
int TgetShellDir(char* output , const int output_buff_size);
bool TisSystemRooted();
int TsetupStorage();

#ifdef __cplusplus
}
#endif
