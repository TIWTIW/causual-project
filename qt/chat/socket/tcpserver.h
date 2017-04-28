#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpsocket.h"
#include <QtNetwork>

class TcpServer : public QTcpServer
{
Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0, int port = 0);
    QList<TcpSocket*> tcpSocketList;


protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
    void updateServer(QString, int);

public slots:
    void updateClients(QString,int);
    void tcpDisconnected(int);
};
#endif // TCPSERVER_H
