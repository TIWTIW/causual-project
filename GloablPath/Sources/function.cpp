#include "function.h"

using namespace std;
using namespace cv;

/******transfer CellVector to Map of Cell ***********/
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


/******* --A* algorithm -- ****************/
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

/***** --RRT algorithm --*****************/
void RRT_Find_Path( Mat &Image, Point Start, Point Goal )
{
    ETree Tree;
    Tree.addNode( Start );

    srand( unsigned( time(NULL) ) );

    const int number_of_k = 4;
    while( true )
    {
        for( int i = 0; i < number_of_k; ++i )
        {
            int x = abs( rand() % Map_Size );            
            int y = abs( rand() % Map_Size );

            Point currentPoint( x, y );

            Point nearNode = Tree.findNearstNode( currentPoint );
            
            uchar *data = Image.ptr<uchar>( y );
            
            if( data[x] != 0 || data[x+1] != 0 || data[x+2] != 0 )
            {
                cout << "Current Point has obstacle!" << endl;
                continue;
            }


            bool noObstacle = true;

            int disX = x - nearNode.x, disY = y - nearNode.y;
            
            int times = 0;
            if( disX > 0 && disY > 0 )
            {
                for( int i = x, j = y; i > nearNode.x; --i, j = j - max( ( disY / disX ), 1 ) )
                {
                    uchar *data = Image.ptr<uchar>(i);

                    if( data[j] != 0 || data[j+1] != 0 || data[j+2] != 0 )
                    {
                       cout << data[i] << " " << data[i+1] << " " << data[i+2] << endl;
                       cout << "line has obstacle! :"  << times << endl;
                       times++;
                       noObstacle = false;
                       break;
                        
                    }
                }
            }
            else if( disX > 0 && disY < 0 )
            {

                for( int i = x, j = y; i > nearNode.x; --i, j = j + max( disY / disX, 1 ) )
                {
                    uchar *data = Image.ptr<uchar>(i);

                    if( data[j] != 0 || data[j+1] != 0 || data[j+2] != 0 )
                    {
                       cout << "line has obstacle!" << endl;
                       noObstacle = false;
                       break;
                        
                    }
                }
            }
            else if( disX < 0 && disY > 0 )
            {
                for( int i = x, j = y; i < nearNode.x; ++i, j = j - max( disY / disX , 1) )
                {
                    uchar *data = Image.ptr<uchar>(j);

                    if( data[i] != 0 || data[i+1] != 0 || data[i+2] != 0 )
                    {
                       cout << "line has obstacle!" << endl;
                       noObstacle = false;
                       break;
                        
                    }
                }

            }
            else if( disX < 0 && disY < 0 )
            {

                for( int i = x, j = y; i < nearNode.x; ++i, j = j + max( disY / disX, 1 ) )
                {
                    uchar *data = Image.ptr<uchar>(j);

                    if( data[i] != 0 || data[i+1] != 0 || data[i+2] != 0 )
                    {
                       cout << "line has obstacle!" << endl;
                       noObstacle = false;
                       break;
                        
                    }
                }
            }

            if( !noObstacle )
            {
                continue;
            }

           // const int step = 5;

            const int step_x = 2, step_y = step_x * max( 1,  disY / disX );

            int newx, newy;
            if( disX > 0 && disY > 0 )
            {
                newx = nearNode.x - step_x;
                newy = nearNode.y - step_y;
            }

            if( disX > 0 && disY < 0 )
            {
                newx = nearNode.x - step_x;
                newy = nearNode.y + step_y;
            }

            if( disX < 0 && disY > 0 )
            {
                newx = nearNode.x + step_x;
                newy = nearNode.y - step_y;
            }

            if( disX < 0 && disY < 0 )
            {
                newx = nearNode.x + step_x;
                newy = nearNode.y + step_y;
            }

            Point newPoint( newx, newy );

            Tree.addNode( newPoint );
            line( Image, nearNode, newPoint, Scalar( 255, 0, 0 ) );

            cout << "add NewPoint!" << newPoint.x << " " << newPoint.y << endl;
            if( newPoint.x == Goal.x && newPoint.y == Goal.y )
                break;

        }
    }
}
