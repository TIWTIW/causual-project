#include "function.h"

//global variable
int Sen_data = 0;
char SerToCilent[4096];
Pose Robot_Pose;
pthread_mutex_t ToCli_buffer_lock;

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

    n = recv( fd, recBuf, MAXLINE, 0 );

        
    //if receive 0, the connection is cut by cilent
    if( n <= 0 )
    {
        cout << "disconnected!" << endl;
       
        return 1;
    }

    recBuf[n] = '\0';

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
    return 0;
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
    servaddr.sin_addr.s_addr = htonl ( INADDR_ANY );
    servaddr.sin_port = htons( port );

    if( ( listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        perror( "create socket error: " );
        return 1;
    }

    if( bind( listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) < 0 )
    {
        perror( "bind socket error: " );
        return 1;
    }

    if( listen( listenfd, LISTENQ ) < 0 )
    {
        perror( "listen socket error: " );
        return 1;
    }

    cout << "Listen socket construct success!" << endl;
    return 0;
}


/********manageThread**********************************
 * function:the main thread.create child thread and 
 *          listen the connected socket
 * parameters:none
 * return:none 
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
void* manageThread( void *arg )
{
    //detach the manage thread(actuall may be not useful)
    pthread_detach( pthread_self() );

    int connfd, listenfd;

    //initial listening...
    if( initialListen( listenfd ) )
    {
        cout << "Initial listen socket failed!" << endl;
        pthread_exit( NULL );
    }

    while( true )
    {
        if( ( connfd = accept( listenfd, (struct sockaddr *)NULL, NULL ) ) != -1 )           
        {
                cout << "Accept success!" << connfd << endl;
        }
        else
        {
            perror( "Accept failed: " );
            continue;
        }

        //int *fd = new int;

        //*fd = connfd;

        pthread_t receive_thread;
        pthread_t send_thread;

        /*if( pthread_create( &receive_thread, NULL, receiveThread, (void *)connfd ) )
        {
            cout << "Create reveive thread failed! connfd:" << connfd << endl;
            pthread_exit( NULL );
        }*/

        if( pthread_create( &send_thread, NULL, sendThread, (void *)connfd ) )
        {
            cout << "Create send thread failed! connfd:" << connfd << endl;
            pthread_exit( NULL );
        }

        usleep( 1000 );
   }

}

/******************receiveThread***************************/
void *receiveThread( void *arg )
{
    //detach this pthread at first
    pthread_detach( pthread_self() );

    int connfd = *(int *)arg;

    while( true )
    {
        if( readMsg( connfd ) )
        {
            cout << "Exit receive thread! connfd is:" << connfd << endl;
            close( connfd );
            pthread_exit( NULL );
        }

        usleep( 1000 );
    }
}

/******************sendThread******************************/
void *sendThread( void *arg )
{
    //detach this thread at first
    pthread_detach( pthread_self() );

    int connfd = reinterpret_cast<int &>( arg );

    while( true )
    {
        if( WriteSimpleMessage( connfd ) == 1 )
        {
            cout << "Exit send thread!Connfd is:" << connfd << endl;
//            close( *connfd );
            pthread_exit( NULL );
        }

        usleep( 10000 );
    }
}

/******************simple send msg test v1.0***************/
int WriteSimpleMessage( int &fd )
{

    pthread_mutex_lock( &ToCli_buffer_lock );

    if( ( send( fd, SerToCilent, sizeof( SerToCilent ), 0 ) ) < 1 )
    {
        perror( "Send message failed: " );
        return 1;
    }
    pthread_mutex_unlock( &ToCli_buffer_lock );

    return 0;
}

/******************create manage thread********************/
int createManageThread()
{

    //create encode thread
    pthread_t p_EncodeThread;
    if( pthread_create( &p_EncodeThread, NULL, encodeThread, NULL ) )
    {
        cout << "Create encode thread failed!" << endl;
    }
    else
    {
        cout << "Create encode thread success!" << endl;
    }

    //create decode thread here...
    //
    //

    //create manage thread to manage the connection of cilent
    pthread_t p_ManageThread;
    if( pthread_create( &p_ManageThread, NULL, manageThread, NULL ) )
    {
        cout << "Create manage thread failed!" << endl;
        return -1;
    }
    else
    {
        cout << "Create manage thread success!" << endl;
        return 0;
    }
}

/******************Encode thread***************************/
void *encodeThread( void *arg )
{
    //suppose there is no image data at first
    //suppose the machine is litten endian  
    
    //Frame head
    //SerToCilent[0] = FRAME_HEAD;

    //Frame type
    //SerToCilent[1] = DATA_TYPE;

    //unsigned int data_length = 12;
    //Frame data length
    //SerToCilent[2] = ( data_length & 0xff000000 ) >> 24;
    //SerToCilent[3] = ( data_length & 0x00ff0000 ) >> 16;
    //SerToCilent[4] = ( data_length & 0x0000ff00 ) >> 8;
    //SerToCilent[5] = ( data_length & 0x000000ff );
    
    test::ToClient message;
    while( true )
    {
        message.set_head( FRAME_HEAD );
        message.set_datatype( test::ToClient::NoImage );
         
        unsigned int length = sizeof( int ) + sizeof( struct Pose );
        message.set_datalength( length );
        message.set_sen_data( Sen_data );
        message.set_pose_x( Robot_Pose.x );
        message.set_pose_y( Robot_Pose.y );
        message.set_pose_theta( Robot_Pose.theta );

        message.set_tail( FRAME_TAIL );

        int size = message.ByteSize();
        //unsigned char bits[size];

        pthread_mutex_lock( &ToCli_buffer_lock );
        message.SerializeToArray( SerToCilent, size );
        pthread_mutex_unlock( &ToCli_buffer_lock );

/*        for( int i = 0; i < size; ++i )
        {
            printf( "%0xx \n", SerToCilent[i] );
        }*/
        usleep( 100000 );
    }

}
