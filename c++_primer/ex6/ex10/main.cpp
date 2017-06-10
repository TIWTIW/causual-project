#include <iostream>

using namespace std;

template<typename T>
void swap( T *t1, T *t2 )
{
    T temp = *t1;
    *t1 = *t2;
    *t2 = temp;

    return ;
}

int main()
{
    char a = 'c', b = 'a';

    ::swap( &a, &b );

    cout << a << b << endl;

    return 0;
}
