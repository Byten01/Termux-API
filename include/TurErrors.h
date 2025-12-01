
#pragma once

#ifdef __cplusplus
extern "C" {
#endif



int T_setError(const char* fmt, ...);
const char* T_getError();
int T_clearError();



#ifdef __cplusplus
}
#endif