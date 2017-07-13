#include <regex>
#include <iostream>
#include <string>

using namespace std;

bool valid( const smatch &m )
{
    if( m[2].matched == m[3].matched )
        return true;
    else
        return false; 
}

int main()
{
    string post = "(\\d{5})(-)?(\\d{4})?";

    regex r( post );
    smatch result;
    string s;
    
    while( cin >> s )
    {
        for( sregex_iterator it( s.begin(), s.end(), r ), end_it; it != end_it; ++it )
        {
            if( valid( *it ) )
                cout << "valid: " << it->str() << endl;
            else
                cout << "unvalid: " << it->str() << endl;
        }
    }
}
