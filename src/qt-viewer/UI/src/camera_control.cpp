#include "camera_control.h"
#include "ui_camera_control.h"

CameraControl::CameraControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraControl)
{
    ui->setupUi(this);

    connect(ui->toolButton_top,SIGNAL(pressed()),this,SLOT(toolButton_top_click()));
    connect(ui->toolButton_left,SIGNAL(pressed()),this,SLOT(toolButton_left()));
    connect(ui->toolButton_right,SIGNAL(pressed()),this,SLOT(toolButton_right()));
    connect(ui->toolButton_buttom,SIGNAL(pressed()),this,SLOT(toolButton_buttom()));
    connect(ui->toolButton_zoom_in,SIGNAL(pressed()),this,SLOT(toolButton_zoom_in()));
    connect(ui->toolButton_zoom_out,SIGNAL(pressed()),this,SLOT(toolButton_zoom_out()));
    connect(ui->toolButton_focus_in,SIGNAL(pressed()),this,SLOT(toolButton_focus_in()));
    connect(ui->toolButton_focus_out,SIGNAL(pressed()),this,SLOT(toolButton_focus_out()));
    connect(ui->toolButton_iris_in,SIGNAL(pressed()),this,SLOT(toolButton_iris_in()));
    connect(ui->toolButton_iris_out,SIGNAL(pressed()),this,SLOT(toolButton_iris_out()));

    connect(ui->toolButton_top,SIGNAL(released()),this,SLOT(toolButton_top_click_release()));
    connect(ui->toolButton_left,SIGNAL(released()),this,SLOT(toolButton_left_release()));
    connect(ui->toolButton_right,SIGNAL(released()),this,SLOT(toolButton_right_release()));
    connect(ui->toolButton_buttom,SIGNAL(released()),this,SLOT(toolButton_buttom_release()));
    connect(ui->toolButton_zoom_in,SIGNAL(released()),this,SLOT(toolButton_zoom_in_release()));
    connect(ui->toolButton_zoom_out,SIGNAL(released()),this,SLOT(toolButton_zoom_out_release()));
    connect(ui->toolButton_focus_in,SIGNAL(released()),this,SLOT(toolButton_focus_in_release()));
    connect(ui->toolButton_focus_out,SIGNAL(released()),this,SLOT(toolButton_focus_out_release()));
    connect(ui->toolButton_iris_in,SIGNAL(released()),this,SLOT(toolButton_iris_in_release()));
    connect(ui->toolButton_iris_out,SIGNAL(released()),this,SLOT(toolButton_iris_out_release()));
}

CameraControl::~CameraControl()
{
    delete ui;
}

#include <qdebug.h>


//////////////////////////////////////////////////////////////////////////

void CameraControl::toolButton_top_click()
{
    control_cmd = CameraControlEnum::CameraControlUpOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_left()
{
    control_cmd = CameraControlEnum::CameraControlLeftOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_right()
{
    control_cmd = CameraControlEnum::CameraControlRightOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_buttom()
{
    control_cmd = CameraControlEnum::CameraControlButtomOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_zoom_in()
{
    control_cmd = CameraControlEnum::CameraControlZoomInOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_zoom_out()
{
    control_cmd = CameraControlEnum::CameraControlZoomOutOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_focus_in()
{
    control_cmd = CameraControlEnum::CameraControlFucosInOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_focus_out()
{
    control_cmd = CameraControlEnum::CameraControlFuconsOutOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_iris_in()
{
    control_cmd = CameraControlEnum::CameraControlIrisInOn;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_iris_out()
{
    control_cmd = CameraControlEnum::CameraControlIrisOutOn;
    emit emitCameraControlCmd(control_cmd);
}




//////////////////

void CameraControl::toolButton_top_click_release()
{
    control_cmd = CameraControlEnum::CameraControlUpOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_left_release()
{
    control_cmd = CameraControlEnum::CameraControlLeftOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_right_release()
{
    control_cmd = CameraControlEnum::CameraControlRightOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_buttom_release()
{
    control_cmd = CameraControlEnum::CameraControlButtomOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_zoom_in_release()
{
    control_cmd = CameraControlEnum::CameraControlZoomInOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_zoom_out_release()
{
    control_cmd = CameraControlEnum::CameraControlZoomOutOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_focus_in_release()
{
    control_cmd = CameraControlEnum::CameraControlFucosInOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_focus_out_release()
{
    control_cmd = CameraControlEnum::CameraControlFuconsOutOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_iris_in_release()
{
    control_cmd = CameraControlEnum::CameraControlIrisInOff;
    emit emitCameraControlCmd(control_cmd);
}

void CameraControl::toolButton_iris_out_release()
{
    control_cmd = CameraControlEnum::CameraControlIrisOutOff;
    emit emitCameraControlCmd(control_cmd);
}


