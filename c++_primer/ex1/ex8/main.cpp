#include <iostream>

using namespace std;

int main()
{
    cout << "/*" << endl;
    cout << "*/" << endl;
    cout << /* "*/" */;
    cout << /* "*/" /* "/*" */;

    return 0;
}
