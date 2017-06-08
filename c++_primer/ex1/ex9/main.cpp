#include <iostream>

using namespace std;

int main()
{
    int i = 50;
    int sum = 0;

    while( i <= 100 )
    {
        sum += i;
        i++;
    }

    cout << "The sum of 50 to 100 is " << sum << endl;

    return 0;
}
