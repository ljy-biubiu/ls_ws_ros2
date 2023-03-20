#-------------------------------------------------
#
# Project created by QtCreator 2020-06-08T13:59:38
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

CONFIG -= qtquickcompiler

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PortMonitor
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
OBJECTS_DIR = temp/obj
UI_DIR      = temp/ui
DESTDIR     = bin

#QMAKE_CC += -g
#QMAKE_CXX += -g
#QMAKE_LINK += -g
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the JsChatQtation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/SDK/lib\'"
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/SDK/HCNetSDKCom\'"

SOURCES += \
        src/main.cpp \
        src/maindeal.cpp

HEADERS +=  \
    include/maindeal.h


include("./UI/ui.pri")
include("./DRIVER/driver.pri")
include("./PROTOCOL/protocol.pri")
include("./MSGSERIVE/msg_service.pri")
include("./ALGORITHM/algorithm.pri")
include("./LOG/my_log.pri")


DISTFILES += \
    LOG/my_log.pri \
    PROTOCOL/protocol.pri \
    UI/ui.pri \
    DRIVER/driver.pri \
    MSGSERIVE/msg_service.pri \
    MSGSERIVE/algorithm.pri


#Eigen
#INCLUDEPATH += /usr/include/eigen3

INCLUDEPATH += /usr/local/include/pcl-1.9
LIBS += /usr/local/lib/libpcl_*.so

INCLUDEPATH += /usr/opencv-3.4.8/include/
LIBS += /usr/opencv-3.4.8/lib/libopencv_*

INCLUDEPATH += /usr/local/include/vtk-8.2
LIBS += /usr/local/lib/libvtk*.so

INCLUDEPATH += /usr/include/jsoncpp
LIBS += /usr/lib/x86_64-linux-gnu/libjsoncpp*.so


INCLUDEPATH += $$PWD/.

#Boost
INCLUDEPATH += /usr/local/include/boost
LIBS += /usr/local/lib/libboost_*


LIBS +=/usr/lib/x86_64-linux-gnu/libalibabacloud-sdk-dysmsapi.so
LIBS +=/usr/lib/x86_64-linux-gnu/libalibabacloud-sdk-core.so
LIBS += /usr/lib/x86_64-linux-gnu/libcurl.so.4

LIBS += -ldl


INCLUDEPATH += $$PWD/include/.
DEPENDPATH += $$PWD/.
QMAKE_LFLAGS += -no-pie #生成可双击打开的可执行文件

