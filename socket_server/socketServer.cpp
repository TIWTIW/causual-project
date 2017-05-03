#include "socketServer.h"
#include "keyboard.h"

socketServer::socketServer( int port )
{
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl (INADDR_ANY );
    servaddr.sin_port = htons( port );

    if( ( listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
        printf( "create socket error: %s(errno: %d)\n", strerror(errno), errno );
        exit( 0 );
    }

    if( bind( listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) == -1 )
    {
        printf( "bind socket error: %s(errno: %d)\n", strerror(errno), errno );
        exit( 0 );
    }

    if( listen( listenfd, 10 ) == -1 )
    {
        printf( "listen socket error: %s(errno: %d)\n", strerror(errno), errno );
        exit(0);
    }

    printf( "socket construct success!\n" );
}

void socketServer::waiting()
{
    connfd = 0;
    printf( "======waiting for client's request======\n" );
    while( 1 )
    {
        if( connfd == 0 )
        {
            if( ( connfd = accept( listenfd,  (struct sockaddr*)NULL, NULL) ) == -1 )
            {   
                printf( "accept socket error\n" );
     //           continue;
            }
        }
        readThread();
        writeMsg();
       // readMsg();
     //  close( connfd );
   // close( listenfd );
    }
}

void socketServer::readThread()
{
    pthread_t thread;
    int rc;
    rc = pthread_create( &thread, NULL, (void *)readMsg, NULL );
    if( rc )
    {
        printf( "error create thread" );
        exit( -1 );
    }
    return ;
}

void socketServer::readMsg(void *)
{
    int n;
    n = recv( connfd, recBuf, MAXLINE, 0 );
    if( n == 0 )
    {
        printf( "disconected!\n" );
        close( connfd );
        connfd = 0;
        return ;
    }

    recBuf[n] = '\0';
    printf( "recv msg from client: %s\n", recBuf );
}

void socketServer::writeMsg()
{
    int len = 0;
    FILE *fd = fopen( "map.jpg", "rb" );

    if ( fd == NULL )
    {
        printf( "file open error!\n" );
        exit( 1 );
    }

    struct stat buf;

    if(stat("map.jpg", &buf)<0)
    {
        return ;
    }
    printf( "%lu\n", (unsigned long)buf.st_size );           //获取图片大小 

    long file_size = buf.st_size;
    char transfer_size[10];
    int i = 0;

    while( file_size != 0 )
    {
        transfer_size[i++] = file_size - file_size / 10 * 10 + 48;
        file_size /= 10;
    }

    transfer_size[i] = '\0';

    for( int x = 0; x <= (i - 1) / 2; ++x )
    {
        int temp = transfer_size[x];
        transfer_size[x] = transfer_size[i - 1 - x];
        transfer_size[i - x - 1] = temp;
    }

    printf( "b=%s\n", transfer_size );        

    int a = send( connfd, transfer_size, sizeof( transfer_size ), 0 );   //传送数据大小
    if( a  < 0 )
        printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  


    readMsg();   

    while( 1 )
    {
        if( recBuf[0] == 'O' )   //等待服务器传回消息
           break;
    }
   
    char sendBuf[MAXLINE];
    while(!feof(fd))
    {
        len = fread( sendBuf, 1, MAXLINE, fd );

        if( len <= 0 )
            break;
        else if( ( send( connfd, sendBuf, sizeof( sendBuf ) , 0 ) ) < 0)  
        {  
            printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  
            exit(0);  
        }
        else
            printf( "write success!\n");
    }

    readMsg();
    while( recBuf[0] != 'N' )     //等待服务器传回下一次传送消息
        ;
    fclose( fd );
}

void socketServer::show()
{
    struct hostent *hent;
    char hname[128];

}


