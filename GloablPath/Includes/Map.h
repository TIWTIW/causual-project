#ifndef _MAP_H
#define _MAP_H

#include "Cell.h"
#include <memory>

class Map
{
public:
    Map() : CellMapPtr( std::make_shared<std::vector<Cell>>() ), MatImagePtr( std::make_shared<cv::Mat>( Map_Size, Map_Size, CV_8UC3, cv::Scalar( 0, 0, 0 ) ) ) {}

public:
    //Random make some obstacles in Image
    void Initial();
    //make cell map corresponding to the Image map
    void MakeCellMap();
    //transfer Cell Map to Mat
    cv::Mat TransferCellToImage();

public:
    //maybe only for test
    cv::Mat getImage() { return *MatImagePtr; }
    std::vector<Cell> getCellImage() { return *CellMapPtr; }

private:
    std::shared_ptr<std::vector<Cell>> CellMapPtr;
    std::shared_ptr<cv::Mat> MatImagePtr;

};

#endif
