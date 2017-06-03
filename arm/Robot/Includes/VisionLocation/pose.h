#ifndef POSE_H_
#define POSE_H_

#include <math.h>
//#include "videodevice.h"
#include <sstream>
#include <string>
#include <iostream>  
#include <fstream>  
#include <iomanip>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "videodevice.h"
#include "cornerextraction.h"
#include "cornermatching.h"
#include "poseestimate.h"

#include "frame.h"
#include "common_include.h"

#include "RobotTypes.h"
#include "COMUART.h"
//#include "mappoint.h"
//#include "map.h"
using namespace std;
using namespace cv;

#define PI 3.1415926
#include "RobotTypes.h"
#include "COMUART.h"

#define FILE_VIDEO0  "/dev/video0"
#define FILE_VIDEO1  "/dev/video1"
#define FILE_VIDEO4  "/dev/video4"

extern videoDevice getframe;

class cornerExtraction;
class cornerMatching;
class poseEstimate;

class Pose
{
private:
	void getFitCorners(const Mat &img, vector<Point> &corners, vector<KeyPoint> &kpCorners, Mat& descriptors, int &cornererror);
	
	//POSE poserobot_;

public:
	typedef shared_ptr<Pose> Ptr;
	
	enum PoseState
	{
		INIT,
		OK,
		LOST
	};
	
	PoseState      state_; //current VO state
	MoveState      movestate_;
	//Map::Ptr       map_;

	Frame::Ptr     ref_;
	Frame::Ptr     curr_; //current frame
	POSE           poserobot_;
	POSE           posetotal_;
	DATA           sensordata_;
	int            cornererror;
	int            successflag ;
	
	//Point3f        p(0,0,0);
	//uchar          descriptors_curr_[32*100];
    //uchar          descriptors_ref_[32*100];
	//vector<MapPoint::Ptr>   match_3dpts_;       // matched 3d points 
    //vector<int>             match_2dkp_index_;  // matched 2d pixels (index of kp_curr)

public:
	Pose();
	~Pose();
	bool addFrame(Frame::Ptr frame, int frame_id, const unsigned char movestate_, DATA& sensordata);
	//void addMapPoints();
	void poseTotal();
	void poseTotal(DATA& sensordata);
	void world2pixel(POSE& posetotal,Point3f& p_world,Point2f& pixel);
	POSE getPose() { return poserobot_; }
	POSE getPoseTotal() { return posetotal_; }
	//void optimizeMap();
	//POSE computePoseLine(INFO_FRAME& lastFrame,DATA& sensordata , int& flag);
	//POSE computePoseRotate(INFO_FRAME& lastFrame, DATA& sensordata , int& flag);

public:
	//virtual bool processFirstFrame();
	/// 处理第二帧
	//virtual bool processSecondFrame();
	/// 处理完开始的两个帧后处理所有帧
	//virtual bool processFrame(int frame_id);
	//std::vector<cv::Mat> toDescriptorVector(const cv::Mat &Descriptors);
	void poseEstimationRotate (DATA& sensordata);
	//Rotate pose
	void poseEstimationForward(DATA& sensordata);
	//Forward pose
	void poseEstimationAny(DATA& sensordata);
	void calculateWorldCoordinate(const KeyPoint &cornerpoint, Point2f &worldpoint);

};	



#endif //POSE_H_

