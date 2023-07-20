#include "ros_talk.h"
#include <chrono>

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
    node = rclcpp::Node::make_shared("qt_viewer_node");
    RCLCPP_INFO(node->get_logger(), " qt_viewer_node initialized ");

    // node->declare_parameter<std::string>("softName", "镭神智能");
    // node->get_parameter("softName", soft_name_);

    // RCLCPP_INFO(node->get_logger(), soft_name_);
    // RCLCPP_INFO(node->get_logger(), soft_name_);
    // RCLCPP_INFO(node->get_logger(), soft_name_);

    // RCLCPP_INFO_STREAM(this->get_logger(), "qtviewer init");
    //  发布话题
    save_param_pub_ =
        node->create_publisher<std_msgs::msg::String>("/params_config/save_params", rclcpp::QoS{1}.transient_local());

    to_d_area_pub_ =
        node->create_publisher<sys_msgs::msg::ToDArea>("/qt_viewer/area_points", rclcpp::QoS{1}.transient_local());

    log_pub_ = node->create_publisher<std_msgs::msg::String>(
        "/log_sys/log", rclcpp::QoS{1}.transient_local());

    heart_keeper_pub_ = node->create_publisher<std_msgs::msg::String>(
        "/qt_viewer/heart_keep", rclcpp::QoS{1}.transient_local());

    save_point_cloud_pub_ = node->create_publisher<std_msgs::msg::Int8MultiArray>(
        "/qt_viewer/save_point_cloud", rclcpp::QoS{1}.durability_volatile());

    camera_control_cmd_pub = node->create_publisher<std_msgs::msg::Int8>(
        "/qt_viewer/camera_control_cmd", rclcpp::QoS{10});

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

    to_d_area_sub = node->create_subscription<sys_msgs::msg::ToDArea>(
        "/params_config/area_points",
        rclcpp::QoS{1}.transient_local(),
        [this](const sys_msgs::msg::ToDArea::SharedPtr msg)
        { to_d_area_Callback(msg); });

    // camera_drive_sub_test = node->create_subscription<sensor_msgs::msg::Image>(
    //     "/carama_driver/image0",
    //     rclcpp::QoS{1}.best_effort(),
    //     [this](const sensor_msgs::msg::Image::SharedPtr msg)
    //     { camera_drive_imgae_callback(msg); });

    camera_drive_sub = node->create_subscription<sensor_msgs::msg::Image>(
        "/algorithm/imgae",
        rclcpp::QoS{1}.best_effort(),
        [this](const sensor_msgs::msg::Image::SharedPtr msg)
        { camera_drive_imgae_callback(msg); });

    for (int i{0}; camera_numb > i; i++)
    {
        camera_drive_subs.push_back(
            node->create_subscription<sensor_msgs::msg::Image>(
                "/carama_driver/image" + std::to_string(i),
                rclcpp::QoS{1}.best_effort(),
                [&](const sensor_msgs::msg::Image::SharedPtr msg)
                { camera_drive_imgae_callback(msg); }));
    }

    // lidar_drive_sub = node->create_subscription<sensor_msgs::msg::PointCloud2>(
    //     "/lslidar_1/lslidar_point_cloud",
    //     rclcpp::QoS{1},
    //     [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    //     { lidar_driver_callback(msg); });

    algorithm_data_sub = node->create_subscription<sys_msgs::msg::DectData>(
        "/algorithm/perception_data",
        rclcpp::QoS{1},
        [this](const sys_msgs::msg::DectData::SharedPtr msg)
        { decct_data_callback(msg); });

    log_sub = node->create_subscription<std_msgs::msg::String>(
        "/log_sys/log",
        rclcpp::QoS{10},
        [this](const std_msgs::msg::String::SharedPtr msg)
        { log_callback(msg); });

    monitor_node_sub_ = node->create_subscription<sys_msgs::msg::GeneralTableArray>(
        "/monitor/node_alive",
        rclcpp::QoS{1},
        [this](const sys_msgs::msg::GeneralTableArray::SharedPtr msg)
        { monitor_node_callback(msg); });

    monitor_sensor_sub_ = node->create_subscription<sys_msgs::msg::GeneralTableArray>(
        "/monitor/sensor_alive",
        rclcpp::QoS{1},
        [this](const sys_msgs::msg::GeneralTableArray::SharedPtr msg)
        { monitor_sensor_callback(msg); });

    // ros2 topic echo --qos-profile services_default --qos-durability
    // transient_local  /cti/error_status/set 定时器
    timer_ =
        node->create_wall_timer(100ms, std::bind(&RosTalk::timerCallback, this));

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // this->start();

    // 解绑话题
    // camera_drive_sub_test = nullptr;

    start_t = std::chrono::steady_clock::now();
    end_t = std::chrono::steady_clock::now();
}

void RosTalk::run()
{
    std_msgs::msg::String pub_msg;
    pub_msg.data = "";
    rclcpp::WallRate loop_rate(1000);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    rclcpp::shutdown();
}


void RosTalk::setLidarTypeMode(int msg)
{
    if (msg == LidarTypeMode::LidartypeOrignal)
    {
        algorithm_data_sub = nullptr;
        lidar_drive_sub = node->create_subscription<sensor_msgs::msg::PointCloud2>(
            "/lslidar_1/lslidar_point_cloud",
            rclcpp::QoS{1},
            [this](const sensor_msgs::msg::PointCloud2::SharedPtr msg)
            { lidar_driver_callback(msg); });
    }
    else if (msg == LidarTypeMode::LidartypeAlgorithm)
    {
        lidar_drive_sub = nullptr;
        algorithm_data_sub = node->create_subscription<sys_msgs::msg::DectData>(
            "/algorithm/perception_data",
            rclcpp::QoS{1},
            [this](const sys_msgs::msg::DectData::SharedPtr msg)
            { decct_data_callback(msg); });
    }
    else
    {
        RCLCPP_INFO(node->get_logger(), " error params setLidarTypeMode ");
    }
}

void RosTalk::setCameraTypeMode(int msg)
{
    camera_type_mode = (CameraTypeMode)msg;
}

void RosTalk::setCameraControlCmd(int msg)
{
    std_msgs::msg::Int8 cmd;
    cmd.data = msg;
    camera_control_cmd_pub->publish(cmd);
}

void RosTalk::save_point_cloud(int msg)
{
    std_msgs::msg::Int8MultiArray dat;
    for (int j = 0; j < 2; j++)
    {
        dat.data.push_back(0);
    }
    dat.data[0] = msg;
    save_point_cloud_pub_->publish(dat);
}

void RosTalk::save_point_backgroud_cloud(int msg)
{
    std_msgs::msg::Int8MultiArray dat;
    for (int j = 0; j < 2; j++)
    {
        dat.data.push_back(0);
    }
    dat.data[1] = msg;
    save_point_cloud_pub_->publish(dat);
}

void RosTalk::monitor_sensor_callback(const sys_msgs::msg::GeneralTableArray::SharedPtr &msg)
{
    bool is_normal = true;
    for (auto dat : msg->gereral_table_array)
    {
        // dat.data_name;
        if (dat.data_value != "normal")
        {
            is_normal = false;
        }
    }

    if (is_normal == true)
    {
        alarm_status.communicate_status.data = 255;
    }
    else
    {
        alarm_status.communicate_status.data = 0;
    }

    emit emit_alarm_data(alarm_status);
}

void RosTalk::monitor_node_callback(const sys_msgs::msg::GeneralTableArray::SharedPtr &msg)
{
    bool is_normal = true;
    for (auto dat : msg->gereral_table_array)
    {
        // dat.data_name;
        if (dat.data_value != "normal")
        {
            is_normal = false;
        }
    }

    if (is_normal == true)
    {
        alarm_status.work_status.data = 255;
    }
    else
    {
        alarm_status.work_status.data = 0;
    }

    emit emit_alarm_data(alarm_status);
}

void RosTalk::to_d_area_Callback(const sys_msgs::msg::ToDArea::SharedPtr &msg)
{
    std::cout << "to_d_area_Callback" << std::endl;

    QList<QList<PointT>> qt_msg;

    for (auto dat_top : msg->area)
    {
        QList<PointT> qt_top;
        for (auto dat_down : dat_top.point_array)
        {
            PointT point;
            point.x = dat_down.x;
            point.y = dat_down.y;
            point.z = dat_down.z;
            qt_top.push_back(point);
        }
        qt_msg.push_back(qt_top);
    }

    emit ros_to_qt_area_points(qt_msg);
}

void RosTalk::saveLidarDatas(QString msg)
{

    std::cout << "------saveLidarDatas----" << std::endl;

    std_msgs::msg::String str;
    str.data = msg.toStdString();
    save_param_pub_->publish(str);
    //    std::cout <<root.toStyledString()<<std::endl;
}

void RosTalk::decct_data_callback(const sys_msgs::msg::DectData::SharedPtr &msg)
{
    auto PointCouldrosTopcl = [&]()
    {
        PointCloudTPtr cloudPtr(new PointCloudT);
        // Get the field structure of this point cloud
        int pointBytes = msg->origin_cloud.point_step;
        int offset_x, offset_y, offset_z, offset_int;
        for (int f = 0; f < msg->origin_cloud.fields.size(); ++f)
        {
            if (msg->origin_cloud.fields[f].name == "x")
                offset_x = msg->origin_cloud.fields[f].offset;
            if (msg->origin_cloud.fields[f].name == "y")
                offset_y = msg->origin_cloud.fields[f].offset;
            if (msg->origin_cloud.fields[f].name == "z")
                offset_z = msg->origin_cloud.fields[f].offset;
            if (msg->origin_cloud.fields[f].name == "intensity")
                offset_int = msg->origin_cloud.fields[f].offset;
        }

        // populate point cloud object
        for (int p = 0; p < msg->origin_cloud.width; ++p)
        {
            pcl::PointXYZI newPoint;
            newPoint.x = *(float *)(&msg->origin_cloud.data[0] + (pointBytes * p) + offset_x);
            newPoint.y = *(float *)(&msg->origin_cloud.data[0] + (pointBytes * p) + offset_y);
            newPoint.z = *(float *)(&msg->origin_cloud.data[0] + (pointBytes * p) + offset_z);
            newPoint.intensity = *(unsigned char *)(&msg->origin_cloud.data[0] + (pointBytes * p) + offset_int);
            cloudPtr->points.push_back(newPoint);
        }
        return cloudPtr;
    };

    auto cloud = boost::make_shared<PointCloudT>();
    // pcl::fromROSMsg(msg->origin_cloud, *cloud);
    cloud = PointCouldrosTopcl();

    DectData dect_data;
    *dect_data.Origin_Cloud = *cloud;

    for (auto dat : msg->data_vec)
    {
        SendObjectInf send_object_inf;
        send_object_inf.center_x = dat.obj_inf.x;
        send_object_inf.center_y = dat.obj_inf.y;
        send_object_inf.center_z = dat.obj_inf.z;
        send_object_inf.classify = dat.obj_inf.classify;
        send_object_inf.distance = dat.obj_inf.distance;
        send_object_inf.heading = dat.obj_inf.heading;
        send_object_inf.height = dat.obj_inf.height;
        send_object_inf.id = dat.obj_inf.id;
        send_object_inf.kind_risk = dat.obj_inf.kind_risk;
        send_object_inf.length = dat.obj_inf.length;
        send_object_inf.speed = dat.obj_inf.speed;
        send_object_inf.width = dat.obj_inf.width;
        dect_data.Data_vec.push_back(send_object_inf);
    }

    for (auto dat : msg->objcloud_vec)
    {
        auto cloud = boost::make_shared<PointCloudT>();
        pcl::fromROSMsg(dat, *cloud);
        // if(cloud->size() == 0) continue;
        dect_data.ObjCloud_vec.push_back(cloud);
    }

    emit emit_decct_data(dect_data);
}

void RosTalk::log_callback(const std_msgs::msg::String::SharedPtr &msg)
{
    // std::cout << "11111111111111" << std::endl;
    emit emit_show_log(QString::fromStdString(msg->data));
}

void RosTalk::lidar_driver_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{

    end_t = std::chrono::steady_clock::now();                                              // 记录定时器结束时间
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t); // 计算执行时间
    std::cout << "雷达驱动数据显示的周期时间:" << elapsed.count() << " ms" << std::endl;
    start_t = std::chrono::steady_clock::now(); // 记录定时器开始时间

    auto cloud =
        boost::make_shared<PointCloudT>();
    pcl::fromROSMsg(*msg, *cloud);
    emit emit_lidar_drive(cloud);
};

// PointCloudTPtr

// Convert sensor_msgs::Image to cv::Mat
cv::Mat rosImgToCv(const sensor_msgs::msg::Image::SharedPtr msg)
{
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (const cv_bridge::Exception &e)
    {
        fprintf(stderr, "cv_bridge exception: %s", e.what());
        return cv::Mat();
    }
    return cv_ptr->image;
}

QPixmap matToPixmap(const cv::Mat &mat)
{
    QImage image(mat.data,
                 mat.cols, mat.rows,
                 static_cast<int>(mat.step),
                 QImage::Format_RGB888);
    return QPixmap::fromImage(image.rgbSwapped());
}

void RosTalk::camera_drive_imgae_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{

    std::cout << "camera_drive_imgae_callback<<" << std::endl;

    auto start_time = std::chrono::steady_clock::now();

    auto cvToQpixmap = [&](const sensor_msgs::msg::Image::SharedPtr msg)
    {
        try
        {
            int width = msg->width;
            int height = msg->height;
            std::vector<uint8_t> image_data = msg->data;

            cv::Mat cv_image(height, width, CV_8UC3);
            std::memcpy(cv_image.data, image_data.data(), image_data.size());

            cv::cvtColor(cv_image, cv_image, cv::COLOR_BGR2RGB);                               // 将颜色空间转换为 RGB
            QImage qimage(cv_image.data, cv_image.cols, cv_image.rows, QImage::Format_RGB888); // 创建 QImage 对象
            QPixmap pixmap = QPixmap::fromImage(qimage);                                       // 转换为 QPixmap

            emit emit_camera_drive(pixmap, QString::fromStdString(msg->header.frame_id));
        }
        catch (const cv::Exception &e)
        {
            std::cerr << e.what() << "读取相机驱动失败！！！！！" << '\n';
        }
    };

    if (camera_type_mode == CameraTypeMode::CameratypeOrignal)
    {
        if (msg->header.frame_id.substr(msg->header.frame_id.length() - 6) != "worked")
        {
            // cvToQpixmap(msg);
            emit emit_camera_drive(matToPixmap(rosImgToCv(msg)), QString::fromStdString(msg->header.frame_id));
        }
    }
    else if (camera_type_mode == CameraTypeMode::CameratypeAlgorithm)
    {
        if (msg->header.frame_id.substr(msg->header.frame_id.length() - 6) == "worked")
        {
            // cvToQpixmap(msg);
            emit emit_camera_drive(matToPixmap(rosImgToCv(msg)), QString::fromStdString(msg->header.frame_id));
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "图像  elapsed time: " << elapsed_time.count() << " ms" << std::endl;
}

void RosTalk::parameterServerCallback(const std_msgs::msg::String::SharedPtr msg)
{
    // std::cout << "parameter_server_callback: " << msg->data << std::endl;
    emit emitTopicParams(QString::fromStdString(msg->data));
}

void RosTalk::save2dlists(QList<QList<PointT>> msg)
{
    sys_msgs::msg::ToDArea to_d_area;

    for (auto dat_top : msg)
    {
        sys_msgs::msg::PointArray points_array;
        for (auto dat_down : dat_top)
        {
            sys_msgs::msg::Point point;
            point.x = dat_down.x;
            point.y = dat_down.y;
            point.z = dat_down.z;
            points_array.point_array.push_back(point);
        }
        to_d_area.area.push_back(points_array);
    }
    to_d_area_pub_->publish(to_d_area);
}

void RosTalk::saveTopicParams(QString msg)
{
    std_msgs::msg::String str;
    str.data = msg.toStdString();
    save_param_pub_->publish(str);
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

//    //str.substr(str.length() - 8); camera_0_algorithm

//    //    auto cvToQpixmap = [&](const sensor_msgs::msg::Image::SharedPtr msg)
//    //    {
//    //        QImage::Format format;
//    //        format = QImage::Format_RGB888;
//    //        cv_bridge::CvImagePtr cv_ptr;
//    //        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
//    //        uchar *uchar_iamge_data = cv_ptr->image.data;
//    //        QPixmap showImage = QPixmap::fromImage(QImage(uchar_iamge_data, msg->width, msg->height, msg->step, format));
//    //        return showImage;
//    //    };

//    try
//    {
//        int width = msg->width;
//        int height = msg->height;
//        std::vector<uint8_t> image_data = msg->data;

//        cv::Mat cv_image(height, width, CV_8UC3);
//        std::memcpy(cv_image.data, image_data.data(), image_data.size());

//        cv::cvtColor(cv_image, cv_image, cv::COLOR_BGR2RGB);                               // 将颜色空间转换为 RGB
//        QImage qimage(cv_image.data, cv_image.cols, cv_image.rows, QImage::Format_RGB888); // 创建 QImage 对象
//        QPixmap pixmap = QPixmap::fromImage(qimage);                                       // 转换为 QPixmap

//        emit emit_camera_drive(pixmap, QString::fromStdString(msg->header.frame_id));

//        //
//        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
//    }
//    catch (const cv::Exception &e)
//    {
//        std::cerr << e.what() << '\n';
//    }

//    // int width = msg->width;
//    // int height = msg->height;
//    // std::vector<uint8_t> image_data = msg->data;

//    // cv::Mat cv_image(height, width, CV_8UC3);
//    // std::memcpy(cv_image.data, image_data.data(), image_data.size());

//    // cv::cvtColor(cv_image, cv_image, cv::COLOR_BGR2RGB);                               // 将颜色空间转换为 RGB
//    // QImage qimage(cv_image.data, cv_image.cols, cv_image.rows, QImage::Format_RGB888); // 创建 QImage 对象
//    // QPixmap pixmap = QPixmap::fromImage(qimage);                                       // 转换为 QPixmap

//    // emit emit_camera_drive(pixmap, QString::fromStdString(msg->header.frame_id));

//    // //
//    // cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);

//    //    std::cout<<"===================888888888888======================="<<std::endl;
//    //    QImage::Format format;
//    //    format = QImage::Format_RGB888;
//    //   cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
//    //    uchar *uchar_iamge_data = cv_ptr->image.data;
//    //    QPixmap showImage = QPixmap::fromImage(QImage(uchar_iamge_data, msg->width, msg->height, msg->step, format));

//    //    std::cout<<"===================111233435======================="<<std::endl;
//    //    auto sdas = cvToQpixmap(msg);
