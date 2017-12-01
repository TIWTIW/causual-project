#include <iostream>
#include <set>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <queue>

using namespace std;

struct Point
{
    //coordinate
    int x_;
    int y_;

    //color of this point
    uchar color_;

    //if this point has visited
    bool hasVisited_ = false;

    //distance from start point
    int distanceFromStart_;
    //belong to which edge
    int belongEdge_ = 0;

    //constructor
    Point(int x, int y) : x_(x), y_(y), distanceFromStart_(0) {}

    //< for set
    bool operator<(const Point& p) const {return x_ < p.x_ || y_ < p.y_;}
    bool operator==(const Point &p) const {return y_ == p.y_ && x_ == p.x_;}
};

class Edge
{
public:
    void push(const Point& p)
    {
        pointInEdge_.insert(p);
    }
    set<Point> pointInEdge_;
    size_t size() {return pointInEdge_.size();}
};


//Extend the point
void extendPoint(Point &pt_, queue<Point> &npq, vector<vector<Point>> &map, bool &isEdge)
{
    int x = pt_.x_;
    int y = pt_.y_;

    if(map[x - 1][y].color_ == 255 && !(map[x - 1][y].hasVisited_))
        npq.push(map[x - 1][y]);
    if(map[x + 1][y].color_ == 255 && !(map[x + 1][y].hasVisited_))
        npq.push(map[x + 1][y]);
    if(map[x][y - 1].color_ == 255 && !(map[x][y - 1].hasVisited_))
        npq.push(map[x][y - 1]);
    if(map[x][y + 1].color_ == 255 && !(map[x][y + 1].hasVisited_))
        npq.push(map[x][y + 1]);

    map[x - 1][y].hasVisited_ = true;
    map[x + 1][y].hasVisited_ = true;
    map[x][y - 1].hasVisited_ = true;
    map[x][y + 1].hasVisited_ = true;

    if(map[x - 1][y].color_ == 127)
        isEdge = true;
    if(map[x + 1][y].color_ == 127)
        isEdge = true;
    if(map[x][y - 1].color_ == 127)
        isEdge = true;
    if(map[x][y + 1].color_ == 127)
        isEdge = true;
}

void drawMap(cv::Mat& map_)
{
    cv::rectangle(map_, cv::Point(100, 50), cv::Point(540, 430), cv::Scalar(255), -1, 8);
    cv::rectangle(map_, cv::Point(300, 250), cv::Point(450, 300), cv::Scalar(0), -1, 8);
    cv::rectangle(map_, cv::Point(120, 140), cv::Point(200, 250), cv::Scalar(0), -1, 8);

    line(map_, cv::Point(150, 50), cv::Point(400, 50), cv::Scalar(0), 1, 8);
    line(map_, cv::Point(420, 50), cv::Point(500, 50), cv::Scalar(0), 1, 8);

    line(map_, cv::Point(100, 70), cv::Point(100, 200), cv::Scalar(0), 1, 8);

    line(map_, cv::Point(540, 70), cv::Point(540, 230), cv::Scalar(0), 1, 8);

    line(map_, cv::Point(230, 430), cv::Point(400, 430), cv::Scalar(0), 1, 8);
}

//construct point map, in fact it can be seen as grid
void ConstructPointMap(vector<vector<Point>> &pointMap, cv::Mat &map_)
{
    drawMap(map_);
    for(int i = 0; i < map_.rows; ++i)
    {
        //pointMap.resize(map_.cols);
        for(int j = 0; j < map_.cols; ++j)
        {
            Point tempPoint(i, j);
            tempPoint.color_ = map_.ptr<uchar>(i)[j];
            pointMap[i].push_back(tempPoint);
        }
    }

    cv::imshow("map", map_);
    cv::waitKey(0);
}

void clearQueue(queue<Point> &qp_)
{
    queue<Point> empty;
    swap(empty, qp_);
}

//Decide if the point is belong to an edge
bool f_isEdge(Point &pt_, vector<vector<Point>> &map)
{
    int x = pt_.x_;
    int y = pt_.y_;

    if(map[x][y].color_ != 255)
        return false;

    if(map[x - 1][y].color_ == 127)
        return true;
    if(map[x + 1][y].color_ == 127)
        return true;
    if(map[x][y - 1].color_ == 127)
        return true;
    if(map[x][y + 1].color_ == 127)
        return true;

    return false;
}

void extendEdge(Point &pt_, vector<vector<Point>> &pointMap, int edgeNo, Edge &newEdge)
{
    pt_.belongEdge_ = edgeNo;
    newEdge.push(pt_);

    queue<Point> pointQueue;
    pointQueue.push(pt_);

    while(!pointQueue.empty())
    {
        Point currPoint = pointQueue.front();
        int x = currPoint.x_;
        int y = currPoint.y_;

        pointQueue.pop();

        newEdge.push(pointMap[x][y]);
        pointMap[x][y].belongEdge_ = edgeNo;

        if(f_isEdge(pointMap[x - 1][y], pointMap) && pointMap[x - 1][y].belongEdge_ == 0)
        {
            pointQueue.push(pointMap[x - 1][y]);
        }
        if(f_isEdge(pointMap[x + 1][y], pointMap) && pointMap[x + 1][y].belongEdge_ == 0)
        {
            pointQueue.push(pointMap[x + 1][y]);
        }
        if(f_isEdge(pointMap[x][y - 1], pointMap) && pointMap[x][y - 1].belongEdge_ == 0)
        {
            pointQueue.push(pointMap[x][y - 1]);
        }
        if(f_isEdge(pointMap[x][y + 1], pointMap) && pointMap[x][y + 1].belongEdge_ == 0)
        {
            pointQueue.push(pointMap[x][y + 1]);
        }
    }
}

vector<Edge> processMap(cv::Mat &map_, Point &sp_)
{
    //result
    vector<Edge> res;

    vector<vector<Point>> pointMap(map_.rows);

    //construct Point Map of this pic
    ConstructPointMap(pointMap, map_);

    cout << "Construct success!" << endl;

    queue<Point> currentPointQueue, nextPointQueue;
    currentPointQueue.push(sp_);

    int currDis = -1;
    int totalEdgeNo = 0;
    int totalPointNo = 0;

    int i = 0;
    while(true)
    {
        currDis ++;
        //traversal current queue
        while(!currentPointQueue.empty())
        {
            Point currentPoint = currentPointQueue.front();
            currentPointQueue.pop();
            Point &pointInMap = pointMap[currentPoint.x_][currentPoint.y_];

            pointInMap.distanceFromStart_ = currDis;
            //pointMap[currentPoint.x_][currentPoint.y_].hasVisited_ = true;

            //if there are points next to this point which are white
            //just extend them
            //find if there are grey points next to this one
            //if there is, then this point should belong to an edge
            bool isEdge = false;
            extendPoint(pointInMap, nextPointQueue, pointMap, isEdge);

            //if it's edge and it's edgeNp has not been set
            //then add one edge and expand that point to find
            //the points belong to this edge
            if(isEdge && (pointInMap.belongEdge_ == 0))
            {
                totalEdgeNo++;
                Edge edge_temp;
                extendEdge(pointInMap, pointMap, totalEdgeNo, edge_temp);
                res.push_back(edge_temp);
            }
        }
        totalPointNo += nextPointQueue.size();

        currentPointQueue = nextPointQueue;
        clearQueue(nextPointQueue);
        if(currentPointQueue.empty() )
            break;
    }

    cout << "Total Map Point No: " << pointMap.size() * pointMap[0].size() << endl;
    cout << "Total Travel Point No: " << totalPointNo << endl;
    cout << "Total Edge No: " << totalEdgeNo << endl;
    cout << "ProcessMap End!" << endl;


    //Draw distance map, just for debug
    cv::Mat distanceMap(480, 640, 0);
    for(int i = 0; i < pointMap.size(); ++i)
    {
        for(int j = 0; j < pointMap[i].size(); ++j)
        {
            distanceMap.ptr<uchar>(i)[j] = pointMap[i][j].distanceFromStart_ > 255 ? 255 : pointMap[i][j].distanceFromStart_;
        }
    }

    cv::imshow("disMap", distanceMap);
    cv::waitKey(0);
    return res;
}

int main()
{
    //define a map
    cv::Mat map(480, 640, 0, 127);
    vector<Edge> result;

    Point startPoint(map.rows / 2, map.cols / 2);
    result = processMap(map, startPoint);

    //Edge Map to show the edges which were found
    cv::Mat EdgeMap(480, 640, 0, cv::Scalar(0));
    int i = 0;
    for(auto &e : result)
    {
        ++i;
        cout << "Edge " << i << "'s Size: " << e.size() << endl;
        for(auto it = e.pointInEdge_.begin(); it != e.pointInEdge_.end(); ++it)
        {
            //cout << "Point: " << it->x_ << " " << it->y_ << endl;
            EdgeMap.ptr<uchar>(it->x_)[it->y_] = i * 40;
        }
    }

    cv::imshow("EdgeMap", EdgeMap);
    cv::waitKey(0);

}
