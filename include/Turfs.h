
#pragma once


#ifdef __cplusplus
extern "C" {
#endif


int TgetHomeDir(char* output , int output_buff_size);
int TgetCurrentDir(char* output, int output_buff_size);
int TgetTempDir(char* output , int output_buff_size);


int TgetPrefixDir(char* output, int output_buff_size);
int TgetBinDir(char* output , int output_buff_size);
int TgetShellDir(char* output , int output_buff_size);


int TgetExtrnlStorageDir(char* output, int output_buff_size);
int TgetLdPreloadDir(char* output, int output_buff_size);
int TgetBuildDataDir(char* output, int output_buff_size);


int TgetAndroidDataDir(char* output, int output_buff_size);
int TgetAndroidRootDir(char* output, int output_buff_size);
int TgetAndroidAssetsDir(char* output, int output_buff_size);


int TgetAndroidSysDir(char* output, int output_buff_size);
int TgetTmuxBaseApkDir(char* output, int output_buff_size);

#ifdef __cplusplus
}
#endif
