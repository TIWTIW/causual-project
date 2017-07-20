#include <iostream>
#include <vector>

using namespace std;

template <typename Iterator, typename Object>
Iterator find( Iterator start, Iterator end, const Object &x )
{
    for( Iterator it = start; it < end; ++it )
    {
        if( *it == x )
            return it;
    }

    return end;
}

int main()
{
    vector<int> a{2, 3, 54, 1, 2, 1};

    vector<int>::iterator it  = find( a.begin(), a.end(), 1 );
        
    int c = 0;
    for( auto ie = a.begin(); ie < it; ++ie )
        c++;

    cout << c << endl;

}
