

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include "Turdefs.h"
#include "TurHelper.h"
#include "TurErrors.h"




// Environment variable

int T_Getenv(const char* Envname, const char** output, int* get_output_size)
{
        
    if(!Envname) 
    {
        T_setError("envname is NULL or invalid");
        return TMUX_INVALID_PTR;
    }
    
   const char* env_ = getenv(Envname);
   
   if(!env_)
   {
       T_setError("failed to get env of %s", Envname);
       return TMUX_FAILED;
   }
   
   if(output)
   {
       *output = env_;
   }
   
   if(get_output_size)
       *get_output_size = strlen(env_);
      
   
   
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



int T_HaveAccess(const char* filepath, int flags)
{
    return access(filepath , flags);
}


int T_SendSignalToPid(pid_t pid, int signal) 
{

    if(pid == 0 || signal <=0)
    {
        T_setError("failed to kill process by process id, invalid args given");
        return TMUX_FAILED;
    }
        
    if(kill(pid, signal) < 0)
    {
        T_setError("failed to kill process id %u, Error: %s", pid, strerror(errno));
        return TMUX_FAILED;
    }
    return TMUX_SUCCESS;
}




int T_OpenFileDescriptor(const char* filepath, char* mode, TFile** output, TFile_Mode open_mode)
{
    
    if(!filepath || !mode || !output)
    {
        T_setError("failed to open file discriptor, invalid arguments given");
        return TMUX_INVALID_PTR;    
    }
    
    TFile* fp = NULL;
    
    
    switch(open_mode)
    {
        case TMUX_FTYPE_NORMAL:
        {            
            fp = fopen(filepath , mode);             
            break;           
        }
        
        case TMUX_FTYPE_PIPE: 
        {
            fp = popen(filepath, mode);
            break;
        }
    }
    

    if(!fp)
    {
        printf("an error occured while opening file (%s) with (%s) permission. Error: ", filepath , mode, strerror(errno));
        return TMUX_FAILED;
    }
    
    if(output)
    {
        *output = fp;
    }
            
    return TMUX_SUCCESS;
}



int T_CloseFileDescriptor(TFile* handle, TFile_Mode close_mode, int* returncode)
{
    if (!handle) {
        T_setError("file handle is NULL");
        return TMUX_INVALID_PTR;
    }
    
    int returned_ = 0;

    switch(close_mode)
    {
        case TMUX_FTYPE_NORMAL:
        {
            returned_ = fclose(handle);
            break;
        }
        
        case TMUX_FTYPE_PIPE:
        {
            returned_ = pclose(handle);
            break;
        }
    }
    
    
    if(returncode)
    {
        *returncode = returned_;
    }
    
    return TMUX_SUCCESS;
}



int T_FReadBufferD(TFile* fp, char** output) {
    
    
    if(!fp ||  !output)
    {
        T_setError("failed to dynamically read file buffer, file pointer is invalid or NULL");
        return TMUX_FAILED;
    }
    
    
    TUint cap = 1024;
    TUint len_total = 0;
    
    char *buffer_total;
   
   
    if(T_MemAlloc((TPtr*)&buffer_total, cap) < 0)
        return TMUX_FAILED;
        
    while (1) {
        
        size_t n = fread(
                buffer_total + len_total, 
                1, 
                cap - len_total, 
                fp
        );
        len_total += n;

        if (n == 0)
            break;

        if (len_total == cap) {
            cap *= 2;
            char *tmp = realloc(buffer_total, cap);
            
            if(!tmp)
            {
                T_MemFree((TPtr*)&buffer_total);
                T_setError("failed to realloc buffer in tmp");
                return TMUX_FAILED;
            }
                        
            buffer_total = tmp;
        }
    }
    
    buffer_total[len_total] = '\0';        
    *output = buffer_total;
    
    return TMUX_SUCCESS;
}



int T_GetParentPgid(pid_t* output)
{
    pid_t ppid = getppid();
    
    if(!ppid)
    {
        T_setError("failed to get ppid in GetParentPgid");
        return TMUX_FAILED;
    }
    
    pid_t pgid = getpgid(ppid);
    
    if(!pgid)
    {
        T_setError("failed to get pgid of %d", ppid);
        return TMUX_FAILED;
    }
    
    *output =  pgid;
    return TMUX_SUCCESS;
}






int T_ReadFile(const char* filepath , char* output, int output_buff_size)
{
    
    TFile* handle;
    char* buffer;
    int returned_;
    int f_returned_;
    
    if(!filepath)
    {
        T_setError("failed to read file, file path is NULL");
        return TMUX_INVALID_PTR;
    }
    
    
    returned_ = T_OpenFileDescriptor(
            filepath, 
            "r" , 
            &handle,
            TMUX_FTYPE_NORMAL
    );
    
    if(returned_ < 0)
        return returned_;
        
        

    returned_ = T_FReadBufferD(
            handle , 
            &buffer
    );
    

    if(returned_ < 0)
    {
        T_CloseFileDescriptor(
                handle, 
                TMUX_FTYPE_NORMAL, 
                NULL
        );
        return returned_;
    }
        
    returned_ = T_MoveCharBuffer(
            buffer, 
            output, 
            output_buff_size
    );
    
    T_MemFree((TPtr*)&buffer);
    
    T_CloseFileDescriptor(
            handle, 
            TMUX_FTYPE_NORMAL, 
            NULL
    );
    
    return returned_;
                     
    
}


int T_GetEnvOrDefault(const char* Envname, char* output, int output_buff_size)
{
    
    int returned_;
    const char* data;
    
    returned_ = T_Getenv(
            Envname,
            &data,
            NULL
    );
    
    if(returned_ < 0)
        return returned_;
        
        
    returned_ = T_MoveCharBuffer(
            data,
            output,
            output_buff_size
    );
    
    return returned_;
}