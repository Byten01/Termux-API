


#include <stdlib.h>
#include <stdio.h>


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


int TgetPid(TUint* output)
{
    TUint pid_ = (TUint)getpid();
    
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


int TgetTmuxPid(TUint* output)
{
    const char* termux_pid_env = "TERMUX_APP__PID";
    char* termux_pid;
    
    if(T_Getenv(termux_pid_env, &termux_pid) < 0)   
        return TMUX_FAILED;
     
    const long pid_conv = atol(termux_pid);
    TUint pid_ = (TUint)pid_conv;
    
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








int TgetSessionCountSinceBoot(TUint* output)
{
    const char* session_num_env = "SHELL_CMD__APP_TERMINAL_SESSION_NUMBER_SINCE_BOOT";
    char* session_num;
        
    
    if(T_Getenv(session_num_env, &session_num) < 0)
        return TMUX_FAILED;
        

    int session_count = atoi(session_num);    
    
    free(session_num);
    
    if(output == NULL)
        return session_count;
        
    *output = (TUint)session_count;    
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


int TgetApkRelease(char* output, const int output_buff_size)
{
    const char* apk_release_env = "TERMUX_APP__APK_RELEASE";
    char* apk_release;
    
    
    if(T_Getenv(apk_release_env, &apk_release) < 0)
        return TMUX_PLATFORM_UNKNOWN;
        
    if(output != NULL && output_buff_size)
    {
        int returned_ = T_MoveCharBuffer(apk_release, output, output_buff_size);
        free(apk_release);
        return returned_;
    }
    
    
    int flag = TMUX_PLATFORM_UNKNOWN;
    
    if (strcmp(apk_release, "F_DROID") == 0)
        flag = TMUX_PLATFORM_F_DROID;
        
    if (strcmp(apk_release, "GITHUB") == 0)
        flag = TMUX_PLATFORM_GITHUB;
        
    if(strcmp(apk_release, "PLAY_STORE") == 0)
        flag = TMUX_PLATFORM_PLAY_STORE;
        

    free(apk_release);
    return flag;
}


int TgetAndroidSdkVersion(TUint* output)
{
    const char* android_sdk_version_env = "ANDROID__BUILD_VERSION_SDK";
    char* sdk_version;
    
          
    if(T_Getenv(android_sdk_version_env, &sdk_version) < 0)
        return TMUX_FAILED;
        
    int version_num = atoi(sdk_version);
    
    free(sdk_version);
    
    if(version_num <= 0 || version_num > 100)
    {
        T_setError("android vesion index out of range (%d).. its either conversion failed or a miscondigured environment variable is set", version_num);
        return TMUX_FAILED;
    }
    
    if(output == NULL)
        return version_num;
        
        
    *output = (TUint)version_num;            
    return TMUX_SUCCESS;

        
}




