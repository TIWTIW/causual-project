#include "canvas.h"

using namespace std;
using namespace cv;

void canvas::SetSP(int ht, int wd, int pt_x, int pt_y)
{
    height = ht;
    width = wd;
    position.first = pt_x;
    position.second = pt_y;
}

void canvas::GetSP(int &ht, int &wd, pair<int, int> &pt)
{
    ht = height;
    wd = width;
    pt = position;
}

int canvas::initial(Mat &Image)
{
    rectangle(Image, Rect(position.first, position.second, height,width),
    Scalar(0,0,255));

    return 0;
}

int clear(Mat &Image)
{
    Image = Mat::zeros(Image.size(), CV_8UC3);

    return 0;
}
