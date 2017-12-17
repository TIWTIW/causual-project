#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T10:19:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        client.cpp \
    test_ToClient.pb.cc \
    test_ToServer.pb.cc

HEADERS += \
        client.h \
    test_ToClient.pb.h \
    test_ToServer.pb.h

FORMS += \
        client.ui


LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lprotobuf

INCLUDEPATH += $$PWD/../../../../../../opt/FriendlyARM/toolschain/4.5.1/include
DEPENDPATH += $$PWD/../../../../../../opt/FriendlyARM/toolschain/4.5.1/include
PRE_TARGETDEPS += $$PWD/../../../../../../opt/FriendlyARM/toolschain/4.5.1/lib/libprotobuf.a
