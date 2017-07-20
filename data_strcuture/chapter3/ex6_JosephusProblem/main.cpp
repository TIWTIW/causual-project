#include <iostream>
#include <list>

using namespace std;

int Josephus( list<int> &array, int N, int M )
{
    auto it = array.begin();
    while( array.size() > 1 )
    {
        int i = 0;
        while( i < M )
        {
            ++it;
            ++i;
            if( it == array.end() )
                it = array.begin();
        }

        it = array.erase( it );
        if( it == array.end() )
            it = array.begin();
    }

    return *it;
}

int main()
{
    list<int> Person{ 1, 2, 3, 4, 5};

    cout << Josephus( Person, 5, 2 ) << endl;
}

