#ifndef _ZFT_MALLOC_H
#define _ZFT_MALLOC_H

#if 0
#  include <new>
# define __THROW_BAD_ALLOC throw bad_alloc
#else
#  include <iostream>
#  define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);
#endif

namespace zft
{
//commonly thread safe, efficient
template <int inst>
class __malloc_alloc_template
{
private:
    //for memory is not enough
    //oom : out of memory
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static void (* __malloc_alloc_oom_handler)();

public:
    //call malloc to get memory
    //if the calling failed, call oom_malloc
    static void *allocate(size_t n)
    {
        void *result = malloc(n);
        if(0 == result)
            result = oom_malloc(n);

        return result;
    }

    //just call free to free the memory
    static void deallocate(void *p, size_t /* n */)
    {
        free(p);
    }

    //called reallo, if failed, call oom_realloc
    static void *reallocate(void *p, size_t  old_sz, size_t new_sz)
    {
        void *result = realloc(p, new_sz);
        if(0 == result)
            result = oom_realloc(p, new_sz);
        return result;
    }

    //function name set_malloc_handler
    //return a pointer which points to a non-parameter and
    //void return value function
    //its parameter is a function pointer which points to
    //a non-parameter and void return value function
    static void (* set_malloc_handler(void (*f)()))()
    {
        void (* old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return old;
    }
};

//malloc_alloc out-of-memory handling
template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

//call __malloc_alloc_oom_handler to handle the case that there is no enough memory
//however, the __malloc_alloc_oom_handler is not finished, so here an exception would be thrown
template <int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void (* my_malloc_handler)();
    void *result;

    for(;;)
    {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();
        result = malloc(n);
        if(result)
            return result;
    }
}

//same as above
template <int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
    void (* my_malloc_handler)();
    void *result;

    for(;;)
    {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();
        result = realloc(p, n);
        if(result)
            return result;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;
}

#endif
