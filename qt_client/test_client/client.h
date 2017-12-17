#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include "test_ToClient.pb.h"
#include "test_ToServer.pb.h"

//IP and Port Number
#define IP "192.168.1.20"
#define PORT "9600"
#define MAXLINE 4096

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;

//private functions
private:
    void Initial();
    void showInformation();
    void showImage( char *ImageBuf, int size );

//auto private slots
private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonDisconnect_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonControlMode_clicked();
    void on_pushButtonNeedImage_clicked();

//my add private slots
private slots:
    void ClientConnected();
    void ClientDisconnected();
    void ClientSocketError(QAbstractSocket::SocketError e);
    void ClientRecvData();
    void ClientSendData(qint64 bytes);

    void on_pushButtonSelfClean_clicked();

    void on_pushButtonNoImage_clicked();

    void on_pushButtonForward_clicked();

    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

    void on_pushButtonBackward_clicked();

private:
    QTcpSocket *ClientSocket;
    test::ToClient RecvMessage;
    test::ToServer SendMessage;
    QImage *MapImage;
};

#endif // CLIENT_H
