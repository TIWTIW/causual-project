#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void eilmDups( vector<string> &words )
{
    sort( words.begin(), words.end() );

    auto uni = unique( words.begin(), words.end() );

    words.erase( uni, words.end() );
}

bool isShorter( const string &s1, const string &s2 )
{
    return s1.size() < s2.size();
}

int main()
{
    vector<string> vs{"the", "quick", "red", "fox", "jump", "over", "the",                      "slow", "red", "turtle"};

    eilmDups( vs );

    stable_sort( vs.begin(), vs.end(), isShorter );

    for( auto &s : vs )
        cout << s << " ";

    cout << endl;
}
