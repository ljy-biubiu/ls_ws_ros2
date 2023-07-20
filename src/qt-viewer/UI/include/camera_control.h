#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#include <QWidget>
#include "common_ui_type.h"

namespace Ui {
class CameraControl;
}


class CameraControl : public QWidget
{
    Q_OBJECT

public:
    explicit CameraControl(QWidget *parent = nullptr);
    ~CameraControl();

    int control_cmd;

signals:
    void emitCameraControlCmd(int);

private slots:
    void toolButton_top_click();

    void toolButton_left();

    void toolButton_right();

    void toolButton_buttom();

    void toolButton_zoom_in();

    void toolButton_zoom_out();

    void toolButton_focus_in();

    void toolButton_focus_out();

    void toolButton_iris_in();

    void toolButton_iris_out();


    void toolButton_top_click_release();

    void toolButton_left_release();

    void toolButton_right_release();

    void toolButton_buttom_release();

    void toolButton_zoom_in_release();

    void toolButton_zoom_out_release();

    void toolButton_focus_in_release();

    void toolButton_focus_out_release();

    void toolButton_iris_in_release();

    void toolButton_iris_out_release();



private:
    Ui::CameraControl *ui;


};

#endif // CAMERA_CONTROL_H
