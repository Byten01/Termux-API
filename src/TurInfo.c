


#include <stdlib.h>
#include <stdio.h>


#include "Turdefs.h"
#include "TurHelper.h"
#include "TurErrors.h"
#include "TurInfo.h"


int TgetVersionInfo(char* output, int output_buff_size)
{
    const char* version_env = "TERMUX_VERSION";
    const char* version;
    int returned_;
    
    returned_ = T_Getenv(
            version_env, 
            &version, 
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
    
       
    returned_ = T_MoveCharBuffer(
            version, 
            output, 
            output_buff_size
    );
    return returned_;
    
    
}


int TgetShellCmdRunnerName(char* output, int output_buff_size)
{
    const char* shell_cmd_env = "SHELL_CMD__RUNNER_NAME";
    const char* shell_cmd;
    int returned_;
    
            
    returned_ = T_Getenv(shell_cmd_env, &shell_cmd, NULL);
    
    if(returned_ < 0)
        return returned_;
    
   
    returned_ = T_MoveCharBuffer(shell_cmd, output, output_buff_size);
    return returned_;
}



int TgetLanguage(char* output, int output_buff_size)
{
    const char* language_env = "LANG";
    const char* language;
    int returned_;
    
    returned_ = T_Getenv(language_env, &language, NULL);
    
    if(returned_ < 0)
        return returned_;
    
    
    returned_ = T_MoveCharBuffer(language, output, output_buff_size);
    return returned_;
}


int TgetPid(pid_t* output)
{
    pid_t pid_ = getpid();
    
   if(output)
   {
       *output = pid_;
       return TMUX_SUCCESS;
   }
   
    return (int)pid_;
}


int TgetLastCmdExecutedPath(char* output, int output_buff_size)
{
    const char* last_executed_env = "_";
    const char* last_executed;
    int returned_;
    
    returned_ = T_Getenv(last_executed_env, &last_executed, NULL);    

    if(returned_ < 0)
        return returned_;
     
    
    returned_ = T_MoveCharBuffer(last_executed, output, output_buff_size);
    return returned_;
    
    
}


int TgetTmuxPid(pid_t* output)
{
    const char* termux_pid_env = "TERMUX_APP__PID";
    const char* termux_pid;
    int returned_;
    
    returned_ = T_Getenv(termux_pid_env, &termux_pid, NULL);
    
    if(returned_ < 0)
        return returned_;
     
    const int pid_conv = atoi(termux_pid);      
    pid_t pid_ = (pid_t)pid_conv;
    
     
    if(pid_ <= 0)
    {
        T_setError("failed to get the termux pid, type conversion from long to unsigned int returned a value (0)");
        return TMUX_FAILED;
    }
    
    
    
    if(output)
        *output = pid_;
        return returned_;
    
    
    return (int)pid_;
     
}


int TgetSEInfo(char* output, int output_buff_size)
{
    const char* termux_se_info_env = "TERMUX_APP__SE_INFO";
    const char* termux_se_info;
    int returned_;
    
    returned_ = T_Getenv(termux_se_info_env, &termux_se_info, NULL);
    
    if(returned_ < 0)
        return returned_;
        
    returned_ = T_MoveCharBuffer(termux_se_info, output,output_buff_size);
    return returned_;
}








int TgetSessionCountSinceBoot(TUint* output)
{
    const char* session_num_env = "SHELL_CMD__APP_TERMINAL_SESSION_NUMBER_SINCE_BOOT";
    const char* session_num;
    int returned_;
        
    
    returned_ = T_Getenv(session_num_env, &session_num, NULL);
    
    if(returned_ < 0)
        return returned_;
        

    int session_count = atoi(session_num);    
    
    if(output == NULL)        
        return session_count;
        
    *output = (TUint)session_count;    
    return returned_;    
}


int TgetPackageName(char* output, int output_buff_size)
{
    const char* package_name_env = "TERMUX_APP__PACKAGE_NAME";
    const char* package_name;
    int returned_; 
    
    returned_ = T_Getenv(package_name_env, &package_name, NULL);
    
    if(returned_ < 0)
        return returned_;
        
    returned_ = T_MoveCharBuffer(package_name, output,output_buff_size);
    return returned_;
}


int TgetApkRelease(char* output, int output_buff_size)
{
    const char* apk_release_env = "TERMUX_APP__APK_RELEASE";
    const char* apk_release;
    
    int return_flag = 0;
    int flag = TMUX_PLATFORM_UNKNOWN;
    int returned_;
    
    
    returned_ = T_Getenv(apk_release_env, &apk_release, NULL);
    
    
    if(returned_ < 0)
        return returned_;
        
                        
    if(output != NULL)
    {
        returned_ = T_MoveCharBuffer(apk_release, output, output_buff_size);
        return returned_;
    }
    
    
    if (strcmp(apk_release, "F_DROID") == 0)
        flag = TMUX_PLATFORM_F_DROID;
        
    if (strcmp(apk_release, "GITHUB") == 0)
        flag = TMUX_PLATFORM_GITHUB;
        
    if(strcmp(apk_release, "PLAY_STORE") == 0)
        flag = TMUX_PLATFORM_PLAY_STORE;
        

    return flag;
}


int TgetAndroidSdkVersion(TUint* output)
{
    const char* android_sdk_version_env = "ANDROID__BUILD_VERSION_SDK";
    const char* sdk_version;
    int returned_;
    
          
    returned_ = T_Getenv(android_sdk_version_env, &sdk_version, NULL);
    
    if(returned_ < 0)
        return returned_;
        
    int version_num = atoi(sdk_version);
    

    if(version_num <= 0 || version_num > 100)
    {
        T_setError("android vesion index out of range (%d).. its either conversion failed or a miscondigured environment variable is set", version_num);
        return TMUX_FAILED;
    }
    
    if(output == NULL)
        return version_num;
        
        
    *output = (TUint)version_num;            
    return returned_;

        
}



int TgetTmuxSdkVersion(TUint* output)
{
    const char* termux_sdk_version_env = "TERMUX_APP__TARGET_SDK";
    const char* termux_sdk_version;
    int returned_;
    
          
    returned_ = T_Getenv(termux_sdk_version_env, &termux_sdk_version, NULL);
    
    if(returned_ < 0)
        return returned_;
        
    int version_num = atoi(termux_sdk_version);
    

    if(version_num <= 0 || version_num > 100)
    {
        T_setError("termux vesion index out of range (%d).. its either conversion failed or a miscondigured environment variable is set", version_num);
        return TMUX_FAILED;
    }
    
    if(output == NULL)
        return version_num;
        
        
    *output = (TUint)version_num;            
    return returned_;

        
}




