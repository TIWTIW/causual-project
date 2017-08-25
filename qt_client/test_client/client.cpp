#include "client.h"
#include "ui_client.h"
#include "test_ToClient.pb.h"
#include <QThread>

//global variable
bool HasImage = false;

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    Initial();
}

Client::~Client()
{
    delete ui;
}

void Client::Initial()
{
    ui->lineEditIP->setText(IP);
    ui->lineEditPort->setText(PORT);
    ui->pushButtonDisconnect->setDisabled(true);

    ui->lineEditTheta->setReadOnly(true);
    ui->lineEditX->setReadOnly(true);
    ui->lineEditY->setReadOnly(true);

    ClientSocket = new QTcpSocket(this);
    ClientSocket->setReadBufferSize(MAXLINE * 10);

    MapImage = new QImage;

    //Client has connected with host
    connect(ClientSocket, SIGNAL(connected()), this, SLOT(ClientConnected()));
    //Client has disconnected with host
    connect(ClientSocket, SIGNAL(disconnected()), this, SLOT(ClientDisconnected()));
    //Client Socket may has an error
    connect(ClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ClientSocketError(QAbstractSocket::SocketError)));

    //A new chunk of data has arrived
    connect(ClientSocket, SIGNAL(readyRead()), this, SLOT(ClientRecvData()));

    //Data has been sent successfully
    connect(ClientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(ClientSendData(qint64)));
}

void Client::ClientConnected()
{
    ui->pushButtonConnect->setDisabled(true);
    ui->pushButtonDisconnect->setEnabled(true);

    ui->textBrowser->append((tr("Connected with host!")));
}

void Client::ClientDisconnected()
{
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);

    ui->textBrowser->append(tr("Disconnected with host!"));
}

void Client::ClientSocketError(QAbstractSocket::SocketError e)
{
    ui->textBrowser->append(ClientSocket->errorString());
}

void Client::ClientRecvData()
{
    int numRead = 0;
    char buffer[MAXLINE];

    numRead = ClientSocket->read(buffer, sizeof(buffer));

    int i = 0;
    for( i = 0; i < numRead - 1; ++i)
    {
        if(buffer[i] == 'c' && buffer[i + 1] == 'c')
            break;
    }

    //Head isn't found
    if( i == numRead - 1 )
    {
        qDebug() << "Head isn't found";
        return;
    }
    else
    {
        qDebug() << "Found head!Started to parsing...";
    }

    qDebug() << "The read number is" << numRead;
    //Head found
    if( RecvMessage.ParseFromArray(buffer + i + 2, sizeof(buffer)) )
    {
        qDebug() << "Parse failed!";
        return ;
    }

    //show Information
    showInformation();

    //show Image
    if( RecvMessage.datatype() == test::ToClient::HasImage )
    {
        HasImage = true;
    }
    else
    {
        HasImage = false;
    }

    if( HasImage )
    {
        int ImageLength = RecvMessage.image_length();
        char ImageBuffer[ImageLength];
        int ImageHasRead = 0;

        int ImageRead = 0;
        while( true )
        {
            //Notion: waitForReadyRead
            if( ImageHasRead < ImageLength && ClientSocket->waitForReadyRead() )
            {
                qDebug() << "Bytes Avail:" << ClientSocket->bytesAvailable();
                ImageRead = ClientSocket->read(ImageBuffer + ImageHasRead, ImageLength - ImageHasRead);
                ImageHasRead += ImageRead;
                qDebug() << ImageHasRead;
            }
            else
            {
                break;
            }
        }

        showImage( ImageBuffer, sizeof(ImageBuffer) );
    }
}

void Client::showInformation()
{
    qDebug() << "Start show information";

    int pose_x = RecvMessage.pose_x();
    int pose_y = RecvMessage.pose_y();
    int pose_theta = RecvMessage.pose_theta();

    ui->lineEditX->setText(QString::number(pose_x));
    ui->lineEditY->setText(QString::number(pose_y));
    ui->lineEditTheta->setText(QString::number(pose_theta));
}

void Client::showImage(char *ImageBuf, int size)
{
    QByteArray *p_ImageByte = new QByteArray(ImageBuf, size);

    if( MapImage->loadFromData(*p_ImageByte) )
    {
        qDebug() << "Load Image successfully!";
    }
    else
    {
        qDebug() << "Load Image failed!";
        return;
    }

    ui->labelImage->clear();
    ui->labelImage->setPixmap(QPixmap::fromImage(*MapImage));
    delete p_ImageByte;
}

void Client::on_pushButtonConnect_clicked()
{
    QString StrIP = ui->lineEditIP->text();
    QString StrPort = ui->lineEditPort->text();

    ClientSocket->connectToHost(StrIP, StrPort.toUInt());
}

void Client::on_pushButtonDisconnect_clicked()
{
    ClientSocket->disconnectFromHost();
    SendMessage.Clear();
}

void Client::on_pushButtonClear_clicked()
{
    ui->textBrowser->clear();
    ui->labelImage->clear();
}

void Client::on_pushButtonControlMode_clicked()
{
    SendMessage.Clear();
    SendMessage.clear_datatype();

    SendMessage.set_modeinfo(test::ToServer::ControlMode);

    char buf[MAXLINE];
    SendMessage.SerializeToArray(buf, sizeof(buf));

    ClientSocket->write(buf, sizeof(buf));

}

void Client::on_pushButtonNeedImage_clicked()
{
    SendMessage.Clear();
    SendMessage.clear_modeinfo();

    SendMessage.set_datatype(test::ToServer::NeedImage);

    char buf[MAXLINE];
    SendMessage.SerializeToArray(buf, sizeof(buf));

    ClientSocket->write(buf, sizeof(buf));
}

void Client::ClientSendData(qint64 bytes)
{
    qDebug() << bytes << " data has been sent";
}

void Client::on_pushButtonSelfClean_clicked()
{
    SendMessage.Clear();
    SendMessage.clear_datatype();

    SendMessage.set_modeinfo(test::ToServer::SelfMode);

    char buf[MAXLINE];
    SendMessage.SerializeToArray(buf, sizeof(buf));

    ClientSocket->write(buf, sizeof(buf));
}

void Client::on_pushButtonNoImage_clicked()
{
    SendMessage.Clear();
    SendMessage.clear_modeinfo();

    SendMessage.set_datatype(test::ToServer::NoNeedImage);

    char buf[MAXLINE];
    SendMessage.SerializeToArray(buf, sizeof(buf));

    ClientSocket->write(buf, sizeof(buf));
}
