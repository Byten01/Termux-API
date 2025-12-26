
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

int T_setError(const char* fmt, ...);
const char* T_getError();
int T_clearError();


void T_logError(bool status);
bool T_logStatus();


#ifdef __cplusplus
}
#endif