#include "cameraviewer.h"
#include "ui_cameraviewer.h"
#include <QImage>
#include <QPixmap>

CameraViewer::CameraViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraViewer)
{
    ui->setupUi(this);

    my_label = new QLabel(this);

    my_widget = new QWidget(this);
    my_image = new QImage();

    //ui->my_label2->setGeometry(0,0,1200,900);





//    my_label = new QLabel("圖片",this);
    //ui->my_label2->setFrameShape(QFrame::Box);


    //     QDesktopWidget *screenResolution = QApplication::desktop();
    //     int appWindowWidth = this->geometry().width();
    //     int appWindowHeight = this->geometry().height();

    //     int center_y = screenResolution->height() * (3/16) - appWindowHeight/2;
    //     int center_x = screenResolution->width() * (3/16) - appWindowWidth/2;
    //     //此处的Width,Height不要被修改了(例如除以2了)
    //    //不然看起来不是居中的
    //     setGeometry(center_x, center_y,
    //                 appWindowWidth,appWindowHeight);


    //    my_widget = new QWidget(this);
    //    this->ui->my_layout->addWidget(my_widget);
    //    //设置背景黑色
    //    QPalette palBackGround(this->palette());
    //    palBackGround.setColor(QPalette::Background, QColor(74, 74, 74));
    //    this->setAutoFillBackground(true);
    //    this->setPalette(palBackGround);
    //    this->setStyleSheet("background-color:rgb(74, 74, 74)");



}


QImage CameraViewer::MatToQImage(cv::Mat &mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
    {
        QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Grayscale8);
        return img;
    }
        break;
    case CV_8UC3:
    {
        QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
        break;
    case CV_8UC4:
    {
        QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
        return img;
    }
        break;
    default:
    {
        QImage img;
        return img;
    }
        break;
    }
}


void CameraViewer::setCameraMat(cv::Mat &msg)
{
    //ui->my_label2->autoFillBackground();
    QImage image_tmp = MatToQImage(msg);
    image_tmp = image_tmp.scaled(ui->my_label2->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->my_label2->setPixmap(QPixmap::fromImage(image_tmp));
}

void CameraViewer::setCameraMat(QPixmap msg)
{
    ui->my_label2->setPixmap(msg);
}

CameraViewer::~CameraViewer()
{
    delete ui;
}
