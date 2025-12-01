


#include <stdlib.h>

#include "Turdefs.h"
#include "TurHelper.h"
#include "TurErrors.h"
#include "TurInfo.h"



int TgetVersionInfo(char* output, const int output_buff_size)
{
    const char* version_env = "TERMUX_VERSION";
    char* version;
    
    if(T_Getenv(version_env, &version) < 0)
        return TMUX_FAILED;
    
       
    int returned_ = T_MoveCharBuffer(version, output, output_buff_size);
    free(version);
    return returned_;
    
    
}


int TgetShellCmdRunnerName(char* output, const int output_buff_size)
{
    const char* shell_cmd_env = "SHELL_CMD__RUNNER_NAME";
    char* shell_cmd;
    
            
    if(T_Getenv(shell_cmd_env, &shell_cmd) < 0)
        return TMUX_FAILED;
    
   
    int returned_ = T_MoveCharBuffer(shell_cmd, output, output_buff_size);
    free(shell_cmd);
    return returned_;
}



int TgetLanguage(char* output, const int output_buff_size)
{
    const char* language_env = "LANG";
    char* language;
    
    if(T_Getenv(language_env, &language) < 0)
        return TMUX_FAILED;
    
    
    int returned_ = T_MoveCharBuffer(language, output, output_buff_size);
    free(language);
    return returned_;
}


int TgetPid(int* output)
{
    int pid_ = (int)getpid();
    
   if(output)
   {
       *output = pid_;
       return 0;
   }
   
    return pid_;
}


int TgetLastCmdExecutedPath(char* output, const int output_buff_size)
{
    const char* last_executed_env = "_";
    char* last_executed;
    
    if(T_Getenv(last_executed_env, &last_executed) < 0)   
        return TMUX_FAILED;
     
    
    int returned_ = T_MoveCharBuffer(last_executed, output, output_buff_size);
    free(last_executed);
    return returned_;
    
    
}






