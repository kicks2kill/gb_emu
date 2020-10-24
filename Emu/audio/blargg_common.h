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

#endif