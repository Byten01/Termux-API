

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Turdefs.h"
#include "TurHelper.h"



extern "C" {

    // error handling things
    
    const static int  T_err_buff_size = 1024; 
    static thread_local char T_ErrmsgBuffer[T_err_buff_size];
    /* 
    this prints the char buffer directly onto the terminal
    so you dont need to call T_getError()
    */
    static bool T_debugPrint = true;
    
    
    
    void T_clearError()
    {
        ClearCharBuffer(T_ErrmsgBuffer, T_err_buff_size);
    }
    
    
    const char* T_getError()
    {
        return T_ErrmsgBuffer;
    }
    
    int T_setError(const char* Errormsg)
    {
        if(!Errormsg)    
            return TMUX_FAILED;
           
        
        if(T_debugPrint)
        {
            std::cerr << "Termux API error: " << Errormsg << "\n";
            return TMUX_SUCCESS;
        }
        
        T_clearError();        
        return MoveCharBuffer(Errormsg , T_ErrmsgBuffer, T_err_buff_size);
    }
    
    
    
    
    // buffer based things
    
    
    
    int MoveCharBuffer(const char* input  , char* output , const int output_size) 
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
        
        std::strncpy(output , input , output_size);
        output[output_size - 1] = '\0';
        return TMUX_SUCCESS;
     
    }
    
    
    void ClearCharBuffer(char* buffer , const int buffer_size)
    {
        memset(buffer, 0, buffer_size);
    }
    






}