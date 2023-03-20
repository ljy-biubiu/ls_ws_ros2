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


#include <QLabel>
#include <QImage>
#include <opencv2/core/core.hpp>
#include "cv_bridge/cv_bridge.h"
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::PointCloud<PointT>::Ptr PointCloudTPtr;



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

protected:
  void run() override;

private:
  // 订阅
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr parameter_server_sub;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_drive_sub;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_drive_sub;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr log_sub;

  // 发布
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr parameter_server_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr save_param_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr log_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr heart_keeper_pub_;

  // 定时器
  rclcpp::TimerBase::SharedPtr timer_;

  // 参数服务
  Json::Value parameter_server_;

  std::shared_ptr<rclcpp::Node> node;

signals:
  void emitTopicParams(QString);
  void emit_camera_drive(QPixmap);
  void emit_lidar_drive(PointCloudTPtr);
  void emit_show_log(QString);
private slots:
  void saveTopicParams(QString);
  void saveLog(QMultiMap<QString, QString>);
};
#endif
