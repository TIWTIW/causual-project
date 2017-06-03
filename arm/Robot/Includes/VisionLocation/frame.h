/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef FRAME_H
#define FRAME_H

#include "common_include.h"
//#include "ORBVocabulary.h"
#include "camera.h"


// forward declare 
//class MapPoint;
class Frame
{
public:
    typedef std::shared_ptr<Frame> Ptr;
    unsigned long                  id_;         // id of this frame
   // double                         time_stamp_; // when it is recorded
  //  SE3                            T_c_w_;      // transform from frame to world
    Point3f                        pose_;
    Camera::Ptr                    camera_;     // Pinhole RGBD Camera model 
    Mat                            img_; // color and depth image 
    // std::vector<cv::KeyPoint>      keypoints_;  // key points in image
    // std::vector<MapPoint*>         map_points_; // associated map points
  //  bool                           is_key_frame_;  // whether a key-frame
    vector<Point>                  fastcorners_;
    vector<KeyPoint>               corners_;
    Mat                            descriptors_;
    //uchar                          descriptors_curr_[32*100];
    //uchar                          descriptors_ref_[32*100];
    //BoW
   // DBoW2::BowVector                mBowVec_; ///< Vector of words to represent images
   // DBoW2::FeatureVector            mFeatVec_; ///< Vector of nodes with indexes of local features
   // ORBVocabulary*                  mpORBvocabulary_;
    // Number of KeyPoints.
    int N; ///< KeyPoints数量
public: // data members 
    Frame();

    //Frame(const Frame &frame);
   // Frame( long id ,Camera::Ptr camera=nullptr, Mat img=Mat(), vector<Point> fastcorners=vector<Point>(), vector<KeyPoint> corners = vector<KeyPoint>(), Mat descriptors = Mat());
    //, ORBVocabulary* voc,vector<Point> fastcorners=vector(), vector<KeyPoint> corners = vector(), uchar descriptors[32*100] = {'\0'}ORBVocabulary* mpVocabulary;mpVocabulary = new ORBVocabulary();
    //Camera::Ptr camera1 (new Camera );
    Frame( long id ,Camera::Ptr camera , Mat img=Mat(), vector<Point> fastcorners=vector<Point>(), vector<KeyPoint> corners = vector<KeyPoint>(), Mat descriptors = Mat());

    Frame( long id , Mat img=Mat(), vector<Point> fastcorners=vector<Point>(), vector<KeyPoint> corners = vector<KeyPoint>(), Mat descriptors = Mat());
    ~Frame();
    static Frame::Ptr createFrame(); 
    
    // find the depth in depth map
    
    
    // Get Camera Center
   // Vector3d getCamCenter() const;
    void setPose( const Point3f& pose);
    std::vector<KeyPoint> GetKeyPointMatches(); 
    // Compute Bag of Words representation.
    // 存放在mBowVec中
    std::vector<cv::Mat> toDescriptorVector(const cv::Mat &Descriptors);
    //void ComputeBoW();

    // check if a point is in this frame 
   // bool isInFrame( const Vector3d& pt_world );
};



#endif // FRAME_H
