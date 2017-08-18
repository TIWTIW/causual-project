#include "function.h"

//global variable
int Sen_data = 0;
//char SerToCilent[MAXLINE];
Pose Robot_Pose;
pthread_mutex_t ToCli_buffer_lock;
bool Need_Image = true;

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
int readMsg( int &fd )
{
    
    int n;
    char recBuf[MAXLINE];

    n = read( fd, recBuf, sizeof( recBuf ) );

        
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

    return -1;

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
int writeMsg_Mat( Mat &image, int connfd )
{
    return 0;
}

/**************Get file size and return**************/
int getFileSize()
{
    string file_name = "./map.jpg";

    struct stat buf;
    
    if( stat( file_name.data(), &buf ) < 0 )
    {
        cout << "File information failed!" << endl;
        return -1;
    }

    return buf.st_size;
}

/********writeMsg*************************************
 * function:send the message to connected socket
 * parameters:1.connfd:the fd of connected socket
 * return:1 means send error,0 means success, -1 means 
 *        file operations failed
 * author:zft                                          
 * Time:2017.5.17                                      
 * ****************************************************/
int writeMatMsg( int &connfd )
{


    int len = 0;

    //static long num = 132315;
   
    cout << "My connfd is" << connfd << endl;
    //char file_name[10] = "./map.jpg";
    string file_name = "./map.jpg";
    char sendBuf[MAXLINE];

    //char num_ch[6];
    //intToChar( num , num_ch );

    //for( int i = 0; i < 6; ++i )
    //{
    //    file_name[31 + i] = num_ch[i];
   // }

    //char back[5] = ".jpg";
    //for( int i = 0; i < 5; ++i )
    //{
      //  file_name[37 + i] = back[i];
    //}

    //file_name[42] = '\0';

    //num++;

    //if( num == 132520 )
      //  num = 132315;

    //cout << file_name << endl;
    FILE *fd = fopen( file_name.data(), "rb" );

    if( fd == NULL )
    {
        perror( "file read error!" );
        return -1;
    }

    /*struct stat buf;

    if( stat( file_name.data(), &buf ) < 0 )
    {
        cout << "acquire stat failed!" << endl;
        return -1;
    }

    long file_size = buf.st_size;*/
    //char transfer_size[10];
    //char rest_size[5];
    //int rest = MAXLINE >= file_size ? MAXLINE - file_size : MAXLINE - file_size % MAXLINE;


    //将发送溢出量转化为char型
    //intToChar( rest, rest_size );
    //将图片大小转化为char型
    //intToChar( file_size, transfer_size );


    //传送帧头
    //int head_flag = send( connfd, "H", 1, 0 );   
    //if( head_flag < 0 )
    //{
      //  perror( "send head error!" );
        //return 1;
    //}
    //传送数据大小
    //int a = send( connfd, transfer_size, sizeof( transfer_size ), 0 );  
    //if( a  < 0 )
    //{
       // perror( "send datasize error!" ); 
       // return 1;
    //}
    //传送剩下的值大小
    //int rest_flag = send( connfd, rest_size, sizeof( rest_size ), 0 );
    //if( rest_flag < 0 )
    //{
      //  perror( "send resesize error!" );
      //  return 1;
   // }

    while( !feof(fd) )
    {
        len = fread( sendBuf, 1, MAXLINE, fd );
        cout << "read length is " << len << endl;
        if( len <= 0 )
        {
            cout << "send msg complete!" << endl;
            return -1;
        }
        else if( ( write( connfd, sendBuf, len ) ) < 0)  
        {  
            perror( "Send msg error!close connection!" );
            cout << "close connfd is" << connfd << endl;
            return -1;
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
 * return:-1 means some error happened, 0 means success 
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
        return -1;
    }

    if( bind( listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) < 0 )
    {
        perror( "bind socket error: " );
        return -1;
    }

    if( listen( listenfd, LISTENQ ) < 0 )
    {
        perror( "listen socket error: " );
        return -1;
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
        int *newfd = new int;
        if( ( *newfd = accept( listenfd, (struct sockaddr *)NULL, NULL ) ) != -1 )           
        {
                cout << "Accept success! connfd is :" << *newfd << endl;
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

        if( pthread_create( &receive_thread, NULL, receiveThread, (void *)newfd ) )
        {
            cout << "Create reveive thread failed! connfd:" << connfd << endl;
            pthread_exit( NULL );
        }

        if( pthread_create( &send_thread, NULL, sendThread, (void *)newfd ) )
        {
            cout << "Create send thread failed! connfd:" << connfd << endl;
            pthread_exit( NULL );
        }

        usleep( 1000 );
   }

}

/********receiveThread**********************************
 * function:receive thread, receive information from 
 *          client. Every client has a thread
 * parameters: 1.arg:It's actually the pointer of the fd
 *               of the connection, just have a type transfer
 * return:none 
 * author:zft                                          
 * Time:2017.8.18                                      
 * ****************************************************/
void *receiveThread( void *arg )
{
    //detach this pthread at first
    pthread_detach( pthread_self() );

    int *connfd = (int *)arg;

    while( true )
    {
        if( readMsg( *connfd ) )
        {
            //if read failed or, mostly, the client cut the connection
            cout << "Exit receive thread! connfd is:" << *connfd << endl;

            //close the connection
            close( *connfd );
            pthread_exit( NULL );
        }

        usleep( 1000 );
    }
}

/********sendThread**********************************
 * function:send thread, send information to
 *          client. Every client has a thread
 * parameters: 1.arg: It's actually the pointer to the 
 *               connected fd
 * return:none 
 * author:zft                                          
 * Time:2017.8.18                                      
 * ****************************************************/
void *sendThread( void *arg )
{
    //detach this thread at first
    pthread_detach( pthread_self() );

    int *connfd = (int *)arg;

    cout << "Enter send thread. The connfd is: " << *connfd << endl;

    //give the frame a piece of dynamic memory
    char *SerToCilent = new char[MAXLINE];

    while( true )
    {
        int MatSize = getFileSize();
        
        if( ( Encode( SerToCilent, MatSize ) == -1 ) || ( WriteSimpleMessage( *connfd, SerToCilent ) == -1 ) )
        {
            //encode failed or, mostly, the connection has been closed by receive thread
            //note: here may has a question: what if other occasion happend? no need to delete connfd!
            cout << "Exit send thread!Connfd is:" << *connfd << endl;
            delete connfd;
            pthread_exit( NULL );
        }

        //if client needs image, send image to them
        if( Need_Image )
        {
            if( writeMatMsg( *connfd ) )
            {
                cout << "Write image failed!" << endl;

            }
        }

        usleep( 1000 );
    }
}

/********writeSimpleMessage**********************************
 * function:Write information except for Image information to 
 *          the client
 * parameters: 1.fd: The connected fd
 *             2.SerToClient: The buffer in which there is the
 *             information to be transferd
 * return:0 means success, 1 means failed
 * author:zft                                          
 * Time:2017.8.18                                      
 * ****************************************************/
int WriteSimpleMessage( int &fd, char *SerToCilent )
{

    int nwrite;

    if( ( ( nwrite = write( fd, SerToCilent, MAXLINE ) ) ) < 1 )
    {
        perror( "Send message failed: " );   
        return -1;
    }
    else
    {
        cout << "Write" << nwrite << "bytes" << endl;
    }

    return 0;
}

/********createManageThread**********************************
 * function:Create manage thread
 * parameters: none
 * return: 0 means success, -1 means failed
 * author:zft      
 * Time:2017.8.18
 * *********************************************************/
int createManageThread()
{

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

/********Encode**********************************
 * function:Encode the information to be sent using Google protobuf
 * parameters: 1.SerToClient: buffer of information to be sent
 *             2.ImageSize:If there is a image to be sent, 
 *             this parameter will be encoded,otherwise won't
 * return: 0 means success, -1 means failed
 * author:zft      
 * Time:2017.8.18
 * *********************************************************/
int Encode( char *SerToCilent, int ImageSize )
{
    //suppose there is no image data at first
    //suppose the machine is litten endian  
    
    test::ToClient message;

    message.set_datatype( test::ToClient::HasImage );
         
    Sen_data = 20;
    Robot_Pose.x = 100;
    Robot_Pose.y = 50000;
    Robot_Pose.theta = 20;

    message.set_sen_data( Sen_data );
    message.set_pose_x( Robot_Pose.x );
    message.set_pose_y( Robot_Pose.y );
    message.set_pose_theta( Robot_Pose.theta );

    message.set_image_length( ImageSize );

    unsigned int size = message.ByteSize();
    SerToCilent[0] = 'c';
    SerToCilent[1] = 'c';

    if( size > MAXLINE )
    {
        cout << "Error! Size after Serialize is bigger than size of buffer!" << endl;
        return -1;
    }
    message.SerializeToArray( SerToCilent + 2, size );

    usleep( 100000 );

    return 0;

}
