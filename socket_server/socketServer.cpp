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
    rc = pthread_create( &thread, NULL, readMsg, this );
    if( rc )
    {
        printf( "error create thread" );
        exit( -1 );
    }
    return ;
}

void* socketServer::readMsg( void *arg )
{
    socketServer *s = (socketServer *) arg;
    int n;
    while( 1 )
    {
        n = recv( s->connfd, s->recBuf, MAXLINE, 0 );
    /*if( n == 0 )
    {
        printf( "disconected!\n" );
        close( s->connfd );
        s->connfd = 0;
    }*/

        s->recBuf[n] = '\0';

    //    printf( "%s\n", s->recBuf );
        for( int i = 0; i < n; ++i )
        {
        //if( s->recBuf[i] == ' ' )
           // printf( "recv msg from client: %s\n", s->recBuf );
            if( s->recBuf[i] == 'h' )
            {
                s->flag_head = 1;
                printf( "head\n" );
            }
            else if( s->recBuf[i] == 'n')
            { 
                s->flag_next = 1;
                printf( "next\n" );
            }
        }

        if( s->recBuf[0] == 'f' )
            printf( "f\n" );

    }
}

void socketServer::writeMsg()
{
    int len = 0;
    FILE *fd = fopen( "map.jpg", "rb" );

    //pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    if( fd == NULL )
    {
        printf( "file open error!\n" );
        exit( 1 );
    }

    struct stat buf;

    if( stat( "map.jpg", &buf ) < 0 )
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



    while( 1 )
    {
        if( flag_head == 1 )   //等待服务器传回消息
           break;
    }

    flag_head = 0;
   
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

    while( 1 )
    {
       if( flag_next == 1 )
            break;
    }

    flag_next = 0;

    fclose( fd );
}

void socketServer::show()
{
    struct hostent *hent;
    char hname[128];

}


