#ifndef TCPSOCKET_H
#define TCPSOCKET_H


#include <QTcpSocket>
class TcpSocket : public QTcpSocket
{
Q_OBJECT
public:
    TcpSocket(QObject *parent = 0);

signals:
    void updateClients(QString, int);
    void disconnected(int);

public slots:
    void dataReceived();
    void datadisconnected();
};
#endif // TCPSOCKET_H
