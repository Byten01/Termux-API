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
    
    int returned_;
    
    
    struct passwd *pw = getpwuid(getuid());
    
    
    if(!pw || !pw->pw_shell)
    {
        printf("[FATAL ERROR] %s : failed to get the shell dir\n", __FILE__);
        exit(1);
    }
    
    char* shell_path = pw->pw_shell;
    int shell_path_size = strlen(shell_path);
    
    
    returned_ = T_MemAlloc(
            (TPtr*)&TermuxFsPaths.T_AppRootDir, 
            shell_path_size + 1
    );
    
    if(returned_ < 0)
    {
        const char* Error = T_getError();
        printf("[FATAL ERROR] %s : %s\n", __FILE__, Error);
        exit(1);
    }
        
        
    strncpy(
        TermuxFsPaths.T_AppRootDir , 
        shell_path, 
        shell_path_size + 1
    );

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
    
    const char* Root = TermuxFsPaths.T_AppRootDir;
    
    
    

    
    
    const char* PathFormats[] = {
        
        "%s",
        "%s/files",
        "%s/files/usr/bin",
        
        "%s/files/usr/lib",        
        "%s/files/usr/libexec",
        "%s/files/etc",
        
        "%s/files/home",        
        "%s/files/usr/tmp",
        "%s/files/usr"
    };
    
    
    char** PathMem[] = {
        &TermuxFsPaths.T_AppRootDir,
        &TermuxFsPaths.T_FilesDir,
        &TermuxFsPaths.T_BinDir,
        &TermuxFsPaths.T_LibDir,
        &TermuxFsPaths.T_LibexecDir,
        &TermuxFsPaths.T_EtcDir,
        &TermuxFsPaths.T_HomeDir,
        &TermuxFsPaths.T_TmpDir,
        &TermuxFsPaths.T_PrefixDir
    };
    

             
    const int path_count = sizeof(TermuxFsPaths.T_AllPaths) / sizeof(char*);
    
    
    for(int i=1; i < path_count; i++)
    {
        const char** Ptr = PathMem[i];  
        const char* format = PathFormats[i];
        
        const int size = snprintf(NULL, 0, format , Root);
        
        

        
        returned_ = T_MemAlloc(
                (TPtr*)Ptr,
                size + 1
        );
        
        if(returned_ < 0)
        {
            const char* Error = T_getError();
            printf("[FATAL ERROR] %s : %s\n", __FILE__, Error);
            exit(1);
        }
        
        snprintf(
            *Ptr, 
            size + 1, 
            format, 
            Root
        );
        
        
        if(access(*Ptr, F_OK) != 0)
        {
            #ifdef TURFS_DBGPRINT
                printf("[INFO] Path doesnt exists %s\n", *Ptr);
            #endif
            
        } else {
            #ifdef TURFS_DBGPRINT
                printf("[INFO] Path exists %s\n", *Ptr);
            #endif
        }
        
        TermuxFsPaths.T_AllPaths[i] = *Ptr;
        
    }
    


        
    
    #ifdef TURFS_DBGPRINT
        printf("root: %s\n", TermuxFsPaths.T_AppRootDir);
        printf("rootfs: %s\n", TermuxFsPaths.T_FilesDir);
        printf("libexec: %s\n", TermuxFsPaths.T_LibexecDir);
        printf("etc: %s\n", TermuxFsPaths.T_EtcDir);
        printf("lib: %s\n", TermuxFsPaths.T_LibDir);
        printf("home: %s\n", TermuxFsPaths.T_HomeDir);
        printf("tmp: %s\n", TermuxFsPaths.T_TmpDir);
        printf("prefix: %s\n", TermuxFsPaths.T_PrefixDir);
   #endif




    
    
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

    return T_GetEnvOrDefault(
            shell_env,
            output,
            output_buff_size
    );
}


int TgetExtrnlStorageDir(char* output, int output_buff_size)
{
    
    const char* android_storage_path = "/storage";
    
    return T_MoveCharBuffer(
            android_storage_path, 
            output,
            output_buff_size
    );
}


int TgetLdPreloadDir(char* output, int output_buff_size)
{
    const char* ld_preload_env = "LD_PRELOAD";

    return T_GetEnvOrDefault(
            ld_preload_env,
            output,
            output_buff_size
    );
}


int TgetBuildDataDir(char* output, int output_buff_size)
{
    const char* build_dir_env = "TERMUX_APP__BUILD_DATA_DIR";
    
    return T_GetEnvOrDefault(
            build_dir_env,    
            output,
            output_buff_size
    );
}






int TgetAndroidDataDir(char* output, int output_buff_size)
{
    const char* android_data_path = "/data";
    
    return T_MoveCharBuffer(
            android_data_path, 
            output,
            output_buff_size
    );
}


int TgetAndroidRootDir(char* output, int output_buff_size)
{
    
    const char* android_root_path = "/";
    
    return T_MoveCharBuffer(
            android_root_path, 
            output, 
            output_buff_size
    );
}



int TgetAndroidAssetsDir(char* output, int output_buff_size)
{
    
    const char* android_assets_dir = "/system/app";
    
    
    return T_MoveCharBuffer(
            android_assets_dir, 
            output, 
            output_buff_size
    );
}


int TgetAndroidSysDir(char* output, int output_buff_size)
{
    
    const char* android_sys_dir = "/sys";
    
    
    return T_MoveCharBuffer(
            android_sys_dir, 
            output, 
            output_buff_size
    );
}


int TgetTmuxBaseApkDir(char* output, int output_buff_size)
{
    const char* termux_baseApk_dir_env = "TERMUX_APP__APK_FILE";
    
    return T_GetEnvOrDefault(
            termux_baseApk_dir_env,
            output,
            output_buff_size
    );
    
}


int TreadFileBuffer(const char* filepath, char* output, int output_buff_size)
{
    return T_ReadFile(
            filepath , 
            output, 
            output_buff_size
    );
}