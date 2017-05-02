#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork>
#include <tcpserver.h>

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

private:
    QTcpServer *tcpServer;
    int port;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateServer(QString, int);
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
