#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<string> WordFind( set<string> &wordTable, vector<vector<char>> &vvc )
{
    set<string> WordFinded;
    int row = vvc.size();
    int col = vvc[0].size();

    for( int i = 0; i < row; ++i )
    {
        for( int j = 0; j < col; ++j )
        {
            string s_row, s_col, s_diag;
            int cur_i = i, cur_j = j;
            while( cur_j < col )
            {
                s_col = s_col + vvc[i][cur_j];
                cur_j++;
                if( wordTable.find( s_col ) != wordTable.end() )
                    WordFinded.insert( s_col );
            }
            while( cur_i < row )
            {
                s_row = s_row + vvc[cur_i][j];
                ++cur_i;
                if( wordTable.find( s_row ) != wordTable.end() )
                    WordFinded.insert( s_row );
            }
            cur_i = i;
            cur_j = j;
            while( cur_i < row && cur_j < col )
            {
                s_diag = s_diag + vvc[cur_i][cur_j];
                ++cur_i;
                ++cur_j;
                if( wordTable.find( s_diag ) != wordTable.end() )
                    WordFinded.insert( s_diag );
            }
        }
    }

    return WordFinded;
}

int main()
{
    set<string> wordTable = {"this", "two", "fat"};
    vector<vector<char>> vvc = { {'t', 'h', 'i', 's'},
                                 {'w', 'a', 't', 's'},
                                 {'o', 'a', 'h', 'g'},
                                 {'f', 'g', 'd', 't'} };

    set<string> result = WordFind( wordTable, vvc );

    for( auto &s : result )
        cout << s << " ";

    cout << endl;
    return 0;
}
