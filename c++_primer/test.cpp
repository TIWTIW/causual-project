#include <iostream>

using namespace std;

class cat
{
public:
    cat() { cout << "construct" << endl; }
    cat( const cat &a ) { cout << "copy" << endl; }
    cat( cat &&a ) { cout << "move" << endl; }
    ~cat() { cout << "delete" << endl; }
};

cat show( cat &a )
{
    cat b( a );
  //  cat c( b );
    return b;
}

int main()
{
    cat a;
    cat b( show( a ) );
}
