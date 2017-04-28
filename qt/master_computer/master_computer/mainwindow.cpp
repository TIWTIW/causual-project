#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_2->setEnabled( false );
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

    tcpSocket-> connectToHost(ipAddress, port.toInt());
}

void MainWindow::errorOccur( QAbstractSocket::SocketError e)
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
    QString message = "connected success!";
    ui->textBrowser->append( message );
    ui->pushButton->setEnabled( false );
    ui->pushButton_2->setEnabled( true );
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
    while(tcpSocket-> bytesAvailable() > 0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket-> bytesAvailable());
        tcpSocket->read(datagram.data(), datagram.length());
        QString message = datagram.data();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser->clear();
}

/**************Control***********************/
void MainWindow::on_pushButton_3_clicked()
{
    QString message = "forward";
    QByteArray message_latin = message.toLatin1();
    char *message_char = message_latin.data();

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message_char, message.length() );
}

void MainWindow::on_pushButton_4_clicked()
{
    QString message = "left";

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message.toLatin1(), message.length() );
}

void MainWindow::on_pushButton_5_clicked()
{
    QString message = "right";

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message.toLatin1(), message.length() );
}

void MainWindow::on_pushButton_6_clicked()
{
    QString message = "back";

    connect( tcpSocket, SIGNAL( bytesWritten(qint64) ), this, SLOT( written(qint64) ) );
    tcpSocket->write( message.toLatin1(), message.length() );
}

void MainWindow::written( qint64 )
{
    qDebug( "success!" );
}




