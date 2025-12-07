
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
    pid_t shell = getppid();
    pid_t group = getpgid(shell);
    kill(-group, SIGHUP);
}

