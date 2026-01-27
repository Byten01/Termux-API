
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>


int T_SendSignalToPid(pid_t pid, int signal);
int T_GetParentPgid(pid_t* output);


#ifdef __cplusplus
}
#endif

