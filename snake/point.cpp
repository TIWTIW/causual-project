#include "point.h"

using namespace std;
using namespace cv;

int point::SetPosition(int x, int y)
{
    pposition.first = x;   
    pposition.second = y;

    return 0;
}

pair<int, int> point::GetPT()
{
    return pposition;
}

unsigned int point::GetSZ()
{
    return size;
}

int point::RandomPosition(Mat &Image, canvas &cvas)
{
    srand(unsigned(time(NULL)));

    pposition.first = cvas.position.first + rand() % cvas.width;
    pposition.second = cvas.position.second + rand() % cvas.height;

    rectangle(Image, Point(pposition.first, pposition.second),
                     Point(pposition.first + size, pposition.second + size),
                     Scalar(255,0,0), -1);
    return 0;
}
