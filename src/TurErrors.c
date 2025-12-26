
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>


#include "TurErrors.h"
#include "Turdefs.h"
#include "TurHelper.h"

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
    
    #ifdef TURERRORS_DBGPRINT
        printf("%s\n", T_ErrmsgBuffer);
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


