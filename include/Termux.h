

#pragma once


// main header of termux api to be included in projects


#ifndef __ANDROID__
    #error "this is a termux only api, so it should only be compiled in a termux environment"
#endif




#ifdef __cplusplus
extern "C" {
#endif


#include "Turdefs.h"
#include "TurHelper.h"
#include "Turfs.h"
#include "TurErrors.h"
#include "TurInfo.h"
#include "TurProcess.h"



#ifdef __cplusplus
}
#endif


