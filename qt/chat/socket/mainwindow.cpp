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

//send map
/*void MainWindow::on_pushButton_3_clicked()
{
    QPixmap pix(tr("map.jpg"));
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    pix.save(&buffer,"jpg");
    quint32 pix_len = (quint32)buffer.data().size();
    //qDebug("image size:%d",pix_len);

     char buf[10];
     //memcpy(buf,&pix_len,4);
     QByteArray dataArray(buf,pix_len);

     dataArray.append(buffer.data());

     //qDebug()<<"connect success";
     quint32 write_len = tcpServer->write(dataArray);
     //qDebug("write len:%d",write_len);
}*/

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
