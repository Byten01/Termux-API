
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#include "Turdefs.h"
#include "TurInfo.h"
#include "TurProcess.h"
#include "TurHelper.h"


int Tlogout()
{
    pid_t parent_pid_grp;
    int returned_;
    
    returned_ = T_GetParentPgid(&parent_pid_grp);
    
    if(returned_ < 0)
        return returned_;
        
        
    returned_ = T_SendSignalToPid(-parent_pid_grp, SIGHUP);
    return returned_;
        
}


int TgetParentPgid(pid_t* output)
{
    pid_t parent_pgid;
    int returned_;
    
    returned_ = T_GetParentPgid(&parent_pgid);
    
    if(returned_ < 0)
        return returned_;
        
        
    if(output != NULL)
        *output = parent_pgid;
        return returned_;
        
    return (int)parent_pgid;
}

int TsendSignalToPid(pid_t pid, int signal)
{
    return T_SendSignalToPid(pid, signal);
}

