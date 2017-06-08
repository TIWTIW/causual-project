#include <iostream>

using namespace std;

int main()
{
    int num1, num2;

    cout << "Enter two numbers:" << endl;

    cin >> num1 >> num2;

    if( num1 > num2 )
    {
        num1 = num1 ^ num2;
        num2 = num1 ^ num2;
        num1 = num1 ^ num2;
    }

    cout << "The numbers between them are:";
    while( num1 <= num2 )
        cout << num1++ << " ";

    cout << endl;

    return 0;
}
