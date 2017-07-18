#include <iostream>

using namespace std;

int f( int x )
{
    int temp = 2 * x + 12;
    return temp;
}

int rooting( int(*f)(int), int low, int high )
{
    int mid = 0;

    while( low <= high )
    {
        mid = ( low + high ) >> 1;
        if( (*f)( mid ) > 0 )
            high = mid - 1;
        else if( (*f)( mid ) < 0 )
            low = mid + 1;
        else
            break;
    }

    return mid;
}

int main()
{
    int i = -100, j = 20;

    cout << rooting( f, i, j ) << endl;
}
