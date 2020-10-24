/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

#ifndef BLARGG_SOURCE_H
#define BLARGG_SOURCE_H

#include <assert.h>

//meant for checking caller-supplied parameters and operations that are outside control of module
#undef require
#define require(expr) assert(expr)

//similar to printf except goes to debugging console
static inline void blargg_dprintf_(const char*, ...) { }
#undef dprintf
#define dprintf (1) ? (void) 0 : blargg_dprintf_

//if expr is false, prints file and line # to debug console, then continues. Flagging potential problems
#undef check
#define check(expr) ((void) 0)


// If ptr is NULL, returns "Out of memory" error string, otherwise continues normally.
#undef  CHECK_ALLOC
#define CHECK_ALLOC( ptr ) do { if ( (ptr) == 0 ) return "Out of memory"; } while ( 0 )

// The usual min/max functions for built-in types.
//
// template<typename T> T min( T x, T y ) { return x < y ? x : y; }
// template<typename T> T max( T x, T y ) { return x > y ? x : y; }
#define BLARGG_DEF_MIN_MAX( type ) \
	static inline type blargg_min( type x, type y ) { if ( y < x ) x = y; return x; }\
	static inline type blargg_max( type x, type y ) { if ( x < y ) x = y; return x; }

BLARGG_DEF_MIN_MAX( int )
BLARGG_DEF_MIN_MAX( unsigned )
BLARGG_DEF_MIN_MAX( long )
BLARGG_DEF_MIN_MAX( unsigned long )
BLARGG_DEF_MIN_MAX( float )
BLARGG_DEF_MIN_MAX( double )

#undef  min
#define min blargg_min

#undef  max
#define max blargg_max

// typedef unsigned char byte;
typedef unsigned char blargg_byte;
#undef  byte
#define byte blargg_byte

// deprecated
#define BLARGG_CHECK_ALLOC CHECK_ALLOC
#define BLARGG_RETURN_ERR RETURN_ERR

// BLARGG_SOURCE_BEGIN: If defined, #included, allowing redefition of dprintf and check
#ifdef BLARGG_SOURCE_BEGIN
	#include BLARGG_SOURCE_BEGIN
#endif

#endif

