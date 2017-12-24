#ifndef _ZFTCONSTRUCT_
#define _ZFTCONSTRUCT_

#include <new>
#include "iterators/zft_type_traits.h"
#include "iterators/zft_iterator.h"

namespace zft
{

//placement new
//construct a T2 class object at address p
//T2 should be from T1??
template<class T1, class T2>
inline void construct(T1 *p, const T2 &value)
{
    new (p) T1(value);
}

//just destruct
template <class T>
inline void destroy(T *pointer)
{
    pointer->~T();
}

template <class ForwordIterator>
inline void
__destroy_aux(ForwordIterator first, ForwordIterator last, __false_type)
{
    for(; first < last; ++first)
        destroy(&(*first));
}

template <class ForwordIterator>
inline void
__destroy_aux(ForwordIterator, ForwordIterator, __true_type)
{

}
template <class ForwordIterator, class T>
inline void __destroy(ForwordIterator first, ForwordIterator last, T*)
{
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
}

//destroy the iterator range first & last
//becaue not all objects have destructor
//so it's divided into two categories
//if there's no trivial_destructor, call destroy above
//if there's trivial_destructor, do nothing
template <class ForwordIterator>
inline void destroy(ForwordIterator first, ForwordIterator last)
{
    __destroy(first, last, value_type(first));
}

}

#endif
