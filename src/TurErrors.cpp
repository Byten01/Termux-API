
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#include "TurErrors.h"
#include "Turdefs.h"


extern "C" {

char* T_ErrmsgBuffer;


int T_setError(const char* fmt, ...) {
    if (!fmt)
        return TMUX_INVALID_PTR;
        
        
    va_list args;
    va_start(args, fmt);

   
    int size_needed = vsnprintf(nullptr, 0, fmt, args) + 1; // +1 for '\0'
    va_end(args);


    char* new_buffer = (char*)malloc(size_needed);
    if (!new_buffer)
        return TMUX_FAILED_MALLOC;

    va_start(args, fmt);
    vsnprintf(new_buffer, size_needed, fmt, args);
    va_end(args);


    T_clearError();
    T_ErrmsgBuffer = new_buffer;

    return TMUX_SUCCESS;
}


const char* T_getError()
{
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


}

