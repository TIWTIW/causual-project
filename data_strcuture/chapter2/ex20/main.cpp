#include <iostream>
#include <cmath>

using namespace std;

bool isPrime( int x )
{
    if( x == 1 || x == 2 )
        return true;
    if( !( x % 2 )  )
        return false;

    for( int i = 3; i <= sqrt( x ); i = i + 2 )
        if( !( x % i ) )
            return false;

    return true;
}

int main()
{
    int number;
    cout << "input a number:";
    cin >> number;

    cout << endl << number << " " << (isPrime(number) ? "is " : "isn't ") << "a prime" << endl;
    return 0;
}
