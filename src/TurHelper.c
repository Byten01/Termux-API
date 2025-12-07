

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

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
   int returned_;
   
   if((returned_ = T_MemAlloc((TPtr*)output, str_size + 1)) < 0)
       return returned_;
   
   strcpy(*output, env_);
   return TMUX_SUCCESS;

}

// buffer based things



int T_MoveCharBuffer(const char* input  , char* output , int output_size) 
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


void T_ClearCharBuffer(char* buffer , int buffer_size)
{
    memset(buffer, 0, buffer_size);
}



int T_MemAlloc(TPtr* allocator_Ptr , TUint alloc_size)
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
    
    
    if(!allocated_Ptr || !*allocated_Ptr)
    {
        T_setError("failed to free allocated memory, pointer is already NULL or invalid");
        return TMUX_FAILED;
    }
    
    free(*allocated_Ptr);
    *allocated_Ptr = NULL;
    return TMUX_SUCCESS;
}






int T_sendSignalToPid(pid_t Pid, int signal) 
{

    if(Pid == 0 || signal <=0)
    {
        T_setError("failed to kill process by process id, invalid args given");
        return TMUX_FAILED;
    }
        
    if(kill(Pid, signal) < 0)
    {
        T_setError("failed to kill process id %u, Error: %s", Pid, strerror(errno));
        return TMUX_FAILED;
    }
    return TMUX_SUCCESS;
}

