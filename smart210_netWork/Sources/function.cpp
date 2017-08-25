#include "function.h"
#include "test_ToServer.pb.h"

//global variable
int Sen_data = 0;
//char SerToCilent[MAXLINE];
Pose Robot_Pose;
pthread_mutex_t ToCli_buffer_lock;
bool Need_Image = false;
bool ControlMode = false;

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
    if( n == 0 )
    {
        cout << "Disconnected!" << endl;
       
        return -1;
    } 
    else if( n < 0 )
    {
        perror( "Read failed : " );
        return -1;
    }

    cout << "Receive " << n << " bytes" << endl;
    //debug
    //cout << "Receive message!" << endl;

    test::ToServer RecvMessage;
    if( RecvMessage.ParseFromArray( recBuf, sizeof( recBuf ) ) )
    {
        cout << "Parse failed!" << endl;
        return -1;
    }

    if( RecvMessage.datatype() == test::ToServer::NeedImage )
    {
        cout << "Require Image!" << endl;
        Need_Image = true;
    }
    else if( RecvMessage.datatype() == test::ToServer::NoNeedImage )
    {
        cout << "Don't need Image any more!" << endl;
        Need_Image = false;
    }

    if( RecvMessage.modeinfo() == test::ToServer::SelfMode )
    {
        cout << "Enter Self Clean Mode!" << endl;
        ControlMode = false;
        return 0;
    }
    else if( RecvMessage.modeinfo() == test::ToServer::ControlMode )
    {
        cout << "Enter Remote Control Mode!" << endl;
        ControlMode = true;
    }

    if( ControlMode )
    {
        if( RecvMessage.forward() )
            cout << "f" << endl;
        else if( RecvMessage.backward() )
            cout << "b" << endl;
        else if( RecvMessage.left() )
            cout << "l" << endl;
        else if( RecvMessage.right() )
            cout << "r" << endl;
    }
        //解码收到的数据
    return 0;

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

/********getFileSize*************************************
 * function:get the size of Image to be sent so that the 
 *          information can be encoded to the buffer
 * parameters:none
 * return: The size of file or -1 means failed
 * author:zft                                          
 * Time:2017.8.19                                      
 * ****************************************************/
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

    //cout << "My connfd is" << connfd << endl;
    string file_name = "./map.jpg";
    char sendBuf[MAXLINE];

    FILE *fd = fopen( file_name.data(), "rb" );

    if( fd == NULL )
    {
        perror( "file read error!" );
        return -1;
    }

    while( !feof(fd) )
    {
        len = fread( sendBuf, 1, MAXLINE, fd );
      //  cout << "read length is " << len << endl;
        if( len <= 0 )
        {
        //    cout << "send msg complete!" << endl;
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

    int listenfd;

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

        pthread_t receive_thread;
        pthread_t send_thread;

        if( pthread_create( &receive_thread, NULL, receiveThread, (void *)newfd ) )
        {
            cout << "Create reveive thread failed! connfd:" << *newfd << endl;
            pthread_exit( NULL );
        }

        if( pthread_create( &send_thread, NULL, sendThread, (void *)newfd ) )
        {
            cout << "Create send thread failed! connfd:" << *newfd << endl;
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

            //reset status
            Need_Image = false;
            ControlMode = false;

            pthread_exit( NULL );
        }

        usleep( 5000 );
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

        usleep( 5000 );
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
    //    cout << "Write" << nwrite << "bytes" << endl;
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

    if( Need_Image )
    {
        message.set_datatype( test::ToClient::HasImage );
        message.set_image_length( ImageSize );
    }
    else
    {
        message.set_datatype( test::ToClient::NoImage );
    }
         
    Sen_data = 20;
    Robot_Pose.x += 1;
    Robot_Pose.y += 2;
    Robot_Pose.theta += 3;

    message.set_sen_data( Sen_data );
    message.set_pose_x( Robot_Pose.x );
    message.set_pose_y( Robot_Pose.y );
    message.set_pose_theta( Robot_Pose.theta );

    unsigned int size = message.ByteSize();
    SerToCilent[0] = 'c';
    SerToCilent[1] = 'c';

    if( size > MAXLINE )
    {
        cout << "Error! Size after Serialize is bigger than size of buffer!" << endl;
        return -1;
    }
    message.SerializeToArray( SerToCilent + 2, size );

    return 0;

}
