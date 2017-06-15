#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int main()
{
    map<string, vector<pair<string, string>>> name;

    string family, child_name;

    while( true )
    {
        cout << "please enter family name" << endl;
        cin >> family;

        cout << "please enter child_name" << endl;

        cin >> child_name;
        
        cin.clear();

        cout << "please enter birthday" << endl;

        string birthday;
        cin >> birthday;

        pair<string, string> p( child_name, birthday );

        name[family].push_back( p );

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
            cout << s.first << ":" << s.second << endl;

        cout << endl;
    }

}
