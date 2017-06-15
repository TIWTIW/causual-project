#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main()
{
    map<string, vector<string>> name;

    string family, child_name;

    while( true )
    {
        cout << "please enter family name" << endl;
        cin >> family;

        cout << "please enter child_name" << endl;

        while( cin >> child_name )
            name[family].push_back( child_name );

       cout << "need more?Y/N" << endl; 

       cin.clear();
       string s;
       cin >> s;
       if( s == "y" )
           ;
       else
           break;
    }

    for( const auto &c : name )
    {
        cout << c.first << ":";
        for( const auto &s : c.second )
            cout << s << " ";

        cout << endl;
    }

}
