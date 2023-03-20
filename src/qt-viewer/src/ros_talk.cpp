#include "ros_talk.h"

//--------------------------------------
using std::placeholders::_1;
using namespace std::chrono_literals;
//-----------------------------------------

template <class T>
void NodeState<T>::init()
{
  if (!topic_state_.topic.empty())
  {
    sub_ = node_->template create_subscription<T>(
        topic_state_.topic, rclcpp::QoS{1}.best_effort(),
        std::bind(&NodeState::callback, this, std::placeholders::_1));
  }
}

template <class T>
int NodeState<T>::getState()
{
  int stat = StateType::ERROR;

  // if (topic_state_.enable == true)
  // {
  //   if (timer_.state)
  //   {
  //     if (timer_.getDuration(node_->now().seconds()) > topic_state_.timeout)
  //     {
  //       stat = StateType::OVERTIME;
  //     }
  //     else
  //     {
  //       stat = StateType::NORMAL;
  //     }
  //   }
  // }
  // else
  // {
  //   stat = StateType::NORMAL;
  // }

  return stat;
}

template <class T>
std::string NodeState<T>::getTopic()
{
  return topic_state_.topic;
}

template <class T>
float NodeState<T>::getTimeout()
{
  return topic_state_.timeout;
}

template <class T>
void NodeState<T>::callback(const DataTypeSharedPtr msg)
{
  // timer_.set();
}

template <class T>
void NodeState<T>::monitor_exist_lidar(const std::string &str)
{
}

template <class T>
std::string NodeState<T>::getName()
{
  return topic_state_.topic;
}

template <class T>
std::string NodeState<T>::getType()
{
  return topic_state_.topic;
}

template <class T>
bool NodeState<T>::getEnable()
{
  return true;
}

//-----------------------------------------
RosTalk::RosTalk() { init(); }

RosTalk::~RosTalk() = default;

void RosTalk::init()
{

  int argc = 0;
  char **argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("qt_viewer");
  // node = rclcpp::create_node("qt_viewer");

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
      "/lidar_driver/lslidar_point_cloud_1",
      rclcpp::QoS{1}.best_effort(),
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

  load_lidars_config(lidar_topics_names_, "lidar_datas");
  init_lidars_datas(lidar_topics_names_, lidar_datas_);

  timer_ =
      node->create_wall_timer(100ms, std::bind(&RosTalk::timerCallback, this));
  this->start();
}

void RosTalk::run()
{
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

void RosTalk::init_lidars_datas(std::vector<TopicState> &vec, std::vector<std::shared_ptr<StateBase>> &vec2)
{
  std::shared_ptr<StateBase> ptr;
  for (auto topic : vec)
  {
    if (topic.type == "std_msgs::msg::String")
    {
      ptr = std::make_shared<NodeState<std_msgs::msg::String>>(node, topic);
    }
    else if (topic.type == "sensor_msgs::msg::PointCloud2")
    {
      ptr = std::make_shared<NodeState<sensor_msgs::msg::PointCloud2>>(node, topic);
    }
    else if (topic.type == "sensor_msgs::msg::Image")
    {
      ptr = std::make_shared<NodeState<sensor_msgs::msg::Image>>(node, topic);
    }
    vec2.emplace_back(ptr);
  }
}

void RosTalk::load_lidars_config(std::vector<TopicState> &vec, const std::string &name)
{
  Json::Reader reader;
  Json::Value json_value;
  auto read_file_path = ament_index_cpp::get_package_share_directory("qt_viewer") + "/config/lidars_sensor.json";
  RCLCPP_INFO_STREAM(node->get_logger(), "qt_viewer:lidars_sensor.json file path: " << read_file_path);

  std::ifstream ifs(read_file_path, std::ios::binary);

  if (!ifs.is_open())
  {
    RCLCPP_ERROR_STREAM(node->get_logger(), "lidars_sensor file isnt exist");
    return;
  }

  if (reader.parse(ifs, json_value))
  {
    TopicState topic_state;
    auto array_cnt = json_value["Topics"].size();
    for (int i = 0; array_cnt > i; i++)
    {
      topic_state.topic = json_value["Topics"][i]["topic"].asString();
      topic_state.type = json_value["Topics"][i]["type"].asString();
      topic_state.timeout = json_value["Topics"][i]["timeout"].asDouble();
      topic_state.enable = json_value["Topics"][i]["enabled"].asBool();
      vec.push_back(topic_state);
      RCLCPP_INFO_STREAM(node->get_logger(), "lidars_sensor topic:" + json_value["Topics"][i]["topic"].asString());
      RCLCPP_INFO_STREAM(node->get_logger(), "lidars_sensor type:" + json_value["Topics"][i]["type"].asString());
      RCLCPP_INFO_STREAM(node->get_logger(), "lidars_sensor timeout:" + std::to_string(json_value["Topics"][i]["timeout"].asDouble()));
      RCLCPP_INFO_STREAM(node->get_logger(), "lidars_sensor enabled:" + std::to_string(json_value["Topics"][i]["enabled"].asBool()));
    }
  }
}

void RosTalk::log_callback(const std_msgs::msg::String::SharedPtr &msg)
{
  // emit emit_show_log( QString::fromStdString(msg->data));
}

void ros_to_plc_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg, PointCloudTPtr cloudPtr)
{
  // Get the field structure of this point cloud
  int pointBytes = msg->point_step;
  int offset_x;
  int offset_y;
  int offset_z;
  int offset_int;
  for (int f = 0; f < msg->fields.size(); ++f)
  {
    if (msg->fields[f].name == "x")
      offset_x = msg->fields[f].offset;
    if (msg->fields[f].name == "y")
      offset_y = msg->fields[f].offset;
    if (msg->fields[f].name == "z")
    {
      offset_z = msg->fields[f].offset;
    }
    // if (msg->fields[f].name == "intensity")
    // {
    //   offset_int = msg->fields[f].offset;
    // }
  }
  // populate point cloud object
  for (int p = 0; p < msg->width; ++p)
  {
    PointT newPoint;
    newPoint.x = *(float *)(&msg->data[0] + (pointBytes * p) + offset_x);
    newPoint.y = *(float *)(&msg->data[0] + (pointBytes * p) + offset_y);
    newPoint.z = *(float *)(&msg->data[0] + (pointBytes * p) + offset_z);
    // newPoint.intensity = *(unsigned char *)(&msg->data[0] + (pointBytes * p) + offset_int);
    cloudPtr->points.push_back(newPoint);
  }
}

void RosTalk::lidar_driver_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  PointCloudTPtr cloudPtr(new PointCloudT);
  ros_to_plc_pointcloud(msg,cloudPtr);
  emit emit_lidar_drive(cloudPtr);

  // auto cloud =
  //     boost::make_shared<PointCloudT>();
  // pcl::fromROSMsg(*msg, *cloud);
  // emit emit_lidar_drive(cloud);
  //  std::cout << "wwwwwwwwwww" << std::endl;
  // //  RCLCPP_INFO(this->get_logger(), "points_size(%d,%d)", msg->height, msg->width);
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