#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


#include "Turdefs.h"
#include "TurHelper.h"
#include "Turfs.h"
#include "TurErrors.h"


int TgetHomeDir(char* output ,  int output_buff_size) 
{
    const char* env_home = "TERMUX__HOME";
    const char* home_path;
    int returned_;

    returned_ = T_Getenv(env_home, &home_path, NULL);
    
    if(returned_ < 0)
        return returned_;           
    
    returned_ = T_MoveCharBuffer(home_path  , output , output_buff_size);
    return returned_;
                
}

int TgetCurrentDir(char* output, int output_buff_size) 
{
    
    char* cwd = getcwd(NULL, 0);
    int returned_;
    
    if(!cwd) {
        T_setError("failed to get the current dir via unix getcwd, returned nullptr");
        return TMUX_FAILED;
    }
    returned_ = T_MoveCharBuffer(cwd , output, output_buff_size);
    T_MemFree((TPtr*)&cwd);
    return returned_;
          
}

int TgetTempDir(char* output , int output_buff_size) {
    
    const char* temp_env = "TMPDIR";
    const char* temp_path;
    int returned_;
        
    returned_ = T_Getenv(temp_env, &temp_path, NULL);
    
    if(returned_ < 0)
        return returned_;
    
    
    returned_ = T_MoveCharBuffer(temp_path, output , output_buff_size);
    return returned_;
}

int TgetPrefixDir(char* output, int output_buff_size) 
{
    const char* prefix_env = "PREFIX";
    const char* prefix_dir;
    int returned_;
    
    
    returned_ = T_Getenv(prefix_env, &prefix_dir, NULL);
    
    if(returned_ < 0)
        return returned_;
    
    
    returned_ = T_MoveCharBuffer(prefix_dir , output , output_buff_size);
    return returned_;
    
}

int TgetBinDir(char* output , int output_buff_size)
{
    const char* bin_env = "PATH";
    const char* bin_path;
    int returned_;
    
    returned_ = T_Getenv(bin_env, &bin_path, NULL);
    
    if(returned_ < 0)
        return returned_;
    
    
    returned_ = T_MoveCharBuffer(bin_path , output , output_buff_size);
    return returned_;
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
    return T_MoveCharBuffer("/storage", output,output_buff_size);
}


int TgetLdPreloadDir(char* output, int output_buff_size)
{
    const char* ld_preload_env = "LD_PRELOAD";
    const char* ld_preload;
    int returned_;
    
    returned_ = T_Getenv(ld_preload_env, &ld_preload, NULL);
    
    if(returned_ < 0)
        return returned_;
        
    returned_ = T_MoveCharBuffer(ld_preload, output,output_buff_size);
    return returned_;
}


int TgetBuildDataDir(char* output, int output_buff_size)
{
    const char* build_dir_env = "TERMUX_APP__BUILD_DATA_DIR";
    const char* build_dir;
    int returned_;
    
    returned_ = T_Getenv(build_dir_env, &build_dir, NULL);
   
   if(returned_ < 0)
       return returned_;

        
    returned_ = T_MoveCharBuffer(build_dir, output,output_buff_size);
    return returned_;
}






int TgetAndroidDataDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer("/data", output,output_buff_size);
}


int TgetAndroidRootDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer("/", output, output_buff_size);
}



int TgetAndroidAssetsDir(char* output, int output_buff_size)
{
    const char* android_asset_dir_env = "ANDROID_ASSETS";
    const char* asset_dir;
    int returned_;
    
    returned_ = T_Getenv(android_asset_dir_env, &asset_dir, NULL);
    
    if(returned_ < 0)
        return returned_;               
       
    returned_ = T_MoveCharBuffer(asset_dir, output, output_buff_size);
    return returned_;
}


int TgetAndroidSysDir(char* output, int output_buff_size)
{
    return T_MoveCharBuffer("/system", output, output_buff_size);
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