#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>


#include "TurErrors.h"
#include "custom/datatypes.h"
#include "Turdefs.h"

#define LOG T_setError



typedef struct
{
    const char* data;
    const char* endptr;
    const char* type_name;

    int check_overflow;
    long long value;
    long long min;
    long long max;
    
} Container;

int ErrorHandler(Container* container) {
    
    
    const char* data = container->data;
    const char* endptr = container->endptr;
    const char* type_name = container->type_name;
    int check_overflow = container->check_overflow;
    
    
    long long value = container->value;
    long long min = container->min;
    long long max = container->max;
    

    if (data == NULL) {
        LOG("Type convertor : Input data is NULL");
        return TMUX_INVALID_DATA;
    }

    if (endptr == data)
    {        
        LOG("Error: No valid conversion could be performed for %s\n", type_name);
        return TMUX_INVALID_DATA;
    }

    if (*endptr != '\0') 
    {
        LOG("Error: Invalid characters found after number for %s\n", type_name);
        return TMUX_INVALID_DATA;
    }

    if (errno == ERANGE) 
    {
        LOG("Error: Overflow detected for %s\n", type_name);
        return TMUX_OUT_OF_RANGE;
    }


    if ((check_overflow > 0) && (value > max || value < min)) {
        LOG("Error: Overflow detected for %s (range: %lld to %lld)\n",
                type_name, min, max);
        return TMUX_OUT_OF_RANGE;
    }

    return TMUX_SUCCESS;
}

int T_TypeCnvrt(const char* data, TMux_TypeCnvrtFlags flag, void** output) {
    
    
    if (output == NULL) {
        fprintf(stderr, "Error: Output argument pointer is NULL\n");
        return TMUX_INVALID_PTR;
    }

    char* endptr;
    int returned_;
    Container container;

    container.data = data;
    errno = 0;

    switch (flag) {
        
        case TYPE_CNVRT_INT: {
            
            long temp = strtol(data, &endptr, 10);

            container.endptr = endptr;
            container.value = temp; 
            container.min = INT_MIN;
            container.max = INT_MAX;
            container.type_name = "INT";
            container.check_overflow = 1;

            returned_ = ErrorHandler(&container);

            if(returned_ < 0)  
                return returned_;

            *(int*)output = (int)temp;
            break;
        }

        case TYPE_CNVRT_LONG: {
            
            long temp = strtol(data, &endptr, 10);

            container.endptr = endptr;
            container.value = temp;
            container.check_overflow = 0;
            container.type_name = "LONG";

            returned_ = ErrorHandler(&container);

            if(returned_ < 0)
                return returned_;

            *(long*)output = temp;
            break;
        }

        case TYPE_CNVRT_FLOAT: {
            
            float temp = strtof(data, &endptr);

            container.endptr = endptr;
            container.check_overflow = 0;
            container.type_name = "FLOAT";

            returned_ = ErrorHandler(&container);

            if(returned_ < 0)
                return returned_;

            *(float*)output = (float)temp;
            break;
        }

        case TYPE_CNVRT_DOUBLE: {
            
            double temp = strtod(data, &endptr);
            
            container.endptr = endptr;
            container.check_overflow = 0;
            container.type_name = "DOUBLE";

            returned_ = ErrorHandler(&container);

            if(returned_ < 0)
                return returned_;

            *(double*)output = temp;
            break;
        }

        case TYPE_CNVRT_UNSIGNED_INT: {
            
            unsigned long temp = strtoul(data, &endptr, 10);

            container.endptr = endptr;
            container.value = (long long)temp;
            container.min = 0;
            container.max = UINT_MAX;
            container.type_name = "UINT";
            container.check_overflow = 1;

            returned_ = ErrorHandler(&container);

            if(returned_ < 0)
                return returned_;

            *(unsigned int*)output = (unsigned int)temp;
            break;
        }

        default:
            fprintf(stderr, "Error: Invalid conversion flag specified\n");
            return TMUX_FAILED;
    }

    return TMUX_SUCCESS;
}

