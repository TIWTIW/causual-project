#include "map.h"
#include <iostream>

using namespace std;
using namespace cv;


void map::drawWall()
{
    line(map_frame, Point(50, 50), Point(50, 550), Scalar(0, 0, 0), 2);
    line(map_frame, Point(50, 550), Point(550, 550), Scalar(0, 0, 0), 2);
    line(map_frame, Point(50, 50), Point(550, 50), Scalar(0, 0, 0), 2);
    line(map_frame, Point(550, 50), Point(550, 550), Scalar(0, 0, 0), 2);
}

map::map(int sz)
{
    map_frame = Mat(sz, sz, CV_8UC3, Scalar(0, 127, 127));

    drawWall();
    size = sz;
}

void map::show()
{
    imshow("World map",map_frame);
}

Mat &map::getFrame()
{
    return map_frame;
}

void map::setObstacle()
{
    cout << "Setting obstacle.." << endl;
    obstacle *obstacleInMap = new myRect;
    obstacleInMap->setObstacle(map_frame, 40);

    obstacleInMap = new myCircle;
    obstacleInMap->setObstacle(map_frame, 40);

    obstacleInMap = new myTriangle;
    obstacleInMap->setObstacle(map_frame, 40);
}

void map::fillRect(int x, int y, int sz, CvScalar value)
{
    rectangle(map_frame, Point(x - sz / 2, y - sz / 2), Point(x + sz / 2, y + sz / 2), value, -1);
}
