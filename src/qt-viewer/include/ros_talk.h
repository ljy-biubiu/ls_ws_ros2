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

#include <QLabel>
#include <QImage>
#include <opencv2/core/core.hpp>
#include "cv_bridge/cv_bridge.h"
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::PointCloud<PointT>::Ptr PointCloudTPtr;

struct TopicState
{
  std::string name;
  std::string topic;
  std::string type;
  float timeout{0};
  bool enable{false};
  int mul{0};
};

enum StateType
{
  ERROR = -1,   // 错误，开机未读取到数据
  NORMAL = 0,   // 正常
  OVERTIME = 1, // 超时
};

class StateBase
{
  struct StateTimer
  {
    explicit StateTimer(rclcpp::Node::SharedPtr node_) : node__(node_)
    {
      // node__ = rclcpp::Node::make_shared("ljy");
    }
    // rclcpp::Time start_time = clock.now();

    void set()
    {
      state = true;
      start_timer = node__->now().seconds();
    }

    [[nodiscard]] double getDuration(double now) const
    {
      return now - start_timer;
    }
    bool state{false};
    double start_timer{0};
    rclcpp::Node::SharedPtr node__;
  };

public:
  explicit StateBase(rclcpp::Node::SharedPtr node)
      : node_(node), timer_(node) {}
  virtual ~StateBase() {}
  virtual void init() = 0;
  virtual int getState() = 0;
  virtual std::string getTopic() = 0;
  virtual std::string getName() = 0;
  virtual std::string getType() = 0;
  virtual float getTimeout() = 0;
  virtual bool getEnable() = 0;
  virtual void monitor_exist_lidar(const std::string &str) = 0;

protected:
  rclcpp::Node::SharedPtr node_;
  StateTimer timer_;
};

template <class T>
class NodeState : public StateBase
{
  using DataTypeSharedPtr = typename T::SharedPtr;
  using SubscriptionType = typename rclcpp::Subscription<T>::SharedPtr;

public:
  NodeState(rclcpp::Node::SharedPtr node, TopicState topic_state)
      : StateBase(node), topic_state_(topic_state)
  {
    init();
  }
  ~NodeState() override = default;

public:
  virtual void init() override;
  virtual int getState() override;
  virtual std::string getTopic() override;
  virtual std::string getName() override;
  std::string getType() override;
  virtual float getTimeout() override;
  virtual bool getEnable() override;
  virtual void monitor_exist_lidar(const std::string &str) override;
  void callback(const DataTypeSharedPtr msg);

private:
  SubscriptionType sub_;
  std::string topic_name_;
  TopicState topic_state_;
};

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

  void load_lidars_config(std::vector<TopicState> &vec, const std::string &name);
  void init_lidars_datas(std::vector<TopicState> &vec, std::vector<std::shared_ptr<StateBase>> &vec2);

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

  //std::shared_ptr<rclcpp::Node> node;
  rclcpp::Node::SharedPtr node;

  std::vector<TopicState> lidar_topics_names_;
  std::vector<std::shared_ptr<StateBase>> lidar_datas_;

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
