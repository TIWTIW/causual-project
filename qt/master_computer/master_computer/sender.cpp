#include "sender.h"

//extern QTcpSocket *tcpSocket;

Sender::Sender()
{

}

void Sender::start( QString ipAddress, QString port )
{
    tcpSocket = new QTcpSocket( this );

    connect( tcpSocket, SIGNAL( connected() ),
             this, SLOT( tcpConnected() ) );

    connect( tcpSocket, SIGNAL( disconnected() ),
             this, SLOT( tcpDisconnected() ) );

    connect( tcpSocket, SIGNAL( readyRead() ),
             this, SLOT( dataReceived() ) );

    connect( tcpSocket, SIGNAL( hostFound() ),
             this, SLOT( hostFounded() ) );

    connect( tcpSocket, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( errorOccur( QAbstractSocket::SocketError ) ) );

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ),
             this, SLOT( written(qint64) ) );

    tcpSocket-> connectToHost(ipAddress, port.toInt());

    connect( &Qtim, SIGNAL( timeout() ), this, SLOT( sendMsg() ) );
    Qtim.start( 100 );
}

void Sender::errorOccur( QAbstractSocket::SocketError e )
{
    QString message = "error occured!";
    QString errorNum;
    errorNum = QString::number( e );

    ui->textBrowser->append( message );
    ui->textBrowser->append( errorNum );
}

void Sender::hostFounded()
{
    QString message = "host Founded";
    ui->textBrowser->append( message );
}

void Sender::disconnect()
{
    tcpSocket->disconnectFromHost();
}

void Sender::tcpConnected()
{
    QString message = "connect success!";
    ui->textBrowser->append( message );
    ui->pushButton->setEnabled( false );
    ui->pushButton_2->setEnabled( true );
    qDebug() << tcpSocket->socketDescriptor();
}

void Sender::tcpDisconnected()
{
    QString message = "disconnected!";
    ui->textBrowser->append( message );
    ui->pushButton_2->setEnabled( false );
    ui->pushButton->setEnabled( true );
}

void Sender::dataReceived()
{
    static long dataSize = 0;
    static long len_now = 0;
    qDebug("receive");
    QByteArray array;

    while( tcpSocket->bytesAvailable() > 0 )
    {
        //qDebug() << dataSize;
        if( dataSize == 0 )
        {
            //QDataStream stream( tcpSocket );
            //stream.setVersion( QDataStream::Qt_4_0 );

           // if( tcpSocket->bytesAvailable() < sizeof(quint32) )
              //return;

            tcpSocket->read( array.data(), tcpSocket->bytesAvailable() );
            qDebug() << array.data();
            QString size_str = array.data();
            qDebug() << size_str;
            dataSize = size_str.toLong();
            qDebug() << "dataSize:" << dataSize;

            QString message( "OK" );
            tcpSocket->write( message.toLatin1(), message.length() );
        }
        qint64 size = tcpSocket->bytesAvailable();
        qDebug() << "size" << size;
        qDebug() << "len_now:" << len_now;
        len_now += (long)tcpSocket->bytesAvailable();
        qDebug() << "len_now:" << len_now;
        array.append((QByteArray)tcpSocket->readAll());

        qDebug() << "len_now:" << len_now;

        if( dataSize <= len_now )
        {
            qDebug()<<"ok,all bytes recvd"<<endl;

            dataSize = 0;
            len_now = 0;

            QString message( "N" );
            tcpSocket->write( message.toLatin1(), message.length() );
        }
        else
            return ;
    }
    //tcpSocket->disconnectFromHost();

        QBuffer buffer( &array );
        buffer.open( QIODevice::ReadOnly );

        QImageReader reader( &buffer );
        QImage image = reader.read();

        if( !image.isNull() )
        {
            ui->label_3->setPixmap( QPixmap::fromImage( image ) );
            qDebug("write!");
            dataSize=0;
        }
        else
        {
            qDebug() << reader.error();
        }

}

void Sender::written( qint64 )
{
    qDebug( "success!" );
}

void Sender::sendMsg()
{
    tcpSocket->write( frame, sizeof(frame) );
}

