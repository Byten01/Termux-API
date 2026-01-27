
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#include "Turdefs.h"
#include "custom/memory.h"
#include "TurErrors.h"
#include "custom/buffer.h"
#include "custom/file.h"


int T_HaveAccess(const char* filepath, int flags)
{
    return access(filepath , flags);
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