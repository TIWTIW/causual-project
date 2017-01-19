#include "common.h"
#include "target.h"
#include "box.h"
#include "obstacle.h"

void calRoute(box box, target target, int &err_x, int &err_y);
void moveToTarget(cv::Mat Image, box box, int &err_x, int &err_y);
void initial(box &box, target &target);
void obstacleInitial(cv::Mat Image, int num);
