#include "ros_talk.h"

//--------------------------------------
using std::placeholders::_1;
using namespace std::chrono_literals;
//-----------------------------------------
RosTalk::RosTalk() { init(); }

RosTalk::~RosTalk() = default;

void RosTalk::init()
{

  int argc = 0;
  char **argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_viewer");

  RCLCPP_INFO(node->get_logger(), " qt_viewer_node initialized ");
  // RCLCPP_INFO_STREAM(this->get_logger(), "qtviewer init");
  //  发布话题
  //  parameter_server_pub_ = this->create_publisher<std_msgs::msg::String>(
  //      "/params_config/parameter_server", rclcpp::QoS{1}.transient_local());

  parameter_server_pub_ =
      node->create_publisher<std_msgs::msg::String>("/params_config/parameter_server", rclcpp::QoS{1}.transient_local());

  save_param_pub_ =
      node->create_publisher<std_msgs::msg::String>("/params_config/save_params", rclcpp::QoS{1}.transient_local());

  // 订阅话题
  // parameter_server_sub = this->create_subscription<std_msgs::msg::String>(
  //     "/params_config/parameter_server",
  //     rclcpp::QoS{10}.transient_local(),
  //     [this](const std_msgs::msg::String::SharedPtr msg)
  //     { parameterServerCallback(msg); });
  // parameter_server_sub = node->create_subscription<std_msgs::msg::String>("ros2_qt_demo_publish", rclcpp::QoS{10}.transient_local(), std::bind(&RosTalk::parameterServerCallback, this, std::placeholders::_1));

  parameter_server_sub = node->create_subscription<std_msgs::msg::String>(
      "/params_config/parameter_server",
      rclcpp::QoS{1}.transient_local(),
      [this](const std_msgs::msg::String::SharedPtr msg)
      { parameterServerCallback(msg); });

  camera_drive_sub = node->create_subscription<sensor_msgs::msg::Image>(
      "/carama_driver/imgae",
      rclcpp::QoS{1}.transient_local(),
      [this](const sensor_msgs::msg::Image::SharedPtr msg)
      { camera_drive_imgae_callback(msg); });

  lidar_drive_sub = node->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/lidar_driver/lidar_driver",
      rclcpp::QoS{1}.transient_local(),
      [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg)
      { lidar_driver_callback(msg); });

  log_sub = node->create_subscription<std_msgs::msg::String>(
      "/log_sys/log",
      rclcpp::QoS{1}.transient_local(),
      [this](const std_msgs::msg::String::SharedPtr msg)
      { log_callback(msg); });

  log_pub_ = node->create_publisher<std_msgs::msg::String>(
      "/log_sys/log", rclcpp::QoS{1}.transient_local());

  heart_keeper_pub_ = node->create_publisher<std_msgs::msg::String>(
      "/qt_viewer/heart_keep", rclcpp::QoS{1}.transient_local());

  // ros2 topic echo --qos-profile services_default --qos-durability
  // transient_local  /cti/error_status/set 定时器
  timer_ =
      node->create_wall_timer(100ms, std::bind(&RosTalk::timerCallback, this));

  this->start();
}

void RosTalk::run()
{

  sys_msgs::msg::DectData a;
  sys_msgs::msg::DectectInf b;
  a.data_vec.push_back(b);

  for(auto v : a.data_vec)
  {
    v.obj_inf.x = 0;
  }

  // 
  std_msgs::msg::String pub_msg;
  pub_msg.data = "";
  rclcpp::WallRate loop_rate(1000);
  while (rclcpp::ok())
  {
    // pub_msg.data = "ss";
    // parameter_server_pub_->publish(pub_msg);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
}
// void rclcomm::recv_callback(const std_msgs::msg::Int32::SharedPtr msg)
// {
//   //  RCLCPP_INFO(node->get_logger(), "I heard: '%d'", msg->data);
//   emitTopicData("I head from ros2_qt_demo_publish:" + QString::fromStdString(std::to_string(msg->data)));
// }

void RosTalk::log_callback(const std_msgs::msg::String::SharedPtr &msg)
{
  // emit emit_show_log( QString::fromStdString(msg->data));
}

void RosTalk::lidar_driver_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  auto cloud =
      boost::make_shared<PointCloudT>();
  pcl::fromROSMsg(*msg, *cloud);
  emit emit_lidar_drive(cloud);
  // std::cout << "wwwwwwwwwww" << std::endl;
  //  RCLCPP_INFO(this->get_logger(), "points_size(%d,%d)", msg->height, msg->width);
};

// PointCloudTPtr

void RosTalk::camera_drive_imgae_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  QImage::Format format;
  format = QImage::Format_RGB888;
  cv_bridge::CvImagePtr cv_ptr;
  cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
  uchar *uchar_iamge_data = cv_ptr->image.data;
  QPixmap showImage = QPixmap::fromImage(QImage(uchar_iamge_data, msg->width, msg->height, msg->step, format));

  emit emit_camera_drive(showImage);
}

void RosTalk::parameterServerCallback(const std_msgs::msg::String::SharedPtr msg)
{
  // std::cout << "parameter_server_callback: " << msg->data << std::endl;
  emit emitTopicParams(QString::fromStdString(msg->data));
  // emitTopicData("I head from ros2_qt_demo_publish:" + QString::fromStdString(std::to_string(msg->data)));
  // std::cout<<"I head from ros2_qt_demo"<<std::endl;
}

void RosTalk::saveTopicParams(QString msg)
{
  std_msgs::msg::String str;
  str.data = msg.toStdString();
  save_param_pub_->publish(str);
  // std::cout<<" ============================================ s"<<std::endl;
}

void RosTalk::saveLog(QMultiMap<QString, QString> msg)
{
  log_event(msg);
}

void RosTalk::log_event(const QMultiMap<QString, QString> &msg)
{

  for (auto i : msg.keys())
  {
    if (i == "INFO")
    {
      RCLCPP_INFO_STREAM(node->get_logger(), msg.value(i).toStdString());
    }
    if (i == "ERROR")
    {
      RCLCPP_ERROR_STREAM(node->get_logger(), msg.value(i).toStdString());
      std_msgs::msg::String data;
      data.data = msg.value(i).toStdString();
      log_pub_->publish(data);
    }
    if (i == "WARN")
    {
      RCLCPP_WARN_STREAM(node->get_logger(), msg.value(i).toStdString());
    }
  }
}

//-------------- timer ---------------------------------------
void RosTalk::timerCallback()
{
  heart_keeper_pub_->publish(std_msgs::msg::String());
  // if (this->lidar_driver_interface_)
  // {
  //   PointCloudTPtr msg =
  //       boost::make_shared<PointCloudT>();
  //   sensor_msgs::msg::PointCloud2 ros2_msg;
  //   if (!lidar_driver_interface_->get_lidar_data(msg))
  //     return;
  //   pcl::toROSMsg(*msg, ros2_msg);

  //   lidar_driver_pub_->publish(ros2_msg);
  //   //std::cout<<"sssssssssssssss"<<std::endl;
  // }
}