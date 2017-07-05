#ifndef _ETREE_
#define _ETREE_

#include "common.h"

class ETree
{
public:
    void addNode( cv::Point node) { TreeBody.push_back( node ); }
    //void ShowTree();
    cv::Point findNearstNode( cv::Point );

private:
    std::vector<cv::Point> TreeBody;

};

#endif
