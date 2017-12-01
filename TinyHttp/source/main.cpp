#include "server.h"
#include "common_include.h"

using namespace std;

int main()
{
    myHttp::httpServer myHttpServer;

    myHttpServer.setPort( 5000 );
    string ip = "127.0.0.1";
    myHttpServer.setIp( ip );

    myHttpServer.start();
}
