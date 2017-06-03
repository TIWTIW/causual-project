#include "function.h"

int main( int argc, char *argv[] )
{
//    socketServer Server;
    
  //  Server.waiting();
    if( createManageThread() == -1 )
    {
        return -1;
    }

    while( true )
    {
        //maybe something here
        sleep( 100 );
    }


    return 0;
}
