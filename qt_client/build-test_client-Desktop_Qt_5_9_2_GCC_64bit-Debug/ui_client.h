/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QAction *actionConnect;
    QAction *actionConnect_2;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout;
    QPushButton *pushButtonBackward;
    QPushButton *pushButtonLeft;
    QPushButton *pushButtonRight;
    QPushButton *pushButtonForward;
    QFrame *line_7;
    QFrame *line_5;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_2;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout_3;
    QLabel *labelTheta;
    QLabel *labelY;
    QLineEdit *lineEditY;
    QLabel *labelX;
    QLineEdit *lineEditX;
    QLineEdit *lineEditTheta;
    QFrame *line_3;
    QGridLayout *gridLayout_4;
    QLineEdit *lineEdit_Left;
    QLabel *label_SEN1;
    QLineEdit *lineEdit_SEN1;
    QLabel *label_MotionSt;
    QLineEdit *lineEdit_MotionSt;
    QLabel *label_Right;
    QLineEdit *lineEdit_Right;
    QLabel *label_Hall_left;
    QLineEdit *lineEdit_Hall_L;
    QLabel *label_MotionEs;
    QLineEdit *lineEdit_MotionEs;
    QLabel *label_Left;
    QFrame *line_6;
    QFrame *line_8;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QLabel *labelImage;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonNeedImage;
    QPushButton *pushButtonNoImage;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButtonConnect;
    QLabel *labelPort;
    QLabel *labelIP;
    QLineEdit *lineEditIP;
    QPushButton *pushButtonClear;
    QLineEdit *lineEditPort;
    QPushButton *pushButtonDisconnect;
    QPushButton *pushButtonSelfClean;
    QPushButton *pushButtonControlMode;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(886, 541);
        Client->setStyleSheet(QStringLiteral(""));
        actionConnect = new QAction(Client);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionConnect_2 = new QAction(Client);
        actionConnect_2->setObjectName(QStringLiteral("actionConnect_2"));
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButtonBackward = new QPushButton(centralWidget);
        pushButtonBackward->setObjectName(QStringLiteral("pushButtonBackward"));

        gridLayout->addWidget(pushButtonBackward, 2, 1, 1, 1);

        pushButtonLeft = new QPushButton(centralWidget);
        pushButtonLeft->setObjectName(QStringLiteral("pushButtonLeft"));

        gridLayout->addWidget(pushButtonLeft, 1, 0, 1, 1);

        pushButtonRight = new QPushButton(centralWidget);
        pushButtonRight->setObjectName(QStringLiteral("pushButtonRight"));

        gridLayout->addWidget(pushButtonRight, 1, 2, 1, 1);

        pushButtonForward = new QPushButton(centralWidget);
        pushButtonForward->setObjectName(QStringLiteral("pushButtonForward"));

        gridLayout->addWidget(pushButtonForward, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 3, 1, 1, 1);

        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_7, 4, 1, 1, 1);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_5, 1, 0, 8, 1);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_4, 1, 2, 7, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalSpacer_4 = new QSpacerItem(278, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        labelTheta = new QLabel(centralWidget);
        labelTheta->setObjectName(QStringLiteral("labelTheta"));

        gridLayout_3->addWidget(labelTheta, 0, 2, 1, 1);

        labelY = new QLabel(centralWidget);
        labelY->setObjectName(QStringLiteral("labelY"));

        gridLayout_3->addWidget(labelY, 1, 0, 1, 1);

        lineEditY = new QLineEdit(centralWidget);
        lineEditY->setObjectName(QStringLiteral("lineEditY"));
        lineEditY->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(lineEditY, 1, 1, 1, 1);

        labelX = new QLabel(centralWidget);
        labelX->setObjectName(QStringLiteral("labelX"));

        gridLayout_3->addWidget(labelX, 0, 0, 1, 1);

        lineEditX = new QLineEdit(centralWidget);
        lineEditX->setObjectName(QStringLiteral("lineEditX"));
        lineEditX->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(lineEditX, 0, 1, 1, 1);

        lineEditTheta = new QLineEdit(centralWidget);
        lineEditTheta->setObjectName(QStringLiteral("lineEditTheta"));
        lineEditTheta->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_3->addWidget(lineEditTheta, 0, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);


        gridLayout_5->addLayout(verticalLayout_2, 7, 1, 2, 1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_3, 7, 4, 1, 3);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        lineEdit_Left = new QLineEdit(centralWidget);
        lineEdit_Left->setObjectName(QStringLiteral("lineEdit_Left"));
        lineEdit_Left->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(lineEdit_Left, 0, 1, 1, 1);

        label_SEN1 = new QLabel(centralWidget);
        label_SEN1->setObjectName(QStringLiteral("label_SEN1"));

        gridLayout_4->addWidget(label_SEN1, 0, 2, 1, 1);

        lineEdit_SEN1 = new QLineEdit(centralWidget);
        lineEdit_SEN1->setObjectName(QStringLiteral("lineEdit_SEN1"));
        lineEdit_SEN1->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(lineEdit_SEN1, 0, 3, 1, 1);

        label_MotionSt = new QLabel(centralWidget);
        label_MotionSt->setObjectName(QStringLiteral("label_MotionSt"));

        gridLayout_4->addWidget(label_MotionSt, 0, 4, 1, 1);

        lineEdit_MotionSt = new QLineEdit(centralWidget);
        lineEdit_MotionSt->setObjectName(QStringLiteral("lineEdit_MotionSt"));
        lineEdit_MotionSt->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(lineEdit_MotionSt, 0, 5, 1, 1);

        label_Right = new QLabel(centralWidget);
        label_Right->setObjectName(QStringLiteral("label_Right"));

        gridLayout_4->addWidget(label_Right, 1, 0, 1, 1);

        lineEdit_Right = new QLineEdit(centralWidget);
        lineEdit_Right->setObjectName(QStringLiteral("lineEdit_Right"));
        lineEdit_Right->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(lineEdit_Right, 1, 1, 1, 1);

        label_Hall_left = new QLabel(centralWidget);
        label_Hall_left->setObjectName(QStringLiteral("label_Hall_left"));

        gridLayout_4->addWidget(label_Hall_left, 1, 2, 1, 1);

        lineEdit_Hall_L = new QLineEdit(centralWidget);
        lineEdit_Hall_L->setObjectName(QStringLiteral("lineEdit_Hall_L"));
        lineEdit_Hall_L->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(lineEdit_Hall_L, 1, 3, 1, 1);

        label_MotionEs = new QLabel(centralWidget);
        label_MotionEs->setObjectName(QStringLiteral("label_MotionEs"));

        gridLayout_4->addWidget(label_MotionEs, 1, 4, 1, 1);

        lineEdit_MotionEs = new QLineEdit(centralWidget);
        lineEdit_MotionEs->setObjectName(QStringLiteral("lineEdit_MotionEs"));
        lineEdit_MotionEs->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_4->addWidget(lineEdit_MotionEs, 1, 5, 1, 1);

        label_Left = new QLabel(centralWidget);
        label_Left->setObjectName(QStringLiteral("label_Left"));

        gridLayout_4->addWidget(label_Left, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 8, 5, 1, 2);

        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_6, 9, 0, 1, 7);

        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line_8, 0, 1, 3, 6);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 6, 3, 3, 3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelImage = new QLabel(centralWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(labelImage->sizePolicy().hasHeightForWidth());
        labelImage->setSizePolicy(sizePolicy);
        labelImage->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(labelImage);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonNeedImage = new QPushButton(centralWidget);
        pushButtonNeedImage->setObjectName(QStringLiteral("pushButtonNeedImage"));

        horizontalLayout->addWidget(pushButtonNeedImage);

        pushButtonNoImage = new QPushButton(centralWidget);
        pushButtonNoImage->setObjectName(QStringLiteral("pushButtonNoImage"));

        horizontalLayout->addWidget(pushButtonNoImage);

        horizontalSpacer_2 = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_5->addLayout(verticalLayout, 2, 6, 4, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(textBrowser, 3, 0, 1, 2);

        pushButtonConnect = new QPushButton(centralWidget);
        pushButtonConnect->setObjectName(QStringLiteral("pushButtonConnect"));

        gridLayout_2->addWidget(pushButtonConnect, 2, 0, 1, 1);

        labelPort = new QLabel(centralWidget);
        labelPort->setObjectName(QStringLiteral("labelPort"));

        gridLayout_2->addWidget(labelPort, 1, 0, 1, 1);

        labelIP = new QLabel(centralWidget);
        labelIP->setObjectName(QStringLiteral("labelIP"));

        gridLayout_2->addWidget(labelIP, 0, 0, 1, 1);

        lineEditIP = new QLineEdit(centralWidget);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        gridLayout_2->addWidget(lineEditIP, 0, 1, 1, 1);

        pushButtonClear = new QPushButton(centralWidget);
        pushButtonClear->setObjectName(QStringLiteral("pushButtonClear"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(pushButtonClear->sizePolicy().hasHeightForWidth());
        pushButtonClear->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButtonClear, 5, 0, 1, 1);

        lineEditPort = new QLineEdit(centralWidget);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));

        gridLayout_2->addWidget(lineEditPort, 1, 1, 1, 1);

        pushButtonDisconnect = new QPushButton(centralWidget);
        pushButtonDisconnect->setObjectName(QStringLiteral("pushButtonDisconnect"));

        gridLayout_2->addWidget(pushButtonDisconnect, 2, 1, 1, 1);

        pushButtonSelfClean = new QPushButton(centralWidget);
        pushButtonSelfClean->setObjectName(QStringLiteral("pushButtonSelfClean"));

        gridLayout_2->addWidget(pushButtonSelfClean, 6, 0, 1, 1);

        pushButtonControlMode = new QPushButton(centralWidget);
        pushButtonControlMode->setObjectName(QStringLiteral("pushButtonControlMode"));
        sizePolicy1.setHeightForWidth(pushButtonControlMode->sizePolicy().hasHeightForWidth());
        pushButtonControlMode->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(pushButtonControlMode, 6, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 5, 1, 1, 1);

        Client->setCentralWidget(centralWidget);
        line_3->raise();
        line_4->raise();
        line->raise();
        line_5->raise();
        line_6->raise();
        line_7->raise();
        line_8->raise();

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", Q_NULLPTR));
        actionConnect->setText(QApplication::translate("Client", "Connect", Q_NULLPTR));
        actionConnect_2->setText(QApplication::translate("Client", "Connect", Q_NULLPTR));
        pushButtonBackward->setText(QApplication::translate("Client", "Backward", Q_NULLPTR));
        pushButtonLeft->setText(QApplication::translate("Client", "Left", Q_NULLPTR));
        pushButtonRight->setText(QApplication::translate("Client", "Right", Q_NULLPTR));
        pushButtonForward->setText(QApplication::translate("Client", "Forward", Q_NULLPTR));
        labelTheta->setText(QApplication::translate("Client", "Theta", Q_NULLPTR));
        labelY->setText(QApplication::translate("Client", "Y", Q_NULLPTR));
        labelX->setText(QApplication::translate("Client", "X", Q_NULLPTR));
        label_SEN1->setText(QApplication::translate("Client", "SEN1", Q_NULLPTR));
        label_MotionSt->setText(QApplication::translate("Client", "MotionSt", Q_NULLPTR));
        label_Right->setText(QApplication::translate("Client", "Right", Q_NULLPTR));
        label_Hall_left->setText(QApplication::translate("Client", "Hall_L", Q_NULLPTR));
        label_MotionEs->setText(QApplication::translate("Client", "MotionEs", Q_NULLPTR));
        label_Left->setText(QApplication::translate("Client", "Left", Q_NULLPTR));
        labelImage->setText(QString());
        pushButtonNeedImage->setText(QApplication::translate("Client", "Need Image", Q_NULLPTR));
        pushButtonNoImage->setText(QApplication::translate("Client", "No Image", Q_NULLPTR));
        pushButtonConnect->setText(QApplication::translate("Client", "Connect", Q_NULLPTR));
        labelPort->setText(QApplication::translate("Client", "Port Number", Q_NULLPTR));
        labelIP->setText(QApplication::translate("Client", "IP Address", Q_NULLPTR));
        pushButtonClear->setText(QApplication::translate("Client", "Clear", Q_NULLPTR));
        pushButtonDisconnect->setText(QApplication::translate("Client", "Disconnect", Q_NULLPTR));
        pushButtonSelfClean->setText(QApplication::translate("Client", "Self Clean Mode", Q_NULLPTR));
        pushButtonControlMode->setText(QApplication::translate("Client", "Control Mode", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
