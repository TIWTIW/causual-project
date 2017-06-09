#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string s;
    string result;

    cout << "input a string:" << endl;

    if( cin >> s )
    {
        for( auto &c : s )
        {
            if( !ispunct( c ) )
            {
                result += c;
            }
        }
    }

    cout << result << endl;

    return 0;
}
