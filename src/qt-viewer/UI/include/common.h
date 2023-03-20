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
#define AREAS 3
#define L_Range 10000
#define Coord_proportion (L_Range * 2.0 / 1000)

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::PointCloud<PointT>::Ptr PointCloudTPtr;

struct war
{
    pcl::PointXYZ point;
    int dist;
    float angle;
    int index;
};

struct tableRow
{
    QTableWidgetItem itemx;
    QTableWidgetItem itemy;
    QTableWidgetItem itemz;
};

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


struct point_angle
{
    Box_Cloud point;
    float angle;
    float r;
};

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

struct point_data
{
    QList<QPointF> out;
    QList<QPointF> in[3];
    QList<QPointF> clust_in;
    int lidarIndex;
};

struct data_set
{
    QPointF point;
    bool visited;
    bool isKey;
    int dpId;
    int cluterID;
    QList<int> arrivalPointID;
};
struct point_column
{
    float startang;
    float endang;
    float r;
    float x;
    float y;
    float z_min;
    float z_max;
};


struct LidarData
{
    std::vector<float> angle;
    std::vector<std::vector<int>> distance;
    std::vector<std::vector<int>> intensity;
    std::vector<std::vector<int>> LaserID;
};

struct LidarDataCHXXX
{
    std::vector<std::vector<float>> angle;
    std::vector<std::vector<float>> distance;
    std::vector<std::vector<int>> intensity;
};

struct LidarDataLS128S1
{
    std::vector<std::vector<float>> angle_h; // 水平角度储存
    std::vector<std::vector<float>> angle_v; // 垂直角度储存
    std::vector<std::vector<float>> distance;
    std::vector<std::vector<int>> intensity;
};

struct LidarC1Data
{
    std::vector<float> angle;
    std::vector<int> distance;
    std::vector<int> intensity;
};

#if 1
struct LidarPara
{
    QString IP;
    int port;
    pcl::PointXYZ base;
    int heart;
    bool connectstate;
};
Q_DECLARE_METATYPE(LidarPara)

struct Boxcloud
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr boxcloud1;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr boxcloud2;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr boxcloud3;
};
#endif
struct lidarCloud
{
    float r;
    float ang;
    float x;
    float y;
    float z;
};
#if 1
struct lidarIntruder
{
    QString ip;
    int port;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tCloud;
    bool war_alarm[3];
};
#endif
Q_DECLARE_METATYPE(lidarIntruder)

#endif // COMMON_H
