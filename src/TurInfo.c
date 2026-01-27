


#include <stdlib.h>
#include <stdio.h>


#include "Turdefs.h"
#include "TurErrors.h"
#include "TurInfo.h"

#include "custom/buffer.h"
#include "custom/env.h"
#include "custom/datatypes.h"

#define TMUX_PLATFORM_F_DROID_CHR            "F_DROID"
#define TMUX_PLATFORM_PLAY_STORE_CHR    "PLAY_STORE"
#define TMUX_PLATFORM_GITHUB_CHR               "GITHUB"




int TgetVersionInfo(char* output, int output_buff_size)
{
    const char* version_env = "TERMUX_VERSION";

    return T_GetEnvOrDefault(
            version_env,
            output,
            output_buff_size
    );
    
    
}


int TgetShellCmdRunnerName(char* output, int output_buff_size)
{
    const char* shell_cmd_env = "SHELL_CMD__RUNNER_NAME";

    return T_GetEnvOrDefault(
            shell_cmd_env,
            output,
            output_buff_size
    );
}



int TgetLanguage(char* output, int output_buff_size)
{
    const char* language_env = "LANG";
    
    return T_GetEnvOrDefault(
            language_env,
            output,
            output_buff_size 
    );
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
    
    return T_GetEnvOrDefault(
            last_executed_env,
            output,
            output_buff_size 
    );
    
    
}


int TgetTmuxPid(pid_t* output)
{
    const char* termux_pid_env = "TERMUX_APP__PID";
    const char* termux_pid;
    int returned_;
    int termux_pid_num;
    
    returned_ = T_Getenv(
            termux_pid_env, 
            &termux_pid, 
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
     
    returned_ = T_TypeCnvrt(
            termux_pid,
            TYPE_CNVRT_INT,
            (TPtr*)&termux_pid_num                                 
    );
    
    if(returned_ < 0)
        return returned_;
        
        
    pid_t pid_ = (pid_t)termux_pid_num;
    
     
    if(pid_ <= 0)
    {
        T_setError("failed to get the termux pid, type conversion from long to unsigned int returned a value (0)");
        return TMUX_FAILED;
    }
    
    
    
    if(output)
    {
        *output = pid_;
        return returned_;
    }
    
    
    return (int)pid_;
     
}


int TgetSEInfo(char* output, int output_buff_size)
{
    const char* termux_se_info_env = "TERMUX_APP__SE_INFO";
    
    return T_GetEnvOrDefault(
            termux_se_info_env,
            output,
            output_buff_size 
    );
}








int TgetSessionCountSinceBoot(TUint* output)
{
    const char* session_num_env = "SHELL_CMD__APP_TERMINAL_SESSION_NUMBER_SINCE_BOOT";
    const char* session_num;
    int returned_;
    int session_count;        
    
    returned_ = T_Getenv(
            session_num_env, 
            &session_num, 
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
        

    returned_ = T_TypeCnvrt(
            session_num,
            TYPE_CNVRT_INT,
            (TPtr*)&session_count
    );
    
    if(returned_ < 0)
        return returned_;
        
        
    
    if(output == NULL)        
        return session_count;
        
    *output = (TUint)session_count;    
    return returned_;    
}


int TgetPackageName(char* output, int output_buff_size)
{
    const char* package_name_env = "TERMUX_APP__PACKAGE_NAME";

    return T_GetEnvOrDefault(
            package_name_env,
            output,
            output_buff_size 
    );
}


int TgetApkRelease(char* output, int output_buff_size)
{
    const char* apk_release_env = "TERMUX_APP__APK_RELEASE";
    const char apk_release[4096];
    
    
    int flag = TMUX_PLATFORM_UNKNOWN;
    int returned_;
    
    
    returned_ = T_GetEnvOrDefault(
            apk_release_env,
            apk_release,
            sizeof(apk_release)  
    );    
    
    if(returned_ < 0)
        return returned_;
        
                        
    if(output != NULL)
    {
        returned_ = T_MoveCharBuffer(
                apk_release, 
                output, 
                output_buff_size
        );
        return returned_;
    }
    
    
    if (strcmp(apk_release, TMUX_PLATFORM_F_DROID_CHR) == 0)
        flag = TMUX_PLATFORM_F_DROID;
        
    if (strcmp(apk_release, TMUX_PLATFORM_GITHUB_CHR) == 0)
        flag = TMUX_PLATFORM_GITHUB;
        
    if(strcmp(apk_release, TMUX_PLATFORM_PLAY_STORE_CHR) == 0)
        flag = TMUX_PLATFORM_PLAY_STORE;
        

    return flag;
}


int TgetAndroidSdkVersion(TUint* output)
{
    const char* android_sdk_version_env = "ANDROID__BUILD_VERSION_SDK";
    const char* sdk_version;
    int returned_;
    int version_num;
    
          
    returned_ = T_Getenv(
            android_sdk_version_env, 
            &sdk_version, 
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
        
        
    returned_ = T_TypeCnvrt(
            sdk_version,
            TYPE_CNVRT_INT,
            (TPtr*)&version_num
    );
    
    if(returned_ < 0)
        return returned_;
        


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
    int sdk_version;
    
          
    returned_ = T_Getenv(
            termux_sdk_version_env, 
            &termux_sdk_version, 
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
        
    returned_ = T_TypeCnvrt(
            termux_sdk_version,
            TYPE_CNVRT_INT,
            (TPtr*)&sdk_version
    );
    

    if(sdk_version <= 0 || sdk_version > 100)
    {
        T_setError("termux vesion index out of range (%d).. its either conversion failed or a miscondigured environment variable is set", sdk_version);
        return TMUX_FAILED;
    }
    
    if(output == NULL)
        return sdk_version;
        
        
    *output = (TUint)sdk_version;            
    return returned_;

        
}




