

#include <stdlib.h>
#include <string.h>

#include "Turdefs.h"
#include "TurHelper.h"
#include "TurErrors.h"


extern "C" {



// Environment variable

const char* T_Getenv(const char* Envname)
{
        
    if(!Envname) 
    {
        T_setError("invalid args given to Getenv");
        return NULL;
    }
    
   return getenv(Envname);
    
    
}

// buffer based things



int T_MoveCharBuffer(const char* input  , char* output , const int output_size) 
{
        
    if(!input) 
    {
        T_setError("failed to move char buffer, given input is empty or invalid");
        return TMUX_FAILED;
    }
    
    const int input_string_size = strlen(input) + 1;
    
    if(output_size < input_string_size) 
    {
        T_setError("failed to move char buffer, the output allocated buffer size is less than the string size");
        return TMUX_INSUFFICIENT_BUFFER_SIZE;
    }
    
    strncpy(output , input , output_size);
    output[output_size - 1] = '\0';
    return TMUX_SUCCESS;

}


void T_ClearCharBuffer(char* buffer , const int buffer_size)
{
    memset(buffer, 0, buffer_size);
}




}