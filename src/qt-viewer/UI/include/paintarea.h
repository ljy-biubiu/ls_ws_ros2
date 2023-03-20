#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <opencv2/opencv.hpp>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/common/common.h>
#include <QVTKWidget.h>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>
#include <QLabel>
#include <QList>
#include <QCursor>
#include <math.h>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>
#include <QtMath>
#include <QPainterPath>
#include <QMessageBox>
#include <common.h>
//#include <opencv.hpp>
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
#define PAINT_SIZE 6000

extern bool flagAllCloud;
extern bool flagPartCloud;


class PaintArea : public QWidget
{
    Q_OBJECT


public:
    PaintArea();
    float                               zoom;
    QScrollArea                         *scroll;
    bool                                move;
    bool                                paint;
    bool                                leftsel;
    bool                                moveStart;
    bool                                dragPoint;
    bool                                dragPropor;
    bool                                removePoint;
    bool                                addPoint;
    int                                 selectPoint;
    QPoint                              mvStartPt;
    QMap<int,lidar>                     LidarMap;
    lidar                               LidarInstance;
    int                                 curPos;        //当前雷达序列
    int                                 curPolygonPos; //当前轮廓序列
    int                                 warning_type[3];

    int col =20;
    float Radius = 100;
    QPointF mousemovepoint;


    float zmax[AREAS];
    float zmin[AREAS];

    Area area[AREAS];

    typedef pcl::PointXYZRGBA PointT;
    typedef pcl::PointCloud<PointT> PointCloudT;
    typedef pcl::PointCloud<PointT>::Ptr PointCloudTPtr;


    PointCloudTPtr tCloud;
    PointCloudTPtr xCloud;
    std::vector<lidarCloud> lidarcloud;

    pcl::PointCloud<Box_Cloud>::Ptr box_cloud[AREAS];
    QList<PointT> Area2d_point[AREAS];

    void paintEvent(QPaintEvent *);
    void drawArea(QPainter &p, int index);
    void wheelEvent(QWheelEvent*event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event); //键盘按下事件
    QList<PointT> getIndexPoints(int index);
    void setPaintPoint(QList<QPointF> &tmp);
    void updataPointFunc();
    PointT  areapoint2d_transform(PointT pt);//绘图坐标系转换到真实坐标系
    void areaList_T_transform();
public slots:
    void setPaintSlot(QList<QPointF> tmp,int index);
    void setSplice(int index);
    void updataPoint(int index,  QList<PointT> ps);
    void UpdateArea_index(int index);

    void setCentralArea(const int& x,const int& y);
    void setAreaSize(int radius);


signals:
    void sigShowData();

    void sigShowData(QList<pcl::PointCloud<Box_Cloud>::Ptr>);


private:
    QPointF                             centerPoint;
    int area_index =0;
    bool                                spliceflag;
};

#endif // PAINTAREA_H
