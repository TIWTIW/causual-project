#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_2->setEnabled( false );
    ui->lineEdit->setText( "127.0.0.1" );
    ui->lineEdit_2->setText( "8010" );

    for( int i = 0; i < 6; ++i )
        frame[i] = ' ';

    showMap();
}


MainWindow::~MainWindow()
{
    delete ui;
}

/********************communication************************/
void MainWindow::on_pushButton_clicked()
{
    QString ipAddress = ui->lineEdit->text();
    QString port = ui->lineEdit_2->text();

    //sender.start( ipAddress, port );

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

}


void MainWindow::errorOccur( QAbstractSocket::SocketError e )
{
    QString message = "error occured!";
    QString errorNum;
    errorNum = QString::number( e );

    ui->textBrowser->append( message );
    ui->textBrowser->append( errorNum );
}

void MainWindow::hostFounded()
{
    QString message = "host Founded";
    ui->textBrowser->append( message );
}

void MainWindow::on_pushButton_2_clicked()
{
    tcpSocket->disconnectFromHost();
}

void MainWindow::tcpConnected()
{
    QString message = "connect success!";
    ui->textBrowser->append( message );
    ui->pushButton->setEnabled( false );
    ui->pushButton_2->setEnabled( true );
    qDebug() << tcpSocket->socketDescriptor();

    timer = new QTimer( this );

    connect( timer, SIGNAL( timeout() ),
             this, SLOT( sendMsg() ) );

    timer->start( 1000 );

}

void MainWindow::tcpDisconnected()
{
    QString message = "disconnected!";
    ui->textBrowser->append( message );
    ui->pushButton_2->setEnabled( false );
    ui->pushButton->setEnabled( true );
}

void MainWindow::dataReceived()
{
    static long dataSize = 0;
    //static long len_now = 0;
    qDebug("receive");
    QByteArray array;
    QByteArray head;

    while( tcpSocket->bytesAvailable() > 0 )
    {
        //qDebug() << dataSize;
        if( dataSize == 0 )
        {
            //QDataStream stream( tcpSocket );
            //stream.setVersion( QDataStream::Qt_4_0 );

           // if( tcpSocket->bytesAvailable() < sizeof(quint32) )
              //return;

            tcpSocket->read( head.data(), tcpSocket->bytesAvailable() );
            qDebug() << head.data();
            QString size_str = head.data();
            qDebug() << size_str;
            dataSize = size_str.toLong();
            qDebug() << "dataSize:" << dataSize;

           // QString message( "OK" );
            //tcpSocket->write( message.toLatin1(), message.length() );
            frame[4] = 'h';
        }
        qint64 size = tcpSocket->bytesAvailable();
        qDebug() << "size" << size;
        //qDebug() << "len_now:" << len_now;
        //len_now += (long)tcpSocket->bytesAvailable();
        //qDebug() << "len_now:" << len_now;
        //array.append((QByteArray)tcpSocket->readAll());

        //qDebug() << "len_now:" << len_now;

        if( dataSize <= tcpSocket->bytesAvailable() )
        {
            qDebug()<<"ok,all bytes recvd"<<endl;

            //tcpSocket->read( array.data(), dataSize );
            array = tcpSocket->read( dataSize );

            tcpSocket->readAll();

            //dataSize = 0;
            //len_now = 0;

           // QString message( "N" );
            //tcpSocket->write( message.toLatin1(), message.length() );
            frame[5] = 'n';
        }
        else
            return ;
    }
    //tcpSocket->disconnectFromHost();
        //array.resize( ds );
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

void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser->clear();
}

/**************Control***********************/
void MainWindow::on_pushButton_3_clicked()
{
    /*QString message = "forward";
    QByteArray message_latin = message.toLatin1();
    char *message_char = message_latin.data();

    //connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message_char, message.length() );*/

    frame[0] = 'f';
}

void MainWindow::on_pushButton_4_clicked()
{
    /*QString message = "left";

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message.toLatin1(), message.length() );*/

    frame[1] = 'b';
}

void MainWindow::on_pushButton_5_clicked()
{
    /*QString message = "right";

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message.toLatin1(), message.length() );*/

    frame[2] = 'c';
}

void MainWindow::on_pushButton_6_clicked()
{
    /*QString message = "back";

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message.toLatin1(), message.length() );*/

    frame[3] = 'r';
}

void MainWindow::written( qint64 )
{
    qDebug( "success!" );

    for( int i = 0; i < 6; ++i )
    {
        if( frame[i] != ' ' )
        {
            qDebug() << frame;
            frame[i] = ' ';
        }
    }
}

/********Map show***********************/
void MainWindow::showMap()
{
    //QPixmap pm = new QPixmap;
    //pm->load()
}


/********send to server**********/
void MainWindow::sendMsg()
{
    //qDebug() << frame;
    tcpSocket->write( frame, sizeof( frame ) );

    /*for( int i = 0; i < 6; ++i )
    {
        if( frame[i] != ' ' )
        {
            qDebug() << frame;
            frame[i] = ' ';
        }
    }*/
}




