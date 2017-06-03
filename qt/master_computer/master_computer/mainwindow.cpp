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

    ui->lineEdit_3->setReadOnly( true );
    ui->lineEdit_4->setReadOnly( true );
    ui->lineEdit_5->setReadOnly( true );
    ui->lineEdit_6->setReadOnly( true );
    ui->lineEdit_7->setReadOnly( true );
    ui->lineEdit_8->setReadOnly( true );
    ui->lineEdit_9->setReadOnly( true );
    ui->lineEdit_10->setReadOnly( true );
    ui->lineEdit_11->setReadOnly( true );

    for( int i = 0; i < 6; ++i )
        frame[i] = ' ';

    connect( ui->actionLogin_2, SIGNAL( triggered() ), this, SLOT( Login_open() ) );

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Login_open()
{
    QMessageBox::information( this, tr( "Login" ), tr( "Too Young Too Simple!" ) );
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

    connected = true;

    qDebug() << tcpSocket->socketDescriptor();
}

void MainWindow::tcpDisconnected()
{
    QString message = "disconnected!";
    ui->textBrowser->append( message );
    ui->pushButton_2->setEnabled( false );
    ui->pushButton->setEnabled( true );
    tcpSocket->readAll();

    connected = false;
}

void MainWindow::dataReceived()
{
    static long dataSize = 0;
    static int restSize = 0;

    //quint8 flag_exit = 0;

    qDebug("receive");

    QByteArray array;
    QByteArray head;
    QByteArray dataSizeArray;
    QByteArray restSizeArray;

    //only when the more than 15 bytes received
    while( tcpSocket->bytesAvailable() > 15 )
    {
        //qDebug() << "data is:" << tcpSocket->readAll();
        //return;
        qDebug() << tcpSocket->bytesAvailable();

        if( dataSize == 0 )
        {
            head = tcpSocket->read( 1 );
            if( head.isEmpty() )
            {
                qDebug() << "error read!";
                return;
            }

            //qDebug() << "headArray.data" << head.data();

            //trans may be incorrect, there are more than 1 bytes??
            //QString head_msg = head.data();
           // qDebug() << head_msg;

            //char *head_msg_ch = head.data();
            //qDebug() << head_msg_ch;
            //QString x = 'H';

            qDebug() << "head" << head;
            if( head[0] == 'H' )
            {
               dataSizeArray = tcpSocket->read( 10 );
               if( dataSizeArray.isEmpty() )
                {
                   qDebug() << "readd dataSizeArray error!" << dataSizeArray.data();
                   return;
               }
               qDebug() << "dataSizeArray" << dataSizeArray;

                restSizeArray = tcpSocket->read( 5 );
                if(  restSizeArray.isEmpty() )
                {
                    qDebug() << "read restSizeArray error!" << restSizeArray.data();
                    return;
                }
                qDebug() << "restSize" << restSizeArray;
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

        if( (dataSize + restSize) <= size )
        {
            qDebug() << "ok,all bytes recvd" << endl;

            array = tcpSocket->read( dataSize );
            //qDebug() << tcpSocket->read( restSize );
            //qDebug() << "array" << array;
            tcpSocket->read( restSize );

            //return;

            if( array.isEmpty() )
            {
                qDebug() << "read empty!";
                return;
            }
            dataSize=0;
            restSize = 0;
            //qDebug() << "next" << tcpSocket->readAll();
            //flag_exit = 1;
            break;
        }
        else
            return ;

    }

    //if( !flag_exit )
        //return;

    qDebug() << "exit!";

    QBuffer buffer( &array );
    buffer.open( QIODevice::ReadOnly );

    QImageReader reader( &buffer );
    QImage image = reader.read();

    qDebug() << image;

    if( !image.isNull() )
    {
        ui->label_3->setPixmap( QPixmap::fromImage( image ) );
        qDebug( "write!" );
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
    ui->textBrowser->clear();
}

/**************Control***********************/
void MainWindow::on_pushButton_3_clicked()
{
    if( connected )
    {
        ui->textBrowser_2->append( "Go ahead!" );
        frame[0] = 'f';
        sendMsg();
    }
    else
    {
        QMessageBox::information( this, tr( "warning" ), tr( "You haven't connected to the server!" ) );
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if( connected )
    {
        ui->textBrowser_2->append( "Turn left!" );
        frame[1] = 'l';
        sendMsg();
    }
    else
    {
        QMessageBox::information( this, tr( "warning" ), tr( "You haven't connected to the server!" ) );
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if( connected )
    {
        ui->textBrowser_2->append( "Turn right!" );
        frame[2] = 'r';
        sendMsg();
    }
    else
    {
        QMessageBox::information( this, tr( "warning" ), tr( "You haven't connected to the server!" ) );
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if( connected )
    {
        ui->textBrowser_2->append( "Go back!" );
        frame[3] = 'b';
        sendMsg();
    }
    else
    {
        QMessageBox::information( this, tr( "warning" ), tr( "You haven't connected to the server!" ) );
    }
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

/*********keyboard??*************/
void MainWindow::keyPressEvent( QKeyEvent *event )
{
    if( event->key() == Qt::Key_W && connected )
    {
        frame[0] = 'f';
        sendMsg();
    }
    else if( event->key() == Qt::Key_A && connected )
    {
        frame[1] = 'l';
        sendMsg();
    }
    else if( event->key() == Qt::Key_D && connected )
    {
        frame[2] = 'r';
        sendMsg();
    }
    else if( event->key() == Qt::Key_S && connected )
    {
        frame[3] = 'b';
        sendMsg();
    }

}


/********send to server**********/
void MainWindow::sendMsg()
{
    tcpSocket->write( frame, sizeof( frame ) );
}




