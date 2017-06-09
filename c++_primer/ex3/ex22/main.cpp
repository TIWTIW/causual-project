#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    vector<string> vs{"asad", "df"};

    auto it = vs.begin();

    for( auto &c : *it )
        c = toupper( c );
   

    for( auto &c : vs )
        cout << c << endl;

    return 0;


}
