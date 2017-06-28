#include "Map.h"
#include "Cell.h"
#include "function.h"

using namespace std;
using namespace cv;

int main()
{
    Map map;

    // initial map and get CellMap
    map.Initial();
    map.MakeCellMap();
    
    vector<Cell> CellVector = map.getCellImage();


    Cell StartCell( 2, 2 ), EndCell( 10, 10 );
    vector<vector<Cell>> CellMap = CellVectorToMap( CellVector );


    vector<Cell> Path = A_Star_FindPath( CellMap, pair<int, int>(10, 10), pair<int, int>(50, 53) );

    //cout << CellMap.size() << endl;

    /*for( auto &c : CellMap )
    {
        if( c.getObstacle() )
            cout << "T" << " ";
    }*/

    Mat AfterCellImage = map.TransferCellToImage();
    Mat PathImage( AfterCellImage );

    for( auto &c : Path )
    {
        rectangle( PathImage, Point( c.getPosition().first - Cell_Size / 2, c.getPosition().second - Cell_Size / 2 ),
                          Point( c.getPosition().first + Cell_Size / 2, c.getPosition().second + Cell_Size / 2 ),  Scalar( 255, 0, 0 ), -1 );
    }

    namedWindow( "MapImage", CV_WINDOW_AUTOSIZE );
    imshow( "MapImage", map.getImage() );

    namedWindow( "CellImage", CV_WINDOW_AUTOSIZE );
    imshow( "CellImage", AfterCellImage );

    namedWindow( "PathImage", CV_WINDOW_AUTOSIZE );
    imshow( "PathImage", PathImage );

    waitKey( 0 );
}
