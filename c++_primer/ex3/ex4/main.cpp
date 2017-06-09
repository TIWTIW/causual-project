#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1, s2;

    cout << "input two strings:" << endl;

    cin >> s1 >> s2;

    if( s1 > s2 )
        cout << s1 << endl;
    else if( s2 > s1 )
        cout << s2 << endl;

    return 0;
}
