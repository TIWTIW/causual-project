#include <iostream>
#include <string>

using namespace std;

class ReadString
{
public:
    ReadString() : is( cin ), contents( "" ) { }
    string &operator()() { getline( is, contents ); if( !is )  contents = ""; return contents; }
private:
    istream &is;
    string contents;
};

int main()
{
    ReadString a;
    cout << a() << endl;


}
