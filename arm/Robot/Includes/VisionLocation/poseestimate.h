/*------------------------------------------------------------------------------------------*\
	功能描述：
	
	输入参数：
		
		
	输出参数：
		
\*------------------------------------------------------------------------------------------*/
#ifndef POSEESTIMATE_H
#define POSEESTIMATE_H

#include <iostream>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace std;
class	poseEstimate
{
	private:
		float x0,y0,theta0;//扫地机前帧姿态	
		float x1,y1,theta1;//扫地机后帧姿态
		float H,d1,d2,k1,k2;
		float fu,fv,u0,v0;//天花板高度，摄像机内参数
		void calculateWorldCoordinate(const KeyPoint &cornerpoint, Point2f &worldpoint);//计算前帧图像某特征点在世界坐标系下的坐标
		void sensorDeterminePointInNextFrame(const Point2f &worldpoint, Point &estimatepoint);//计算三维空间特征点在训练图像上的坐标
	public:
		poseEstimate(float &x0, float &y0, float &theta0, float &x1, float &y1, float &theta1, float &fu, float &fv, float &u0, float &v0, float &H, float &d1, float &d2);//构造函数
		void calculatePoseUsingCameraInLineMotion(const vector<DMatch> &matches, const vector<KeyPoint> &firstimgkpts, const vector<KeyPoint> &lastimgkpts,
				float &xestimate, float &yestimate, float &thetaestimate, int &successflag);//估计直线运动
		void calculateAngleUsingCameraInRotateMotion(const vector<DMatch> &matches, const vector<KeyPoint> &firstimgkpts, const vector<KeyPoint> &lastimgkpts,
				float &thetaestimate, int &successflag);//估计旋转运动
		void calculatePoseUsingCameraInAnyMotion(const vector<DMatch> &matches, const vector<KeyPoint> &firstimgkpts, const vector<KeyPoint> &lastimgkpts,
				float &xestimate, float &yestimate, float &thetaestimate, int &successflag);//估计直线运动
	public:
		Point2f worldpointgooda;
		vector<Point2f> worldpointgood;
};

#endif //POSEESTIMATE_H
