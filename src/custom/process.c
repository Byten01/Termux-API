
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#include "Turdefs.h"
#include "TurErrors.h"
#include "custom/process.h"

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

