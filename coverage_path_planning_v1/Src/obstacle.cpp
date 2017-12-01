#include "obstacle.h"
#include <iostream>

using namespace cv;
using namespace std;

/*******基类******/
obstacle::obstacle()
{
    ;
}

obstacle::~obstacle()
{
    ;
}

void obstacle::initial(int x, int y, int size)
{
    position_x = x;
    position_y = y;
    size = size;
}

/*****派生类******/
/*****矩形********/
myRect::myRect()
{
    shape = RECTANGLE;
}

void myRect::setRect(Mat &Image, int x, int y, int size)
{
    this->position_x = x;
    this->position_y = y;
    this->size = size;

    rectangle(Image, Point(position_x, position_y), Point(position_x+size, position_y+size), Scalar(255, 255, 0), -1);
}

void myRect::setObstacle(Mat &Image, int size)
{
    srand(unsigned(time(NULL)));

    this->position_x = rand() % 300 + 200;
    this->position_y = rand() % 300 + 200;
    this->size = size;

    Mat targetImage = Image(Rect(position_x, position_y, size, size));

    while(checkRange(targetImage, true, 0, -1, 1))
    {
        this->position_x = rand() % 300 + 200;
        this->position_y = rand() % 300 + 200;
        targetImage = Image(Rect(position_x, position_y, size, size));
    }

    cout << "Rect:" << position_x << " " << position_y << endl;

    rectangle(Image, Point(position_x, position_y), Point(position_x+size, position_y+size), Scalar(0, 0, 0), -1);

}

/******圆形******/
myCircle::myCircle()
{
    shape = CIRCLE;
}

void myCircle::setCircle(Mat &Image, int x, int y, int size)
{
    this->position_x = x;
    this->position_y = y;
    this->size = size;

    circle(Image, Point(position_x, position_y), size, Scalar(255, 255, 0), -1);
}

void myCircle::setObstacle(Mat &Image, int size)
{
    //srand(unsigned(time(NULL)));

    this->position_x = rand() % 300 + 200;
    this->position_y = rand() % 300 + 200;
    this->size = size;

    Mat targetImage = Image(Rect(position_x - size/2, position_y - size/2, size, size));

    while(checkRange(targetImage, true , 0, -1, 1))
    {
        this->position_x = rand() % 300 + 200;
        this->position_y = rand() % 300 + 200;
        targetImage = Image(Rect(position_x - size/2, position_y - size/2, size, size));
    }

    circle(Image, Point(position_x, position_y), size, Scalar(0, 0, 0), -1);
}

/******三角形*****/
myTriangle::myTriangle()
{
    shape = TRIANGLE;
}

void myTriangle::setTriangle(Mat &Image, int x, int y, int size)
{
    this->position_x = x;
    this->position_y = y;
    this->size = size;

    Point trianglePoint[1][3];

    trianglePoint[0][0] = Point(position_x - size/2, position_y - size/2);
    trianglePoint[0][1] = Point(position_x + size/2, position_y - size/2);
    trianglePoint[0][2] = Point(position_x, position_y + size/2);

    const Point* ppt[1] = {trianglePoint[0]};
    int npt[] = {3};

    fillPoly(Image, ppt, npt, 1, Scalar(255, 255, 0));
}

void myTriangle::setObstacle(Mat &Image, int size)
{
    //srand(unsigned(time(NULL)));

    this->position_x = rand() % 300 + 200;
    this->position_y = rand() % 300 + 200;
    this->size = size;

    Mat targetImage = Image(Rect(position_x - size/2, position_y - size/2, size, size));

    while(checkRange(targetImage, true , 0, -1, 1))
    {
        this->position_x = rand() % 300 + 200;
        this->position_y = rand() % 300 + 200;
        targetImage = Image(Rect(position_x - size/2, position_y - size/2, size, size));
    }

    Point trianglePoint[1][3];

    trianglePoint[0][0] = Point(position_x - size/2, position_y - size/2);
    trianglePoint[0][1] = Point(position_x + size/2, position_y - size/2);
    trianglePoint[0][2] = Point(position_x, position_y + size/2);

    const Point* ppt[1] = {trianglePoint[0]};
    int npt[] = {3};

    fillPoly(Image, ppt, npt, 1, Scalar(0, 0, 0));
}

