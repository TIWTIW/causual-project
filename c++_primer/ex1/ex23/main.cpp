#include <iostream>
#include "Sales_item.h"
#include <map>
#include <string>

using namespace std;

int main()
{
    Sales_item item;
    map<string, int> num_of_items; 

    while( cin >> item )
    {
        num_of_items[item.isbn()]++;
    }

    for( auto it = num_of_items.begin(); it != num_of_items.end(); ++it )
    {
        cout << it->first << ":" << it->second << endl;
    }

    return 0;
}
