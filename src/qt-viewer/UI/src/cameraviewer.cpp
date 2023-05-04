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
    ui->verticalLayout_2->addWidget(my_label);
//    this->show_widget;
//    ui->show_widget->
//    setStyleSheet( "QWidget{ background-color : rgba( 160, 160, 160, 255); border-radius : 7px;  }" );
//    QLabel *label = new QLabel(this);
//    QHBoxLayout *layout = new QHBoxLayout();
//    label->setText("Random String");
//    layout->addWidget(label);
//    setLayout(layout);
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
//    //ui->my_label2->autoFillBackground();
//    QImage image_tmp = MatToQImage(msg);
//    image_tmp = image_tmp.scaled(my_label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//    my_label->setPixmap(QPixmap::fromImage(image_tmp));
}

void CameraViewer::setCameraMat(QPixmap msg)
{
//    msg.scaled(600,300);
    my_label->setPixmap(msg.scaled(600,300)); //16/9
}

CameraViewer::~CameraViewer()
{
    delete ui;
}
