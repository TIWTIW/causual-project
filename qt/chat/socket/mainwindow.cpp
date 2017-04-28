#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpserver.h"
#include <iostream>


//关闭服务
void MainWindow::on_pushButton_2_clicked()
{
    qApp->quit();
}

//开启服务
void MainWindow::on_pushButton_clicked()
{
    //协议端口号
    port = 8010;
    //实例 tcpServer
    qDebug("butoon");
    tcpServer = new TcpServer(this, port);
    QObject::connect(tcpServer, SIGNAL(updateServer(QString, int)),
                     this, SLOT(updateServer(QString, int)));
    //开启服务后按钮不可点击
    ui->pushButton->setEnabled(false);
}

//监听
void MainWindow::updateServer(QString message, int length)
{

    std::cout << length;
    ui->listWidget->addItem(message.left(length));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
