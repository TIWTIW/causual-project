/*------------------------------------------------------------------------------------------*\
	功能描述：
		使用fast结合Shi-Tomasi算法提取图像中的角点，最大数目为给定值并计算每个角点的方向和ORB特征描述符.
	输入参数：
		一幅图像(Mat)， fast检测阈值(int)， 最大检测的角点数目(int), 角点间的间距值(int)；
	输出参数：
		fastCornerDetect()返回检测到的角点坐标(vector<Point>);
		fastWithTomasiDetect()返回检测到的角点坐标(vector<KeyPoint>);
		角点的方向存于KeyPoint.angle;
		输入图像所有角点的描述符:uchar descriptors[32*maxCorners];
\*------------------------------------------------------------------------------------------*/
#ifndef CORNEREXTRACTION_H
#define CORNEREXTRACTION_H

#include <iostream>
#include <algorithm>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
class	cornerExtraction
{
	private:
		void makeOffsets(int pixel[25], int rowStride);//计算模板圆周像素和中心像素的坐标偏移
		int cornerScore(const uchar* ptr, const int pixel[], int threshold);//计算得分函数
		void fastCornerMinEigenVal(const Mat& inputimg, const vector<Point>& fastcorners, Mat& eigen);//计算某fast角点7*7邻域内协方差矩阵的最小值
		void pointAngle(const Mat& inputimg, vector<KeyPoint>& corners);//计算图像上所有角点的主方向
		//计算图像上每个角点的描述符
	public:
		cornerExtraction();
		void fastCornerDetect(const Mat &inputimg, vector<Point>& fastcorners, int threshold);//fast角点检测
		void shiTomasiDetect(const Mat& inputimg, const vector<Point>& fastcorners,vector<Point2f>& point, vector<KeyPoint>& corners, int maxCorners, int minDistance);
		void fastWithTomasiDetect(const Mat &inputimg, vector<KeyPoint>& corners,vector<Point2f>& point, int threshold, int maxCorners, int minDistance);//fast&Shi-Tomasi实现
		void computeOrbDescriptors(const Mat& inputimg, KeyPoint& corners, uchar* descriptors);
		void computeDescriptors(const Mat& inputimg, vector<KeyPoint>& corners, Mat& descriptors);//计算图像上每个角点的描述符
		void getFitCorners(const Mat &img, vector<KeyPoint> &kpCorners, Mat& descriptors, int &cornererror);
};
#endif //CORNEREXTRACTION_H
