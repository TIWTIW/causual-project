#include "frame.h"



Frame::Frame()
: id_(-1)  
{

}

/*Frame::Frame(const Frame &frame)
	:camera_(frame.camera_),  fastcorners_(frame.fastcorners_), corners_(frame.corners_), descriptors_(frame.descriptors_) ,
	 mpORBvocabulary_(frame.mpORBvocabulary_), mBowVec_(frame.mBowVec_), mFeatVec_(frame.mFeatVec_)
{

}*/

Frame::Frame ( long id, Camera::Ptr camera, Mat img, vector<Point> fastcorners, vector<KeyPoint> corners, Mat descriptors  )
: id_(id), camera_(camera), img_(img), fastcorners_(fastcorners), corners_(corners), descriptors_(descriptors)
{
    N = corners_.size();
    if(corners_.empty())
        return;
}
/*Frame::Frame ( long id, Camera::Ptr camera, Mat img, vector<Point> fastcorners, vector<KeyPoint> corners, Mat descriptors ,ORBVocabulary* voc, FeatureVector mFeatVec, BowVector mBowVec )
: id_(id), camera_(camera), img_(img), fastcorners_(fastcorners), corners_(corners), descriptors_(descriptors),mpORBvocabulary_(voc), mFeatVec_(mFeatVec) ,mBowVec_(mBowVec)
{
    N = corners_.size();
    if(corners_.empty())
        return;
}*/
Frame::Frame ( long id,  Mat img, vector<Point> fastcorners, vector<KeyPoint> corners, Mat descriptors  )
: id_(id),  img_(img), fastcorners_(fastcorners), corners_(corners), descriptors_(descriptors)
{
    N = corners_.size();
    if(corners_.empty())
        return;
}
//ORBVocabulary* voc,mpORBvocabulary_(voc), 
Frame::~Frame()
{

}

Frame::Ptr Frame::createFrame()
{
    static long factory_id = 0;
    return Frame::Ptr( new Frame(factory_id++) );
}



void Frame::setPose ( const Point3f& pose )
{
    pose_ = pose;
}
std::vector<KeyPoint> Frame::GetKeyPointMatches()
{
    return corners_;
} 

std::vector<cv::Mat> Frame::toDescriptorVector(const cv::Mat &Descriptors)
{
    std::vector<cv::Mat> vDesc;
    vDesc.reserve(Descriptors.rows);
    for (int j=0;j<Descriptors.rows;j++)
        vDesc.push_back(Descriptors.row(j));

    return vDesc;
}

/*void Frame::ComputeBoW()
{
    if(mBowVec_.empty() || mFeatVec_.empty())
    {
        vector<cv::Mat> vCurrentDesc = toDescriptorVector(descriptors_);
        // Feature vector associate features with nodes in the 4th level (from leaves up)
        // We assume the vocabulary tree has 6 levels, change the 4 otherwise
        mpORBvocabulary_->transform(vCurrentDesc,mBowVec_,mFeatVec_,4);
    }
}*/
