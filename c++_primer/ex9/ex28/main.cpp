#include <iostream>
#include <forward_list>
#include <string>

using namespace std;

void fun( forward_list<string> &fls, const string &s1, const string &s2 )
{
    auto prev = fls.before_begin(), it = fls.begin();
    for( ; it != fls.end(); ++it, ++prev )
    {
        if( *it == s1 )
        {
            fls.insert_after( it, s2 );
            return ;
        }
    }

    fls.insert_after( prev, s2 );
}

int main()
{
    forward_list<string> fs{"asa", "asfg", "wet"};
    string s1( "asf" );
    string s2( "find?" );

    fun( fs, s1, s2 );

    for( auto &s : fs )
        cout << s << endl;

    return 0;
}
