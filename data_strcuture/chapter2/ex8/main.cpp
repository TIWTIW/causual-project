#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

int randInt( int i, int j )
{
    static default_random_engine e;
    uniform_int_distribution<int> u( i, j );

    return u( e );
}

int method1( int N )
{
    vector<int> a;
    for( int i = 0; i < N; ++i )
    {
        while( true )
        {
            int temp = randInt( 0, N - 1 );
            if( find( a.begin(), a.end(), temp ) == a.end() )
            {
                a.push_back( temp );
                break;
            }
        }

    }
    return 0;
}

int method2( int N )
{
    vector<int> a;
    vector<bool> used( N, false );

    for( int i = 0; i < N; ++i )
    {
        while( true )
        {
            int temp = randInt( 0, N -1 );
            if( !used[temp] )
            {
                a.push_back( temp );
                used[temp] = true;
                break;
            }
        }
    }

    return 0;
}

int method3( int N )
{
    vector<int> a( N );
    for( int i = 0; i < N; ++i )
    {
        a.push_back( i );
    }

    for( int i = 0; i < N; ++i )
        swap( a[i], a[randInt( 0, i )] );

    return 0;
}

int main()
{
    clock_t start, end;

    start = clock();
    method1( 250 );
    end = clock();
    cout << "method1(250): " << end - start << endl;

    start = clock();
    method1( 500 );
    end = clock();
    cout << "method1(500): " << end - start << endl;

    start = clock();
    method1( 1000 );
    end = clock();
    cout << "method1(1000): " << end - start << endl;

    start = clock();
    method1( 2000 );
    end = clock();
    cout << "method1(2000): " << end - start << endl;

    start = clock();
    method2( 25000 );
    end = clock();
    cout << "method2(25000): " << end - start << endl;

    start = clock();
    method2( 50000 );
    end = clock();
    cout << "method2(50000): " << end - start << endl;

    start = clock();
    method2( 100000 );
    end = clock();
    cout << "method2(100000): " << end - start << endl;

    start = clock();
    method2( 200000 );
    end = clock();
    cout << "method2(200000): " << end - start << endl;

    start = clock();
    method2( 400000 );
    end = clock();
    cout << "method2(400000): " << end - start << endl;


    start = clock();
    method2( 800000 );
    end = clock();
    cout << "method2(800000): " << end - start << endl;

    start = clock();
    method3( 100000 );
    end = clock();
    cout << "method3(100000): " << end - start << endl;

    start = clock();
    method3( 200000 );
    end = clock();
    cout << "method3(200000): " << end - start << endl;

    start = clock();
    method3( 400000 );
    end = clock();
    cout << "method3(400000): " << end - start << endl;

    start = clock();
    method3( 800000 );
    end = clock();
    cout << "method3(800000): " << end - start << endl;

    start = clock();
    method3( 1600000 );
    end = clock();
    cout << "method3(1600000): " << end - start << endl;

    start = clock();
    method3( 3200000 );
    end = clock();
    cout << "method3(3200000): " << end - start << endl;

    start = clock();
    method3( 6400000 );
    end = clock();
    cout << "method3(6400000): " << end - start << endl;
}
