
#ifndef __ROSTALK_H__
#define __ROSTALK_H__

#include <iostream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/point_cloud.hpp>
#include "cv_bridge/cv_bridge.h"
#include <std_msgs/msg/string.hpp>
#include <memory>

#include <iostream>
#include <fstream>
#include <ctime>
#include <pwd.h>
#include <vector>
#include "websocket.h"

#include "pcl_conversions/pcl_conversions.h"

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

#include "sensor_msgs/msg/image.hpp"

// class Websocket;

class RosTalk : public rclcpp::Node
{

public:
  explicit RosTalk(std::shared_ptr<websocket::Websocket> websocket_)
      : websocket(websocket_), Node("webtalk_node")
  {
    this->init();
  }

  RosTalk();
  ~RosTalk() override;
  void init();
  void read();

private:
  rclcpp::TimerBase::SharedPtr timer_;
  void timerCallback();
  void camera_driver_callback(const sensor_msgs::msg::Image::SharedPtr msg);
  void lidarDatasCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void lidar_driver_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);

  // 订阅
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr
      lidar_datas_sub_;

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr
      camera_driver_sub_;

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr
      lidar_drive_sub;

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr heart_keeper_pub_;

  std::shared_ptr<websocket::Websocket> websocket;
};
#endif
