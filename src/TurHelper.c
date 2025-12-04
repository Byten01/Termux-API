

#include <stdlib.h>
#include <string.h>

#include "Turdefs.h"
#include "TurHelper.h"
#include "TurErrors.h"




// Environment variable

int T_Getenv(const char* Envname, char** output)
{
        
    if(!Envname || !output) 
    {
        T_setError("invalid args given to Getenv");
        return TMUX_INVALID_PTR;
    }
    
   const char* env_ = getenv(Envname);
   
   if(!env_)
   {
       T_setError("failed to get env of %s", Envname);
       return TMUX_FAILED;
   }
   
   
   const unsigned int str_size = strlen(env_);
   
   *output = malloc(str_size + 1);
   
   if(!*output) 
   {
       T_setError("failed to allocate buffer via malloc");
       return TMUX_FAILED_MALLOC;
   }
   
   strcpy(*output, env_);
   return TMUX_SUCCESS;

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



int T_MemAlloc(TPtr* allocator_Ptr , const TUint alloc_size)
{
    
    if(!allocator_Ptr || alloc_size == 0)
    {
        T_setError("failed to allocate memory, invalid arguments given to T_MemAlloc");
        return TMUX_FAILED;
    }
    
    *allocator_Ptr = malloc(alloc_size);
    
    if(!*allocator_Ptr)
    {
        T_setError("failed to allocate memory, malloc failed");
        *allocator_Ptr = NULL;
        return TMUX_FAILED_MALLOC;
        
    }
        
    return TMUX_SUCCESS;
}


int T_MemFree(TPtr* allocated_Ptr) 
{
    if(!*allocated_Ptr || allocated_Ptr)
    {
        T_setError("failed to free allocated memory, pointer is already NULL or invalid");
        return TMUX_FAILED;
    }
    
    free(*allocated_Ptr);
    return TMUX_SUCCESS;
}
