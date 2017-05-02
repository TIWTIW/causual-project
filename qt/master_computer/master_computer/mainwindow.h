#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QAbstractSocket>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QBuffer>
#include <QImageReader>
#include <QVBoxLayout>

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

/*****************Communication*********/
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_7_clicked();
    void tcpConnected();
    void tcpDisconnected();
    void dataReceived();
    void hostFounded();
    void written( qint64 );
    void errorOccur(QAbstractSocket::SocketError e);

/*******Control************************/
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

/********Map show*********************/
private:
    void showMap();
};

#endif // MAINWINDOW_H
