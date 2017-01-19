#include "common.h"
#include "canvas.h"
#include "point.h"
#include "Snake.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat Image(Mat::zeros(400, 400, CV_8UC3));

    canvas canvas(300, 300, pair<int, int>(50,50));
    point point(5);
    Snake Snake;

    canvas.initial(Image);
    point.RandomPosition(Image, canvas);
    Snake.SnakeInitial(Image);
    namedWindow("snake");
    char c = waitKey(1);
    while(c != 'q')
    {
        Snake.Move(Image);
        imshow("snake", Image);
        c = waitKey(100);
        switch(c)
        {
            case 'a':
                Snake.SetState("left");
                break;
            case 'w':
                Snake.SetState("up");
                break;
            case 'd':
                Snake.SetState("right");
                break;
            case 's':
                Snake.SetState("down");
                break;
            default:
                break;
        }
        if((abs(Snake.GetPosition().first-point.GetPT().first) < 5) &&
            abs(Snake.GetPosition().second-point.GetPT().second) < 5)
        {
            Snake.SAdd(point);
            point.RandomPosition(Image, canvas);
        }
    }

    return 0;
}
