#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void Dict( string &s )
{
    int i;
    for( i = s.size() - 1; i > 0; --i )
    {
        if( s[i] > s[i - 1] ) 
            break;
    }

    if( i == 0 ) 
    {
        cout << "best!" << endl;
    }

    int minIndex = i;
    for( int j = i; j < s.size(); ++j )
    {
        if( s[j] <= s[minIndex] )
            minIndex = j;
    }

    swap( s[i - 1], s[minIndex] );

    sort( s.begin() + i, s.end() );

    cout << s << endl;

}

int main()
{
    string s{ "123456798" };

    Dict( s );
}

