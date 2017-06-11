#include <iostream>
#include <string>

using namespace std;

istream &print( istream &is )
{
    string s;
    while( !is.eof() )
        is >> s;

    cout << s;

    is.clear();

    return is;
}

int main()
{
    print( cin );

    cout << endl;

    return 0;
}
