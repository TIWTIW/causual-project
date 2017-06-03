/*------------------------------------------------------------------------------------------*\
	功能描述：
		利用传感器提供的姿态信息实现特征点的匹配并消除错匹配和多重匹配,返回匹配对;
		使用传感器信息确定当前图像中的特征点在下一帧图像的大致范围，使用ORB特征和汉明距离选择最佳的匹配特征点；
		消除匹配点对的多重匹配后返回按优先级排序的匹配对；使用RANSAC筛选匹配点对。
	输入参数：
		前后帧图像Mat（firstimg, lastimg）、两组vector<KeyPoint>特征点、两组图像特征点描述符uchar descriptors[32*maxCorners]、
		扫地机拍摄前帧时的坐标(x0,y0,theta0)、拍摄后帧时的坐标（x1,y1,theta1）、天花板高度H、摄像机内参数矩阵fu,fv,u0,v0;
		
	输出参数：
		 原始匹配对:vector<DMatch>& matches，消除多重匹配后的匹配对：vector<DMatch>& bettermatches，RANSAC后的匹配对：vector<DMatch>& ransacmatches.
	说明：
		设图像帧序列为1,2,3，...n，则匹配的图像序列为(1,2)、(2,3)、(3，4)、...。未避免重复计算特征点的ORB特征，检查Keypoint.angle值，
		若为-1表示没有计算该帧图像特征点的ORB特征，否则计算过。
\*------------------------------------------------------------------------------------------*/
#ifndef CORNERMATCHING_H
#define CORNERMATCHING_H

#include "common_include.h"
#include "frame.h"
#include <iostream>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace cv;
using namespace std;
class	cornerMatching
{
	private:
		float x0,y0,theta0;//扫地机前帧姿态	
		float x1,y1,theta1;//扫地机后帧姿态
		float H,d1,d2;
		float fu,fv,u0,v0;//天花板高度，摄像机内参数
		
		void sensorDeterminePointInNextFrame(const Point2f &worldpoint, Point &estimatepoint);//计算三维空间特征点在训练图像上的坐标
		void findMinHammingDist(const uchar* src1, const uchar* src2, int flag, int &target, int &hammingdist);//确定与某个查找描述符具有最小汉明距离的后帧图像角点描述符索引号
	public:
		cornerMatching(float &x0, float &y0, float &theta0, float &x1, float &y1, float &theta1, 
			 float &fu, float &fv, float &u0, float &v0, float &H, float &d1, float &d2);//构造函数
		cornerMatching(float nnratio=0.6, bool checkOri=true);
		void calculateWorldCoordinate(const Point2f &cornerpoint, Point2f &worldpoint);//计算前帧图像某特征点在世界坐标系下的坐标
		void calculateWorldCoordinate(const KeyPoint &cornerpoint, Point2f &worldpoint);//
		void pointsTracking(const vector<Point2f>& firstimgkpts, 
				const vector<Point2f>& lastimgkpts,vector<Point2f>& firstimgkptstrack,vector<Point2f>& lastimgkptstrack);
		void pointsMatchingAlgorithm(const vector<KeyPoint>& firstimgkpts, const vector<KeyPoint>& lastimgkpts, 
			 Mat& firstdescriptors, Mat& lastdescriptors, vector<DMatch>& matches);//特征点匹配
		void eliminateErrorMatching(vector<DMatch>& matches, vector<DMatch>& goodmatches);//按照汉明距离降序排序匹配点对，并去除一对多的匹配对
		void ransacWithHomography(const vector<DMatch> &goodmatches, const vector<KeyPoint> &firstimgkpts, 
			 const vector<KeyPoint> &lastimgkpts, vector<DMatch> &ransacmatches);// 使用单应性估计的RANSAC剔除错误匹配
		
		static int DescriptorDistance(const cv::Mat &a, const cv::Mat &b);
		//int SearchByBoW(Frame *pKF, Frame &F, std::vector<KeyPoint> &vpMapPointMatches);
	public:

	    static const int TH_LOW=50;
	    static const int TH_HIGH=100;
	    static const int HISTO_LENGTH=30;

	protected:
		void ComputeThreeMaxima(std::vector<int>* histo, const int L, int &ind1, int &ind2, int &ind3);
		float mfNNratio;
    	bool mbCheckOrientation;
};

#endif //CORNERMATCHING_H
