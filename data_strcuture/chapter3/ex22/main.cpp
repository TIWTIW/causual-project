#include <iostream>
#include <stack>
#include <set>
#include <string>

using namespace std;

int main()
{
    stack<int> si;
    set<char> sc{ '+', '*' };
    string expr = "6523+8*+3+*";

    for( size_t i = 0; i < expr.size(); ++i )
    {
        if( sc.find( expr[i] ) == sc.end() )
        {
            si.push( expr[i] - 0x30 );
            continue;
        }
        if( expr[i] == '+' )
        {
            int result;
            int num1 = si.top();
            si.pop();
            int num2 = si.top();
            si.pop();
            result = num1 + num2;
            si.push( result );
        }
        if( expr[i] == '*' )
        {
            int result;
            int num1 = si.top();
            si.pop();
            int num2 = si.top();
            si.pop();
            result = num1 * num2;
            si.push( result );
        }
    }

    cout << si.top() << endl;
}

