#ifndef _ZFT_STRING_H
#define _ZFT_STRING_H

#include "../memory/zft_default_alloc.h"
#include "../memory/zft_simple_alloc.h"
#include "../memory/zft_uninitialized.h"
#include <string.h>

namespace zft
{
template <class charT>
class char_traits
{
protected:
    typedef char_type charT;
    typedef int_type int;  //don't quite understand


public:
    static void assign(char_type &r, const char_type &a)
    {
        r = a;
    }

    static char_type *assign(char_type *p, size_t count, char_type a)
    {
        while(count-- > 0 && *p != charT())
            *p++ = a;

        return p;
    }

    static bool eq(char_type a, char_type b)
    {
        return a == b;
    }

    static bool lt(char_type a, char_type b)
    {
        return a < b;
    }

    static char_type *move(char_type *dest, const char_type *src, size_t count)
    {
        return memmove(dest, src, count);
    }

    static char_type *copy(char_type *dest, const char_type *src, size_t count)
    {
        return memcpy(dest, src, count);
    }

    static int compare(const char_type *s1, const char_type *s2, size_t count)
    {
        return memcmp(s1, s2, count);
    }

    static size_t length(const char_type *s)
    {
        size_t i = 0;
        while(*s++ != charT())
            ++i;

        return i;
    }

    static const char_type *find(const char_type *p, size_t count, const char_type &ch)
    {
        char_type *result = p;
        while(*result++ != ch && count-- > 0);

        return result;
    }

};

template <class charT,
          class Traits = zft::char_traits<charT>,
          class Allocator = zft::allocator<charT>>
class basic_string
{
    typedef traits_type Traits;
    typedef value_type charT;
    typedef allocator_type Allocator;
    typedef size_type Allocator::size_type;
    typedef difference Allocator::difference_type;
    typedef reference Allocator::reference;
    typedef const_reference Allocator::const_reference;
    typedef pointer Allocator::pointer;
    typedef const_pointer Allocator::const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef random_access_iterator_tag iterator_category;

protected:
    typedef simple_alloc<value_type, Allocator> char_allocator;

    iterator start;
    iterator finish;
    iterator end_of_storage;

//constructor
public:
    //simple constructor
    explicit basic_string(const Allocator &alloc = Allocator()) : char_allocator(simple_alloc<value_type, alloc>()), start(0), finish(0),end_of_storage(0)
    {}

    //fill the string with count ch
    basic_string(size_type count, charT ch,
            const Allocator &alloc = Allocator()) : char_allocator(simple_alloc<value_type, alloc>())
    {
        fill_initialize_n(count, ch);
    }

    //copy the count chars start at s to the allocated string
    basic_string(const charT *s, size_type count, const Allocator &alloc = Allocator()) : char_allocator(simple_alloc<value_type, alloc>())
    {
        copy_initialize(s, count);
    }

    //copy the full string end with "\0" to the new allocated string
    basic_string(const charT *s, const Allocator &alloc = Allocator()) : char_allocator(simple_alloc<value_type, alloc>())
    {
        size_type length = 0;
        const charT *s_tmp = s;
        while(*s_tmp++ != charT())
            ++length;

        copy_initialize(const_iterator(s), length);
    }

    //copy the range between first iterator  & last iterator
    template <class InputIterator>
    basic_string(InputIterator first, InputIterator last, const Allocator &alloc = Allocator()) : char_allocator(simple_alloc<value_type, alloc>())
    {
        InputIterator beg = first;
        size_type n = 0;
        while(beg++ != last)
            ++n;

        copy_initialize(const_iterator(beg), n);
    }

    basic_string(const basic_string &other)
    {
        char_allocator = other::char_allocator;
        start = other.start;
        finish = other.finish;
        end_of_storage = other.end_of_storage;
    }


public:
    ~basic_string()
    {
        char_allocator::deallocate(start, length());
    }
protected:

    void copy_initialize(const_iterator s, size_type n)
    {
        start = allocate_and_copy(s, n);
        finish = start + count;
        end_of_storage = finish;
    }

    iterator allocate_and_copy(const_iterator s, size_type n)
    {
        iterator result = char_allocator::allocate(n);
        iterator begin = s;
        iterator end = begin + n;
        uninitialized_copy(begin, end, result);
        return result;
    }

    void fill_initialize_n(size_type n, const value_type &value)
    {
        start = allocate_and_fill_n(count, ch);
        finish = start + count;
        end_of_storage = finish;
    }

    iterator allocate_and_fill_n(size_type n, const value_type &value)
    {
        iterator result = char_allocator::allocate(n);
        uninitialized_fill_n(result, n, value);
        return result;
    }
};
}

#endif
