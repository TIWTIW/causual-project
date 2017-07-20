#include "queue_vector.h"

using namespace std;

int main()
{
    Vec_Queue<int> vq;

    vq.enqueue( 1 );
    vq.enqueue( 2 );
    vq.print();
    cout << vq.dequeue() << endl;

}
