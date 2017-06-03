#ifndef CAMERA_H
#define CAMERA_H

#include "common_include.h"



// Pinhole RGBD camera model
class Camera
{
public:
    typedef std::shared_ptr<Camera> Ptr;
    float   fu_, fv_, u0_, v0_,H_,d1_,d2_;

    Camera();
   

    Camera ( float fu, float fv, float u0, float v0  ,float H, float d1, float d2 ) :
        fu_ ( fu ), fv_ ( fv ), u0_ ( u0 ), v0_ ( v0 ), H_( H ), d1_( d1 ), d2_( d2 )
    {}
    // coordinate transform: world, camera, pixel
   /* Vector3d world2camera( const Vector3d& p_w, const SE3& T_c_w );
    Vector3d camera2world( const Vector3d& p_c, const SE3& T_c_w );
    Vector2d camera2pixel( const Vector3d& p_c );
    Vector3d pixel2camera( const Vector2d& p_p, double depth=1 ); 
    Vector3d pixel2world ( const Vector2d& p_p, const SE3& T_c_w, double depth=1 );
    Vector2d world2pixel ( const Vector3d& p_w, const SE3& T_c_w );*/

};


#endif // CAMERA_H