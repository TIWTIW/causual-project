#include <iostream>

using namespace std;

long long pow( long long num, int n )
{
    if( n == 0 )
        return 0;
    if( n == 1 )
        return num;
    if( n % 2 == 0)
        return pow( pow( num, 2 ), n / 2 );
    else
        return pow( num * num, n / 2 ) * num;

}

int main()
{
    cout << pow(8, 2) << endl;
    return 0;
}
