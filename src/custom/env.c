


#include <stdlib.h>
#include <string.h>

#include "custom/buffer.h"
#include "custom/env.h"
#include "Turdefs.h"
#include "TurErrors.h"

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



