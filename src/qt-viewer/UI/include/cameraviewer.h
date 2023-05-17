#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <opencv2/core/core.hpp>

namespace Ui
{
    class CameraViewer;
}

class CameraViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CameraViewer(QWidget *parent = nullptr);
    ~CameraViewer();

    void setCameraMat(cv::Mat &msg);
    QImage MatToQImage(cv::Mat &mtx);

private:
    Ui::CameraViewer *ui;
    QLabel *my_label;
    QWidget *my_widget;
    QImage *my_image;

private slots:
    void setCameraMat(QPixmap,QString);
};

#endif // CAMERAVIEWER_H
