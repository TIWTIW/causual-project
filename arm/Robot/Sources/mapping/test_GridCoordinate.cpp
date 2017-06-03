#include "mapping.h"

int main(int argc, char const *argv[])
{
	pose_t currPose;
	currPose.x = 65;
	currPose.y = 0;
	currPose.theta = -0.25;

	Point tmpL1 = GridLocaltoMapIndex( Point(-2, 6), currPose, 40 );
	cout << tmpL1 << endl;
	Point tmpL2 = GridLocaltoMapIndex( Point(2, -6), currPose, 40 );
	cout << tmpL2 << endl;
}