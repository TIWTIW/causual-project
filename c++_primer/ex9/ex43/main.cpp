#include <iostream>
#include <string>

using namespace std;

void fun( string &s, string &oldVal, string &newVal )
{
    for( string::size_type i = 0; i <= s.size() - oldVal.size(); ++i )
    {
        if( s.substr( i, oldVal.size() ) == oldVal )
        {
            s.erase( i, oldVal.size() );
            s.insert( i, newVal );
        }
    }
}

int main()
{
    string s( "thoasdtho" );
    string old( "tho" );
    string news( "though" );

    fun( s, old, news );

    cout << s << endl;
    return 0;
}
