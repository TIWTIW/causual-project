#ifndef WIN
#define WIN

#include "Screen.h"
#include <vector>

class Window_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear( ScreenIndex );

private:
    std::vector<Screen> screens{ Screen( 24, 80, ' ' ) };
};


void Window_mgr::clear( ScreenIndex i )
{
    Screen &s = screens[i];

    s.contents = std::string( s.height * s.width, ' ' );
}

#endif
