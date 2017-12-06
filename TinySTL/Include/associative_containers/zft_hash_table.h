#ifndef _ZFT_HASH_TABLE_H
#define _ZFT_HASH_TABLE_H

#include "../memory/zft_construct.h"
#include "../memory/zft_default_alloc.h"
#include "../memory/zft_simple_alloc.h"
#include "../memory/zft_uninitialized.h"
#include "zft_pair.h"
#include "zft_hash_fun.h"

namespace zft
{

//28 primes & related functions
static const int __zft_num_primes = 28;
static const unsigned long __zft_prime_list[__zft_num_primes] =
{
    53,      97,      193,       389,       769,
    1543,    3079,    6151,      12289,     24593,
    49157,   98317,   196613,    393241,    786433,
    1572869, 3145739, 6291469,   12582917,  25165843,
    50331653, 100663319, 201326611, 402653189, 805306457,
    1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long __zft_next_primes(unsigned long n)
{
    const unsigned long *first = __zft_prime_list;
    const unsigned long *last = __zft_prime_list _ + __zft_num_primes;
    const unsigned long *pos = lower(first, last, n);
    return pos == last ? *(last - 1) : *pos;
}

//declare of hashtable
template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc = alloc>
class hashtable;

template <class Value>
struct __hashtable_node
{
    __hashtable_node *next;
    Value val;
};

template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator
{
    typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
    typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, ALloc>
            iterator;
    typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>
            const_iterator;
    typedef __hashtable_node<Value> node;

    typedef forward_iterator_tag iterator_category;
    typedef Value value_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef Value &reference;
    typedef Value *pointer;

    node *cur;
    hashtable *ht;

    __hashtable_iterator(node *n, hashtable *tab) : cur(n), ht(tab) {}
    __hashtable_iterator() {}
    reference operator*() const {return cur->val;}
    pointer operator->() const {return &(operator*());}
    iterator &operator++();
    iteratpr operator++(int);
    bool operator==(const iterator &it) const {return cur == it.cur;}
    bool operator!=(const iterator &it) const {return cur != it.cur;}
};

template <class V, class K, class HF, class ExK, class EqK, class A>
__hashtable_iterator<V, K, HF, ExK, EqK, A> &
__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++()
{
    const node *old = cur;
    cur = cur->next;
    if(!cur)
    {
        size_type bucket = ht->btk_num(old->val);
        while(!cur && ++bucket < ht->buckets.size())
            cur = ht->buckets[bucket];
    }
    return *this;
}

template <class V, class K, class HF, class ExK, class EqK, class A>
inline __hashtable_iterator<V, K, HF, ExK, EqK, A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++(int)
{
    iterator tmp = *this;
    ++*this;
    return tmp;
}

template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
    typedef HashFcn hasher;
    typedef EqualKey key_equal;
    typedef size_t size_type;

private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    typedef __hashtable_node<Value> node;
    typedef simple_alloc<node, Alloc> node_allocator;

    vector<node*, Alloc> buckets;
    size_type num_elements;

public:
    size_type bucket_count() const {return buckets.size();}
    size_type max_bucket_count() const
    {return __zft_prime_list[__zft_num_primes - 1];}

protected:
    node *new_node(const value_type &obj)
    {
        node *n = node_allocator::allocate();
        n->next = 0;

        construct(&n->val, obj);
        return n;
    }

    void delete_node(node *n)
    {
        destroy(&n->val);
        node_allocator::deallocate(n);
    }

public:
    hashtable(size_type n, const HashFcn &hf, const EqualKey &eql) :
        hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
    {
        initialize_buckets(n);
    }

    void initialize_bucket(size_type n)
    {
        const size_type n_buckets = next_size(n);
        buckets.reserver(n_buckets);
        buckets.insert(buckets.end(), n_buckets, (node *)0);
        num_elements = 0;
    }

    pair<iterator, bool> insert_unique(const value_type &obj)
    {
        resize(num_elements + 1);
        return insert_unique_noresize(obj);
    }

    void resize(size_type num_elements_hint)
    {
        const size_type old_n = buckets.size();
        if(num_elements_hint > old_n)
        {
            const size_type n = next_size(num_elements_hint);
            if(n > old_n)
            {
                vector<node*, A> tmp(n, (node *)0);

                for(size_type bucket = 0; bucket < old_n; ++bucket)
                {
                    node *first = buckets[bucket];
                    while(first)
                    {
                        size_type new_bucket = btk_num(first->val, n);
                        buckets[bucket] = first->next;
                        first->next = tmp[new_bucket];
                        tmp[new_bucket] = first;
                        first = buckets[bucket];
                    }
                }
            buckets.swap(tmp);
            }
        }

    }

    pair<iterator, bool> insert_unique_noresize(const value_type &obj)
    {
        const size_type n = bkt_num(obj);
        node *first = buckets[n];

        for(node *cur = first; cur; cur = cur->next)
            if(equals(get_key(cur->val), get_key(obj)))
                return pair<iterator, bool>(iterator(cur, this), false);

        node *tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return pair<iterator, bool>(iterator(tmp, this), true);
    }

    iterator insert_equal(const value_type &obj)
    {
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    iterator insert_equal_noresize(const value_type &obj)
    {
        const size_type n = btk_num(obj);
        node *first = buckets[n];

        for(node *cur = first; cur; cur = cur->next)
            if(equals(get_key(cur->val), get_key(obj)))
            {
                node *tmp = new_node(obj);
                tmp->next = cur->next;
                cur->next = tmp;
                ++num_elements;
                return iterator(tmp, this);
            }

        node *tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return iterator(tmp, this);
    }

protected:
    size_type bkt_num(const value_type &obj, size_t n) const
    {
        return btk_num_key(get_key(obj), n);
    }

    size_type bkt_num(const value_type &obj) const
    {
        return btk_num_key(get_key(obj));
    }

    size_type bkt_num_key(const key_type &key) const
    {
        return bkt_num_key(key, buckets.size());
    }

    size_type bkt_num_key(const key_type &key, size_t n) const
    {
        return hash(key) % n;
    }

public:
    void clear()
    {
        for(size_type i = 0; i < buckets.size(); ++i)
        {
            node *cur = buckets[i];
            while(cur != 0)
            {
                node *next = cur->next;
                delete_node(cur);
                cur = next;
            }
            buckets[i] = 0;
        }
        num_elements = 0;
    }

    void copy_from(const hashtable &ht)
    {
        buckets.clear();
        buckets.reserve(ht.buckets.size());
        buckets.insert(buckets.end(), ht.buckets.size(), (node *)0);

        for(size_type i = 0; i < ht.buckets.size(); ++i)
        {
            if(const node *cur = ht.buckets[i])
            {
                node *copy = new_node(cur->val);
                buckets[i] = copy;

                for(node *next = cur->next; next; cur = next, next = cur->next)
                {
                    copy->next = new_node(next->val);
                    copy = copy->next;
                }
            }
        }

        num_elements = ht.num_elements;
    }
};
}

#endif
