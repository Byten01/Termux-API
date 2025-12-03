


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


int TgetPid(unsigned int* output)
{
    unsigned int pid_ = (unsigned int)getpid();
    
   if(output)
   {
       *output = pid_;
       return TMUX_SUCCESS;
   }
   
    return (int)pid_;
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


int TgetTmuxPid(unsigned int* output)
{
    const char* termux_pid_env = "TERMUX_APP__PID";
    char* termux_pid;
    
    if(T_Getenv(termux_pid_env, &termux_pid) < 0)   
        return TMUX_FAILED;
     
    const long pid_conv = atol(termux_pid);
    unsigned int pid_ = (unsigned int)pid_conv;
    
    free(termux_pid);
                   
    if(pid_ <= 0)
    {
        T_setError("failed to get the termux pid, type conversion from long to unsigned int returned a value (0)");
        return TMUX_FAILED;
    }
    
    
    
    if(output)
        *output = pid_;
    
    
    return (int)pid_;
     
}


int TgetSEInfo(char* output, const int output_buff_size)
{
    const char* termux_se_info_env = "TERMUX_APP__SE_INFO";
    char* termux_se_info;
    
    if(T_Getenv(termux_se_info_env, &termux_se_info) < 0)
        return TMUX_FAILED;
        
    int returned_ = T_MoveCharBuffer(termux_se_info, output,output_buff_size);
    free(termux_se_info);
    return returned_;
}








int TgetSessionCountSinceBoot(unsigned int* output)
{
    const char* session_num_env = "SHELL_CMD__APP_TERMINAL_SESSION_NUMBER_SINCE_APP_START";
    char* session_num;
    
    if(T_Getenv(session_num_env, &session_num) < 0)
        return TMUX_FAILED;
        
    const long session_count_l = atol(session_num);    
    const int session_count = (unsigned int)session_count_l;
    
    free(session_num);
    
    if(output == NULL)
        return (int)session_count;
        
    *output = session_count;    
    return TMUX_SUCCESS;    
}


int TgetPackageName(char* output, const int output_buff_size)
{
    const char* package_name_env = "TERMUX_APP__PACKAGE_NAME";
    char* package_name;
    
    if(T_Getenv(package_name_env, &package_name) < 0)
        return TMUX_FAILED;
        
    int returned_ = T_MoveCharBuffer(package_name, output,output_buff_size);
    free(package_name);
    return returned_;
}





