#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QAbstractSocket>
#include <QLabel>
#include <QPixmap>
#include <QBuffer>
#include <QImageReader>
#include <QKeyEvent>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTcpSocket *tcpSocket;

    QTimer *timer;

    char frame[6];

    bool connected = false;

/*****************Communication*********/
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_7_clicked();
    void tcpConnected();
    void tcpDisconnected();
    void dataReceived();  //show map
    void hostFounded();
    void written( qint64 );
    void errorOccur(QAbstractSocket::SocketError e);
    void sendMsg();

/*******Control************************/
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

/***********keyboard****************/
protected:
    void keyPressEvent(QKeyEvent *);


/***********joke*****************/
private slots:
    void Login_open();
};

#endif // MAINWINDOW_H
