#include "map.h"
#include "robot.h"
#include <iostream>

using namespace cv;
using namespace std;

#define MAP_SIZE 600

int main(int argc, char **argv)
{
    map worldMap(MAP_SIZE);

    worldMap.setObstacle();
    robot myRobot(60, 540, 6);

    while(true)
    {
        myRobot.move(worldMap);

        worldMap.show();
        waitKey(20);
    }

    worldMap.show();

}
