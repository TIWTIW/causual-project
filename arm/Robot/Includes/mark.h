#ifndef MARK_H_
#define MARK_H_


#include<iostream>
#include<opencv2/opencv.hpp>
#include"pictureType.h"

using namespace std;
using namespace cv;

void getlines(const Mat& img,vector<int>& stRun,vector<int>& enRun,vector<int>& colRun,int &NumberOfRuns,int minrow,int maxrow);
void firstPass(vector<int>& stRun, vector<int>& enRun, vector<int>& colRun, int NumberOfRuns,int * runLabels, vector<pair<int, int> >& equivalences, int offset);
void replaceSameLabel(int* runLabels, vector<pair<int, int> >&equivalence,int number,int &maxLabel);
void mark_white(Mat &image,Mat imageori,vector<piece>&shape,vector<vector<myline> >&coord,int minrow,int maxrow ,int &edgemask);

#endif//MARK_H_


