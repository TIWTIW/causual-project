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

    //create key thread, while key 1 is pressed, the program exit
   // keyThread();

    while( 1 )
    {
       // if( connfd == 0 )
        {
            if( ( connfd = accept( listenfd,  (struct sockaddr*)NULL, NULL) ) == -1 )
            {   
                printf( "accept socket error\n" );
                continue;
            }
            else
                printf( "connect success!\n" );
        }
<<<<<<< HEAD
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
=======

        exit_con_flag = 0;

        //if connect success, create read thread to read msg from cilent
        readThread();

        //while connection isn't finished, continue to send map data
        while( !exit_con_flag )
            writeMsg();
    }
}


/***********create Key thread**************/
void socketServer::keyThread()
>>>>>>> 5a6a30745328926979d1316081e200be357e3a08
{
    pthread_t thread;
    int rc;
    rc = pthread_create( &thread, NULL, keyExit, this );
    if( rc )
    {
        printf( "error create exit thread\n" );
        exit( -1 );
    }
    else
        printf( "create keyThread success!\n" );

    return ;
}

void socketServer::readThread()
{
    pthread_t thread;
    int rc;
    rc = pthread_create( &thread, NULL, readMsg, this );
    if( rc )
    {
        printf( "error create read thread\n" );
        exit( -1 );
    }
    else
        printf( "create readThread success!\n" );

<<<<<<< HEAD
    if ( fd == NULL )
    {
        printf( "file open error!\n" );
        exit( 1 );
    }

    struct stat buf;
=======
    return ;
}

void* socketServer::keyExit( void *arg )
{
    socketServer *s = (socketServer *) arg;
    int buttons_fd;
    char buttons[6] = {'0', '0', '0', '0', '0', '0'};
>>>>>>> 5a6a30745328926979d1316081e200be357e3a08

    buttons_fd = open( "/dev/buttons", 0 );
    if( buttons_fd < 0 )
    {
        perror( "open device buttons" );
        exit( 1 ); 
    }

    while( 1 )
    {
        char current_buttons[6];
        if( read( buttons_fd, current_buttons, sizeof( current_buttons ) ) != sizeof( buttons ) )
        {
            perror( "read buttons" );
            exit( 1 );
        }
        
        //while key 1 is pressed
        if( buttons[0] == '1' && current_buttons[0] == '0' )
        {
            printf( "exit!\n" );
            close( s->connfd );
            close( s->listenfd );
            exit( 0 );
        }
        buttons[0] = current_buttons[0];
    }
}

void* socketServer::readMsg( void *arg )
{
    socketServer *s = (socketServer *) arg;
    int n;
    while( 1 )
    {
        n = recv( s->connfd, s->recBuf, MAXLINE, 0 );

        s->recBuf[n] = '\0';

        
        //if receive 0, the connection is cut by cilent
        if( n == 0 )
        {
            printf( "disconnected!\n" );
            close( s->connfd );

            s->exit_con_flag = 1; //stop send msg
            pthread_exit( NULL );
        }

        //解码收到的数据
        if( s->recBuf[0] == 'f' )
            printf( "f\n" );
        if( s->recBuf[1] == 'l' )
            printf( "l\n" );
        if( s->recBuf[2] == 'r' )
            printf( "r\n" );
        if( s->recBuf[3] == 'b' )
            printf( "b\n" );

    }
}

/**************transfer size which is int to char, eg. 123 -> "123"***********/
void socketServer::intToChar( long size, char * trans )
{
    if( size == 0 )
    {
        trans[0] = '0';
        return ;
    }
<<<<<<< HEAD
    printf( "%lu\n", (unsigned long)buf.st_size );           //获取图片大小 
=======
>>>>>>> 5a6a30745328926979d1316081e200be357e3a08

    int i = 0;

    while( size != 0 )
    {
        trans[i++] = size - size / 10 * 10 + 48;
        size /= 10;
    }

    trans[i] = '\0';

    for( int x = 0; x <= (i - 1) / 2; ++x )
    {
        int temp = trans[x];
        trans[x] = trans[i - 1 - x];
        trans[i - x - 1] = temp;
    }
    
}

/*****send data to cilent***************/
void socketServer::writeMsg()
{
    int len = 0;

    static long num = 132315;
    
    char file_name[43] = "./MapSnapShoots/ocpMap20120101_";

    char num_ch[6];
    intToChar( num , num_ch );

    //file_name[30] = '_';
    for( int i = 0; i < 6; ++i )
    {
        file_name[31 + i] = num_ch[i];
    }

    char back[5] = ".jpg";
    for( int i = 0; i < 5; ++i )
    {
        file_name[37 + i] = back[i];
    }

<<<<<<< HEAD
    printf( "b=%s\n", transfer_size );        

    int a = send( connfd, transfer_size, sizeof( transfer_size ), 0 );   //传送数据大小
    if( a  < 0 )
        printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  
=======
    file_name[42] = '\0';

    num++;

    if( num == 132520 )
        num = 132315;

    printf( "%s\n", file_name );
    FILE *fd = fopen( file_name, "rb" );

    if( fd == NULL )
    {
        printf( "file open error!\n" );
        //exit( 1 );
        return;
    }

    struct stat buf;

    if( stat( file_name, &buf ) < 0 )
    {
        return ;
    }
//    printf( "%lu\n", (unsigned long)buf.st_size );           //获取图片大小 
>>>>>>> 5a6a30745328926979d1316081e200be357e3a08

    long file_size = buf.st_size;
    char transfer_size[10];
    char rest_size[5];
    int rest = MAXLINE >= file_size ? MAXLINE - file_size : MAXLINE - file_size % MAXLINE;

<<<<<<< HEAD
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
=======
   // printf( "rest = %d\n", rest );

    //将发送溢出量转化为char型
    intToChar( rest, rest_size );
    //将图片大小转化为char型
    intToChar( file_size, transfer_size );

   // printf( "b=%s\n", transfer_size );        

    //传送帧头
    int head_flag = send( connfd, "H", 1, 0 );   
    if( head_flag < 0 )
        printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  
        
    //传送数据大小
    int a = send( connfd, transfer_size, sizeof( transfer_size ), 0 );  
    if( a  < 0 )
        printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  
    
    //传送剩下的值大小
    int rest_flag = send( connfd, rest_size, sizeof( rest_size ), 0 );
    if( rest_flag < 0 )
        printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  
 
    while( !feof(fd) )
    {
        len = fread( sendBuf, 1, MAXLINE, fd );
        printf( "%d\n", len );
        if( len <= 0 )
        {
            printf( "send msg compete: %s(errno: %d)\n", strerror(errno), errno );  
>>>>>>> 5a6a30745328926979d1316081e200be357e3a08
            break;
        }
        else if( ( send( connfd, sendBuf, sizeof( sendBuf ) , 0 ) ) < 0)  
        {  
            printf( "send msg error: %s(errno: %d)\n", strerror(errno), errno );  
            exit(0);  
        }
        else
            ;
          //  printf( "write success!\n");
    }

<<<<<<< HEAD
    readMsg();
    while( recBuf[0] != 'N' )     //等待服务器传回下一次传送消息
        ;
=======
>>>>>>> 5a6a30745328926979d1316081e200be357e3a08
    fclose( fd );

    //wait for xms
    usleep( 100000 );
}


