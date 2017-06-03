#include "function.h"

using namespace std;
using namespace cv;

/********readMsg****************************************
 * function:decode the message received, and when recv *
 *          0 bytes cut the connection                 *
 * parameters:1.fd:connection fd                       *
 * return:0 means success, 1 means failed or connection* 
 *        should be cut                                *
 * author:zft                                          *
 * Time:2017.5.17                                      *
 * ****************************************************/
int readMsg( int fd )
{
    
    int n;
    char recBuf[MAXLINE];

    n = recv( fd, recBuf, MAXLINE, MSG_DONTWAIT );

    recBuf[n] = '\0';
        
    //if receive 0, the connection is cut by cilent
    if( n == 0 )
    {
        cout << "disconnected!" << endl;
       
        return 1;
    }

        //解码收到的数据
    if( recBuf[0] == 'f' )
        cout << "f" << endl;
    if( recBuf[1] == 'l' )
        cout << "l" << endl;
    if( recBuf[2] == 'r' )
        cout << "r" << endl;
    if( recBuf[3] == 'b' )
        cout << "b" << endl;

    return 0;

}


/********intToChar*************************************
 * function:change the int(or long) to char
 * parameters:1.size:the number which should be change
 *            2.trans:the result of transfer
 * return:none                           
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
void intToChar( long size, char * trans )
{
    if( size == 0 )
    {
        trans[0] = '0';
        return ;
    }

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


/********writeMsg_Mat*************************************
 * function:send the orignal data to connected socket
 * parameters:1.Mat:orignal Mat data
 *            2.connfd:the fd of connected socket
 * return:1 means send error,0 means success, -1 means 
 *        file operations failed
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
int writeMsg_Mat( Mat image, int connfd )
{
    ;
}

/********writeMsg*************************************
 * function:send the message to connected socket
 * parameters:1.connfd:the fd of connected socket
 * return:1 means send error,0 means success, -1 means 
 *        file operations failed
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
int writeMsg( int connfd )
{


    int len = 0;

    static long num = 132315;
   
    cout << "My connfd is" << connfd << endl;
    char file_name[43] = "./MapSnapShoots/ocpMap20120101_";
    char sendBuf[MAXLINE];

    char num_ch[6];
    intToChar( num , num_ch );

    for( int i = 0; i < 6; ++i )
    {
        file_name[31 + i] = num_ch[i];
    }

    char back[5] = ".jpg";
    for( int i = 0; i < 5; ++i )
    {
        file_name[37 + i] = back[i];
    }

    file_name[42] = '\0';

    num++;

    if( num == 132520 )
        num = 132315;

    cout << file_name << endl;
    FILE *fd = fopen( file_name, "rb" );

    if( fd == NULL )
    {
        perror( "file read error!" );
        return -1;
    }

    struct stat buf;

    if( stat( file_name, &buf ) < 0 )
    {
        cout << "acquire stat failed!" << endl;
        return -1;
    }

    long file_size = buf.st_size;
    char transfer_size[10];
    char rest_size[5];
    int rest = MAXLINE >= file_size ? MAXLINE - file_size : MAXLINE - file_size % MAXLINE;


    //将发送溢出量转化为char型
    intToChar( rest, rest_size );
    //将图片大小转化为char型
    intToChar( file_size, transfer_size );


    //传送帧头
    int head_flag = send( connfd, "H", 1, 0 );   
    if( head_flag < 0 )
    {
        perror( "send head error!" );
        return 1;
    }
    //传送数据大小
    int a = send( connfd, transfer_size, sizeof( transfer_size ), 0 );  
    if( a  < 0 )
    {
        perror( "send datasize error!" ); 
        return 1;
    }
    //传送剩下的值大小
    int rest_flag = send( connfd, rest_size, sizeof( rest_size ), 0 );
    if( rest_flag < 0 )
    {
        perror( "send resesize error!" );
        return 1;
    }

    while( !feof(fd) )
    {
        len = fread( sendBuf, 1, MAXLINE, fd );
        cout << "read length is " << len << endl;
        if( len <= 0 )
        {
            cout << "send msg complete!" << endl;
            return 1;
        }
        else if( ( send( connfd, sendBuf, sizeof( sendBuf ) , 0 ) ) < 0)  
        {  
            perror( "send msg error!i close connection!" );
            cout << "close connfd is" << connfd << endl;
            return 1;
        }
    }


    fclose( fd );

    return 0;

    //wait for xms
   // usleep( 100000 );
}


/********initialListen**********************************
 * function:initial the socket,socket(), bind(), listen()
 * parameters:1.listenfd:the fd which should be constructed
 *            2.port:the port number
 * return:1 means some error happened, 0 means success 
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
int initialListen( int &listenfd, int port )
{
    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl (INADDR_ANY );
    servaddr.sin_port = htons( port );

    if( ( listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
        perror( "create socket error!" );
        return 1;
    }

    if( bind( listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) == -1 )
    {
        perror( "bind socket error!" );
        return 1;
    }

    if( listen( listenfd, 10 ) == -1 )
    {
        perror( "listen socket error!" );
        return 1;
    }

    cout << "socket construct success!" << endl;
    return 0;
}


/********manageThread**********************************
 * function:the main thread.create epoll and listen the 
 *          connected socket
 * parameters:none
 * return:none 
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
static void* manageThread( void *arg )
{
    struct epoll_event ev, events[MAX_EVENTS];
    int nfds, epollfd;
    int connfd, listenfd;

    //initial listening...
    if( initialListen( listenfd ) )
    {
        cout << "initial failed!" << endl;
        pthread_exit( NULL );
    }

    //create and initialize epoll
    epollfd = epoll_create( 256 );
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    epoll_ctl( epollfd, EPOLL_CTL_ADD, listenfd, &ev);

    while( true )
    {
        nfds = epoll_wait( epollfd, events, MAX_EVENTS, -1 );   //waiting for cilent connect

        for( int n = 0; n < nfds; ++n )
        {
            if( events[n].events & EPOLLIN && events[n].data.fd == listenfd )
            {
                connfd = accept( listenfd, (struct sockaddr *)NULL, NULL );
               
                if( fcntl( connfd, F_SETFL, fcntl( connfd, F_GETFL, 0) | O_NONBLOCK ) == -1 )
                {
                    cout << "set nonBlocking failed!" << endl;
                    pthread_exit( NULL );
                } 

                ev.events = EPOLLIN | EPOLLOUT;
                ev.data.fd = connfd;
                epoll_ctl( epollfd, EPOLL_CTL_ADD, connfd, &ev );
                
               
                cout << "accept success!" << connfd << endl;
            }

            if( events[n].events & EPOLLIN && events[n].data.fd != listenfd )
            {
                if( readMsg( events[n].data.fd ) == 1 )
                {
                    close( events[n].data.fd );
                    epoll_ctl( epollfd, EPOLL_CTL_DEL, events[n].data.fd, &ev );
                }

            }
            
            if( events[n].events & EPOLLOUT )
            {
                if( writeMsg( events[n].data.fd ) == 1 )
                {
                    close( events[n].data.fd );
                    epoll_ctl( epollfd, EPOLL_CTL_DEL, events[n].data.fd, &ev );
                }
            }

        }

        usleep( 100000 );
    }

}

/******************create manage thread********************/
int createManageThread()
{
    pthread_t p_ManageThread;
    if( pthread_create( &p_ManageThread, NULL, manageThread, NULL ) )
    {
        cout << "create manage thread failed!" << endl;
        return -1;
    }
    else
    {
        cout << "create manage thread success!" << endl;
        return 0;
    }
}
