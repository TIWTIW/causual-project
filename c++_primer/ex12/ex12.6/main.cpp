/***********c++ primer ex12.6************
 * function:练习new和delete
 * Name:zft
 * Time:2017.3.29
 * *************************************/

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

shared_ptr<vector<int>> VcGenerate()
{
    shared_ptr<vector<int>> vc = make_shared<vector<int>>();
    return vc;
}

void SaveVc( istream &is, shared_ptr<vector<int>> vc  )
{
    int input;
    while( is >> input )
        vc->push_back( input );
}

void printVc( shared_ptr<vector<int>> vc )
{
    for( auto c : *vc )
        cout << c << endl;
}

int main( int argc, char *argv[] )
{
    shared_ptr<vector<int>> vc = VcGenerate();
    SaveVc( cin, vc );
    printVc( vc );
}
