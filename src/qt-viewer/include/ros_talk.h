#ifndef __ROS_TALK_H__
#define __ROS_TALK_H__

#include <string>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <ctime>
#include <jsoncpp/json/json.h>
#include <pwd.h>
#include <vector>
#include "common_ui_type.h"

#include <QObject>
#include <QThread>
#include <QMap>
#include <QString>

#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/int8.hpp>
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "sys_msgs/msg/dect_data.hpp"
#include "sys_msgs/msg/point.hpp"
#include "sys_msgs/msg/point_array.hpp"
#include "sys_msgs/msg/to_d_area.hpp"
#include "sys_msgs/msg/general_table_array.hpp"
#include <std_msgs/msg/int8_multi_array.hpp>

#include <QLabel>
#include <QImage>
#include <QLineEdit>
#include <opencv2/core/core.hpp>
#include "cv_bridge/cv_bridge.h"
#include <pcl_conversions/pcl_conversions.h>

struct SendObjectInf
{
    unsigned int id;
    unsigned int classify;

    std::string kind_risk;

    double center_x;
    double center_y;
    double center_z;

    float length;
    float width;
    float height;

    float speed;
    float heading;
    float distance;
};

// 最终传出结构体
struct DectData
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr Origin_Cloud; // 原始点云
    std::vector<SendObjectInf> Data_vec;                  // 检测出的目标物体数据
    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> ObjCloud_vec;

    DectData()
    {
        Origin_Cloud.reset(new pcl::PointCloud<pcl::PointXYZRGBA>);
        // ObjCloud_vec->reset(new pcl::PointCloud<pcl::PointXYZRGBA>);
    }
};

Q_DECLARE_METATYPE(DectData) // 要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***

class RosTalk : public QThread
{
    Q_OBJECT
public:
    RosTalk();
    ~RosTalk() override;
    void init();

private:
    void load_env_param();

    // 回调函数声明
    void timerCallback();
    void pubParameterServer();
    void parameterServerCallback(const std_msgs::msg::String::SharedPtr msg);
    void camera_drive_imgae_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    void lidar_driver_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
    void log_event(const QMultiMap<QString, QString> &msg);
    void log_callback(const std_msgs::msg::String::SharedPtr &msg);
    void decct_data_callback(const sys_msgs::msg::DectData::SharedPtr &msg);
    void to_d_area_Callback(const sys_msgs::msg::ToDArea::SharedPtr &msg);
    void monitor_node_callback(const sys_msgs::msg::GeneralTableArray::SharedPtr &msg);
    void monitor_sensor_callback(const sys_msgs::msg::GeneralTableArray::SharedPtr &msg);

protected:
    void run() override;

private:
    // 订阅
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr parameter_server_sub;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_drive_sub;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_drive_sub;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr log_sub;
    rclcpp::Subscription<sys_msgs::msg::DectData>::SharedPtr algorithm_data_sub;
    rclcpp::Subscription<sys_msgs::msg::ToDArea>::SharedPtr to_d_area_sub;
    rclcpp::Subscription<sys_msgs::msg::GeneralTableArray>::SharedPtr monitor_node_sub_;
    rclcpp::Subscription<sys_msgs::msg::GeneralTableArray>::SharedPtr monitor_sensor_sub_;

    // 发布
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr parameter_server_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr save_param_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr log_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr heart_keeper_pub_;
    rclcpp::Publisher<sys_msgs::msg::ToDArea>::SharedPtr to_d_area_pub_;
    rclcpp::Publisher<std_msgs::msg::Int8MultiArray>::SharedPtr save_point_cloud_pub_;
    // rclcpp::Publisher<sys_msgs::msg::GeneralTableArray>::SharedPtr save_point_cloud_pub_;

    // 定时器
    rclcpp::TimerBase::SharedPtr timer_;

    // 参数服务
    Json::Value parameter_server_;

    std::shared_ptr<rclcpp::Node> node;
    AlarmStatus alarm_status;

signals:
    void emitTopicParams(QString);
    void emit_camera_drive(QPixmap);
    void emit_lidar_drive(PointCloudTPtr);
    void emit_show_log(QString);
    void emit_decct_data(DectData);
    void emit_alarm_data(AlarmStatus);
    void ros_to_qt_area_points(QList<QList<PointT>>);

private slots:
    void saveTopicParams(QString);
    void saveLog(QMultiMap<QString, QString>);
    void saveLidarDatas(QString);
    void save2dlists(QList<QList<PointT>>);
    void save_point_cloud(int);
    void save_point_backgroud_cloud(int);
};
#endif
