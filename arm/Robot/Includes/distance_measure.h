#ifndef DISTANCE_MEASURE_H_
#define DISTANCE_MEASURE_H_

#include<iostream>
#include<opencv2/opencv.hpp>
//#include "videodevice.h"
#include "dete.h"
#include "mark.h"
#include "centerline.h"


float distance_measure( Mat image,float *distance ,int &edgemask);
//int Frontinit();


#endif//DISTANCE_MEASURE_H_
