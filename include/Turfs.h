
#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>


typedef struct 
{
    char T_AppRootDir[PATH_MAX];
    char T_FilesDir[PATH_MAX];
    char T_BinDir[PATH_MAX];
    char T_LibDir[PATH_MAX];
    char T_LibexecDir[PATH_MAX];
    char T_EtcDir[PATH_MAX];
    char T_HomeDir[PATH_MAX];
    char T_TmpDir[PATH_MAX];
    char T_PrefixDir[PATH_MAX];
    
    char* T_AllPaths[9];
    
} TMux_Paths;


typedef enum 
{
    TMUX_DIR_HOME,
    TMUX_DIR_ROOTFS,
    TMUX_DIR_TMP,
    TMUX_DIR_ETC,
    TMUX_DIR_LIBEXEC,
    TMUX_DIR_BIN,
    TMUX_DIR_LIB,
    TMUX_DIR_PREFIX
    
} TMux_DirFlags;

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
void InitPaths();

int TgetKnownFolderPath(TMux_DirFlags flag, char* output, int output_buff_size);


#ifdef __cplusplus
}
#endif
