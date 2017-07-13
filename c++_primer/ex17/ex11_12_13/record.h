#ifndef _RECORD_H
#define _RECORD_H

#include <iostream>
#include <bitset>

template <unsigned N>
class record
{
public:
    record( unsigned x ) : answer( std::bitset<N>(x) ) {}
    void set( unsigned index, bool ans );
    void reset( unsigned index );
    unsigned score( const std::bitset<N> &rhs );
private:
    std::bitset<N> answer;
};

template <unsigned N>
unsigned record<N>::score( const std::bitset<N> &rhs )
{
    unsigned x = N;

    for( size_t i = 0; i < N; ++i )
    {
        if( answer[i] != rhs[i] )
            --x;
    }

    return x;
}
template <unsigned N>
void record<N>::set( unsigned index, bool ans )
{
    if( index > N )
    {
        std::cout << "out of range!" << std::endl;
        return ;
    }

    answer.set( index, ans );
}

template <unsigned N>
void record<N>::reset( unsigned index )
{
    if( index > N )
    {
        std::cout << "out of range" << std::endl;
        return ;
    }
    answer.reset( index );
}

#endif
