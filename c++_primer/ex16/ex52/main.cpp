#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::endl;

template <typename T, typename... Args>
void foo( const T &t,  const Args& ... rest )
{
    cout << sizeof...( Args ) << endl;
    cout << sizeof...( rest ) << endl;
}

int main()
{
    int i = 0;
    double d = 3.14;
    string s = "how now be";

    foo( i, s, 42, d );
    foo( s, 42, "ho" );
    foo( d, s );
    foo( "h" );

}
