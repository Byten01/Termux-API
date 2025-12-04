
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


int TgetExtrnlStorageDir(char* output, const int output_buff_size);
int TgetLdPreloadDir(char* output, const int output_buff_size);
int TgetBuildDataDir(char* output, const int output_buff_size);


int TgetAndroidDataDir(char* output, const int output_buff_size);
int TgetAndroidRootDir(char* output, const int output_buff_size);
int TgetAndroidAssetsDir(char* output, const int output_buff_size);


int TgetAndroidSysDir(char* output, const int output_buff_size);


#ifdef __cplusplus
}
#endif
