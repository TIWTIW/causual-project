#ifndef DETE_H_
#define DETE_H_

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

float dete(Mat &img,int &minrow,int &maxrow);
float aver(Mat img);
int threshget(float grayaver);
#endif //DETE_H_
