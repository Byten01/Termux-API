
#pragma once

#ifdef __cplusplus
extern "C" {
#endif



int MoveCharBuffer(const char* input  , char* output , const int output_size);
void ClearCharBuffer(char* buffer , const int buffer_size);



void T_clearError();
const char* T_getError();
int T_setError(const char* Errormsg);


#ifdef __cplusplus
}
#endif

