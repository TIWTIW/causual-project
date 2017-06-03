#include "cornermatching.h"
const int imgwidth=640;
const int imgheight=480;
 
struct trainIdxUp
{
    bool operator()(const DMatch a, const DMatch b) const { return a.trainIdx < b.trainIdx; }
};
struct trainHammingDistUp
{
    bool operator()(const DMatch a, const DMatch b) const { return a.distance < b.distance; }
};

//两uchar类型数异或结果中1的数目
const uchar popCountTable[] =
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

/*****************************************************构造函数*****************************************************/
cornerMatching::cornerMatching(float &x0, float &y0, float &theta0, float &x1, float &y1, float &theta1, 
			float &fu, float &fv, float &u0, float &v0, float &H, float &d1, float &d2)
{
	this->x0=x0; this->y0=y0; this->theta0=theta0;
	this->x1=x1; this->y1=y1; this->theta1=theta1;
	this->fu=fu; this->fv=fv; this->u0=u0; this->v0=v0;
	this->H=H;   this->d1=d1; this->d2=d2;
}
cornerMatching::cornerMatching(float nnratio, bool checkOri): mfNNratio(nnratio), mbCheckOrientation(checkOri)
{

}
/*****************************************************私有函数*****************************************************/
//计算前帧图像某特征点在世界坐标系下的坐标
void cornerMatching::calculateWorldCoordinate(const Point2f &cornerpoint, Point2f &worldpoint)
{
	float M=(cornerpoint.x-u0)*H/fu+d2;
	float N=(cornerpoint.y-v0)*H/fv-d1;
	//图像中一点可求解出对应的一条射线，由于天花板高度已知，则该点对应天花板上的坐标是可求的
	worldpoint.x=x0-M*sin(theta0*CV_PI/180.0)-N*cos(theta0*CV_PI/180.0);
	worldpoint.y=y0+M*cos(theta0*CV_PI/180.0)-N*sin(theta0*CV_PI/180.0);
	//cout<<"The real world coordinate is: "<<worldpoint.x<<" with "<<worldpoint.y<<endl;
}
//计算前帧图像某特征点在世界坐标系下的坐标
void cornerMatching::calculateWorldCoordinate(const KeyPoint &cornerpoint, Point2f &worldpoint)
{
	float M=(cornerpoint.pt.x-u0)*H/fu+d2;
	float N=(cornerpoint.pt.y-v0)*H/fv-d1;
	//图像中一点可求解出对应的一条射线，由于天花板高度已知，则该点对应天花板上的坐标是可求的
	worldpoint.x=x0-M*sin(theta0*CV_PI/180.0)-N*cos(theta0*CV_PI/180.0);
	worldpoint.y=y0+M*cos(theta0*CV_PI/180.0)-N*sin(theta0*CV_PI/180.0);
	//cout<<"The real world coordinate is: "<<worldpoint.x<<" with "<<worldpoint.y<<endl;
}
//计算三维空间特征点在训练图像上的坐标
void cornerMatching::sensorDeterminePointInNextFrame(const Point2f &worldpoint, Point &estimatepoint)
{
	estimatepoint.x=u0+fu/H*(-(worldpoint.x-x1)*sin(theta1*CV_PI/180.0)+(worldpoint.y-y1)*cos(theta1*CV_PI/180.0)-d2);
	estimatepoint.y=v0+fv/H*(-(worldpoint.x-x1)*cos(theta1*CV_PI/180.0)-(worldpoint.y-y1)*sin(theta1*CV_PI/180.0)+d1);
	//cout<<"The image coordinate in next frame is: "<<estimatepoint.x<<" with "<<estimatepoint.y<<endl;
}
//确定与某个查找描述符具有最小汉明距离的后帧图像角点描述符索引号
void cornerMatching::findMinHammingDist(const uchar* src1, const uchar* src2, int flag, int &target, int &hammingdist)
{
	const uchar* a=src1;
	int step=32;
	for(int i=0; i<flag; i++)//nves为训练描述符的数目
	{
		int dist=0;
		const uchar* b=src2+step*i;
		for(int j=0; j<=step-4; j+=4)//每次比较4个字节，共比较8次，统计结果为1的数目作为距离;step==32
			dist+=(popCountTable[a[j]^b[j]]+popCountTable[a[j+1]^b[j+1]]+popCountTable[a[j+2]^b[j+2]]+popCountTable[a[j+3]^b[j+3]]);
		if(dist<hammingdist)
		{
			hammingdist=dist;//最小汉明距离
			target=i;//具有最小汉明距离的训练描述符索引号
		}
	}
}
// We perform the matching over ORB that belong to the same vocabulary node (at a certain level)
// 将属于同一节点(特定层)的ORB特征进行匹配
// FeatureVector的数据结构类似于：{(node1,feature_vector1) (node2,feature_vector2)...}
// f1it->first对应node编号，f1it->second对应属于该node的所有特特征点编号

/*****************************************************公有函数*****************************************************/
void cornerMatching::pointsTracking(const vector<Point2f>& firstimgkpts, 
				const vector<Point2f>& lastimgkpts,vector<Point2f>& firstimgkptstrack,vector<Point2f>& lastimgkptstrack)
{
	vector<int> lastimgindex;
	Point2f worldpoint;//前帧图像特征点的世界坐标
	//Point3f worldpointz;
	Point estimatepoint;//前帧图像特征点在后帧图像中的估计坐标
	int firstnumber=firstimgkpts.size();//前帧图像角点数目
	int lastnumber=lastimgkpts.size();//后帧图像角点数目
	
	for(int i=0; i<firstnumber; i++)
	{
		calculateWorldCoordinate(firstimgkpts[i], worldpoint);
		sensorDeterminePointInNextFrame(worldpoint, estimatepoint);
		//筛选条件1：对应点应该位于图像区域内
		int xestimate=estimatepoint.x;
		int yestimate=estimatepoint.y;
		if((xestimate>=0) && (xestimate<imgwidth-10) && (yestimate>=0) && (yestimate<imgheight-10))
		{
			int flag=0;//统计位于查找点附近的后帧图像角点数
			for(int j=0; j<lastnumber; j++)
			{
				int xlastimgcoord=lastimgkpts[j].x;
				int ylastimgcoord=lastimgkpts[j].y;
				//后帧图像存在位于查找点附近的角点
				int DISTANCE=15;
				while(lastimgindex.size()<=20)
				{
					
					if((xlastimgcoord >= xestimate-DISTANCE) && (xlastimgcoord <= xestimate+DISTANCE) && 
						(ylastimgcoord >= yestimate-DISTANCE) && (ylastimgcoord <= yestimate+DISTANCE))
					{
						flag++;
						lastimgindex.push_back(j);
						lastimgkptstrack.push_back(lastimgkpts[j]);
						firstimgkptstrack.push_back(firstimgkpts[j]);
					}
					DISTANCE +=10;
				}
			}
			if(flag<=1)
			{
				cout<<"no matching point"<<endl;
				continue;

			}
		}
	}
}
//利用传感器信息粗略确定匹配的点对,用ORB特征精确匹配
void cornerMatching::pointsMatchingAlgorithm(const vector<KeyPoint>& firstimgkpts, 
				const vector<KeyPoint>& lastimgkpts, Mat& firstdescriptors, Mat& lastdescriptors, vector<DMatch>& matches)
{
	int DISTANCE=15;
	vector<int> lastimgindex;
	Point2f worldpoint;//前帧图像特征点的世界坐标
	//Point3f worldpointz;
	Point estimatepoint;//前帧图像特征点在后帧图像中的估计坐标
	int firstnumber=firstimgkpts.size();//前帧图像角点数目
	int lastnumber=lastimgkpts.size();//后帧图像角点数目
	int dsize=32;//每个描述符的字节数
	uchar nowdescriptors[dsize];//存储前帧图像某角点的描述符
	for(int i=0; i<firstnumber; i++)
	{
		calculateWorldCoordinate(firstimgkpts[i], worldpoint);
		sensorDeterminePointInNextFrame(worldpoint, estimatepoint);
		//筛选条件1：对应点应该位于图像区域内
		int xestimate=estimatepoint.x;
		int yestimate=estimatepoint.y;
		if((xestimate>=0) && (xestimate<imgwidth) && (yestimate>=0) && (yestimate<imgheight))
		{
			int flag=0;//统计位于查找点附近的后帧图像角点数
			for(int j=0; j<lastnumber; j++)
			{
				int xlastimgcoord=lastimgkpts[j].pt.x;
				int ylastimgcoord=lastimgkpts[j].pt.y;
				//后帧图像存在位于查找点附近的角点
				if((xlastimgcoord >= xestimate-DISTANCE) && (xlastimgcoord <= xestimate+DISTANCE) && 
					(ylastimgcoord >= yestimate-DISTANCE) && (ylastimgcoord <= yestimate+DISTANCE))
				{
					flag++;
					lastimgindex.push_back(j);
					
				}
			}
			if(flag>=1)
			{
				int target=0;
				int hammingdist=256;
				uchar lastimgkptdescriptors[dsize*flag];//存储后帧图像某角点的描述符
				//描述符复制
				for(int m=0;m<dsize;m++)
					nowdescriptors[m]=firstdescriptors.ptr((int)i)[m];
				for(int n=0;n<flag;n++)
				{
					for(int k=0;k<dsize;k++)
						lastimgkptdescriptors[n*dsize+k]=lastdescriptors.ptr((int)n)[k];
				}
				findMinHammingDist(nowdescriptors, lastimgkptdescriptors, flag, target, hammingdist);
				if(hammingdist<100)//认定汉明距离小于100，才算匹配成功
				{
					matches.push_back(DMatch(i, lastimgindex[target], 0, hammingdist));//依次存放：前帧图像角点描述符索引、后帧图像角点描述符索引、后帧图像索引、两描述符距离
				}
				lastimgindex.clear();
			}
		}
	}
}
//按照汉明距离降序排序匹配点对，并去除一对多的匹配对
void cornerMatching::eliminateErrorMatching(vector<DMatch>& matches, vector<DMatch>& goodmatches)
{
	int matchnumber=matches.size();//匹配点对数目
	switch(matchnumber)
	{
		case 0: 
		case 1:
			cout<<"Can not find enough matching point pairs!"<<endl;
			break;
		case 2:
			if(matches[0].trainIdx == matches[1].trainIdx)
				cout<<"Can not find enough matching point pairs!"<<endl;
			else
			{
				goodmatches=matches;//保存最佳的两个匹配对
			}			
			break;
		default:
			sort(matches.begin(),matches.end(), trainIdxUp());//匹配对按照后帧图像特征点索引升序排列
			for(int i=0;i<matchnumber-1;i++)
			{
				DMatch outcirc=matches[i];
				for(int j=i+1; j<matchnumber; j++)
				{
					DMatch incirc=matches[j];
					if(outcirc.trainIdx==incirc.trainIdx)
					{
						if(outcirc.distance > incirc.distance)
							outcirc=incirc;
					}
					else
					{
						i=j-1;
						break;
					}
				}
				goodmatches.push_back(outcirc);
			}
			sort(goodmatches.begin(),goodmatches.end(), trainHammingDistUp());//匹配对按照汉明距离升序排列
			break;	
	}
}
// 使用单应性估计的RANSAC剔除错误匹配
void cornerMatching::ransacWithHomography(const vector<DMatch> &goodmatches, const vector<KeyPoint> &firstimgkpts, 
			const vector<KeyPoint> &lastimgkpts, vector<DMatch> &ransacmatches)
{
	vector<Point2f> firstcorners, lastcorners;
	for(vector<DMatch>::const_iterator it=goodmatches.begin(); it!=goodmatches.end(); ++it)
	{
		//得到左边特征点的坐标
		float x=firstimgkpts[it->queryIdx].pt.x;
		float y=firstimgkpts[it->queryIdx].pt.y;
		firstcorners.push_back(Point2f(x,y));
		//得到右边特征点的坐标
		x=lastimgkpts[it->trainIdx].pt.x;
		y=lastimgkpts[it->trainIdx].pt.y;
		lastcorners.push_back(Point2f(x,y));
	}
	// 查找前后帧的单应性
	vector<uchar> inliers(firstcorners.size(),0);
	Mat homography= findHomography(
		Mat(firstcorners),Mat(lastcorners), // 匹配点对
		inliers,	// 输出是否为内外点，1为内点；0为外点
		CV_RANSAC,	// RANSAC 方法
		1.);	    // 认定外点的最大距离超过1
	//提取通过的匹配
	vector<uchar>::iterator itIn=inliers.begin();
	vector<DMatch>::const_iterator itM=goodmatches.begin();
	for(;itIn!=inliers.end();++itIn,++itM)
	{
		if(*itIn)
			ransacmatches.push_back(*itM);
	}
}


/**
 * @brief 通过词包，对关键帧的特征点进行跟踪
 * 
 * 通过bow对pKF和F中的特征点进行快速匹配（不属于同一node的特征点直接跳过匹配） \n
 * 对属于同一node的特征点通过描述子距离进行匹配 \n
 * 根据匹配，用pKF中特征点对应的MapPoint更新F中特征点对应的MapPoints \n
 * 每个特征点都对应一个MapPoint，因此pKF中每个特征点的MapPoint也就是F中对应点的MapPoint \n
 * 通过距离阈值、比例阈值和角度投票进行剔除误匹配
 * @param  pKF               KeyFrame
 * @param  F                 Current Frame
 * @param  vpMapPointMatches F中MapPoints对应的匹配，NULL表示未匹配
 * @return                   成功匹配的数量
 */
/*int cornerMatching::SearchByBoW(Frame* pKF,Frame &F, vector<KeyPoint> &vpMapPointMatches)
{
    const vector<KeyPoint*> vpMapPointsKF = pKF->GetKeyPointMatches();

    vpMapPointMatches = vector<KeyPoint*>(F.N,static_cast<KeyPoint*>(NULL));

    const DBoW2::FeatureVector &vFeatVecKF = pKF->mFeatVec;

    int nmatches=0;
    //bool mbCheckOrientation = true;
    vector<int> rotHist[HISTO_LENGTH];
    for(int i=0;i<HISTO_LENGTH;i++)
        rotHist[i].reserve(500);//预分配内存http://www.cnblogs.com/biyeymyhjob/archive/2013/05/11/3072893.html
    const float factor = 1.0f/HISTO_LENGTH;

    // We perform the matching over ORB that belong to the same vocabulary node (at a certain level)
    // 将属于同一节点(特定层)的ORB特征进行匹配
    DBoW2::FeatureVector::const_iterator KFit = vFeatVecKF.begin();
    DBoW2::FeatureVector::const_iterator Fit = F.mFeatVec.begin();
    DBoW2::FeatureVector::const_iterator KFend = vFeatVecKF.end();
    DBoW2::FeatureVector::const_iterator Fend = F.mFeatVec.end();

    while(KFit != KFend && Fit != Fend)
    {
        if(KFit->first == Fit->first) //步骤1：分别取出属于同一node的ORB特征点(只有属于同一node，才有可能是匹配点)
        {
            const vector<unsigned int> vIndicesKF = KFit->second;
            const vector<unsigned int> vIndicesF = Fit->second;

            // 步骤2：遍历KF中属于该node的特征点
            for(size_t iKF=0; iKF<vIndicesKF.size(); iKF++)
            {
                const unsigned int realIdxKF = vIndicesKF[iKF];

                KeyPoint* pMP = vpMapPointsKF[realIdxKF]; // 取出KF中该特征对应的MapPoint

                //if(!pMP)
                //    continue;

                //if(pMP->isBad())
                //    continue;

                const cv::Mat &dKF= pKF->descriptors_.row(realIdxKF); // 取出KF中该特征对应的描述子

                int bestDist1=256; // 最好的距离（最小距离）
                int bestIdxF =-1 ;
                int bestDist2=256; // 倒数第二好距离（倒数第二小距离）

                // 步骤3：遍历F中属于该node的特征点，找到了最佳匹配点
                for(size_t iF=0; iF<vIndicesF.size(); iF++)
                {
                    const unsigned int realIdxF = vIndicesF[iF];

                    if(vpMapPointMatches[realIdxF])// 表明这个点已经被匹配过了，不再匹配，加快速度
                        continue;

                    const cv::Mat &dF = F.descriptors_.row(realIdxF); // 取出F中该特征对应的描述子

                    const int dist =  DescriptorDistance(dKF,dF); // 求描述子的距离

                    if(dist<bestDist1)// dist < bestDist1 < bestDist2，更新bestDist1 bestDist2
                    {
                        bestDist2=bestDist1;
                        bestDist1=dist;
                        bestIdxF=realIdxF;
                    }
                    else if(dist<bestDist2)// bestDist1 < dist < bestDist2，更新bestDist2
                    {
                        bestDist2=dist;
                    }
                }

                // 步骤4：根据阈值 和 角度投票剔除误匹配
                if(bestDist1<=TH_LOW) // 匹配距离（误差）小于阈值
                {
                    // trick!
                    // 最佳匹配比次佳匹配明显要好，那么最佳匹配才真正靠谱
                    if(static_cast<float>(bestDist1)<mfNNratio*static_cast<float>(bestDist2))
                    {
                        // 步骤5：更新特征点的MapPoint
                        vpMapPointMatches[bestIdxF]=pMP;

                        const cv::KeyPoint &kp = pKF->corners_[realIdxKF];

                        if(mbCheckOrientation)
                        {
                            // trick!
                            // angle：每个特征点在提取描述子时的旋转主方向角度，如果图像旋转了，这个角度将发生改变
                            // 所有的特征点的角度变化应该是一致的，通过直方图统计得到最准确的角度变化值
                            float rot = kp.angle-F.corners_[bestIdxF].angle;// 该特征点的角度变化值
                            if(rot<0.0)
                                rot+=360.0f;
                            int bin = round(rot*factor);// 将rot分配到bin组//round(x)返回x的四舍五入整数值。
                            if(bin==HISTO_LENGTH)
                                bin=0;
                            assert(bin>=0 && bin<HISTO_LENGTH);
                            rotHist[bin].push_back(bestIdxF);
                        }
                        nmatches++;
                    }
                }

            }

            KFit++;
            Fit++;
        }
        else if(KFit->first < Fit->first)
        {
            KFit = vFeatVecKF.lower_bound(Fit->first);
        }
        else
        {
            Fit = F.mFeatVec.lower_bound(KFit->first);
        }
    }

    // 根据方向剔除误匹配的点
    if(mbCheckOrientation)
    {
        int ind1=-1;
        int ind2=-1;
        int ind3=-1;

        // 计算rotHist中最大的三个的index
        ComputeThreeMaxima(rotHist,HISTO_LENGTH,ind1,ind2,ind3);

        for(int i=0; i<HISTO_LENGTH; i++)
        {
            // 如果特征点的旋转角度变化量属于这三个组，则保留
            if(i==ind1 || i==ind2 || i==ind3)
                continue;

            // 将除了ind1 ind2 ind3以外的匹配点去掉
            for(size_t j=0, jend=rotHist[i].size(); j<jend; j++)
            {
                vpMapPointMatches[rotHist[i][j]]=static_cast<KeyPoint*>(NULL);
                nmatches--;
            }
        }
    }

    return nmatches;
}*/

// 取出直方图中值最大的三个index
void cornerMatching::ComputeThreeMaxima(vector<int>* histo, const int L, int &ind1, int &ind2, int &ind3)
{
    int max1=0;
    int max2=0;
    int max3=0;

    for(int i=0; i<L; i++)
    {
        const int s = histo[i].size();
        if(s>max1)
        {
            max3=max2;
            max2=max1;
            max1=s;
            ind3=ind2;
            ind2=ind1;
            ind1=i;
        }
        else if(s>max2)
        {
            max3=max2;
            max2=s;
            ind3=ind2;
            ind2=i;
        }
        else if(s>max3)
        {
            max3=s;
            ind3=i;
        }
    }

    if(max2<0.1f*(float)max1)
    {
        ind2=-1;
        ind3=-1;
    }
    else if(max3<0.1f*(float)max1)
    {
        ind3=-1;
    }
}


// Bit set count operation from
// http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
int cornerMatching::DescriptorDistance(const cv::Mat &a, const cv::Mat &b)
{
    const int *pa = a.ptr<int32_t>();
    const int *pb = b.ptr<int32_t>();

    int dist=0;

    for(int i=0; i<8; i++, pa++, pb++)
    {
        unsigned  int v = *pa ^ *pb;
        v = v - ((v >> 1) & 0x55555555);
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
        dist += (((v + (v >> 4)) & 0xF0F0F0F) * 0x1010101) >> 24;
    }

    return dist;//~~http://hymike.net/blog/?p=492
}