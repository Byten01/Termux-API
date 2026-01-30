
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

typedef enum 
{
    TMUX_DBG_INFO,
    TMUX_DBG_ERROR,
    TMUX_DBG_FATAL
    
} TMux_Dbg_Flags;


int T_setError(const char* fmt, ...);
const char* T_getError();
int T_clearError();


void T_logError(bool status);
bool T_logStatus();

int T_dbgPrint(TMux_Dbg_Flags flag, const char* fmt, ...);

#define DBG_INFO(...) T_dbgPrint(TMUX_DBG_INFO, ##__VA_ARGS__)
#define DBG_ERROR(...) T_dbgPrint(TMUX_DBG_ERROR, ##__VA_ARGS__)
#define DBG_FATAL(...) T_dbgPrint(TMUX_DBG_FATAL, ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif