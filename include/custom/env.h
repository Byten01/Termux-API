


#pragma once

#ifdef __cplusplus
extern "C" {
#endif


int T_Getenv(const char* Envname, const char** output, int* get_output_size);
int T_GetEnvOrDefault(const char* Envname, char* output, int output_buff_size);

#ifdef __cplusplus
}
#endif

