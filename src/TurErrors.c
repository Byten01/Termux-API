
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>


#include "TurErrors.h"
#include "Turdefs.h"
#include "custom/buffer.h"
#include "custom/memory.h"


#define ANSI_COLOR_RED_BOLD "\033[1;91m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



char* T_ErrmsgBuffer;
bool  T_LogError = true;

int T_setError(const char* fmt, ...) 
{
           
    if(!T_LogError)
        return TMUX_SUCCESS;
    
    if (!fmt)
        return TMUX_INVALID_PTR;
        
        
    int size_needed;
    char *new_buffer;
    int returned_;
    
    va_list args;
    
                    
    va_start(args, fmt);
   
    size_needed = vsnprintf(
            NULL, 
            0, 
            fmt, 
            args
    ) + 1; // +1 for '\0'
    
    va_end(args);

    
    returned_ = T_MemAlloc(
            (TPtr*)&new_buffer, 
            size_needed
    );

    if(returned_ < 0)
        return returned_;

    va_start(args, fmt);
    
    vsnprintf(
        new_buffer, 
        size_needed, 
        fmt, 
        args
    );
    
    va_end(args);


    T_clearError();
    T_ErrmsgBuffer = new_buffer;
    
    #ifdef LIB_DBGPRINT
        DBG_ERROR("Direct error output : %s", T_ErrmsgBuffer);
    #endif

    return TMUX_SUCCESS;
}


const char* T_getError()
{
    if(!T_ErrmsgBuffer)
        return "";
        
    return T_ErrmsgBuffer;
}

int T_clearError()
{
    if(T_ErrmsgBuffer)
    {
        free(T_ErrmsgBuffer);
        T_ErrmsgBuffer = NULL;
    }
    
    return TMUX_SUCCESS;
}



void T_logError(bool status)
{
    T_LogError = status;
    
    if(T_LogError && T_ErrmsgBuffer)
    {
        T_MemFree((TPtr*)&T_ErrmsgBuffer);
    }
}


bool T_logStatus()
{
    return T_LogError;
}



int T_dbgPrint(TMux_Dbg_Flags flag, const char* fmt, ...)
{
               
    #ifndef LIB_DBGPRINT
        return 1;
    #endif
        

    int size_needed;    
    int returned_;
    
    va_list args;
    
                    
    va_start(args, fmt);
   
    size_needed = vsnprintf(
            NULL, 
            0, 
            fmt, 
            args
    ) + 1; // +1 for '\0'
    
    va_end(args);

    
    char *new_buffer[size_needed];

    va_start(args, fmt);
    
    vsnprintf(
        new_buffer, 
        size_needed, 
        fmt, 
        args
    );                       
    va_end(args);
    
    
    switch(flag)
    {
        case TMUX_DBG_INFO:
            printf(
                "[ " 
                ANSI_COLOR_YELLOW
                "INFO"
                ANSI_COLOR_RESET
                " ] "
                "%s\n",
                new_buffer
            );
            break;
            
        case TMUX_DBG_ERROR:
            printf(
                "[ "
                ANSI_COLOR_RED
                "ERROR"
                ANSI_COLOR_RESET
                " ] "
                "%s\n",         
                new_buffer             
            );
            break;
            
            
        case TMUX_DBG_FATAL:
            printf(
                "[ "
                ANSI_COLOR_RED_BOLD
                "FATAL"
                ANSI_COLOR_RESET
                " ] "
                "%s\n",
                new_buffer 
            );
            break;
            
        
    }
    return 0;

}

