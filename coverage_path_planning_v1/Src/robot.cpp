#include "robot.h"
#include <iostream>

using namespace std;
using namespace cv;

void robot::move(map &mapData)
{
    if(noObstacle(mapData))
    {
        mapData.fillRect(px, py, window_size, Scalar(255, 255, 255));
        if(upDirection == up)
        {
            py -= window_size / 2;
        }
        else if(upDirection == down)
        {
            py += window_size / 2;
        }
    }
    else
    {
        localPlanning();
    }

//    cout << px << " " << py << endl;

}

bool robot::noObstacle(map &mapData)
{
    Mat frame = mapData.getFrame();

    if(upDirection == up)
    {
        for(int i = py; i >= py - window_size / 2; --i)
        {
            cout << (int)mapData.getFrame().at<Vec3b>(i, px)[1] << endl;
            if(frame.at<Vec3b>(i, px)[0] == 0 &&
               frame.at<Vec3b>(i, px)[1] == 0 &&
               frame.at<Vec3b>(i, px)[2] == 0)
            {
                cout << px << " " << i << endl;
                return false;
            }

        }
    }

    if(upDirection == down)
    {
        for(int i = py; i <= py + window_size / 2; ++i)
        {
            if(frame.at<Vec3b>(i, px)[0] == 0 &&
               frame.at<Vec3b>(i, px)[1] == 0 &&
               frame.at<Vec3b>(i, px)[2] == 0)
                return false;
        }
    }

    return true;

}

void robot::localPlanning()
{
    cout << "Enter local planning..." << endl;
    if(cleanDirection == left && upDirection == up)
    {
        //cleanDirection = right;
        px -= window_size;
        upDirection = down;
    }
    else if(cleanDirection == right && upDirection == down)
    {
        //cleanDirection = left;
        px += window_size;
        upDirection = up;
    }
    else if(cleanDirection == left && upDirection == down)
    {
        //cleanDirection = right;
        px -= window_size;
        upDirection = up;
    }
    else if(cleanDirection == right && upDirection == up)
    {
        //cleanDirection = left;
        px += window_size;
        upDirection = down;
    }
}
