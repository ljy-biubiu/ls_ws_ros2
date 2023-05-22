#include "cameraviewer.h"
#include "ui_cameraviewer.h"
#include <QImage>
#include <QPixmap>

CameraViewer::CameraViewer(int num, QWidget *parent ) :  QWidget(parent), num_(num),
    ui(new Ui::CameraViewer)
{
    ui->setupUi(this);
    ui->mainWidget_left->setHidden(true);
    ui->mainWidget_right->setHidden(false);

    my_labels.push_back(ui->label_muti_1);
    my_labels.push_back(ui->label_muti_2);
    my_labels.push_back(ui->label_muti_3);
    my_labels.push_back(ui->label_muti_4);

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



void CameraViewer::setViewerMode(int mode_type)
{
    camera_show_mode = mode_type;
    if(mode_type == CameraViewMode::CameraViewSolo)
    {
        ui->mainWidget_left->setHidden(true);
        ui->mainWidget_right->setHidden(false);
    }
    else
    {
        ui->mainWidget_left->setHidden(false);
        ui->mainWidget_right->setHidden(true);
    }

    qDebug()<<"mode_type:"<<mode_type;
}

void CameraViewer::setCameraMat(cv::Mat &msg)
{
}

void CameraViewer::setCameraMat(QPixmap msg ,QString name)
{
    if(this->input_num != this->num_)
        return;

    ui->solo_label->setPixmap(msg.scaled(ui->solo_label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    return;

//    qDebug()<<"name:"<<name;
    if(camera_show_mode == CameraViewMode::CameraViewSolo  )
    {
        if(name == "camera_0")
            ui->solo_label->setPixmap(msg.scaled(ui->solo_label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }
    else if(camera_show_mode == CameraViewMode::CameraViewMuti)
    {
        for(int i{0};my_labels.size()>i ;i++)
        {
            if(name.toStdString() == ("camera_"+std::to_string(i+1)))
                my_labels[i]->setPixmap(msg.scaled(my_labels[i]->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        }
    }
}

CameraViewer::~CameraViewer()
{
    delete ui;
}
