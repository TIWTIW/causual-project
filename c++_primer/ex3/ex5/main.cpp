#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s, s_total;

    while( cin >> s )
    {
        s_total += s;
    }

    cout << s_total << endl;

    return 0;
}
