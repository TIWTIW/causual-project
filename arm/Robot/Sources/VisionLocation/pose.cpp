#include "pose.h"
#include "COM_UART/COMUART.h"

//cornerExtraction imgcorner;
//static cornerMatching imgmatching_rotate(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, fu, fv, u0, v0, H, d1, d2);;
videoDevice getframe(FILE_VIDEO1, 30);

Pose::Pose():state_(INIT)
{
	// Add by limin @ 2017-03-13
	posetotal_.x = 0;
	posetotal_.y = 0;
	posetotal_.theta = 0;
}
Pose::~Pose()
{

}

bool Pose::addFrame(Frame::Ptr frame, int frame_id, const unsigned char movestate_ ,DATA& sensordata )
{
	successflag = 0;
	if (frame->img_.empty() )
	{
		cout<<"Frame: provided image is empty ,please make sure the photo's directory"<<endl;
		return false;
	}
	// Add New Frame
	switch( state_ )
    {
	    case INIT:
	        state_ = OK;
	        // extract features from first frame and add them into map
	        getFitCorners(frame->img_, frame->fastcorners_, frame->corners_, frame->descriptors_, cornererror);
	        ref_ = frame;
	        //addKeyFrame();      // the first frame is a key-frame
	        break;
	    case OK:
	        //curr_->pose_ = ref_->pose_;
	        getFitCorners(frame->img_, frame->fastcorners_, frame->corners_, frame->descriptors_, cornererror); 
	        curr_ = frame;
	        switch(movestate_)
	        {
	        	case STAT_MOVE_TURNLEFT:
	        	{
	        		//featureMatching();
	       			poseEstimationRotate(sensordata);
	       			poseTotal();
	        		break;
	        	}
	        	case STAT_MOVE_FORWARD:
	        	{
	        		poseEstimationForward(sensordata);
	        		//optimizeMap();
	        		poseTotal();
	        		break;
	        	}
	        	default:
	        		poseEstimationAny(sensordata);
	        		//optimizeMap();
	        		poseTotal();
	        		break;
	        }
	        if(poserobot_.x==0 && poserobot_.y==0 && poserobot_.theta==0)
	        	cout<<"LOST"<<endl;
	        	//state_ = LOST;
	        ref_ = curr_;
	        break;
	    case LOST:
	        cout<<"vo has lost."<<endl;
	        break;
    }

    if(successflag == -1)
    	return false;
    else
    	return true;
}




void Pose::getFitCorners(const Mat &img, vector<Point> &corners, vector<KeyPoint> &kpCorners, Mat& descriptors, int &cornererror)
{
	int threshold=10;
	int size=0;
	int thresholdcount=0;
	//图像FAST角点提取阈值确定
	cornerExtraction imgcorner;
	vector<Point2f> point;
	if(!img.empty())
	{
		while(1)//fast角点检测
		{
			//cout<<"do fast detect!"<<endl;
			imgcorner.fastCornerDetect(img, corners, threshold);
			//cout<<"hehe fast corners size is: "<<corners.size()<<endl;
			thresholdcount++;
			size=corners.size();
			if(thresholdcount>=3)
			{
				//cout<<"fast threshold is: "<<threshold<<endl;
				//cout<<"fast corners size is: "<<corners.size()<<endl;
				break;
			}
			if(size>=200 && size<=500)
			{
				//cout<<"fast threshold is: "<<threshold<<endl;
				//cout<<"fast corners size is: "<<corners.size()<<endl;
				break;
			}
			else if(size<=50)
				threshold-=5;
			else if(50<size && size<200)
				threshold-=5;
			else if(size>=1000)
				threshold+=5;
			else if(500<size && size<1000)
				threshold+=5;
		}
		imgcorner.shiTomasiDetect(img, corners,point, kpCorners, 110, 15);//Shi-Tomasi角点检测
		//cout<<"image corners size is: "<<kpCorners.size()<<endl;
		if(kpCorners.size()<=20)
		{
			cornererror=-1;
			cout<<"Can not find enough corners!"<<endl;
		}
		else
		{
			imgcorner.computeDescriptors(img, kpCorners, descriptors);//计算图像上每个角点的描述符
			//cout<<"Have done computeDescriptors"<<endl;

		}
	}
	else
	{
		cornererror=-1;
		cout<<"the image is empty!"<<endl;
	}
}


/*std::vector<cv::Mat> Pose::toDescriptorVector(const cv::Mat &Descriptors)
{
    std::vector<cv::Mat> vDesc;
    vDesc.reserve(Descriptors.rows);
    for (int j=0;j<Descriptors.rows;j++)
        vDesc.push_back(Descriptors.row(j));

    return vDesc;
}*/


void Pose::poseEstimationRotate(DATA& sensordata)
{
	vector<DMatch> matches,goodmatches,ransacmatches;
	Mat resultimg;
	//int successflag=0;

	float xstart = 0;
	float ystart = 0;
	float thetastart = 0;
	float fu, fv, u0, v0;
	
	fu=358.836;
	fv=358.599;
	u0=324.41;
	v0=260.263;
	float H=321.80;//天花板离摄像机镜头的高度，单位mm
	float d1=7.8;// 摄像头中心离吸尘器中心的距离，单位mm
	float d2=0.0;// 摄像头中心的偏移量，单位为cm
	
	cornerMatching imgmatching_rotate(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, fu, fv, u0, v0, H, d1, d2);//图像匹配
	imgmatching_rotate.pointsMatchingAlgorithm(ref_->corners_, curr_->corners_, ref_->descriptors_, curr_->descriptors_,matches);//特征点匹配
	//cout<<"matching..."<<endl;
	if(matches.size()<=2)
	{
		successflag=-1;
				//cout<<"Can not find enough matches!"<<endl;
	}
	else
	{
		imgmatching_rotate.eliminateErrorMatching(matches, goodmatches);
		int goodmatchessize=goodmatches.size();
		Mat resultimg;
		//cout<<"goodmatching..."<<endl;
		if(goodmatchessize<=2)
		{
			successflag=-1;
			//cout<<"Can not find enough matches!"<<endl;
		}
		else if(goodmatchessize>=8)
		{
			//cout<<"do ransac!"<<endl;
			imgmatching_rotate.ransacWithHomography(goodmatches, ref_->corners_, curr_->corners_, ransacmatches);// 使用单应性估计的RANSAC剔除错误匹配
			drawMatches(ref_->img_, ref_->corners_, curr_->img_, curr_->corners_, ransacmatches, resultimg);
			imwrite("ransacmatchimge.jpg", resultimg);

			/*match_3dpts_.clear();
    		match_2dkp_index_.clear();
    		for ( cv::DMatch& m : ransacmatches )
		    {
		        
	            //match_3dpts_.push_back( candidate[m.queryIdx] );
	            match_2dkp_index_.push_back( m.trainIdx );
		        
		    }*/
					//运动估计
			poseEstimate getfinalpose_rotate(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, fu, fv, u0, v0, H, d1, d2);
			getfinalpose_rotate.calculateAngleUsingCameraInRotateMotion(ransacmatches, ref_->corners_, curr_->corners_, poserobot_.theta, successflag);
			//cout<<"successflag:R:1:"<<successflag<<endl;
		}
		else
		{
			/*match_3dpts_.clear();
    		match_2dkp_index_.clear();
    		for ( cv::DMatch& m : goodmatches )
		    {
		        
	            //match_3dpts_.push_back( candidate[m.queryIdx] );
	            match_2dkp_index_.push_back( m.trainIdx );
		        
		    }*/
			drawMatches(ref_->img_, ref_->corners_, curr_->img_, curr_->corners_, goodmatches, resultimg);
			imwrite("matchimge.jpg", resultimg);		
				//运动估计
			poseEstimate getfinalpose_rotate(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta,fu, fv, u0, v0, H, d1, d2);
			getfinalpose_rotate.calculateAngleUsingCameraInRotateMotion(goodmatches, ref_->corners_, curr_->corners_, poserobot_.theta, successflag);
			
		}
		poserobot_.x=fabs(sensordata.x); 
		poserobot_.y=fabs(sensordata.y);
		//pose.x=0;pose.y=0;
		//cout<<" pose:x,y,theta:R:"<<poserobot_.x<<" "<<poserobot_.y<<" "<<poserobot_.theta<<endl;
	}

	if (successflag == -1)
	{
		poserobot_.x=fabs(sensordata.x); 
		poserobot_.y=fabs(sensordata.y);
		poserobot_.theta=sensordata.theta;
	}
	//cout<<"successflag:R:2:"<<successflag<<endl;
	//cout<<" pose:x,y,theta:R:"<<poserobot_.x<<" "<<poserobot_.y<<" "<<poserobot_.theta<<endl;
	matches.clear();
	goodmatches.clear();
	ransacmatches.clear();
}

void Pose::poseEstimationForward(DATA& sensordata)
{
	vector<DMatch> matches,goodmatches,ransacmatches;
	Mat resultimg;
	//int successflag=0;
	float xstart = 0;
	float ystart = 0;
	float thetastart = 0;
	float fu, fv, u0, v0;
	
	fu=358.836;
	fv=358.599;
	u0=324.41;
	v0=260.263;
	float H=321.80;//天花板离摄像机镜头的高度，单位mm
	float d1=7.80;// 摄像头中心离吸尘器中心的距离，单位mm
	float d2=0.0;// 摄像头中心的偏移量，单位为cm

	cornerMatching imgmatching_linelength(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, fu, fv, u0, v0, H, d1, d2);//图像匹配
	imgmatching_linelength.pointsMatchingAlgorithm(ref_->corners_, curr_->corners_, ref_->descriptors_, curr_->descriptors_, matches);//特征点匹配
	
	//cout<<"Matching..."<<endl;
	if(matches.size()<=2)
	{
		successflag=-1;
				//cout<<"Can not find enough matches!"<<endl;
	}
	else
	{
		imgmatching_linelength.eliminateErrorMatching(matches, goodmatches);
		int goodmatchessize=goodmatches.size();
		Mat resultimg;
		//cout<<"good matching.."<<endl;
		if(goodmatchessize<=2)
		{
			successflag=-1;
			//cout<<"Can not find enough matches!"<<endl;
		}
		else if(goodmatchessize>=8)
		{
			//cout<<"do ransac!"<<endl;
			imgmatching_linelength.ransacWithHomography(goodmatches, ref_->corners_, curr_->corners_, ransacmatches);// 使用单应性估计的RANSAC剔除错误匹配
			drawMatches(ref_->img_, ref_->corners_, curr_->img_, curr_->corners_, ransacmatches, resultimg);
			imwrite("ransacmatchimge.jpg", resultimg);
					//运动估计
			/*match_3dpts_.clear();
    		match_2dkp_index_.clear();
    		for ( cv::DMatch& m : ransacmatches )
		    {		        
	            //match_3dpts_.push_back( candidate[m.queryIdx] );
	            match_2dkp_index_.push_back( m.trainIdx );
		        
		    }*/
			poseEstimate getfinalpose_linelength(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, fu, fv, u0, v0, H, d1, d2);
			getfinalpose_linelength.calculatePoseUsingCameraInLineMotion(ransacmatches, ref_->corners_, curr_->corners_, poserobot_.x, poserobot_.y, poserobot_.theta, successflag);
			
			//cout<<"successflag:L:1"<<successflag<<endl;
		}
		else
		{
			/*match_3dpts_.clear();
    		match_2dkp_index_.clear();
    		for ( cv::DMatch& m : goodmatches )
		    {
		        
	            //match_3dpts_.push_back( candidate[m.queryIdx] );
	            match_2dkp_index_.push_back( m.trainIdx );
		        
		    }*/
			drawMatches(ref_->img_, ref_->corners_, curr_->img_, curr_->corners_, goodmatches, resultimg);
			imwrite("matchimge.jpg", resultimg);		
				//运动估计
			poseEstimate getfinalpose_linelength(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, fu, fv, u0, v0, H, d1, d2);
			getfinalpose_linelength.calculatePoseUsingCameraInLineMotion(goodmatches, ref_->corners_, curr_->corners_, poserobot_.x, poserobot_.y, poserobot_.theta, successflag);
			
		}
		poserobot_.x = fabs(poserobot_.x);
		poserobot_.y = fabs(poserobot_.y);
		//cout<<" pose:x,y,theta:L:"<<poserobot_.x<<" "<<poserobot_.y<<" "<<poserobot_.theta<<endl;
	}

	if (successflag == -1)
	{
		poserobot_.x=fabs(sensordata.x); 
		poserobot_.y=fabs(sensordata.y);
		poserobot_.theta=sensordata.theta;
	}
	//cout<<"successflag:L:2:"<<successflag<<endl;
	//cout<<" pose:x,y,theta:L:"<<poserobot_.x<<" "<<poserobot_.y<<" "<<poserobot_.theta<<endl;
	matches.clear();
	goodmatches.clear();
	ransacmatches.clear();
}

void Pose::poseEstimationAny(DATA& sensordata)
{
	vector<DMatch> matches,goodmatches,ransacmatches;
	Mat resultimg;
	//int successflag=0;
	float xstart = 0;
	float ystart = 0;
	float thetastart = 0;

	cornerMatching imgmatching_anylength(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, ref_->camera_->fu_, ref_->camera_->fv_, ref_->camera_->u0_, ref_->camera_->v0_, ref_->camera_->H_, ref_->camera_->d1_, ref_->camera_->d2_);//图像匹配
	imgmatching_anylength.pointsMatchingAlgorithm(ref_->corners_, curr_->corners_, ref_->descriptors_, curr_->descriptors_, matches);//特征点匹配
	
	cout<<"Matching..."<<endl;
	if(matches.size()<=2)
	{
		successflag=-1;
				//cout<<"Can not find enough matches!"<<endl;
	}
	else
	{
		imgmatching_anylength.eliminateErrorMatching(matches, goodmatches);
		int goodmatchessize=goodmatches.size();
		Mat resultimg;
		cout<<"good matching.."<<endl;
		if(goodmatchessize<=2)
		{
			successflag=-1;
			cout<<"Can not find enough matches!"<<endl;
		}
		else if(goodmatchessize>=6)
		{
			cout<<"do ransac!"<<endl;
			imgmatching_anylength.ransacWithHomography(goodmatches, ref_->corners_, curr_->corners_, ransacmatches);// 使用单应性估计的RANSAC剔除错误匹配
			drawMatches(ref_->img_, ref_->corners_, curr_->img_, curr_->corners_, ransacmatches, resultimg);
			
			// Commented by limin @ 2017-03-13
			//imwrite("ransacmatchimge.jpg", resultimg);
			
			poseEstimate getfinalpose_anylength(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, ref_->camera_->fu_, ref_->camera_->fv_, ref_->camera_->u0_, ref_->camera_->v0_, ref_->camera_->H_, ref_->camera_->d1_, ref_->camera_->d2_);
			getfinalpose_anylength.calculatePoseUsingCameraInAnyMotion(ransacmatches, ref_->corners_, curr_->corners_, poserobot_.x, poserobot_.y, poserobot_.theta, successflag);
			
			///cout<<"successflag:L:1"<<successflag<<endl;
		}
		else
		{
			drawMatches(ref_->img_, ref_->corners_, curr_->img_, curr_->corners_, goodmatches, resultimg);
			
			// Commented by limin @ 2017-03-13
			//imwrite("matchimge.jpg", resultimg);		
			//运动估计
			poseEstimate getfinalpose_anylength(xstart, ystart, thetastart, sensordata.x, sensordata.y, sensordata.theta, ref_->camera_->fu_, ref_->camera_->fv_, ref_->camera_->u0_, ref_->camera_->v0_, ref_->camera_->H_, ref_->camera_->d1_, ref_->camera_->d2_);
			getfinalpose_anylength.calculatePoseUsingCameraInAnyMotion(goodmatches, ref_->corners_, curr_->corners_, poserobot_.x, poserobot_.y, poserobot_.theta, successflag);
			//cout<<"successflag:L:2:"<<successflag<<endl;
		}
		poserobot_.x = fabs(poserobot_.x);
		poserobot_.y = fabs(poserobot_.y);
		
	}
	if (successflag == -1)
	{
		poserobot_.x=fabs(sensordata.x); 
		poserobot_.y=fabs(sensordata.y);
		poserobot_.theta=sensordata.theta;
	}
	cout<<"successflag:A:2:"<<successflag<<endl;
	//cout<<" pose:x,y,theta:A:"<<poserobot_.x<<" "<<poserobot_.y<<" "<<poserobot_.theta<<endl;
	cout << "poserobot_" << poserobot_ << endl;
	matches.clear();
	goodmatches.clear();
	ransacmatches.clear();
}

void Pose::poseTotal()
{
	posetotal_.theta += poserobot_.theta ;
	float posetotal_PI = posetotal_.theta* PI/180;
	posetotal_.x += poserobot_.x*cosf( posetotal_PI);
	posetotal_.y += poserobot_.y*sinf( posetotal_PI );
	//cout<<" pose:x,y,theta:Total:"<<posetotal_.x<<" "<<posetotal_.y<<" "<<posetotal_.theta<<endl;
	
}
void Pose::poseTotal(DATA& sensordata)
{
	posetotal_.theta += sensordata.theta ;
	float posetotal_PI = posetotal_.theta* PI/180;
	posetotal_.x += fabs(sensordata.x)*cosf( posetotal_PI);
	posetotal_.y += fabs(sensordata.y)*sinf( posetotal_PI );
	//cout<<" pose:x,y,theta:Total:"<<posetotal_.x<<" "<<posetotal_.y<<" "<<posetotal_.theta<<endl;
}
/*void Pose::addMapPoints()
{
	Point2f worldpoint;
	vector<bool> matched(curr_->corners_.size(), false); 
    for ( int index:match_2dkp_index_ )
        matched[index] = true;
    for ( int i=0; i<curr_->corners_.size(); i++ )
    {
        if ( matched[i] == true )   
            //continue;
        /*double d = ref_->findDepth ( keypoints_curr_[i] );
        if ( d<0 )  
            continue;*/
       /* {
	        calculateWorldCoordinate(curr_->corners_[i],worldpoint);
	        worldpoint.x += posetotal_.x;
	        worldpoint.y += posetotal_.y;
	        Point3f p_world(worldpoint.x,worldpoint.y,curr_->camera_->H_);
	        
	        MapPoint::Ptr map_point = MapPoint::createMapPoint(
	            p_world, curr_.get()
	        );
	        //cout<<"map..."<<endl;
	        match_3dpts_.push_back(map_point);
	        //map_->insertMapPoint( map_point );
    	}
    	else
    		continue;
    }*/




void Pose::calculateWorldCoordinate(const KeyPoint &cornerpoint, Point2f &worldpoint)
{
	//float M=(cornerpoint.pt.x-u0)*H/fu+d2;
	//float N=(cornerpoint.pt.y-v0)*H/fv-d1;
	//图像中一点可求解出对应的一条射线，由于天花板高度已知，则该点对应天花板上的坐标是可求的
	worldpoint.x=-(cornerpoint.pt.y-curr_->camera_->v0_)*curr_->camera_->H_/curr_->camera_->fv_+curr_->camera_->d1_;
	worldpoint.y=(cornerpoint.pt.x-curr_->camera_->u0_)*curr_->camera_->H_/curr_->camera_->fu_+curr_->camera_->d2_;
	//cout<<"The real world coordinate is: "<<worldpoint.x<<" with "<<worldpoint.y<<endl;
}

/*void Pose::optimizeMap()
{
	if ( match_2dkp_index_.size()<100 )
		cout<<"match_2dkp_index_.size:"<<match_2dkp_index_.size()<<endl;
        addMapPoints();
	//cout<<"map points: "<<map_->map_points_.size()<<endl;
}
*/
void Pose::world2pixel(POSE& posetotal,Point3f& p_world,Point2f& pixel)
{
	float M = p_world.x - posetotal.x;
	float N = p_world.y - posetotal.y;
	float K1= curr_->camera_->fu_/curr_->camera_->H_;
	float K2= curr_->camera_->fv_/curr_->camera_->H_;
	pixel.x = curr_->camera_->u0_+K1*(-M*sin(posetotal.theta*CV_PI/180.0)+N*cos(posetotal.theta*CV_PI/180.0)-curr_->camera_->d2_);
	pixel.y = curr_->camera_->v0_+K1*(-M*cos(posetotal.theta*CV_PI/180.0)-N*sin(posetotal.theta*CV_PI/180.0)+curr_->camera_->d1_);
}