#ifndef _CENTERLINE_H
#define _CENTERLINE_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "pictureType.h"
using namespace std;
using namespace cv;

void centerline(Mat image,vector<vector<myline> >coord,vector<piece> shape,float *distance);
void downsize(vector<vector<myline> > coord,vector<vector<float> >&centerfinal);
void denoise(vector<vector<float> >&centerfinal,vector<piece> shape);
#endif//_CENTERLINE_H
