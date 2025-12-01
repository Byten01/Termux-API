#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


#include "Turdefs.h"
#include "TurHelper.h"
#include "Turfs.h"
#include "TurErrors.h"


int TgetHomeDir(char* output , const int output_buff_size) 
{
    const char* env_home = "TERMUX__HOME";
    char* home_path;

    if(T_Getenv(env_home, &home_path) < 0)
        return TMUX_FAILED;    
    
    int returned_ = T_MoveCharBuffer(home_path  , output , output_buff_size);
    free(home_path);
    return returned_;
                
}

int TgetCurrentDir(char* output, const int output_buff_size) 
{
    
    char* cwd = getcwd(NULL, 0);
    
    if(!cwd) {
        T_setError("failed to get the current dir via unix getcwd, returned nullptr");
        return TMUX_FAILED;
    }
    int returned_ = T_MoveCharBuffer(cwd , output, output_buff_size);
    free(cwd);
    return returned_;
          
}

int TgetTempDir(char* output , const int output_buff_size) {
    
    const char* temp_env = "TMPDIR";
    char* temp_path;
        
    if(T_Getenv(temp_env, &temp_path) < 0)
        return TMUX_FAILED;
    
    
    int returned_ = T_MoveCharBuffer(temp_path, output , output_buff_size);
    free(temp_path);
    return returned_;
}

int TgetPrefixDir(char* output, const int output_buff_size) 
{
    const char* prefix_env = "PREFIX";
    char* prefix_dir;
    
    
    if(T_Getenv(prefix_env, &prefix_dir) < 0)
        return TMUX_FAILED;
    
    
    int returned_ = T_MoveCharBuffer(prefix_dir , output , output_buff_size);
    free(prefix_dir);
    return returned_;
    
}

int TgetBinDir(char* output , const int output_buff_size)
{
    const char* bin_env = "PATH";
    char* bin_path;
    
    if(T_Getenv(bin_env, &bin_path) < 0)
        return TMUX_FAILED;
    
    
    int returned_ = T_MoveCharBuffer(bin_path , output , output_buff_size);
    free(bin_path);
    return returned_;
}


int TgetShellDir(char* output , const int output_buff_size)
{
    const char* shell_env = "SHELL";
    const char* shell_path;
    
    if(T_Getenv(shell_env, &shell_path) < 0)  
        return TMUX_FAILED;
    
    
    int returned_ = T_MoveCharBuffer(shell_path , output , output_buff_size);
    free(shell_path);
    return returned_;
}




