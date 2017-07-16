#include "Rectangle.h"
#include <vector>

using namespace std;

template <typename Object, typename Comparator>
const Object &findMax( const vector<Object> &arr, Comparator isLessThan )
{
    int maxIndex = 0;

    for( int i = 1; i < arr.size(); ++i )
        if( isLessThan( arr[maxIndex], arr[i]) )
            maxIndex = i;

    return arr[maxIndex];
}

class area
{
public:
    unsigned operator()( Rectangle L, Rectangle W ) 
    { return (L.getLength() * L.getWidth()) < (W.getWidth() * W.getLength()); }
};


class perimeter
{
public:
    unsigned operator()( Rectangle L, Rectangle W ) 
    { return (L.getLength() + L.getWidth()) < (W.getWidth() + W.getLength()); }
};

int main()
{
    vector<Rectangle> vR{ {5, 5}, {1, 2}, {4, 6} };

    Rectangle a = findMax( vR, area{} );
    Rectangle b = findMax( vR, perimeter{} );

    cout << a.getLength() << " " << a.getWidth() << endl;
    cout << b.getLength() << " " << b.getWidth() << endl;
}
