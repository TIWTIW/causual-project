#ifndef SENDER_H
#define SENDER_H

#include <QTimer>
#include <QAbstractSocket>
#include <QtNetwork/QTcpSocket>
#include <QPixmap>
#include <QBuffer>
#include <QImageReader>



class Sender : public QObject
{
    Q_OBJECT

public:
    Sender();
    void start( QString, QString );
    void disconnect();

public:
    char frame[6];

private:
    QTimer Qtim;
    QTcpSocket *tcpSocket;

public slots:
    void sendMsg();
    void tcpConnected();
    void tcpDisconnected();
    void dataReceived();
    void hostFounded();
    void written( qint64 );
    void errorOccur(QAbstractSocket::SocketError e);

};

#endif // SENDER_H
