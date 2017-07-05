#include "ETree.h"

using namespace std;
using namespace cv;

Point ETree::findNearstNode( Point currentPoint )
{
    Point nearestPoint( TreeBody[0].x, TreeBody[0].y );
    int minDis = abs( nearestPoint.x - currentPoint.x ) + abs( nearestPoint.y - currentPoint.y );

    for( int i = 1; i < TreeBody.size(); ++i )
    {
        if( abs( TreeBody[i].x - currentPoint.x ) + abs( TreeBody[i].y - currentPoint.y ) < minDis )
        {
            nearestPoint.x = TreeBody[i].x;
            nearestPoint.y = TreeBody[i].y;
            minDis = abs( nearestPoint.x - currentPoint.x ) + abs( nearestPoint.y - currentPoint.y );
        }
    }

    return nearestPoint;
}
