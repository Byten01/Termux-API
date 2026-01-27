
#include <stdlib.h>
#include <string.h>


#include "TurErrors.h"
#include "Turdefs.h"


int T_MoveCharBuffer(const char* input  , char* output , int output_size) 
{
        
    if(!input) 
    {
        T_setError("failed to move char buffer, given input is empty or invalid");
        return TMUX_FAILED;
    }

    const int input_string_size = strlen(input);
    
    if(output == NULL)
        return (int)input_string_size + 1;
        
    
    if(output_size <= input_string_size) 
    {
        T_setError("failed to move char buffer, the output allocated buffer size is less than the string size");
        return TMUX_INSUFFICIENT_BUFFER_SIZE;
    }
    
    strncpy(output , input , output_size - 1);
    output[output_size - 1] = '\0';
    return TMUX_SUCCESS;

}


void T_ClearCharBuffer(char* buffer , int buffer_size)
{
    memset(buffer, 0, buffer_size);
}