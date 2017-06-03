#ifndef DISTANCE_DECODER_H_
#define DISTANCE_DECODER_H_

#include<iostream>
#include<vector>
#include<cmath>
#include<opencv2/opencv.hpp>
#include "COM_UserTypes.h"
using namespace std;
using namespace cv;

#define R 17
void distance_decoder(float *distance, pair<float,float> *realobst);
int directionGet(pair<float,float> *realobst,int cleanDirection);
void Frontobst(pair<float,float> *realobst,vector<pair<float,float> >&frontobst,float &frontnearest,unsigned int &frontnearestnum,float &extendnearest,float &extendfarthest,int alongdirection);
float AngleANDLengthGet(vector<pair<float,float> >&realobst,float &turnlength,unsigned int nearestnum,int turndirection, float &realfront);
void AngleIsOk(float angle,vector<pair<float,float> >realobst,float nearestnum,float &realfront,int turndirection);
void CrossLine(vector<unsigned int> &slopepair,vector<pair<float,float> >realobst,unsigned int index,unsigned int index2);
float DisP2P(float x1,float y1,float x2,float y2);
void LineParam(float x1,float y1,float x2,float y2,float &a, float &b ,float &c);
float DisP2L(float x0,float y0,float a,float b ,float c);
bool FreeTooMuch(vector<pair<float,float> >realobst,unsigned int index1,unsigned int index2, unsigned int &farest ,float a,float b,float c);
float angleget(float a ,float b ,int direction );
void lengthget(vector<pair<float,float> >realobst,unsigned int index,float angle,float &turnlength,int direction);
int Infrared_decoder(int voltage);
void obst_convert(pose_t posetake, pose_t posenow, pair<float,float> *obsttake, pair<float,float> *obstnow);
void obst_convert2(pose_t posetake, pose_t posenow, pair<float,float> *obsttake, pair<float,float> *obstnow ,int flag);
#endif//DISTANCE_DECODER_H_
