#pragma once


#include <stdio.h>

// custom datatypes 

typedef unsigned int TUint;
typedef unsigned char TUint8;
typedef void* TPtr;
typedef FILE TFile;

typedef enum 
{
    TMUX_FTYPE_NORMAL,
    TMUX_FTYPE_PIPE
    
} TFile_Mode;


// independent macros


#define TMUX_FAILED -1
#define TMUX_SUCCESS 0

#define TMUX_SYSTEM_PERMISSION_DENIED -10
#define TMUX_INSUFFICIENT_BUFFER_SIZE -11
#define TMUX_INVALID_PTR -12
#define TMUX_FAILED_MALLOC -13

#define TMUX_OUT_OF_RANGE -14
#define TMUX_INVALID_DATA -15
#define TMUX_OPEAREATION_NOT_PERMITTED -16


// file system based macros 

#define TMUX_BIN     (1 << 0)
#define TMUX_FR       (1 << 1)
#define TMUX_FRB    (TMUX_BIN | TMUX_R)

#define TMUX_FW       (1 << 2)
#define TMUX_FWB    (TMUX_BIN | TMUX_W)


#define TMUX_FOVERRIDE (1 << 3)




#define TMUX_INSUFFICIENT_STORAGE -102
#define TMUX_FILE_NOT_FOUND -103
#define TMUX_FILE_EMPTY -104
#define TMUX_FILE_IN_USE -105



// platform 

#define TMUX_PLATFORM_F_DROID                (1 << 0)
#define TMUX_PLATFORM_PLAY_STORE        (1 << 1)
#define TMUX_PLATFORM_GITHUB                   (1 << 2)
#define TMUX_PLATFORM_UNKNOWN           (1 << 3)










