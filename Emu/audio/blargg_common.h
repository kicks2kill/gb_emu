/*
   Nintendo Game boy Emulator
   Copyright (C) 2020 Orin
*/

//utilize gameboy sounds - set up common environment for Shay Green's blargg library

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

#ifndef blargg__err
    typedef const char* blargg__err;
#endif


/*
    Borrowing from Gearboy. - lightweight vector of POD type
*/

template <class T>
class blargg_vector {
    T* begin_;
    size_t size_;
public:
    blargg_vector() : begin_ {0}, size_ {0} {}
    ~blargg_vector() {free( begin_ );}
    size_t size() const {return size_;}
    T* begin() const {return begin_;}
    T* end() const {return begin_ + size_;}
    blargg__err resize (size_t n)
    {
        void* p = realloc(begin_, n * sizeof (T));
        if (p)
            begin_ = (T*) p;
        else if (n > size_) //realloc failure only a problem if expanding
            return "Out of memory. sorry bud";
        size_ = n;
        return 0;
    }
    void clear() {void* p = begin_; begin_ = 0; size_ = 0; free(p);}
    T& operator [] (size_t n) const 
    {
        assert(n <= size_); //allow past-the-end value
        return begin_[n];
    }
};

#ifndef BLARGG_DISABLE_NOTHROW
    //throw spec mandatory in ISO C++ when operater new can return NULL
    #if __cplusplus >= 199711 || __GNUC__ >= 3
        #define BLARGG_THROWS(spec) throw spec
    #else
        #define BLARGG_THROWS(spec)
    #endif
    #define BLARGG_DISABLE_NOTHROW \
        void* operator new (size_t n) BLARGG_THROWS(()) {return malloc(n);} \
        void operater delete (void* p) {free (p);}
    #define BLARG__NEW new
#else
    #include <new>
    #define BLARGG_NEW new (std::nothrow)
#endif

//BLARGG_4CHAR('n,'n','n','n') equates to 'nnnn' as a four character int constant
// #define BLARGG_4CHAR(a,b,c,d) 

//BLARGG_COMPILER_HAS_BOOL --- if 0, provide bool support for old compilers. if 1, compiler is assumed to support bool. If neither and undefined, availability is determined
#ifndef BLARGG_COMPILER_HAS_BOOL
    #if defined (__MWERKS__)
        #if !__option(bool)
            #define BLARGG_COMPILER_HAS_BOOL 0
        #endif
    #elif defined (_MSC_VER)
        #if _MSC_VER < 1100
            #define BLARGG_COMPILER_HAS_BOOL 0
        #endif
    #elif defined (__GNUC__)
        //supports bool
    #elif __cplusplus < 199711
        #define BLARGG_COMPILER_HAS_BOOL 0
    #endif
#endif

//blargg_long is at least 32 bits and possibly an int
#if INT_MAX < 0x7FFFFFFF || LONG_MAX == 0x7FFFFFFF
    typedef long blargg_long;
#else
    typedef int blargg_long;
#endif

#if UINT_MAX < 0x7FFFFFFF || ULONG_MAX == 0x7FFFFFFF
    typedef unsigned long blargg_ulong;
#else
    typedef unsigned blargg_ulong;
#endif







#endif