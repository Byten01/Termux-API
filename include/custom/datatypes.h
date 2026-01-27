

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    
    TYPE_CNVRT_INT,
    TYPE_CNVRT_LONG,
    TYPE_CNVRT_FLOAT,
    TYPE_CNVRT_DOUBLE,
    TYPE_CNVRT_UNSIGNED_INT
    
} TMux_TypeCnvrtFlags;



int T_TypeCnvrt(const char* data, TMux_TypeCnvrtFlags flag, void** output);


#ifdef __cplusplus
}
#endif

    