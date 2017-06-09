#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
    int num1, num2;
    
    while( true )
    {
        try
        {
            cin >> num1 >> num2;
            
            if( num2 == 0 )
                throw( runtime_error( "The second number is 0!" ) );

            int result = num1 / num2;

            cout << result << endl;
        }
        catch( runtime_error err )
        {
            cerr << err.what() << endl;
            cout << "Do you want to input the number again? Y/N" << endl;

            char c;

            cin >> c;

            if( c == 'y' )
                ;
            else if( c == 'n' )
                break;
            else
                ;
        }
    }

    return 0;
}
