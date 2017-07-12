#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template <typename T>
unsigned appear( vector<T> &vT, T element )
{
    unsigned i = 0;
    for( auto &c : vT )
    {
        if( c == element )
            ++i;
    }

    return i;
}

template <>
unsigned appear( vector<const char*> &vcc, const char *c )
{
    unsigned i = 0;
    for( auto &x : vcc )
    {
        if( strcmp( c, x ) )
            ++i;
    }
    return i;
}

int main()
{
    vector<int> vi = {1, 2, 34, 5, 6, 7, 6, 4, 6};
    vector<double> vd = {1.2, 3.4, 5.4, 1.2, 1.2};
    vector<const char*> vc = {"asd", "fasdf", "qwe", "qwe"};

    unsigned numInVi = appear( vi, 6 );
    unsigned numIndi = appear( vd, 1.2 );
    unsigned numInvc = appear( vc, "qwe" );

    cout << numInVi << " " << numIndi << endl;
    cout << numInvc << endl;

    return 0;
}
