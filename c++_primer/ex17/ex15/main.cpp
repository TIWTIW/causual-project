#include <iostream>
#include <string>
#include <regex>

using namespace std;

void satisfy( string &s )
{
    string pattern( "[^c]ei" );
    pattern = "[[:alpha:]]:*" + pattern + "[[:alpha:]]*";
    regex r( pattern );
    smatch result;

    for( sregex_iterator it( s.begin(), s.end(), r ), end_it; it != end_it; ++it )
    {
        cout << it->str() << endl;
    }

}

int main()
{
    string s;
    while( true )
    {
        cout << "enter a number:"; 
        cin >> s;
        cout << endl;


        satisfy( s );

        cout << "continue? Y/N" << endl;

        string x;
        cin >> x;
        if( x == "N" | x == "n" )
            break;
    }
}
