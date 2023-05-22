#include "tasklistui.h"
#include "qdebug.h"
#include "QHBoxLayout"
#include <iostream>
#include <sstream>
#include "childtitlebar.h"



// #include "allstylesheets.h"

TaskListUi::TaskListUi(QWidget *parent)
{

    QVBoxLayout *mainLayout_H = new QVBoxLayout();
    QTreeWidget *mainTreeWidget = new QTreeWidget(this);
    ChildTitleBar *my_bar = new ChildTitleBar(this);
    my_bar->setTitleName("参数配置");
    // this->setWindowFlags(Qt::FramelessWindowHint);
    // this->setWindowModality(Qt::WindowModal);
    // setModal(true);

    QLabel *head_label = new QLabel();
    head_label->setText("参数配置");
    mainLayout_H->addWidget(my_bar);
    mainLayout_H->addWidget(head_label);
    mainLayout_H->addWidget(mainTreeWidget);

    this->setLayout(mainLayout_H);
    //    QStringList headers;
    //    headers<<"name";
    mainTreeWidget->setColumnCount(2);
    // mainTreeWidget->setMinimumSize(400,800);
    QHeaderView *head = mainTreeWidget->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    // mainTreeWidget->autoScrollMargin();

    //    mainTreeWidget->setColumnWidth(0,170);
    mainTreeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // mainTreeWidget->setStyleSheet(myStyleSheets::myTree::tasklistUiTree);
    mainTreeWidget->setHeaderHidden(true);
    // mainTreeWidget->setAutoFillBackground(true);

    //    // tool
    //    QTreeWidgetItem *Tool = new QTreeWidgetItem();
    //    // Tool->setIcon(0,QIcon(":/res/images/painter.png"));
    //    //     mainTreeWidget->addTopLevelItem(Tool);
    //    //     Tool->setText(0,QString("工具"));

    //    auto check_box = new QCheckBox(this);
    //    auto check_box2 = new QCheckBox(this);

    //    getQCheckBoxItem(mainTreeWidget, Tool, check_box, "vmap-tool:");
    //    getQCheckBoxItem(mainTreeWidget, Tool, check_box2, "lanelet-tool:");


    //显示设置
    QTreeWidgetItem *showParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(showParams);
    showParams->setText(0, QString("显示参数"));

    for (int i = 0; i < 1; i++)
    {
        QTreeWidgetItem *showParams_1 = new QTreeWidgetItem();
        showParams->addChild(showParams_1); ///
        showParams_1->setText(0, QString(" 检测显示 "));

        RB_line_show_is_open = new QCheckBox(this);
        RB_line_show_classify = new QCheckBox(this);
        RB_line_show_distance = new QCheckBox(this);
        RB_line_show_velocity = new QCheckBox(this);
        LM_line_show_box_size = new QLineEdit(this);

        RB_line_show_is_open->setChecked(true);
        RB_line_show_distance->setChecked(true);
        LM_line_show_box_size->setText("1");

        getQCheckBoxItem(mainTreeWidget, showParams_1, RB_line_show_is_open, "开启开关");
        getQCheckBoxItem(mainTreeWidget, showParams_1, RB_line_show_classify, "显示分类");
        getQCheckBoxItem(mainTreeWidget, showParams_1, RB_line_show_distance, "显示距离");
        getQCheckBoxItem(mainTreeWidget, showParams_1, RB_line_show_velocity, "显示速度");
        getQLineEditItem(mainTreeWidget, showParams_1, LM_line_show_box_size, "字号大小");

    }

    for (int i = 0; i < 1; i++)
    {
        QTreeWidgetItem *showParams_1 = new QTreeWidgetItem();
        showParams->addChild(showParams_1); ///
        showParams_1->setText(0, QString(" 相机模式 "));

        block_camera_mode = new QButtonGroup(this);            //分组
        multi_camera = new QRadioButton(this);
        solo_camera = new QRadioButton(this);
        solo_camera->setChecked(true);

        block_camera_mode->addButton(solo_camera,0);                   //一个值为0
        block_camera_mode->addButton(multi_camera,1);                 //一个值为1

        getQRadiobuttonItem(mainTreeWidget, showParams_1, solo_camera, "单相机模式");
        getQRadiobuttonItem(mainTreeWidget, showParams_1, multi_camera, "多相机模式");

    }
    //    block_camera_mode->checkedId();

    //雷达参数
    QTreeWidgetItem *lidarParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(lidarParams);
    lidarParams->setText(0, QString("雷达参数"));

    for (int i = 0; i < 4; i++)
    {
        QTreeWidgetItem *lidarParams_1 = new QTreeWidgetItem();
        lidarParams->addChild(lidarParams_1); ///
        lidarParams_1->setText(0, QString("雷达 ") + QString::number(i + 1));

        LM_line_edit_lidar_IP.push_back(new QLineEdit(this));
        LM_line_edit_lidar_device_port.push_back(new QLineEdit(this));
        LM_line_edit_lidar_data_port.push_back(new QLineEdit(this));
        LM_line_edit_lidar_x.push_back(new QLineEdit(this));
        LM_line_edit_lidar_y.push_back(new QLineEdit(this));
        LM_line_edit_lidar_z.push_back(new QLineEdit(this));
        LM_line_edit_lidar_picth.push_back(new QLineEdit(this));
        LM_line_edit_lidar_roll.push_back(new QLineEdit(this));
        LM_line_edit_lidar_yaw.push_back(new QLineEdit(this));

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_IP[i], "雷达地址"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_device_port[i], "设备端口"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_data_port[i], "数据端口"+QString::fromStdString( std::to_string(i)));

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_x[i], "X轴相距(m)"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_y[i], "y轴相距(m)"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_z[i], "z轴相距(m)"+QString::fromStdString( std::to_string(i)));

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_picth[i], "X方向(角度)"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_roll[i], "Y轴方向(角度)"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_yaw[i], "Z轴方向(角度)"+QString::fromStdString( std::to_string(i)));

        //        mainTreeWidget->
        //        lidarParams_1->setExpanded(true);
    }
    //    lidarParams->
    lidarParams->setExpanded(false);

    //摄像头
    QTreeWidgetItem *cameraParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(cameraParams);
    cameraParams->setText(0, QString("摄像头参数"));

    for (int i = 0; i < 4; i++)
    {
        QTreeWidgetItem *cameraParams_1 = new QTreeWidgetItem();
        cameraParams->addChild(cameraParams_1); ///
        cameraParams_1->setText(0, QString("摄像头 ") + QString::number(i + 1));

        LM_line_edit_camera_IP.push_back(new QLineEdit(this));
        LM_line_edit_camera_ID.push_back(new QLineEdit(this));
        LM_line_edit_camera_Pass.push_back(new QLineEdit(this));

        getQLineEditItem(mainTreeWidget, cameraParams_1, LM_line_edit_camera_IP[i], "用户名"+ QString::number(i + 1));
        getQLineEditItem(mainTreeWidget, cameraParams_1, LM_line_edit_camera_ID[i], "相机IP"+ QString::number(i + 1));
        getQLineEditItem(mainTreeWidget, cameraParams_1, LM_line_edit_camera_Pass[i], "密码"+ QString::number(i + 1));

    }


    //检测配置
    QTreeWidgetItem *detectorParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(detectorParams);
    detectorParams->setText(0, QString("检测配置参数"));

    for (int i = 0; i < 1; i++)
    {
        LM_line_edit_Tolerance = new QLineEdit(this);
        LM_line_edit_maxSize = new QLineEdit(this);
        LM_line_edit_minSize = new QLineEdit(this);

        getQLineEditItem(mainTreeWidget, detectorParams, LM_line_edit_Tolerance, "聚类距离");
        getQLineEditItem(mainTreeWidget, detectorParams, LM_line_edit_maxSize, "聚类最大值");
        getQLineEditItem(mainTreeWidget, detectorParams, LM_line_edit_minSize, "聚类最小值");

    }

    //算法配置
    QTreeWidgetItem *preprocessorParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(preprocessorParams);
    preprocessorParams->setText(0, QString("预处理配置参数"));

    for (int i = 0; i < 1; i++)
    {

        LM_line_Area_height_down = new QLineEdit(this);
        LM_line_Area_height_top = new QLineEdit(this);
        LM_line_edit_K = new QLineEdit(this);
        LM_line_euclidean_disatance = new QLineEdit(this);
        LM_line_interpolation_interval = new QLineEdit(this);
        LM_line_m_grid_x = new QLineEdit(this);
        LM_line_m_grid_y = new QLineEdit(this);
        LM_line_m_grid_z = new QLineEdit(this);
        LM_line_resolution = new QLineEdit(this);
        LM_line_start_dist = new QLineEdit(this);

        LM_line_cloudMapFrame = new QLineEdit(this);
        RB_line_save_bclold_isOpen = new QCheckBox(this);
        LM_line_save_bclold_hour = new QLineEdit(this);
        LM_line_save_bclold_min = new QLineEdit(this);
        LM_line_roi_limit = new QLineEdit(this);
        LM_line_detect_text_size = new QLineEdit(this);
        LM_line_difference_threshold = new QLineEdit(this);

        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_Area_height_down, "防区高度最小值(m)");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_Area_height_top, "防区高度最大值(m)");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_edit_K, "K邻域值");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_euclidean_disatance, "欧式聚类值");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_interpolation_interval, "插值间距");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_m_grid_x, "下采样x值");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_m_grid_y, "下采样y值");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_m_grid_z, "下采样z值");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_resolution, "栅格大小");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_difference_threshold, "栅格高度差");
        // difference_threshold
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_start_dist, "开始距离");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_cloudMapFrame, "点云地图保存帧数");
        getQCheckBoxItem(mainTreeWidget, preprocessorParams, RB_line_save_bclold_isOpen, "保存背景点云");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_save_bclold_hour, "保存点云(h)");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_save_bclold_min, "保存点云(min)");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_roi_limit, "roi限制");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_detect_text_size, "检测文本大小");

        //        getQRadiobuttonItem(mainTreeWidget, preprocessorParams, isSaveBackgroud, "isSaveBackgroud");

    }


    //web配置
    QTreeWidgetItem *webParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(webParams);
    webParams->setText(0, QString("网络配置参数"));

    for (int i = 0; i < 1; i++)
    {
        LM_line_edit_ServerAddress = new QLineEdit(this);
        LM_line_edit_ServerPort = new QLineEdit(this);
        LM_line_edit_UploadDataAddress = new QLineEdit(this);
        LM_line_edit_UplodaDeviceId = new QLineEdit(this);


        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_ServerAddress, "服务端地址");
        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_ServerPort, "服务端口");
        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_UploadDataAddress, "上传数据地址");
        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_UplodaDeviceId, "上传设备编号");

    }


    //mqtt配置
    QTreeWidgetItem *mqttParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(mqttParams);
    mqttParams->setText(0, QString("mqtt配置参数"));

    for (int i = 0; i < 1; i++)
    {

        LM_line_edit_3d_lidar_id = new QLineEdit(this);
        LM_line_edit_SendAddress = new QLineEdit(this);
        LM_line_edit_SendPort = new QLineEdit(this);
        LM_line_edit_info_topic = new QLineEdit(this);
        LM_line_edit_status_topic = new QLineEdit(this);

        getQLineEditItem(mainTreeWidget, mqttParams, LM_line_edit_3d_lidar_id, "3d_lidar_id");
        getQLineEditItem(mainTreeWidget, mqttParams, LM_line_edit_SendAddress, "SendAddress");
        getQLineEditItem(mainTreeWidget, mqttParams, LM_line_edit_SendPort, "SendPort");
        getQLineEditItem(mainTreeWidget, mqttParams, LM_line_edit_info_topic, "info_topic");
        getQLineEditItem(mainTreeWidget, mqttParams, LM_line_edit_status_topic, "status_topic");

    }



    //按钮
    comfire_button = new QPushButton(this);
    comfire_button->setText("保存");
    comfire_button->setMaximumSize(380, 30);
    comfire_button->setMinimumSize(380, 30);
    //    mainTreeWidget->expandAll();
    this->setMinimumWidth(400);
    this->setMaximumWidth(400);
    ////        this->setWindowFlags(Qt::FramelessWindowHint);

    QObject::connect(this->comfire_button, &QPushButton::clicked, this, &TaskListUi::savePushButton);

    mainLayout_H->addWidget(comfire_button);

    initConnect();

}


void TaskListUi::initConnect()
{
//    connect(this->)
//    block_camera_mode.toggled.connect(my_slot_function);

//    connect(block_camera_mode,&QButtonGroup,[&](bool){qDebug()<<"device=="<<device;});
}


QString getJsonData(Json::Value json_value,std::string fir,std::string last,int trm = 0)
{
    if(json_value.isNull())
    {
        return QString();
    }
    else {
        if(trm == 0)
        {
            return QString::fromStdString(json_value[fir][last].asString());
        }
        else
        {
            return QString::fromStdString(json_value[fir][last].asString()).left(trm);
        }

    }
}


void TaskListUi::updateTopicParams(QString msg)
{
    //    vec_lidar_datas

    qDebug()<<"updateTopicParams";
    Json::Value parameter_server;
    Json::Reader reader;
    reader.parse(msg.toStdString(), parameter_server); // LidarParam.LidarParam0.IP

    //mqtt
    LM_line_edit_SendPort->setText(getJsonData(parameter_server,"mqtt","SendPort",15));
    LM_line_edit_3d_lidar_id->setText(getJsonData( parameter_server,"mqtt","3d_lidar_id",15));
    LM_line_edit_SendAddress->setText(getJsonData( parameter_server,"mqtt","SendAddress",15));
    LM_line_edit_info_topic->setText(getJsonData( parameter_server,"mqtt","info_topic",15));
    LM_line_edit_status_topic->setText(getJsonData( parameter_server,"mqtt","status_topic",15));

    //web
    LM_line_edit_ServerAddress->setText(getJsonData( parameter_server,"web","ServerAddress",15));
    LM_line_edit_ServerPort->setText(getJsonData( parameter_server,"web","ServerPort",15));
    LM_line_edit_UploadDataAddress->setText(getJsonData( parameter_server,"web","UploadDataAddress",15));
    LM_line_edit_UplodaDeviceId->setText(getJsonData( parameter_server,"web","UplodaDeviceId",15));


    // show
    RB_line_show_is_open->setChecked(std::stoi(getJsonData(parameter_server,"show","is_show_open").toStdString()));
    RB_line_show_classify->setChecked(std::stoi( getJsonData(parameter_server,"show","is_show_classify").toStdString()));
    RB_line_show_distance->setChecked(std::stoi( getJsonData(parameter_server,"show","is_show_distance").toStdString()));
    RB_line_show_velocity->setChecked(std::stoi( getJsonData(parameter_server,"show","is_show_velocit").toStdString()));
    LM_line_show_box_size->setText(getJsonData( parameter_server,"show","show_box_size"));


     if(getJsonData(parameter_server,"show","camera_mode").toStdString()=="1")
     {
         multi_camera->setChecked(true);
     }
     else
     {
         solo_camera->setChecked(true);
     }

    //preprocessor
    LM_line_Area_height_down->setText(getJsonData( parameter_server,"preprocessor","Area_height_down",8));
    LM_line_Area_height_top->setText(getJsonData( parameter_server,"preprocessor","Area_height_top",8));
    LM_line_edit_K->setText(getJsonData( parameter_server,"preprocessor","K",8));
    LM_line_euclidean_disatance->setText(getJsonData( parameter_server,"preprocessor","euclidean_disatance",8));
    LM_line_interpolation_interval->setText(getJsonData( parameter_server,"preprocessor","interpolation_interval",8));
    LM_line_m_grid_x->setText(getJsonData( parameter_server,"preprocessor","m_grid_x",8));
    LM_line_m_grid_y->setText(getJsonData( parameter_server,"preprocessor","m_grid_y",8));
    LM_line_m_grid_z->setText(getJsonData( parameter_server,"preprocessor","m_grid_z",8));
    LM_line_resolution->setText(getJsonData( parameter_server,"preprocessor","resolution",8));
    LM_line_difference_threshold->setText(getJsonData( parameter_server,"preprocessor","difference_threshold",8));
    LM_line_start_dist->setText(getJsonData( parameter_server,"preprocessor","start_dist",8));

    LM_line_cloudMapFrame->setText(getJsonData( parameter_server,"preprocessor","cloudMapFrame",8));
    RB_line_save_bclold_isOpen->setChecked(std::stoi(getJsonData( parameter_server,"preprocessor","save_bclold_isOpen").toStdString()));
    //    RB_line_save_bclold_isOpen->setText(getJsonData( parameter_server,"preprocessor","save_bclold_isOpen",8));
    LM_line_save_bclold_hour->setText(getJsonData( parameter_server,"preprocessor","save_bclold_hour",8));
    LM_line_save_bclold_min->setText(getJsonData( parameter_server,"preprocessor","save_bclold_min",8));
    LM_line_roi_limit->setText(getJsonData( parameter_server,"preprocessor","roi_limit",8));

    //    LM_line_detect_text_size, "detect_text_size");


    //Detector
    LM_line_edit_Tolerance->setText(getJsonData( parameter_server,"Detector","Tolerance",8));
    LM_line_edit_maxSize->setText(getJsonData( parameter_server,"Detector","maxSize",8));
    LM_line_edit_minSize->setText(getJsonData( parameter_server,"Detector","minSize",8));

    //Lidar
    for(int i{0};LM_line_edit_lidar_IP.size()>i;i++)
    {
        LM_line_edit_lidar_IP[i]->setText(getJsonData( parameter_server,"Lidar","device_ip"+std::to_string(i)));
        LM_line_edit_lidar_device_port[i]->setText(getJsonData( parameter_server,"Lidar","device_port"+std::to_string(i)));
        LM_line_edit_lidar_data_port[i]->setText(getJsonData( parameter_server,"Lidar","data_port"+std::to_string(i)));
        LM_line_edit_lidar_x[i]->setText(getJsonData( parameter_server,"Lidar","x_offset"+std::to_string(i),10));
        LM_line_edit_lidar_y[i]->setText(getJsonData( parameter_server,"Lidar","y_offset"+std::to_string(i),10));
        LM_line_edit_lidar_z[i]->setText(getJsonData( parameter_server,"Lidar","z_offset"+std::to_string(i),10));
        LM_line_edit_lidar_picth[i]->setText(getJsonData( parameter_server,"Lidar","setXAngle"+std::to_string(i),10));
        LM_line_edit_lidar_roll[i]->setText(getJsonData( parameter_server,"Lidar","setYAngle"+std::to_string(i),10));
        LM_line_edit_lidar_yaw[i]->setText(getJsonData( parameter_server,"Lidar","setZAngle"+std::to_string(i),10));
    }

    //Camera
    for(int i{0};LM_line_edit_camera_ID.size()>i;i++)
    {
        LM_line_edit_camera_IP[i]->setText(getJsonData( parameter_server,"Camera","IP"+std::to_string(i)));
        LM_line_edit_camera_ID[i]->setText(getJsonData( parameter_server,"Camera","ID"+std::to_string(i)));
        LM_line_edit_camera_Pass[i]->setText(getJsonData( parameter_server,"Camera","Pass"+std::to_string(i)));
    }
}

void TaskListUi::savePushButton()
{

    // 根节点
    Json::Value root;

    // 子节点
    Json::Value mqtt;
    // 子节点挂到根节点上
    mqtt["3d_lidar_id"] = Json::Value(LM_line_edit_3d_lidar_id->text().toStdString());
    mqtt["SendAddress"] = Json::Value(LM_line_edit_SendAddress->text().toStdString());
    mqtt["SendPort"] = Json::Value(LM_line_edit_SendPort->text().toStdString());
    mqtt["info_topic"] = Json::Value(LM_line_edit_info_topic->text().toStdString());
    mqtt["status_topic"] = Json::Value(LM_line_edit_status_topic->text().toStdString());
    root["mqtt"] = Json::Value(mqtt);


    Json::Value web;
    web["ServerAddress"] = Json::Value(LM_line_edit_ServerAddress->text().toStdString());
    web["ServerPort"] = Json::Value(LM_line_edit_ServerPort->text().toStdString());
    web["UploadDataAddress"] = Json::Value(LM_line_edit_UploadDataAddress->text().toStdString());
    web["UplodaDeviceId"] = Json::Value(LM_line_edit_UplodaDeviceId->text().toStdString());
    root["web"] = Json::Value(web);


    //show
    Json::Value show;
    show["is_show_open"] = Json::Value(std::to_string( RB_line_show_is_open->isChecked()));
    show["is_show_classify"] = Json::Value(std::to_string( RB_line_show_classify->isChecked()));
    show["is_show_distance"] = Json::Value(std::to_string( RB_line_show_distance->isChecked()));
    show["is_show_velocit"] = Json::Value(std::to_string( RB_line_show_velocity->isChecked()));
    show["show_box_size"] = Json::Value(LM_line_show_box_size->text().toStdString());
    show["camera_mode"] = Json::Value(block_camera_mode->checkedId());
    root["show"] = Json::Value(show);


    Json::Value preprocessor;
    preprocessor["Area_height_down"] = Json::Value(LM_line_Area_height_down->text().toStdString());
    preprocessor["Area_height_top"] = Json::Value(LM_line_Area_height_top->text().toStdString());
    preprocessor["K"] = Json::Value(LM_line_edit_K->text().toStdString());
    preprocessor["euclidean_disatance"] = Json::Value(LM_line_euclidean_disatance->text().toStdString());
    preprocessor["interpolation_interval"] = Json::Value(LM_line_interpolation_interval->text().toStdString());
    preprocessor["m_grid_x"] = Json::Value(LM_line_m_grid_x->text().toStdString());
    preprocessor["m_grid_y"] = Json::Value(LM_line_m_grid_y->text().toStdString());
    preprocessor["m_grid_z"] = Json::Value(LM_line_m_grid_z->text().toStdString());
    preprocessor["resolution"] = Json::Value(LM_line_resolution->text().toStdString());
    preprocessor["difference_threshold"] = Json::Value(LM_line_difference_threshold->text().toStdString());
    preprocessor["start_dist"] = Json::Value(LM_line_start_dist->text().toStdString());

    preprocessor["cloudMapFrame"] = Json::Value(LM_line_cloudMapFrame->text().toStdString());
    preprocessor["save_bclold_isOpen"] = Json::Value(std::to_string( RB_line_save_bclold_isOpen->isChecked()));
    preprocessor["save_bclold_hour"] = Json::Value(LM_line_save_bclold_hour->text().toStdString());
    preprocessor["save_bclold_min"] = Json::Value(LM_line_save_bclold_min->text().toStdString());
    preprocessor["roi_limit"] = Json::Value(LM_line_roi_limit->text().toStdString());

    root["preprocessor"] = Json::Value(preprocessor);

    Json::Value Detector;
    Detector["Tolerance"] = Json::Value(LM_line_edit_Tolerance->text().toStdString());
    Detector["maxSize"] = Json::Value(LM_line_edit_maxSize->text().toStdString());
    Detector["minSize"] = Json::Value(LM_line_edit_minSize->text().toStdString());
    root["Detector"] = Json::Value(Detector);


    Json::Value Lidar;
    for(int i{0};LM_line_edit_lidar_IP.size()>i;i++)
    {
        Lidar["device_ip"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_IP[i]->text().toStdString());
        Lidar["device_port"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_device_port[i]->text().toStdString());
        Lidar["data_port"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_data_port[i]->text().toStdString());
        Lidar["x_offset"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_x[i]->text().toStdString());
        Lidar["y_offset"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_y[i]->text().toStdString());
        Lidar["z_offset"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_z[i]->text().toStdString());
        Lidar["setXAngle"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_picth[i]->text().toStdString());
        Lidar["setYAngle"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_roll[i]->text().toStdString());
        Lidar["setZAngle"+std::to_string(i)] = Json::Value(LM_line_edit_lidar_yaw[i]->text().toStdString());
    }
    root["Lidar"] = Json::Value(Lidar);

    Json::Value Camera;
    for(int i{0};LM_line_edit_camera_ID.size()>i;i++)
    {
        Camera["IP"+std::to_string(i)] = Json::Value(LM_line_edit_camera_IP[i]->text().toStdString());
        Camera["ID"+std::to_string(i)] = Json::Value(LM_line_edit_camera_ID[i]->text().toStdString());
        Camera["Pass"+std::to_string(i)] = Json::Value(LM_line_edit_camera_Pass[i]->text().toStdString());
    }
    root["Camera"] = Json::Value(Camera);

    Json::FastWriter writer;
    std::string json_string = writer.write(root);
    QString final_data = QString::fromStdString( json_string );
    emit sigSavePushButton(final_data);
}

void TaskListUi::getQRadiobuttonItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QRadioButton *&radiobutton, const QString &info)
{
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, radiobutton);
}
void TaskListUi::getQCheckBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QCheckBox *&checkbox, const QString &info)
{
    // checkbox->setStyleSheet(myStyleSheets::myCheckBox::tasklistUiCheckBox);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, checkbox);
}
void TaskListUi::getQLineEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QLineEdit *&lineedit, const QString &info)
{
    // lineedit->setStyleSheet(myStyleSheets::myLineEdit::tasklistUiLineEdit);
    lineedit->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, lineedit);
}
void TaskListUi::getQComboBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QComboBox *&combobox, const QString &info)
{
    // combobox->setStyleSheet(myStyleSheets::myCombox::tasklistUiComboBox);
    combobox->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, combobox);
}
void TaskListUi::getQSpinBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QSpinBox *&spinbox, const QString &info)
{
    // spinbox->setStyleSheet(myStyleSheets::mySpinBox::tasklistUiSpinBox);
    spinbox->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, spinbox);
}
void TaskListUi::getQLabelItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QLabel *&label, const QString &info)
{
    // spinbox->setStyleSheet(myStyleSheets::myLabel::tasklistUiComboBox);
    // label->adjustSize();
    label->setFixedSize(155, 39);
    // label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, label);
}
void TaskListUi::getQPushButtonItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QPushButton *&pushbutton, const QString &info)
{
    pushbutton->setMaximumWidth(150);
    // pushbutton->setAlignment(Qt::AlignCenter);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, pushbutton);
}

QCheckBox *TaskListUi::creteQCheckBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info)
{
    QCheckBox *modeBox = new QCheckBox;
    modeBox->setDisabled(true);
    // modeBox->setStyleSheet(myStyleSheets::myCheckBox::tasklistUiCheckBox);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, modeBox);
    return modeBox;
}

QLineEdit *TaskListUi::creteQlineEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info)
{
    QLineEdit *LineEdit = new QLineEdit("255;255;255");
    LineEdit->setDisabled(true);
    // LineEdit->setStyleSheet(myStyleSheets::myLineEdit::tasklistUiLineEdit);
    LineEdit->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, LineEdit);
    return LineEdit;
}

QComboBox *TaskListUi::creteQComboBoxEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info, const QStringList &list)
{
    QComboBox *comboBox = new QComboBox();
    // comboBox->setStyleSheet(myStyleSheets::myCombox::tasklistUiComboBox);
    comboBox->setDisabled(true);
    for (int i = 0; i < list.size(); i++)
    {
        comboBox->addItem(list.at(i));
    }
    comboBox->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, comboBox);
    return comboBox;
}



//    QTreeWidgetItemIterator It(mainTreeWidget);
//    while(*It)
//    {
//        qDebug() << (*It)->text(0);
//        It++;
//    }


//    int p{0};
//    int w{0};
//    for( auto child :  mainTreeWidget->children())
//    {
//        w++;
//        qDebug()<<"================================="<<w;
//        for(auto dat : child->children())
//        {
//            p++;
//            qDebug()<<"================================="<<p;
////            qDebug()<<dat->;
//        }
//    }
////    for()




//    //    QTreeWidgetItem *lidarParams=new QTreeWidgetItem();
//    //    mainTreeWidget->addTopLevelItem(lidarParams);
//    //    lidarParams->setText(0,QString("雷达参数"));

//    //mode
//    QTreeWidgetItem *Mode=new QTreeWidgetItem();
//    //Mode->setIcon(0,QIcon(":/res/images/param-mode.png"));
//    mainTreeWidget->addTopLevelItem(Mode);
//    Mode->setText(0,QString("类型"));

//    auto combo_box = new QComboBox(this);
//    auto spin_box = new QSpinBox(this);

//    getQComboBoxItem(mainTreeWidget,Mode,combo_box,"类型:");
//    getQSpinBoxItem(mainTreeWidget,Mode,spin_box,"数量:");

//    //vmap-param
//    QTreeWidgetItem *Point=new QTreeWidgetItem();
//    //Point->setIcon(0,QIcon(":/res/images/Point.png"));
//    mainTreeWidget->addTopLevelItem(Point);
//    Point->setText(0,QString("点"));

//    auto line_edit = new QLineEdit(this);
//    auto line_edit2 = new QLineEdit(this);
//    auto line_edit3 = new QLineEdit(this);
//    auto line_edit4 = new QLineEdit(this);
//    auto line_edit5 = new QLineEdit(this);
//    auto line_edit6 = new QLineEdit(this);

//    getQLineEditItem(mainTreeWidget,Point,line_edit,"x:");
//    getQLineEditItem(mainTreeWidget,Point,line_edit2,"y:");
//    getQLineEditItem(mainTreeWidget,Point,line_edit3,"z:");
//    getQLineEditItem(mainTreeWidget,Point,line_edit4,"w-dir:");
//    getQLineEditItem(mainTreeWidget,Point,line_edit5,"lat:");
//    getQLineEditItem(mainTreeWidget,Point,line_edit6,"lon:");

//    //point-type
//    QTreeWidgetItem *Point_type=new QTreeWidgetItem();
//    //Point_type->setIcon(0,QIcon(":/res/images/type.png"));
//    mainTreeWidget->addTopLevelItem(Point_type);
//    Point_type->setText(0,QString("属性"));

//    auto combo_box3 = new QComboBox(this);
//    auto combo_box4 = new QComboBox(this);
//    auto combo_box5 = new QComboBox(this);
//    auto combo_box6 = new QComboBox(this);
//    auto combo_box7 = new QComboBox(this);
//    auto combo_box8 = new QComboBox(this);
//    auto combo_box9 = new QComboBox(this);
//    auto combo_box10 = new QComboBox(this);

//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box3,"道路:");
//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box4,"场景:");
//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box5,"避障:");
//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box6,"方向:");
//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box7,"宽窄:");
//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box8,"坡度:");
//    getQComboBoxItem(mainTreeWidget,Point_type,combo_box9,"室内外:");

//    //parameter
//    QTreeWidgetItem *Parameter=new QTreeWidgetItem();
//    //Parameter->setIcon(0,QIcon(":/res/images/Link.png"));
//    mainTreeWidget->addTopLevelItem(Parameter);
//    Parameter->setText(0,QString("参数"));

//    auto line_edit7 = new QLineEdit(this);
//    //auto line_edit8 = new QLineEdit(this);
//    auto line_edit9 = new QLineEdit(this);
//    auto line_edit10 = new QLineEdit(this);

//    getQLineEditItem(mainTreeWidget,Parameter,line_edit7,"限速/编号:");
//    getQComboBoxItem(mainTreeWidget,Parameter,combo_box10,"链接:");
//    getQLineEditItem(mainTreeWidget,Parameter,line_edit9,"链接号:");
//    getQLineEditItem(mainTreeWidget,Parameter,line_edit10,"laneletid/楼层:");

//    //info
//    QTreeWidgetItem *infomessage=new QTreeWidgetItem();
//    //infomessage->setIcon(0,QIcon(":/res/images/infomessage.png"));
//    mainTreeWidget->addTopLevelItem(infomessage);
//    infomessage->setText(0,QString("信息"));

//    auto my_label = new QLabel(this);
//    auto my_label2 = new QLabel(this);

//    getQLabelItem(mainTreeWidget,infomessage,my_label,"vmap总数:");
//    getQLabelItem(mainTreeWidget,infomessage,my_label2,"lanelet2总数:");

//    //pcd-z
//    // QTreeWidgetItem *Point_z=new QTreeWidgetItem();
//    // Point_z->setIcon(0,QIcon(":/res/images/Point.png"));
//    // mainTreeWidget->addTopLevelItem(Point_z);
//    // Point_z->setText(0,QString("高度"));

//    // getQLineEditItem(mainTreeWidget,Point_z,mainwindow_->pcdzmax_edit,"z-max:");
//    // getQLineEditItem(mainTreeWidget,Point_z,mainwindow_->pcdzmin_edit,"z-min:");
//    // getQPushButtonItem(mainTreeWidget,Point_z,mainwindow->reload_pBtn,"刷新:");

//    //
//    QTreeWidgetItem *laneletInfo=new QTreeWidgetItem();
//    // laneletInfo->setIcon(0,QIcon(":/res/images/.png"));
//    mainTreeWidget->addTopLevelItem(laneletInfo);
//    laneletInfo->setText(0,QString("信息"));

//    auto line_edit11 = new QLineEdit(this);

//    getQLineEditItem(mainTreeWidget,laneletInfo,line_edit11,"规则ID:");
