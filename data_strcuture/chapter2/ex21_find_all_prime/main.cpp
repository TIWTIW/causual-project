#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class IntObj
{
public:
    IntObj( int x = 0, bool flag = false ) : i( x ), deleted( flag ) { }
    int getNum() { return i; }
    bool isDel() { return deleted; }
    void setDel() { deleted = true; }

private:
    int i;
    bool deleted;
};

void findAllPrime( int N )
{
    vector<IntObj> a;

    for( int i = 0; i <= N; ++i )
        a.push_back( IntObj( i ) );

    int currentNum = 2;
    cout << 1 << endl;

    while( true )
    {
        currentNum = 2;
        while( currentNum <= sqrt( N ) )
        {
            if( !(a[currentNum].isDel()) )
                break;
            ++currentNum;
        }

        if( currentNum >= sqrt( N ) )
            break;

        cout << currentNum << endl;
        for( int i = currentNum, j = 1, x = i; x <= N; x = (j++) * i )
            a[x].setDel();
    }

    for( ;currentNum < N; ++currentNum )
        if( !a[currentNum].isDel() )
            cout << a[currentNum].getNum() << endl;
}

int main()
{
    int N = 100;
    findAllPrime( N );
}


