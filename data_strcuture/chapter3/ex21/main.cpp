#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    string s = "(())[]{}/**/";

    stack<string> sc;

    for( size_t i = 0; i < s.size(); ++i )
    {
        if( s[i] == '(' || s[i] == '{' || s[i] == '[' )
        {
            string x;
            x = s[i];
            sc.push( x );
        }
        if( s[i] == '/' && ( i != s.size() - 1 ) && s[i+1] == '*' )
            sc.push( "/*" );

        if( s[i] == ')' || s[i] == '}' || s[i] == ']' )
        {
            if( sc.empty() )
            {
                cout << "wrong!" << endl;
                exit( -1 );
            }
            switch( s[i] )
            {
                case ')': 
                    if( sc.top() == "(" )
                    {
                        sc.pop();
                    }
                    else
                    {
                        cout << "wrong!" << endl;
                        exit( -1 );
                    }
                    break;
                case ']':
                    if( sc.top() == "[" )
                    {
                        sc.pop();
                    }
                    else
                    {
                        cout << "wrong!" << endl;
                        exit( -1 );
                    }
                    break;
                case '}':
                    if( sc.top() == "{" )
                    {
                        sc.pop();
                    }
                    else
                    {
                        cout << "wrong!" << endl;
                        exit( -1 );
                    }
                    break;
            }
        }
        if( s[i] == '*' && ( i != s.size() - 1 ) && s[i+1] == '/' )
        {
            if( sc.empty() )
            {
                cout << "wrong!" << endl;
                exit( -1 );
            }
            if( sc.top() == "/*" )
            {
                sc.pop();
            }
            else
            {
                cout << "wrong!" << endl;
            }   
        }
    }

    if( !sc.empty() )
    {
        cout << "wrong!" << endl;
    }
    else
    {
        cout << "success!" << endl;
    }

    return 0;
}
