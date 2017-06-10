#include <iostream>

using namespace std;

void swapP( int *(&p), int *(&q) )
{
    int *temp = p;
    p = q;
    q = temp;
}

int main()
{
    int i = 0, j = 12;

    int *pi = &i, *pj = &j;

    swapP( pi, pj );

    cout << *pi << *pj << endl;

    return 0;


}
