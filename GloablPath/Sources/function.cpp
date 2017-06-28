#include "function.h"

using namespace std;
using namespace cv;

vector<vector<Cell>> CellVectorToMap( vector<Cell> &CellVector )
{
    vector<vector<Cell>> result;
    vector<Cell> temp;
    auto sz = CellVector.size();
    int cols = Map_Size / Cell_Size;

    temp.push_back( CellVector[0] );

    
    cout << CellVector.size() << endl;

    for( auto i = 1; i < sz; ++i )
    {
        if( !( i%cols ) )
        {
            result.push_back( temp );
            temp.clear();
        }

        temp.push_back( CellVector[i] );
    }

    result.push_back( temp );
    return result;
}


vector<Cell> A_Star_FindPath( vector<vector<Cell>> &CellMap, pair<int, int> Start, pair<int, int> End )
{
   cout << "get in A_start!" << endl;
   vector<Cell> openCell;
   vector<Cell> closeCell;

   Cell &StartCell = CellMap[Start.first][Start.second];
   Cell &EndCell = CellMap[End.first][End.second];


   cout << StartCell.getPosition().first << endl;

   StartCell.parent = nullptr;

   if( StartCell.getObstacle() )
   {
       cout << "Start Point have obstacle!" << endl;
       return vector<Cell>();
   }

   if( EndCell.getObstacle() )
   {
       cout << "Start Point have obstacle!" << endl;
       return vector<Cell>();
   }

   StartCell.g = 0;
   StartCell.h = abs( EndCell.getPosition().first - StartCell.getPosition().first ) / 10 + abs( EndCell.getPosition().second - StartCell.getPosition().second ) / 10;
   StartCell.f = StartCell.g + StartCell.h;

   cout << "Start Cell seT up!" << endl;
   openCell.push_back( StartCell );

   cout << "Start to find Path!" << endl;
   while( find( openCell.begin(), openCell.end(), EndCell ) == openCell.end() )
   {
       Cell Current = *(openCell.begin());
       openCell.erase( openCell.begin() );
      
       cout << "CurrentCell:" << Current.getPosition().first << " " << Current.getPosition().second << endl;
       closeCell.push_back( Current );

       for( int i = -1; i < 2; ++i )
       {
           for( int j = -1; j < 2; ++j )
           {
               int nPosition_x = Current.getPosition().first / 10 + i;
               int nPosition_y = Current.getPosition().second / 10 + j;

               cout << "current position " << nPosition_x << " " << nPosition_y << endl;

               if( nPosition_x < 0 || nPosition_x >= CellMap[0].size() || nPosition_y < 0 || nPosition_y >= CellMap[0].size() )
               {
                   cout << "expand out of range!" << endl;
                   continue;
               }

               if( (abs(i) + abs(j) == 2 || abs(i) + abs(j) == 0 ) )
               {
                   cout << "current position!" << endl;
                   continue;
               }

               Cell &nCell = CellMap[nPosition_x][nPosition_y];
            
               int cost = Current.g + abs(i) + abs(j);

               if( nCell.getObstacle() || find( closeCell.begin(), closeCell.end(), nCell ) != closeCell.end() )
               {
                   cout << "have obstacle or have been in close!" << endl;
                   continue; 
               }

               if( (find( openCell.begin(), openCell.end(), nCell ) != openCell.end()) && cost < nCell.g )
               {
                   nCell.g = cost;
                   nCell.f = nCell.g + nCell.h;
                   nCell.parent = &(CellMap[nPosition_x - i][nPosition_y - j]);
                   cout << "in the openlist and it's better!" << endl;
                   sort( openCell.begin(), openCell.end() );
               }

               if( find( openCell.begin(), openCell.end(), nCell ) == openCell.end() )
               {
                   nCell.g = cost;
                   nCell.h = abs( EndCell.getPosition().first - nCell.getPosition().first ) / 10 + abs( EndCell.getPosition().second - nCell.getPosition().second ) / 10;
                   nCell.f = nCell.g + nCell.h;
                   nCell.parent = &(CellMap[nPosition_x - i][nPosition_y - j]);
                   openCell.push_back( nCell );
                   sort( openCell.begin(), openCell.end() );
                   cout << "add to open!" << endl;
               }

           }
       }

   }
   vector<Cell> result;

   cout << "End Cell:" << (*openCell.begin()).getPosition().first << " " << (*openCell.begin()).getPosition().second << endl;
   cout << "FindPath!" << endl;

   Cell *PathCell = &EndCell;
   while( PathCell->parent != &StartCell )
   {
       result.push_back( *PathCell );
       PathCell = PathCell->parent;
       //cout << "pushing path!" << endl;
   }

   return result;

}
