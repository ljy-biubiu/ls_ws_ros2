#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <QDebug>
#include "common_ui_type.h"

namespace Ui
{
class CameraViewer;
}

class CameraViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CameraViewer(int num,QWidget *parent = nullptr);
    ~CameraViewer();

    void setCameraMat(cv::Mat &msg);
    QImage MatToQImage(cv::Mat &mtx);

    void setInputNum(const int dat)
    {
        input_num  = dat;
    }

private:
    Ui::CameraViewer *ui;
    QLabel *my_label;
    QWidget *my_widget;
    QImage *my_image;
    QVector<QLabel*> my_labels;
    int camera_show_mode{0};
    int num_{CameraViewNub::CameraViewFir};
    int input_num{0};

private slots:
    void setCameraMat(QPixmap,QString);
    void setViewerMode(int);
};

#endif // CAMERAVIEWER_H
