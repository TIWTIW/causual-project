#include <iostream>
#include <string>

using namespace std;

void permute( string &, size_t, size_t );

bool isSwap( string &s, int i, int j )
{
    for( ; i < j; ++i )
        if( s[i] == s[j] )
            return false;

    return true;
}
void permute( string &str )
{
    permute( str, 0, str.size() - 1 );
}

void permute( string &str, size_t low, size_t high )
{
    if( low == high )
    {
        cout << str << endl;
        return ;
    }

    for( int i = low; i <= high; ++i )
    {
        if( isSwap( str, low, i ) )
        {
            swap( str[low], str[i] );
            permute( str, low + 1, high );
            swap( str[low], str[i] );
        }
    }
}

int main()
{
    string s = "1234";

    permute( s );
}
