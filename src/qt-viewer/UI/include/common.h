#ifndef COMMON_H
#define COMMON_H
#include <pcl/point_cloud.h>
#include <pcl/io/io.h>
#include <QTableWidgetItem>
#include <vector>
#include <QVariant>
#include <QMetaType>
#include <QList>
#include <QPointF>
#include <vector>
#include <pcl/io/io.h>
#include <pcl/point_cloud.h>
#include <pcl/Vertices.h>
#define PI 3.14159
#define AREAS 16
#define L_Range 10000
#define Coord_proportion (L_Range * 2.0 / 1000)

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::PointCloud<PointT>::Ptr PointCloudTPtr;

struct Box_Cloud
{
    float x;
    float y;
    float zmin;
    float zmax;
    float r, g, b;
};

struct Area
{
    int id;
    float Obstacle_times;
    float Area_height_down;
    float Area_height_top;
    QList<PointT> Area2D_point;   // 二维绘图坐标
    QList<PointT> Area2D_point_T; // 二维真实坐标
    QList<QList<Box_Cloud>> des_list;       // 三维绘图的坐标
};
Q_DECLARE_METATYPE(Area)


struct lidar
{
    int lidar_Index;
    float lidar_Radius;
    QString lidar_Ip;
    int lidar_port;
    pcl::PointXYZ lidar_base;
    float angle_hor;
    float angle_ver;

    QList<QPointF> Polygon[3]; //
    QList<QPointF> inPolygon;  //
};
Q_DECLARE_METATYPE(lidar)

struct SetData
{

    float setDis;
    float setAng;
    float setXAngle;
    float setYAngle;
    float setZAngle;

    float setBase_X;
    float setBase_Y;
    float setBase_Z;
    float setRadius;

    float clusterTolerance; // 6cm// 这里是60cm
    int minClusterSize;
    int maxClusterSize;
    float resolution;
    float difference_threshold;
    float kValue;
    float distance;
    QString lidarModel;

    float pos_x;
    float pos_y;
    float pos_z;
    float view_x;
    float view_y;
    float view_z;
    float up_x;
    float up_y;
    float up_z;

    std::string ledIp;
    int lidarPort;
    int cloudMapFrame;
    std::string dataAddress;
    std::string deviceId;
    std::string lidarAddress;

    std::string serverAddress;
    int serverPort;
};
Q_DECLARE_METATYPE(SetData)


struct lidarCloud
{
    float r;
    float ang;
    float x;
    float y;
    float z;
};

#endif // COMMON_H
