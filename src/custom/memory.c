
#include <stdlib.h>


#include "Turdefs.h"
#include "TurErrors.h"

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
