#ifndef _ZFT_ALLOC_H
#define _Zft_ALLOC_H

#include "zft_malloc_alloc.h"

namespace zft
{

//my own definiation
//because it's used
//I guess it's the meaning that if it's thread safe
#define __NODE_ALLOCATOR_THREADS false


enum {__ALIGN = 8};
enum {__MAX_BYTES_ = 128};
enum {__NFREELISTS = __MAX_BYTES_ / __ALIGN};

template <bool threads, int inst>
class __default_alloc_template
{
private:
    //Round up to align bytes
    static size_t ROUND_UP(size_t bytes)
    {
        return ((bytes) + __ALIGN - 1) & ~(__ALIGN - 1);
    }

private:
    //union is useful
    //it either points to the next free link
    //or points to the client_data
    //as both can not exist at the same time
    union obj
    {
        union obj *free_list_link;
        char client_data[1];
    };

private:
    //the free_list self
    //every obj in the free_list is a pointer points to the first buffer
    static obj* volatile free_list[__NFREELISTS];
    //get the index in the free_list according to the needed bytes
    //the free_list is made up of 16 kinds of sizes of buffers
    static size_t FREELIST_INDEX(size_t bytes)
    {
        return (((bytes) + __ALIGN - 1) / __ALIGN - 1);
    }

    static void *refill(size_t n);
    static char *chunk_alloc(size_t size, int &nobjs);

    //the start of the free_list
    static char *start_free;
    //the end of the free_list
    static char *end_free;
    //the size of the allocated heap
    //because at first the heap(or free_list & buffer) will be allocated
    //just see this as a memory pool size
    static size_t heap_size;

public:
    static void *allocate(size_t n);
    static void deallocate(void *p, size_t n);
    static void *reallocate(void *p, size_t old_sz, size_t new_sz);
};

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::start_free = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj *volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] =
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

//allocate n bytes
//static can not be used outside class
template <bool threads, int inst>
void *__default_alloc_template<threads, inst>::allocate(size_t n)
{
    obj *volatile *my_free_list;
    obj *result;

    //if needed bytes is bigger than max bytes
    //just call malloc
    if(n > (size_t)__MAX_BYTES_)
    {
        return malloc_alloc::allocate(n);
    }

    //find the corresponding buffer list
    my_free_list = free_list + FREELIST_INDEX(n);
    //get result, because the link in free_list is always the free link
    result = *my_free_list;
    if(result == 0)
    {
        void *r = refill(ROUND_UP(n));
        return r;
    }

    //make the free_list link points to the next buffer
    *my_free_list = result->free_list_link;
    return result;
}

template <bool threads, int inst>
void __default_alloc_template<threads, inst>::deallocate(void *p, size_t n)
{
    obj *q = (obj *)p;
    obj *volatile *my_free_list;

    //if deallocated size is bigger than max_bytes, just call malloc_alloc
    //here exists a question
    //what if allocate 129 bytes
    //and deallocate 1 bytes?
    //or how can I know the parameter p is corresponding to the size n?
    if(n > (size_t)__MAX_BYTES_)
    {
        malloc_alloc::deallocate(p, n);
        return ;
    }

    //find the corresponding free_list buffer
    my_free_list = free_list + FREELIST_INDEX(n);

    //make the p points to the current free buffer and than make current free_list points to p
    q->free_list_link = *my_free_list;
    *my_free_list = q;
}

//refill the buffer corresponding to parameter n
//n is the size of the objs(or buffer)
template <bool threads, int inst>
void *__default_alloc_template<threads, inst>::refill(size_t n)
{
    int nobjs = 20;

    //first get nobjs free buffers
    //the nobjs is a reference
    //when return it maybe changed
    char *chunk = chunk_alloc(n, nobjs);
    obj *volatile *my_free_list;
    obj *result;
    obj *current_obj, *next_obj;
    int i;

    if( 1 == nobjs )
        return chunk;

    my_free_list = free_list + FREELIST_INDEX(n);

    //make my_free_list points to the next obj of the malloced buffer
    //make result points to the start of the malloced buffer
    result = (obj *)chunk;
    *my_free_list = next_obj = (obj *)(chunk + n);
    //in a word, construct the buffer to a linked list
    for(i = 1; ; ++i)
    {
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + n);
        if(nobjs - 1 == i)
        {
            current_obj->free_list_link = 0;
            break;
        }
        else
        {
            current_obj->free_list_link = next_obj;
        }
    }

    return result;
}

//allocate enough memory to the size bytes objects
template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::
chunk_alloc(size_t size, int &nobjs)
{
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;

    //if left bytes is enough
    if(bytes_left >= total_bytes)
    {
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else if(bytes_left >= size)   //if left bytes can just afford more than one object and less than nobj objects
    {
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else
    {
        //get 2 times the total_bytes so that wouldn't refill frequently
        //besides, + heap_size because the malloced heap_size is bigger, than the need memory may be larger
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        //if there is free memory left, than make use of them
        if(bytes_left > 0)
        {
            obj *volatile *my_free_list =
                free_list + FREELIST_INDEX(bytes_left);
            ((obj *)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }

        //call malloc to get enough bytes
        start_free = (char *)malloc(bytes_to_get);

        //if malloc failed, than travel the whole free_list to find enough memory
        if(0 == start_free)
        {
            int i;
            obj *volatile *my_free_list, *p;
            for(i = size; i <= __MAX_BYTES_; i += __ALIGN)
            {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if(0 != p)
                {
                    *my_free_list = p->free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;

                    return chunk_alloc(size, nobjs);
                }
            }

            end_free = 0;
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
        }

        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

# ifdef __USE_MALLOC
    typedef __malloc_alloc_template<0> malloc_alloc;
    typedef malloc_alloc alloc;
# else
    typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
# endif
}


#endif
