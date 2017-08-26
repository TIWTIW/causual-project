#ifndef ROBOT_DATA_H
#define ROBOT_DATA_H

#include <vector>

// temp definetion of pose
struct Pose
{
    int x;
    int y;
    int theta;
};

//temp definetion of sensor data
extern int Sen_data;

//temp definetion of img
extern int Image_data;

//temp definetion of path
struct Path
{
    std::vector<int> Path_data;
};

#endif
