#include "Map.h"
#include <time.h>

using namespace std;
using namespace cv;

void Map::Initial()
{
    srand( unsigned( time(NULL) ) );

    for( int i = 0; i < 3; ++i )
    {
        unsigned x = rand() % 300 + 200;
        unsigned y = rand() % 300 + 200;
        unsigned size = Obstacle_Size;


        cout << "The position of obstacle is" << x << " " << y << endl;

        circle( *MatImagePtr, Point( x, y ), size, Scalar( 255, 255, 0 ), -1 );
    }
}

void Map::MakeCellMap()
{
    for( int x = Cell_Size / 2; x < Map_Size; x = x + Cell_Size  )
    {
        for( int y = Cell_Size / 2; y < Map_Size; y = y + Cell_Size )
        {
            Mat Image = *MatImagePtr;
            Mat currImage = Image( Rect( x - Cell_Size/2, y - Cell_Size/2, Cell_Size, Cell_Size ) );
            
            Cell currCell( x, y );

            if( !checkRange( currImage, true, 0, -1, 1 ) )
                currCell.setObstacle( true );

            CellMapPtr->push_back( currCell );
        }
    }
}

Mat Map::TransferCellToImage()
{
    Mat Image( Map_Size, Map_Size, CV_8UC3, Scalar( 0, 0, 0 )  );
    vector<Cell> CellMap = *CellMapPtr;

    for( auto &c : CellMap )
    {
        if( c.getObstacle() )
        {
            rectangle( Image, Point( c.getPosition().first - Cell_Size / 2, c.getPosition().second - Cell_Size / 2 ),
                              Point( c.getPosition().first + Cell_Size / 2, c.getPosition().second + Cell_Size / 2 ), Scalar( 255, 255, 0 ), -1 );
        }
    }

    return Image;
}
