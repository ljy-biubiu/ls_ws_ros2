#include <iostream>
#include "rostalk.h"
#include "google/protobuf/text_format.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <sys/time.h>
#include "rapidjson/document.h"
// #include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
using namespace std::chrono_literals;

//--------------------------------------
using std::placeholders::_1;
using namespace cv;

std::string Mat2Base64(const cv::Mat &img, std::string imgType);
std::string base64Encode(const unsigned char *Data, int DataByte);

RosTalk::~RosTalk() = default;

void RosTalk::init()
{
  RCLCPP_INFO_STREAM(this->get_logger(), "web server init");

  // ////////////////////////////////////////////////////////// camera test
  // // 读取视频或摄像头
  // // VideoCapture capture(0);

  // std::string source = "rtsp://admin:ls123456@192.168.2.127:554/h265/ch1/main/av_stream"; // 摄像头的rtsp地址
  // VideoCapture capture(source, CAP_FFMPEG);

  // while (true)
  // {
  //   Mat frame;
  //   capture >> frame;
  //   imshow("读取视频", frame);
  //   waitKey(30); // 延时30

  //   static int a{3};
  //   a--;
  //   if (a == 0)
  //   {
  //     a = 1;
  //     std::vector<std::string> data;
  //     cv::Mat shrink;
  //     cv::resize(frame, shrink, cv::Size(frame.cols / 2, frame.rows / 2));
  //     std::string camera_data = "data:image/png;base64," + Mat2Base64(shrink, "jpeg");
  //     data.push_back("image");
  //     data.push_back(camera_data);
  //     this->websocket->pushData(data);
  //   }
  //   usleep(1 * 1000);

  //   // std::vector<std::string> data;
  //   // data.push_back("image");
  //   // data.push_back("data");
  //   // this->websocket->pushData(data);
  //   // usleep(1000*1000);
  // }

  /////////////////////////////////////////////////////////////////////

  camera_driver_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
      "/carama_driver/image0",
      rclcpp::QoS{10},
      [this](const sensor_msgs::msg::Image::SharedPtr msg)
      { camera_driver_callback(msg); });

  lidar_datas_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/lidar_driver/lidar_driver",
      rclcpp::QoS{10},
      [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg)
      { lidarDatasCallback(msg); });

  lidar_drive_sub = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/ch128x1/lslidar_point_cloud",
      rclcpp::QoS{1},
      [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg)
      { lidar_driver_callback(msg); });

  heart_keeper_pub_ = this->create_publisher<std_msgs::msg::String>(
      "/web_server/heart_keep", rclcpp::QoS{1}.transient_local());

  timer_ =
      this->create_wall_timer(100ms, std::bind(&RosTalk::timerCallback, this));
}

unsigned long long timeUs()
{
  timespec ts{};
  timespec_get(&ts, TIME_UTC);
  return (unsigned long long)(ts.tv_sec * 1000.0 * 1000.0 + ts.tv_nsec / (1000.0));
}

int timersss{0};

void RosTalk::timerCallback()
{
  heart_keeper_pub_->publish(std_msgs::msg::String());
  // std::cout << timersss << std::endl;
  // timersss = 0;
}

void RosTalk::lidar_driver_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  // std::cout<<"lidar_driver_callback"<<std::endl;

  auto caculate2Bit = [](const double &val)
  {
    char *chCode;
    chCode = new char[20];
    sprintf(chCode, "%.2lf", int(val * 100) * 0.01);
    std::string str(chCode);
    delete[] chCode;
    return str;
    // return std::to_string(int(data * 100) * 0.01);
  };

  auto cloud =
      boost::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
  pcl::fromROSMsg(*msg, *cloud);

  //  std::cout << "cloud->points[i].x" << cloud->points.size() << std::endl;

  std::string lidar_data;

  double time2 = timeUs();
  rapidjson::StringBuffer buf;
  // rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
  // rapidjson::PrettyWriter<rapidjson::StringBuffer> writer_rap(buf); // it can word wrap
  rapidjson::Writer<rapidjson::StringBuffer> writer_rap(buf); // it can word wrap
  writer_rap.StartArray();
  for (int i = 0; i < cloud->points.size(); i++)
  {
    // 区域过滤
    if (abs(cloud->points[i].x) < 40 && abs(cloud->points[i].y) < 40)
    {
      // 数据精度调整
      writer_rap.String(caculate2Bit(cloud->points[i].x).c_str());
      writer_rap.String(caculate2Bit(cloud->points[i].y).c_str());
      writer_rap.String(caculate2Bit(cloud->points[i].z).c_str());
    }
  }
  writer_rap.EndArray();
  lidar_data = buf.GetString();
  // std::cout << "time_rap:" << timeUs() - time2 << " strr: " << lidar_data.length() << std::endl;
  /////////////////////////////////////////////////////////////////
  // std::cout<<lidar_data<<std::endl;

  std::vector<std::string> data;
  data.push_back("lidar");
  data.push_back(lidar_data);
  this->websocket->pushData(data);
  timersss++;
}

void RosTalk::camera_driver_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  static bool flag_{false};
  flag_ = !flag_;
  if (flag_ == false)
    return;

  std::string camera_data;
  cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  cv::Mat img__ = cv_ptr->image;

  cv::Mat shrink;
  cv::resize(img__, shrink, cv::Size(img__.cols / 2, img__.rows / 2));
  camera_data = "data:image/png;base64," + Mat2Base64(shrink, "jpeg");

  std::vector<std::string> data;
  data.push_back("image");
  data.push_back(camera_data);
  this->websocket->pushData(data);
}

void RosTalk::lidarDatasCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{

  // auto caculate2Bit = [](const double &val)
  // {
  //   char *chCode;
  //   chCode = new char[20];
  //   sprintf(chCode, "%.2lf", int(val * 100) * 0.01);
  //   std::string str(chCode);
  //   delete[] chCode;
  //   return str;
  //   // return std::to_string(int(data * 100) * 0.01);
  // };

  // auto cloud =
  //     boost::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
  // pcl::fromROSMsg(*msg, *cloud);

  // //  std::cout << "cloud->points[i].x" << cloud->points.size() << std::endl;

  // std::string lidar_data;

  // double time2 = timeUs();
  // rapidjson::StringBuffer buf;
  // // rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
  // // rapidjson::PrettyWriter<rapidjson::StringBuffer> writer_rap(buf); // it can word wrap
  // rapidjson::Writer<rapidjson::StringBuffer> writer_rap(buf); // it can word wrap
  // writer_rap.StartArray();
  // for (int i = 0; i < cloud->points.size(); i++)
  // {
  //   // 区域过滤
  //   if (abs(cloud->points[i].x) < 40 && abs(cloud->points[i].y) < 40)
  //   {
  //     // 数据精度调整
  //     writer_rap.String(caculate2Bit(cloud->points[i].x).c_str());
  //     writer_rap.String(caculate2Bit(cloud->points[i].y).c_str());
  //     writer_rap.String(caculate2Bit(cloud->points[i].z).c_str());
  //   }
  // }
  // writer_rap.EndArray();
  // lidar_data = buf.GetString();
  // // std::cout << "time_rap:" << timeUs() - time2 << " strr: " << lidar_data.length() << std::endl;
  // /////////////////////////////////////////////////////////////////
  // // std::cout<<lidar_data<<std::endl;

  // std::vector<std::string> data;
  // data.push_back("lidar");
  // data.push_back(lidar_data);
  // this->websocket->pushData(data);
  // timersss++;
}

std::string base64Encode(const unsigned char *Data, int DataByte)
{
  // 编码表
  const char EncodeTable[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  // 返回值
  std::string strEncode;
  unsigned char Tmp[4] = {0};
  int LineLength = 0;
  for (int i = 0; i < (int)(DataByte / 3); i++)
  {
    Tmp[1] = *Data++;
    Tmp[2] = *Data++;
    Tmp[3] = *Data++;
    strEncode += EncodeTable[Tmp[1] >> 2];
    strEncode += EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
    strEncode += EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
    strEncode += EncodeTable[Tmp[3] & 0x3F];
    if (LineLength += 4, LineLength == 76)
    {
      strEncode += "\r\n";
      LineLength = 0;
    }
  }
  // 对剩余数据进行编码
  int Mod = DataByte % 3;
  if (Mod == 1)
  {
    Tmp[1] = *Data++;
    strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
    strEncode += EncodeTable[((Tmp[1] & 0x03) << 4)];
    strEncode += "==";
  }
  else if (Mod == 2)
  {
    Tmp[1] = *Data++;
    Tmp[2] = *Data++;
    strEncode += EncodeTable[(Tmp[1] & 0xFC) >> 2];
    strEncode += EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
    strEncode += EncodeTable[((Tmp[2] & 0x0F) << 2)];
    strEncode += "=";
  }

  return strEncode;
}

// imgType 包括png bmp jpg jpeg等opencv能够进行编码解码的文件
std::string Mat2Base64(const cv::Mat &img, std::string imgType)
{
  // Mat转base64
  std::string img_data;
  std::vector<uchar> vecImg;
  std::vector<int> vecCompression_params;
  vecCompression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
  vecCompression_params.push_back(90);
  imgType = "." + imgType;
  cv::imencode(imgType, img, vecImg, vecCompression_params);
  img_data = base64Encode(vecImg.data(), vecImg.size());
  return img_data;
}

// void RosTalk::lidarDatasCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
// {

//   auto caculate2Bit = [](const double &val)
//   {
//     char *chCode;
//     chCode = new char[20];
//     sprintf(chCode, "%.2lf", int(val * 100) * 0.01);
//     std::string str(chCode);
//     delete[] chCode;
//     return str;
//     // return std::to_string(int(data * 100) * 0.01);
//   };

//   auto cloud =
//       boost::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
//   pcl::fromROSMsg(*msg, *cloud);

//   //  std::cout << "cloud->points[i].x" << cloud->points.size() << std::endl;

//   // double time = timeUs();
//   // usleep(1000 * 1);
//   // std::cout << "time_real" << timeUs() - time << std::endl;

//   std::string lidar_data;

//   double time1 = timeUs();

//   // 子节点
//   Json::Value root;
//   Json::Value friends;
//   Json::FastWriter writer;

//   Json::Value valueArray;
//   for (int i = 0; i < cloud->points.size(); i++)
//   {
//     // friends["x"] = Json::Value(caculate2Bit(cloud->points[i].x));
//     // friends["y"] = Json::Value(caculate2Bit(cloud->points[i].y));
//     // friends["z"] = Json::Value(caculate2Bit(cloud->points[i].z));
//     // root.append(friends);
//     valueArray.append(caculate2Bit(cloud->points[i].x));
//     valueArray.append(caculate2Bit(cloud->points[i].y));
//     valueArray.append(caculate2Bit(cloud->points[i].z));
//   }
//   // root["array"] = valueArray;
//   lidar_data = writer.write(valueArray);

//   std::cout << "time_cpp:" << timeUs() - time1 << " strr: " << lidar_data.length() << std::endl;
//   std::cout << lidar_data << std::endl;
//   std::cout << "bbbbbbbbbbbbbbbb" << std::endl;
//   std::cout << "bbbbbbbbbbbbbbbb" << std::endl;
//   std::cout << "bbbbbbbbbbbbbbbb" << std::endl;
//   std::cout << "bbbbbbbbbbbbbbbb" << std::endl;
//   ////////////////////////////////////////////////////////////////

//   double time2 = timeUs();
//   rapidjson::StringBuffer buf;
//   // rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
//   // rapidjson::PrettyWriter<rapidjson::StringBuffer> writer_rap(buf); // it can word wrap
//   rapidjson::Writer<rapidjson::StringBuffer> writer_rap(buf); // it can word wrap
//   writer_rap.StartArray();
//   for (int i = 0; i < cloud->points.size(); i++)
//   {
//     writer_rap.String(caculate2Bit(cloud->points[i].x).c_str());
//     writer_rap.String(caculate2Bit(cloud->points[i].y).c_str());
//     writer_rap.String(caculate2Bit(cloud->points[i].z).c_str());
//   }
//   writer_rap.EndArray();
//   lidar_data = buf.GetString();
//   // std::cout << lidar_data << std::endl;
//   // std::cout << "aaaaaaaaaaaaa" << std::endl;
//   // std::cout << "aaaaaaaaaaaaa" << std::endl;
//   // std::cout << "aaaaaaaaaaaaa" << std::endl;
//   std::cout << "time_rap:" << timeUs() - time2 << " strr: " << lidar_data.length() << std::endl;
//   /////////////////////////////////////////////////////////////////

//   double time3 = timeUs();

// //  pt::Points2 points_pt;
//   pt::Point2 point_pt;
// //  point_pt = points_pt.add_data();
//   for (int i = 0; i < cloud->points.size(); i++)
//   {
//     point_pt.add_x(caculate2Bit(cloud->points[i].x));
//     point_pt.add_x(caculate2Bit(cloud->points[i].y));
//     point_pt.add_x(caculate2Bit(cloud->points[i].z));
//     // point_pt = points_pt.add_data();
//     // point_pt->set_x(cloud->points[i].y);
//     // point_pt = points_pt.add_data();
//     // point_pt->set_x(cloud->points[i].z);
//   }
//   point_pt.SerializeToString(&lidar_data);

//   pt::Point2 point_pt2;

//   point_pt2.ParseFromString(lidar_data);

//   // std::string new_str;
//   // google::protobuf::TextFormat::PrintToString(point_pt2, &new_str);
//   // std::cout<< new_str <<std::endl;

//   std::cout << "time_pro:" << timeUs() - time3 << " lidar_data: " << lidar_data.length() << std::endl;

//   std::cout<<"writer.write(root) :"<<writer.write(root).length()<<std::endl;
//   std::string lidar_data = strr;

//   std::vector<std::string> data;
//   data.push_back("lidar");
//   data.push_back(lidar_data);
//   this->websocket->pushData(data);

//   std::cout << "1111111111111111111111111111" << std::endl;

//   for (int i = 0; i < cloud->points.size(); i++)
//   {
//     // cout << out_pointcloud.points[i].x << ", " << out_pointcloud.points[i].y << ", " << out_pointcloud.points[i].z << endl;
//     friends["x"] = Json::Value(caculate2Bit(cloud->points[i].x));
//     friends["y"] = Json::Value(caculate2Bit(cloud->points[i].y));
//     friends["z"] = Json::Value(caculate2Bit(cloud->points[i].z));

//     // friends["z"] = Json::Value(lidardata.mark);
//     root.append(friends);
//   }

//   std::string lidar_data = writer.write(root);
//   std::string lidar_data = buf.GetString();
//   std::vector<std::string> data;
//   data.push_back("lidar");
//   data.push_back(lidar_data);
//   this->websocket->pushData(data);
//   timersss++;
// }