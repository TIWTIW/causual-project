#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <vector>

template <typename Object>
class matrix
{
public:
    matrix() : array{ std::vector<std::vector<Object>>{} } { }
    matrix( int rows, int cols ) : array( rows )
    {
        for( auto &thisRow : array )
            thisRow.resize( cols );
    }

    matrix( std::vector<std::vector<Object>> v ) : array( v )
    { }
    matrix( std::vector<std::vector<Object>> &&v ) : array{ std::move( v ) }
    { }
    const std::vector<Object> &operator[]( int row ) const
    { return array[row]; }
    std::vector<Object> &operator[]( int row )
    { return array[row]; }

    int numrows() const { return array.size(); }
    int numcols() const { return numrows() ? array[0].size() : 0; }

    void resize( int row, int col );

private:
    std::vector<std::vector<Object>> array;
};

template <typename Object>
void matrix<Object>::resize( int row, int col )
{
    array.resize( row );

    if( numrows() == 0 )
    {
        array.push_back( std::vector<Object> {} );
    }

    for( auto &c : array )
        c.resize( col );
}

#endif
