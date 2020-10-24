/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

//utilize gameboy sounds

#ifndef BLARGG_COMMON_H
#define BLARGG_COMMON_H

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>


#if __GNUC__ >= 3 || _MSC_VER >= 1100
    #define BLARGG_RESTRICT __restrict
#else
    #define BLARGG_RESTRICT
#endif


#ifndef STATIC_CAST
    #if __GNUC__ >= 4
        #define STATIC_CAST(T,expr) static_cast<T> (expr)
        #define CONST_CAST(T,expr) const_cast<T> (expr)
    #else
        #define STATIC_CAST(T,expr) ((T) (expr))
        #define CONST_CAST(T,expr) ((T) (expr))
    #endif
#endif

#endif