#ifndef _ZFTCONSTRUCT_
#define _ZFTCONSTRUCT_

#include <new.h>

namespace zft
{

template<class T1, class T2>
inline void construct(T1 *p, const T2 &value)
{
    new (p) T1(value);
}

template <class T>
inline void destroy(T *pointer)
{
    pointer->~T();
}

template <class ForwordIterator>
inline void destroy(ForwordIterator first, ForwordIterator last)
{
    __destroy(first, last, value_type(first));
}

template <class ForwordIterator, class T>
inline void __destroy(ForwordIterator first, ForwordIterator last, T*)
{
    typedef typename __type_traits<T>::has_trival_destructor trival_destructor;
    __destroy_aux(first, last, trival_destructor());
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
}

#endif
