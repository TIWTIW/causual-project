#include <memory>

using namespace std;

int main()
{
    unique_ptr<int> u( new int(42) );

    unique_ptr<int> x = u;
}
