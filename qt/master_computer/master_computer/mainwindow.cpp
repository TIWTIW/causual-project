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
}

void MainWindow::tcpDisconnected()
{
    QString message = "disconnected!";
    ui->textBrowser->append( message );
    ui->pushButton_2->setEnabled( false );
    ui->pushButton->setEnabled( true );
    tcpSocket->readAll();
}

void MainWindow::dataReceived()
{
    static long dataSize = 0;
    static int restSize = 0;

    quint8 flag_exit = 0;

    qDebug("receive");

    QByteArray array;
    QByteArray head;
    QByteArray dataSizeArray;
    QByteArray restSizeArray;

    //only when the more than 15 bytes received
    while( tcpSocket->bytesAvailable() > 15 )
    {
        qDebug() << tcpSocket->bytesAvailable();

        if( dataSize == 0 )
        {
            if( tcpSocket->read( head.data(), 1 ) == -1 )
            {
                qDebug() << "error read!";
                return;
            }

            qDebug() << "headArray" << head;

            //trans may be incorrect, there are more than 1 bytes??
            QString head_msg = head.data();
            qDebug() << head_msg;

            if( head_msg[0] == 'H' )
            {
               if( tcpSocket->read( dataSizeArray.data(), 10 ) == -1 )
                {
                   qDebug() << "readd dataSizeArray error!" << dataSizeArray.data();
                   return;
               }

                if( tcpSocket->read( restSizeArray.data(), 5 ) == -1 )
                {
                    qDebug() << "read restSizeArray error!" << restSizeArray.data();
                    return;
                }
            }
            else
                return;

            bool transfer_ok;

            QString sizeMsg = dataSizeArray.data();
            dataSize = sizeMsg.toLong( &transfer_ok, 10 );
            qDebug() << "dataSize:" << dataSize;
            if( !transfer_ok )
                return;

            QString sizeRest = restSizeArray.data();
            restSize = sizeRest.toInt( &transfer_ok, 10 );
            qDebug() << "restSize:" << restSize;
             if( !transfer_ok )
                return;
        }

        qint64 size = tcpSocket->bytesAvailable();
        qDebug() << "size" << size;

        if( dataSize <= tcpSocket->bytesAvailable() )
        {
            qDebug() << "ok,all bytes recvd" << endl;

            array = tcpSocket->read( dataSize );
            if( array.isEmpty() )
            {
                qDebug() << "read empty!";
                return;
            }
            tcpSocket->read( restSize );
            flag_exit = 1;
        }
        else
            return ;

    }

    if( !flag_exit )
        return;

    QBuffer buffer( &array );
    buffer.open( QIODevice::ReadOnly );

    QImageReader reader( &buffer );
    QImage image = reader.read();

    qDebug() << image;

    if( !image.isNull() )
    {
        ui->label_3->setPixmap( QPixmap::fromImage( image ) );
        qDebug( "write!" );
        dataSize=0;
        restSize = 0;
    }
    else
    {
        qDebug() << reader.error();
    }

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser->clear();
    ui->label_3->clear();
}

/**************Control***********************/
void MainWindow::on_pushButton_3_clicked()
{
    frame[0] = 'f';
    sendMsg();
}

void MainWindow::on_pushButton_4_clicked()
{
    frame[1] = 'l';
    sendMsg();
}

void MainWindow::on_pushButton_5_clicked()
{
    frame[2] = 'r';
    sendMsg();
}

void MainWindow::on_pushButton_6_clicked()
{
    frame[3] = 'b';
    sendMsg();
}

void MainWindow::written( qint64 )
{
    qDebug( "success!" );

    //let the frame be 0 after send success
    for( int i = 0; i < 6; ++i )
    {
        if( frame[i] != ' ' )
        {
            qDebug() << frame;
            frame[i] = ' ';
        }
    }
}


/********send to server**********/
void MainWindow::sendMsg()
{
    tcpSocket->write( frame, sizeof( frame ) );
}




