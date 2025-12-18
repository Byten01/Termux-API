#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <pwd.h>

#include "Turdefs.h"
#include "TurHelper.h"
#include "Turfs.h"
#include "TurErrors.h"


TMux_Paths TermuxFsPaths;


void InitPaths() 
{
    
    
    struct passwd *pw = getpwuid(getuid());
    
    
    if(!pw || !pw->pw_shell)
    {
        printf("[FATAL ERROR] %s : failed to get the shell dir\n", __FILE__);
        exit(1);
    }
    
    char* shell_path = pw->pw_shell;
    strncpy(TermuxFsPaths.T_AppRootDir , shell_path, PATH_MAX);

    char* marker = strstr(
            TermuxFsPaths.T_AppRootDir, 
            "/files/"
    );
    
    if (!marker)
    {
        printf("[FATAL ERROR] %s : failed to get the /files/ dir in termux fs\n", __FILE__);
        exit(1);
    }    
    *marker = '\0';
    
    

    snprintf(TermuxFsPaths.T_FilesDir,
             sizeof(TermuxFsPaths.T_FilesDir),
             "%s/files",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_BinDir,
             sizeof(TermuxFsPaths.T_BinDir),
             "%s/files/usr/bin",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_LibexecDir,
             sizeof(TermuxFsPaths.T_LibexecDir),
             "%s/files/usr/libexec",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_EtcDir,
             sizeof(TermuxFsPaths.T_EtcDir),
             "%s/files/etc",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_LibDir,
             sizeof(TermuxFsPaths.T_LibDir),
             "%s/files/usr/lib",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_HomeDir,
             sizeof(TermuxFsPaths.T_HomeDir),
             "%s/files/home",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_TmpDir,
             sizeof(TermuxFsPaths.T_TmpDir),
             "%s/files/usr/tmp",
             TermuxFsPaths.T_AppRootDir);
    
    snprintf(TermuxFsPaths.T_PrefixDir,
             sizeof(TermuxFsPaths.T_PrefixDir),
             "%s/files/usr",
             TermuxFsPaths.T_AppRootDir); 
             
             
    TermuxFsPaths.T_AllPaths[0] = TermuxFsPaths.T_AppRootDir;
    TermuxFsPaths.T_AllPaths[1] = TermuxFsPaths.T_FilesDir;
    TermuxFsPaths.T_AllPaths[2] = TermuxFsPaths.T_BinDir;
    TermuxFsPaths.T_AllPaths[3] = TermuxFsPaths.T_LibexecDir;
    TermuxFsPaths.T_AllPaths[4] = TermuxFsPaths.T_EtcDir;
    TermuxFsPaths.T_AllPaths[5] = TermuxFsPaths.T_LibDir;
    TermuxFsPaths.T_AllPaths[6] = TermuxFsPaths.T_HomeDir;
    TermuxFsPaths.T_AllPaths[7] = TermuxFsPaths.T_TmpDir;
    TermuxFsPaths.T_AllPaths[8] = TermuxFsPaths.T_PrefixDir;

  
    printf("root: %s\n", TermuxFsPaths.T_AppRootDir);
    printf("rootfs: %s\n", TermuxFsPaths.T_FilesDir);
    printf("libexec: %s\n", TermuxFsPaths.T_LibexecDir);
    printf("etc: %s\n", TermuxFsPaths.T_EtcDir);
    printf("lib: %s\n", TermuxFsPaths.T_LibDir);
    printf("home: %s\n", TermuxFsPaths.T_HomeDir);
    printf("tmp: %s\n", TermuxFsPaths.T_TmpDir);
    printf("prefix: %s\n", TermuxFsPaths.T_PrefixDir);


    const int path_count = sizeof(TermuxFsPaths.T_AllPaths) / sizeof(char*);
    
    for(int i=0; i < path_count; i++)
    {
        if(access(TermuxFsPaths.T_AllPaths[i], F_OK) == 0)
        {
            printf("path exists %s\n", TermuxFsPaths.T_AllPaths[i]);
        }
    }
    
    
}



int TgetKnownFolderPath(TMux_DirFlags flag, char* output, int output_buff_size)
{
    
    char* ptr;
    int returned_; // for future pourpouse 
    
    switch(flag)
    {
        
        case TMUX_DIR_HOME:
        {
            ptr = TermuxFsPaths.T_HomeDir;
            break;
        }
        
        case TMUX_DIR_ROOTFS:
        {
            ptr = TermuxFsPaths.T_FilesDir;
            break;
        }
        
        case TMUX_DIR_TMP:
        {
            ptr = TermuxFsPaths.T_TmpDir;
            break;
        }
        
        case TMUX_DIR_ETC:
        {
            ptr = TermuxFsPaths.T_EtcDir;
            break;
        }
        
        case TMUX_DIR_LIBEXEC:
        {
            ptr = TermuxFsPaths.T_LibexecDir;
            break;     
        }
        
        case TMUX_DIR_BIN:
        {
            ptr = TermuxFsPaths.T_BinDir;
            break;
        }
        
        case TMUX_DIR_LIB:
        {
            ptr = TermuxFsPaths.T_LibDir;
            break;
        }
        
        case TMUX_DIR_PREFIX:
        {
            ptr = TermuxFsPaths.T_PrefixDir;
            break;
        }
    }
    
    return T_MoveCharBuffer(
            ptr,
            output,
            output_buff_size
    );
}

int TgetHomeDir(char* output ,  int output_buff_size) 
{
    return TgetKnownFolderPath(
            TMUX_DIR_HOME,
            output,
            output_buff_size
    );
}

int TgetCurrentDir(char* output, int output_buff_size) 
{
    
    char* cwd = getcwd(NULL, 0);
    int returned_;
    
    if(!cwd)
    {
        T_setError("failed to get the current dir via unix getcwd, returned nullptr");
        return TMUX_FAILED;
    }
    returned_ = T_MoveCharBuffer(
            cwd , 
            output, 
            output_buff_size
    );
    T_MemFree((TPtr*)&cwd);
    return returned_;
          
}

int TgetTempDir(char* output , int output_buff_size) 
{
    
    return TgetKnownFolderPath(
            TMUX_DIR_TMP,
            output,
            output_buff_size
    );
}

int TgetPrefixDir(char* output, int output_buff_size) 
{        
    return TgetKnownFolderPath(
            TMUX_DIR_PREFIX,
            output,
            output_buff_size
    );
}

int TgetBinDir(char* output , int output_buff_size)
{  
    return TgetKnownFolderPath(
            TMUX_DIR_BIN,
            output,
            output_buff_size
    );
}


int TgetShellDir(char* output , int output_buff_size)
{
    const char* shell_env = "SHELL";
    const char* shell_path;
    int returned_;
    
    returned_ = T_Getenv(shell_env, &shell_path, NULL);
    
    if(returned_ < 0)
        return returned_;
    
    
    returned_ = T_MoveCharBuffer(shell_path , output , output_buff_size);
    return returned_;
}


int TgetExtrnlStorageDir(char* output, int output_buff_size)
{     
    return T_MoveCharBuffer(
            "/storage", 
            output,
            output_buff_size
    );
}


int TgetLdPreloadDir(char* output, int output_buff_size)
{
    const char* ld_preload_env = "LD_PRELOAD";
    const char* ld_preload;
    int returned_;
    
    returned_ = T_Getenv(
            ld_preload_env, 
            &ld_preload, 
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
        
    returned_ = T_MoveCharBuffer(
            ld_preload, 
            output,
            output_buff_size
    );
    return returned_;
}


int TgetBuildDataDir(char* output, int output_buff_size)
{
    const char* build_dir_env = "TERMUX_APP__BUILD_DATA_DIR";
    const char* build_dir;
    int returned_;
    
    returned_ = T_Getenv(
            build_dir_env, 
            &build_dir, 
            NULL
    );
   
   if(returned_ < 0)
       return returned_;

        
    returned_ = T_MoveCharBuffer(build_dir, output,output_buff_size);
    return returned_;
}






int TgetAndroidDataDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer(
            "/data", 
            output,
            output_buff_size
    );
}


int TgetAndroidRootDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer(
            "/", 
            output, 
            output_buff_size
    );
}



int TgetAndroidAssetsDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer(
            "/system/app", 
            output, 
            output_buff_size
    );
}


int TgetAndroidSysDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer(
            "/system", 
            output, 
            output_buff_size
    );
}


int TgetTmuxBaseApkDir(char* output, int output_buff_size)
{
    const char* termux_baseApk_dir_env = "TERMUX_APP__APK_FILE";
    const char* baseApk_dir;
    int returned_;
    
    returned_ = T_Getenv(termux_baseApk_dir_env, &baseApk_dir, NULL);
    
    if(returned_ < 0)
        return returned_;
       
    returned_ = T_MoveCharBuffer(baseApk_dir, output, output_buff_size);
    return returned_;    
    
}


int TreadFileBuffer(const char* filepath, char* output, int output_buff_size)
{
    return T_ReadFile(filepath , output, output_buff_size);
}