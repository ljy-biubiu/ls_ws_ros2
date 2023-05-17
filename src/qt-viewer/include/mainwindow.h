#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ros_talk.h"

#include <QMainWindow>
#include "maintitlebar.h"
#include "imageWidget.h"
#include "addlidar.h"
#include "paintarea.h"
#include "setroi.h"
#include "diary.h"
#include "alarm.h"
#include "cameraviewer.h"
#include "webui.h"
#include "tasklistui.h"
#include "common_ui_type.h"


// Visualization Toolkit (VTK)
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>
#include "vtkGenericOpenGLRenderWindow.h"

// pcl
#include <pcl/io/ifs_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/vtk.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/point_cloud_geometry_handlers.h>

#include <QLabel>
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QHBoxLayout>
#include <QWidget>
#include <QApplication>

#include <QSplashScreen>
#include <QSharedPointer>

#include <QMetaType> //自定义参数类型的头文件----***



Q_DECLARE_METATYPE(PointCloudTPtr) // 要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***
Q_DECLARE_METATYPE(AlarmStatus) // 要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QApplication *my_app_, QWidget *parent = nullptr);
    ~MainWindow();

    void updatePointCould();

    QSplashScreen *getqSplashScreen()
    {
        return screen;
    }

private:
    RosTalk *ros_talk;
    QApplication *my_app;
    PaintArea *paint_area;
    SetROI *setROI;
    CameraViewer *camera_viewer;
    CameraViewer *camera_viewer2;
    QVTKOpenGLNativeWidget *qvtkOpenglNativeWidget;
    WebUi *web_ui;
    MainTitleBar *main_title_bar;
    QTimer *my_timer;
    AddLidar *add_lidar;
    //    EchartWindow *echartWindow;
    Diary *diary;
    Alarm *alarm;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

private:
    CameraViewer *getCameraWidget();
    void initMenu();
    void initToolBar();
    void initConnect();
    void createActions();
    void mainLayOut();
    void initPointCShow();
    void initObeject();

    void updateAlgPointCould();
    void updateCameraImage();
    void paint_area_2setROI();

    // void initCameraDriveShow();

    void mainEventCallback();
    void deleteItem(QLayout *layout);

private:
    ImageWidget *frameWidgetLidar;
    ImageWidget *frameWidgetCamera;
    ImageWidget *mainImageWidget;

    QWidget *main_widget;
    QWidget *right_camera_widget;
    QWidget *right_data_widget;
    QWidget *right_table_widget;
    QWidget* camera_block_l;
    QWidget* camera_block_r;
    QWidget* childWidget;

    // layout
    QVBoxLayout *body_frame_layout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *headLayout;
    QHBoxLayout *body_layout;
    QHBoxLayout *left_body_layout;
    QVBoxLayout *right_body_layout;
    QHBoxLayout *layout;
    QHBoxLayout *right_camera_layout;
    QHBoxLayout *right_data_layout;
    QHBoxLayout *right_table_layout;
    QVBoxLayout *vtkLayout;
    QVBoxLayout *imageWidget_layout;
    QVBoxLayout *paramsListLayout;
    QVBoxLayout *cameraLayout;

    QLabel *imageLabel;
    QScrollArea *scrollAera;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QAction *view_mode;
    QAction *view1_mode;
    QAction *view2_mode;
    QAction *param_set;
    QAction *lidar_area_set;
    QAction *save_point_cloud;
    QAction *svae_background_pont_cloud;
    QAction *qt_version;

    QSplashScreen *screen;
    TaskListUi* task_list_ui;

private slots:
    void view_mode_Action();
    void view_mode1_Action();
    void view_mode2_Action();
    void param_set_Action();
    void lidar_area_set_Action();
    void getAreaDatas();
    void params_set(QString);
    void receive_lidar_driver(PointCloudTPtr);
    void show_dect_data(DectData msg);
    void setAreaDatas(QList<QList<PointT>> msg);
    void save_point_backgourd_cloud_set_Action();
    void save_point_cloud_set_Action();

    // void show_log(QString);

signals:
    void emitTopicSetParams(QString);
    void uploadLog(QMultiMap<QString, QString>);
    void emitTopicParams(QString);
    void emit2dlists(QList<QList<PointT>>);
    void emit_save_point_cloud(int);
    void emit_save_point_backgourd_cloud(int);
};
#endif // MAINWINDOW_H
