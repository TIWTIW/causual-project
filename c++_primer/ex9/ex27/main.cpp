#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
    forward_list<int> fl{1, 2, 3, 4, 5, 6};

    auto prev = fl.before_begin();
    auto curr = fl.begin();

    while( curr != fl.end() )
    {
        if( *curr % 2 )
        {
            curr = fl.erase_after( prev );
        }
        else
        {
            prev = curr;
            ++curr;
        }
    }

    for( auto &c : fl )
        cout << c << " ";

    cout << endl;

    return 0;
}
