#include "poseestimate.h"
/*****************************************************构造函数*****************************************************/
poseEstimate::poseEstimate(float &x0, float &y0, float &theta0, float &x1, float &y1, float &theta1, float &fu, float &fv, 
		float &u0, float &v0, float &H, float &d1, float &d2)
{
	this->x0=x0; this->y0=y0; this->theta0=theta0;
	this->x1=x1; this->y1=y1; this->theta1=theta1;
	this->fu=fu; this->fv=fv; this->u0=u0; this->v0=v0;
	this->H=H; this->d1=d1; this->d2=d2;
	k1=fu/H; k2=fv/H;
}

/*****************************************************私有函数*****************************************************/
//计算前帧图像某特征点在世界坐标系下的坐标
void poseEstimate::calculateWorldCoordinate(const KeyPoint &cornerpoint, Point2f &worldpoint)
{
	float M=(cornerpoint.pt.x-u0)*H/fu+d2;
	float N=(cornerpoint.pt.y-v0)*H/fv-d1;
	//图像中一点可求解出对应的一条射线，由于天花板高度已知，则该点对应天花板上的坐标是可求的
	worldpoint.x=x0-M*sin(theta0*CV_PI/180.0)-N*cos(theta0*CV_PI/180.0);
	worldpoint.y=y0+M*cos(theta0*CV_PI/180.0)-N*sin(theta0*CV_PI/180.0);
	//cout<<"The real world coordinate is: "<<worldpoint.x<<" with "<<worldpoint.y<<endl;
}
/*****************************************************公有函数*****************************************************/
//计算吸尘器的位姿
void poseEstimate::calculatePoseUsingCameraInLineMotion(const vector<DMatch> &matches, const vector<KeyPoint> &firstimgkpts, const vector<KeyPoint> &lastimgkpts,
			float &xestimate, float &yestimate, float &thetaestimate, int &successflag)
{
	successflag=0;//默认为0
	int matchsize=matches.size();
	//cout<<"the match size is: "<<matchsize<<endl;
	Point2f worldpointa, worldpointb;
	vector<Point2f> worldpoint;
	worldpoint.clear();
	for(int i=0;i<matchsize;i++)//计算前帧图像特征点在世界坐标下的坐标
	{
		calculateWorldCoordinate(firstimgkpts[matches[i].queryIdx], worldpointa);
		worldpoint.push_back(worldpointa);
	}
	//估计旋转的角度值
	vector<float> thetastore;
	float a=0,b=0,m=0,n=0,theta=0,thetaadd=0;
	for(int i=0;i<matchsize-1;i++)
	{
		worldpointa=worldpoint[i];
		for(int j=i+1;j<matchsize;j++)
		{
			worldpointb=worldpoint[j];
			a=(worldpointb.x-worldpointa.x);
			b=(worldpointb.y-worldpointa.y);
			m=(lastimgkpts[matches[i].trainIdx].pt.x-lastimgkpts[matches[j].trainIdx].pt.x)/k1;
			n=(lastimgkpts[matches[i].trainIdx].pt.y-lastimgkpts[matches[j].trainIdx].pt.y)/k2;
			if(a!=0 || b!=0)
			{
				/*float temp=(a*n-b*m)/(a*a+b*b);
				if(temp>=1.0)
					temp=1;
				else if(temp<=-1.0)
					temp=-1;
				theta=acos(temp)*180.0/CV_PI;//当次估计的角度值,cos(theta)在[-90 +90]内没有正负号*/  
				
				float temp=(a*m+b*n)/(a*a+b*b);
				if(temp>=1.0)
					temp=1;
				else if(temp<=-1.0)
					temp=-1;
				theta=asin(temp)*180.0/CV_PI;//当次估计的角度值
				if(theta<theta1+5 && theta>theta1-5)
				{
					thetaadd+=theta;
					thetastore.push_back(theta);
				}
			}
		}
	}	
	int thetasize=thetastore.size();
	theta=0;
	if(thetasize==0)
		successflag=-1;//表示定位出错
	else
	{
		//计算角度
		thetaadd/=thetasize;
		int count=0;
		for(int i=0;i<thetasize;i++)
		{
			if(thetastore[i]<thetaadd+5 && thetastore[i]>thetaadd-5)
			{
				count++;
				theta+=thetastore[i];
			}
		}
		if(count==0)
			successflag=-1;//表示定位出错
		else
		{
			thetaestimate=theta/count;//估计的角度值
			if(thetaestimate<=3 && thetaestimate>=-3)//角度满足条件，则计算移动的距离
			{
				//估计扫地机在世界坐标系下的坐标
				float costheta=cos(thetaestimate*CV_PI/180.0);
				float sintheta=sin(thetaestimate*CV_PI/180.0);
				float xnumber=0,ynumber=0;
				int realnumber=0;
				for(int i=0;i<matchsize;i++)
				{
					//计算在世界坐标系下的平移量x和y
					Point lpt=lastimgkpts[matches[i].trainIdx].pt;
					float m=(lpt.x-u0)/k1+d2;
					float n=(lpt.y-v0)/k2-d1;
					float xtemp=worldpoint[i].x+m*sintheta+n*costheta;
					float ytemp=worldpoint[i].y-m*costheta+n*sintheta;
					//cout<<"xtemp and ytemp are: "<<xtemp<<" "<<ytemp<<endl;
					if(xtemp<x1+5 && xtemp>x1-5 && ytemp<y1+5 && ytemp>y1-5)//移动5cm范围，x方向的偏差不能超过[-5,5]cm,y方向的偏差不能超过[-3,3]cm
					{
						realnumber++;
						xnumber+=xtemp;
						ynumber+=ytemp;
						//此处为筛选过的keypoint,减少计算量
						
						/*calculateWorldCoordinate(firstimgkpts[matches[i].queryIdx], worldpointgooda);
						worldpointgood.push_back(worldpointgooda);

						cout<<"The real world coordinate is: "<<worldpointgooda.x<<" with "<<worldpointgooda.y<<endl;*/
					}
		
				}
				if(realnumber==0)
					successflag=-1;//表示定位出错
				else
				{
					xestimate=xnumber/realnumber;
					yestimate=ynumber/realnumber;
					//cout<<"number is: "<<realnumber<<endl;
					successflag=1;//表示定位成功
					cout<<"The pose angle is: "<<thetaestimate<<"."<<endl;
					cout<<"The estimated robot site is: "<<xestimate<<" with "<<yestimate<<endl;
				}
				
			}
			else
				successflag=-1;//表示定位出错
		}
	}
}
void poseEstimate::calculateAngleUsingCameraInRotateMotion(const vector<DMatch> &matches, const vector<KeyPoint> &firstimgkpts, const vector<KeyPoint> &lastimgkpts,
			float &thetaestimate, int &successflag)
{
	successflag=0;//默认为0
	int matchsize=matches.size();
	Point2f worldpointa, worldpointb;
	vector<Point2f> worldpoint;
	worldpoint.clear();
	for(int i=0;i<matchsize;i++)//计算前帧图像特征点在世界坐标下的坐标
	{
		calculateWorldCoordinate(firstimgkpts[matches[i].queryIdx], worldpointa);
		worldpoint.push_back(worldpointa);
	}
	//估计旋转的角度值
	vector<float> thetastore;
	float a=0,b=0,m=0,n=0,theta=0,thetaadd=0;
	for(int i=0;i<matchsize-1;i++)
	{
		worldpointa=worldpoint[i];
		for(int j=i+1;j<matchsize;j++)
		{
			worldpointb=worldpoint[j];
			a=(worldpointb.x-worldpointa.x);
			b=(worldpointb.y-worldpointa.y);
			m=(lastimgkpts[matches[i].trainIdx].pt.x-lastimgkpts[matches[j].trainIdx].pt.x)/k1;
			n=(lastimgkpts[matches[i].trainIdx].pt.y-lastimgkpts[matches[j].trainIdx].pt.y)/k2;
			if(a!=0 || b!=0)
			{
				float temp=(a*m+b*n)/(a*a+b*b);
				if(temp>=1.0)
					temp=1;
				else if(temp<=-1.0)
					temp=-1;
				theta=asin(temp)*180.0/CV_PI;//当次估计的角度值
				if(theta<theta1+5 && theta>theta1-5)
				{
					thetaadd+=theta;
					thetastore.push_back(theta);
				}
			}
		}
	}	
	int thetasize=thetastore.size();
	theta=0;
	if(thetasize==0)
	{
		successflag=-1;//表示定位出错
		//cout<<"successflag:"<<successflag<<endl;
	}
	else
	{
		//计算角度
		thetaadd/=thetasize;
		int count=0;
		for(int i=0;i<thetasize;i++)
		{
			if(thetastore[i]<thetaadd+5 && thetastore[i]>thetaadd-5)
			{
				count++;
				theta+=thetastore[i];
			}
		}
		if(count==0)
		{
			successflag=-1;//表示定位出错
			//cout<<"successflag:2"<<successflag<<endl;
		}
		else
		{
			thetaestimate=theta/count;//估计的角度值
			cout<<"thetaestimate is: "<<thetaestimate<<endl;
			successflag=1;
		}
	}
}

void poseEstimate::calculatePoseUsingCameraInAnyMotion(const vector<DMatch> &matches, const vector<KeyPoint> &firstimgkpts, const vector<KeyPoint> &lastimgkpts,
			float &xestimate, float &yestimate, float &thetaestimate, int &successflag)
{
	successflag=0;//默认为0
	int matchsize=matches.size();
	//cout<<"the match size is: "<<matchsize<<endl;
	Point2f worldpointa, worldpointb;
	vector<Point2f> worldpoint;
	worldpoint.clear();
	for(int i=0;i<matchsize;i++)//计算前帧图像特征点在世界坐标下的坐标
	{
		calculateWorldCoordinate(firstimgkpts[matches[i].queryIdx], worldpointa);
		worldpoint.push_back(worldpointa);
	}
	//估计旋转的角度值
	vector<float> thetastore;
	float a=0,b=0,m=0,n=0,theta=0,thetaadd=0;
	for(int i=0;i<matchsize-1;i++)
	{
		worldpointa=worldpoint[i];
		for(int j=i+1;j<matchsize;j++)
		{
			worldpointb=worldpoint[j];
			a=(worldpointb.x-worldpointa.x);
			b=(worldpointb.y-worldpointa.y);
			m=(lastimgkpts[matches[i].trainIdx].pt.x-lastimgkpts[matches[j].trainIdx].pt.x)/k1;
			n=(lastimgkpts[matches[i].trainIdx].pt.y-lastimgkpts[matches[j].trainIdx].pt.y)/k2;
			if(a!=0 || b!=0)
			{
				/*float temp=(a*n-b*m)/(a*a+b*b);
				if(temp>=1.0)
					temp=1;
				else if(temp<=-1.0)
					temp=-1;
				theta=acos(temp)*180.0/CV_PI;//当次估计的角度值,cos(theta)在[-90 +90]内没有正负号*/  
				
				float temp=(a*m+b*n)/(a*a+b*b);
				if(temp>=1.0)
					temp=1;
				else if(temp<=-1.0)
					temp=-1;
				theta=asin(temp)*180.0/CV_PI;//当次估计的角度值
				if(theta<theta1+5 && theta>theta1-5)
				{
					thetaadd+=theta;
					thetastore.push_back(theta);
				}
			}
		}
	}	
	int thetasize=thetastore.size();
	theta=0;
	if(thetasize==0)
		successflag=-1;//表示定位出错
	else
	{
		//计算角度
		thetaadd/=thetasize;
		int count=0;
		for(int i=0;i<thetasize;i++)
		{
			if(thetastore[i]<thetaadd+5 && thetastore[i]>thetaadd-5)
			{
				count++;
				theta+=thetastore[i];
			}
		}
		if(count==0)
			successflag=-1;//表示定位出错
		else
		{
			thetaestimate=theta/count;//估计的角度值
			
				//估计扫地机在世界坐标系下的坐标
			float costheta=cos(thetaestimate*CV_PI/180.0);
			float sintheta=sin(thetaestimate*CV_PI/180.0);
			float xnumber=0,ynumber=0;
			int realnumber=0;
			for(int i=0;i<matchsize;i++)
			{
				//计算在世界坐标系下的平移量x和y
				Point lpt=lastimgkpts[matches[i].trainIdx].pt;
				float m=(lpt.x-u0)/k1+d2;
				float n=(lpt.y-v0)/k2-d1;
				float xtemp=worldpoint[i].x+m*sintheta+n*costheta;
				float ytemp=worldpoint[i].y-m*costheta+n*sintheta;
				//cout<<"xtemp and ytemp are: "<<xtemp<<" "<<ytemp<<endl;
				if(xtemp<x1+10 && xtemp>x1-10 && ytemp<y1+10 && ytemp>y1-10)//移动5cm范围，x方向的偏差不能超过[-5,5]cm,y方向的偏差不能超过[-3,3]cm
				{
					realnumber++;
					xnumber+=xtemp;
					ynumber+=ytemp;
				}
	
			}
			if(realnumber==0)
			{
				successflag=-1;//表示定位出错
				cout<<"successflag: "<<successflag<<endl;
			}
			else
			{
				xestimate=xnumber/realnumber;
				yestimate=ynumber/realnumber;
				//cout<<"number is: "<<realnumber<<endl;
				successflag=1;//表示定位成功
				cout<<"The pose angle is: "<<thetaestimate<<"."<<endl;
				cout<<"The estimated robot site is: "<<xestimate<<" with "<<yestimate<<endl;
			}
				
			
		}
	}
}