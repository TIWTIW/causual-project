#include <iostream>

using namespace std;

int main()
{
    int num, sum = 0;

    cout << "input numbers:";

    while( cin >> num )
        sum += num;

    cout << endl;
    cout << "The sum of them is:" << sum << endl;

    return 0;
}
