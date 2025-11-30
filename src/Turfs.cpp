#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <sys/types.h>


#include "Turdefs.h"
#include "TurHelper.h"
#include "Turfs.h"

extern "C" {

int TgetHomeDir(char* output , const int output_buff_size) 
{
    const char* env_home = "TERMUX__HOME";
    const char* home_path = std::getenv(env_home);

    if(!home_path) {
        T_setError("Failed to get env variable of home dir, getenv returned nullptr");
        return TMUX_FAILED;
    }
    
    return MoveCharBuffer(home_path  , output , output_buff_size);
                
}

int TgetCurrentDir(char* output, const int output_buff_size) 
{
    
    char* cwd = getcwd(nullptr, 0);
    
    if(!cwd) {
        T_setError("failed to get the current dir via unix getcwd, returned nullptr");
        return TMUX_FAILED;
    }
    int returned_ = MoveCharBuffer(cwd , output, output_buff_size);
    free(cwd);
    return returned_;
          
}

int TgetTempDir(char* output , const int output_buff_size) {
    
    const char* temp_env = "TMPDIR";
    const char* temp_path = std::getenv(temp_env);
    
    if(!temp_path)
    {
        T_setError("Failed to get env variable of temp dir, getenv returned nullptr");
        return TMUX_FAILED;
    }
    
    return MoveCharBuffer(temp_path, output , output_buff_size);
}

int TgetPrefixDir(char* output, const int output_buff_size) 
{
    const char* prefix_env = "PREFIX";
    const char* prefix_dir = std::getenv(prefix_env);
    
    if(!prefix_dir)
    {
         T_setError("Failed to get env variable of prefix dir, getenv returned nullptr");
        return TMUX_FAILED;
    }
    
    return MoveCharBuffer(prefix_dir , output , output_buff_size);
    
}

int TgetBinDir(char* output , const int output_buff_size)
{
    const char* bin_env = "PATH";
    const char* bin_path = std::getenv(bin_env);
    
    if(!bin_path) 
    {
         T_setError("Failed to get env variable of bin dir, getenv returned nullptr");
        return TMUX_FAILED;
    }
    
    return MoveCharBuffer(bin_path , output , output_buff_size);
}


int TgetShellDir(char* output , const int output_buff_size)
{
    const char* shell_env = "SHELL";
    const char* shell_path = std::getenv(shell_env);
    
    if(!shell_path) 
    {
         T_setError("Failed to get env variable of shell dir, getenv returned nullptr");
        return TMUX_FAILED;
    }
    
    return MoveCharBuffer(shell_path , output , output_buff_size);
}




}