/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/


#ifndef DEFINITIONS_h
#define DEFINITIONS_h

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define Log(msg, ...)


#define FLAG_ZERO 0x80
#define FLAG_SUB 0x40
#define FLAG_HALF 0x20
#define FLAG_NONE 0

#define GAMEBOY_WIDTH 160
#define GAMEBOY_HEIGHT 144

#define AUDIO_BUFFER 4096

#define SAVESTATE 0x28000000


#define MAX_ROM_SIZE 0x800000

#define InitPointer(pointer)((pointer) = NULL)
#define IsValidPointer(pointer)((pointer) != NULL)

#define SafeDelete(pointer) if(pointer != NULL) {delete pointer; pointer = NULL;}
#define SafeDeleteArray(pointer) if(pointer != NULL) {delete [] pointer; pointer = NULL;}

typedef void (*RamChangedCallback) (void);

enum Gameboy_Keys
{
    A_Key = 4,
    B_Key = 5,
    Start_Key = 7,
    Select_Key = 6,
    Right_Key = 0,
    Left_Key = 1,
    Up_Key = 2,
    Down_Key = 3
};

inline void LogFunc(const char* const msg, ...) 
{
    static int count = 1;
    char szBuf[512];

    va_list args;               //init an obj of this type so that subsequent calls to va_arg sequentially retrieve additional args passed to func
    va_start(args, msg);        //init variable arg list to retrieve additional args after param N
    vsprintf(szBuf,msg,args);   // store resulting content as a C string in buffer pointed to by s
    va_end(args);               //performs actions to facilitate normal return by a function that has used va_list to retrieve additional args

    printf("%d: %s\n", count, szBuf);

    count++;
}

inline uint8_t SetBit(const uint8_t value, const uint8_t bit) 
{
    return value | static_cast<uint8_t>(0x01 << bit);
}


inline uint8_t UnsetBit(const uint8_t value, const uint8_t bit)
{
    return value & (~(0x01 << bit));
}

inline bool IsSetBit(const uint8_t value, const uint8_t bit)
{
    return (value & (0x01 << bit)) != 0;
}

inline int AsHex(const char c)
{
    return c >= 'A' ? c - 'A' + 0xA : c - '0'; //this one is a bit confusing
} 

#endif