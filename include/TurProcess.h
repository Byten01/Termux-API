
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>

int Tlogout();
int TgetParentPgid(pid_t* output);
int TsendSignalToPid(pid_t pid, int signal);


#ifdef __cplusplus
}
#endif