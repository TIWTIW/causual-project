#ifndef _ZFT_UNINITIALIZED_H
#define _ZFT_UNINITIALIZED_H

#include "zft_construct.h"
#include "../algorithms/zft_algo.h"

namespace zft
{
template <class ForwordIterator, class Size, class T>
inline ForwordIterator uninitialized_fill_n(ForwordIterator first,
                                            Size n, const T &x)
{
    return __uninitialized_fill_n(first, n, x, value_type(first));
}

template <class ForwordIterator, class Size, class T, class T1>
inline ForwordIterator __uninitialized_fill_n(ForwordIterator first,
                                             Size n, const T &x, T1 *)
{
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

template <class ForwordIterator, class Size, class T>
inline ForwordIterator __uninitialized_fill_n_aux(ForwordIterator first,
                                                 Size n, const T &x,
                                                 __true_type)
{
    return fill_n(first, n, x);
}

template <class ForwordIterator, class Size, class T>
inline ForwordIterator __uninitialized_fill_n_aux(ForwordIterator first,
                                                 Size n, const T &x,
                                                 __false_type)
{
    ForwordIterator cur = first;
    for(; n > 0; --n, ++cur)
        construct( &(*cur), x );
    return cur;
}

template <class InputIterator, class ForwordIterator>
inline ForwordIterator
uninitialized_copy_(InputIterator first, InputIterator last,
                    ForwordIterator result)
{
    return __uninitialized_copy(fist, last, result, value_type(result));
}

template <class InputIterator, class ForwordIterator, class T>
inline ForwordIterator
__uninitialized_copy(InputIterator first, InputIterator last,
                     ForwordIterator result, T*)
{
    typedef typename __type_traits<T>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, result, is_POD());
}

template <class InputIterator, class ForwordIterator>
inline ForwordIterator
__uninitialized_copy_aux(InputIterator first, InputIterator last,
                         ForwordIterator result, __true_type)
{
    return copy(first, last, result);
}

template <class InputIterator, class ForwordIterator>
inline ForwordIterator
__uninitialized_copy_aux(InputIterator first, InputIterator last,
                         ForwordIterator result, __false_type)
{
    ForwordIterator cur = result;
    for(; first != last; ++first, ++cur)
        construct(&*cur, *first);

    return cur;
}

template <class ForwordIterator, class T>
inline void uninitialized_fill(ForwordIterator first,
                               ForwordIterator last, const T &x)
{
    __uninitialized_fill(first, last, x, value_type(first));
}

template <class ForwordIterator, class T, class T1>
inline void __uninitialized_fill(ForwordIterator first,
                                 ForwordIterator last, const T &x, T1 *)
{
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    __uninitialized_fill_aux(first, last, x, is_POD());
}

template <class ForwordIterator, class T>
inline void
__uninitialized_fill_aux(ForwordIterator first, ForwordIterator last,
                         const T &x, __true_type)
{
    fill(first, last, x);
}

template <class ForwordIterator, class T>
inline void
__uninitialized_fill_aux(ForwordIterator first, ForwordIterator last,
                         const T &x, __false_type)
{
    ForwordIterator cur = first;
    for(; cur != last; ++cur)
        construct(&*cur, x);
}

}

#endif
