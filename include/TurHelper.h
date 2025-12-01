
#pragma once

#ifdef __cplusplus
extern "C" {
#endif



int T_MoveCharBuffer(const char* input  , char* output , const int output_size);
void T_ClearCharBuffer(char* buffer , const int buffer_size);
const char* T_Getenv(const char* Envname);


#ifdef __cplusplus
}
#endif

