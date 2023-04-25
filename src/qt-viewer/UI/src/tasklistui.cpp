#include "tasklistui.h"
#include "qdebug.h"
#include "QHBoxLayout"
#include <iostream>
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

    //雷达参数
    QTreeWidgetItem *lidarParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(lidarParams);
    lidarParams->setText(0, QString("雷达参数"));


    for (int i = 0; i < 1; i++)
    {
        QTreeWidgetItem *lidarParams_1 = new QTreeWidgetItem();
        lidarParams->addChild(lidarParams_1); ///
        lidarParams_1->setText(0, QString("雷达 ") + QString::number(i + 1));

        LM_line_edit_lidar_IP = new QLineEdit(this);
        LM_line_edit_lidar_device_port = new QLineEdit(this);
        LM_line_edit_lidar_data_port = new QLineEdit(this);
        LM_line_edit_lidar_x = new QLineEdit(this);
        LM_line_edit_lidar_y = new QLineEdit(this);
        LM_line_edit_lidar_z = new QLineEdit(this);
        LM_line_edit_lidar_picth = new QLineEdit(this);
        LM_line_edit_lidar_roll = new QLineEdit(this);
        LM_line_edit_lidar_yaw = new QLineEdit(this);

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_IP, "IP"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_device_port, "Device_Port"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_data_port, "Data_Port"+QString::fromStdString( std::to_string(i)));

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_x, "x_offset"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_y, "y_offset"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_z, "z_offset"+QString::fromStdString( std::to_string(i)));

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_picth, "pitch"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_roll, "roll"+QString::fromStdString( std::to_string(i)));
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_lidar_yaw, "yaw"+QString::fromStdString( std::to_string(i)));

    }

    //摄像头
    QTreeWidgetItem *cameraParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(cameraParams);
    cameraParams->setText(0, QString("摄像头参数"));

    for (int i = 0; i < 1; i++)
    {
        QTreeWidgetItem *cameraParams_1 = new QTreeWidgetItem();
        cameraParams->addChild(cameraParams_1); ///
        cameraParams_1->setText(0, QString("摄像头 ") + QString::number(i + 1));

        LM_line_edit_camera_IP = new QLineEdit(this);
        LM_line_edit_camera_ID = new QLineEdit(this);
        LM_line_edit_camera_Pass = new QLineEdit(this);


        getQLineEditItem(mainTreeWidget, cameraParams_1, LM_line_edit_camera_IP, "ID"+ QString::number(i + 1));
        getQLineEditItem(mainTreeWidget, cameraParams_1, LM_line_edit_camera_ID, "IP"+ QString::number(i + 1));
        getQLineEditItem(mainTreeWidget, cameraParams_1, LM_line_edit_camera_Pass, "Pass"+ QString::number(i + 1));

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

        getQLineEditItem(mainTreeWidget, detectorParams, LM_line_edit_Tolerance, "Tolerance");
        getQLineEditItem(mainTreeWidget, detectorParams, LM_line_edit_maxSize, "maxSize");
        getQLineEditItem(mainTreeWidget, detectorParams, LM_line_edit_minSize, "minSize");

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
        RB_line_save_bclold_isOpen = new QRadioButton(this);
        LM_line_save_bclold_hour = new QLineEdit(this);
        LM_line_save_bclold_min = new QLineEdit(this);
        LM_line_roi_limit = new QLineEdit(this);
        LM_line_detect_text_size = new QLineEdit(this);

        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_Area_height_down, "Area_height_down");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_Area_height_top, "Area_height_top");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_edit_K, "K");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_euclidean_disatance, "euclidean_disatance");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_interpolation_interval, "interpolation_interval");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_m_grid_x, "m_grid_x");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_m_grid_y, "m_grid_y");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_m_grid_z, "m_grid_z");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_resolution, "resolution");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_start_dist, "start_dist");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_cloudMapFrame, "cloudMapFrame");
        getQRadiobuttonItem(mainTreeWidget, preprocessorParams, RB_line_save_bclold_isOpen, "save_bclold_isOpen");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_save_bclold_hour, "save_bclold_hour");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_save_bclold_min, "save_bclold_min");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_roi_limit, "roi_limit");
        getQLineEditItem(mainTreeWidget, preprocessorParams, LM_line_detect_text_size, "detect_text_size");

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


        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_ServerAddress, "ServerAddress");
        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_ServerPort, "ServerPort");
        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_UploadDataAddress, "UploadDataAddress");
        getQLineEditItem(mainTreeWidget, webParams, LM_line_edit_UplodaDeviceId, "UplodaDeviceId");

    }


    //mqtt配置
    QTreeWidgetItem *mqttParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(mqttParams);
    mqttParams->setText(0, QString("网络配置参数"));

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


    //按钮
    comfire_button = new QPushButton(this);
    comfire_button->setText("保存");
    comfire_button->setMaximumSize(380, 30);
    comfire_button->setMinimumSize(380, 30);
    mainTreeWidget->expandAll();
    this->setMinimumWidth(400);
    this->setMaximumWidth(400);
////        this->setWindowFlags(Qt::FramelessWindowHint);

    QObject::connect(this->comfire_button, &QPushButton::clicked, this, &TaskListUi::savePushButton);

    mainLayout_H->addWidget(comfire_button);

}

void TaskListUi::updateTopicParams(QString msg)
{
    //    vec_lidar_datas

    qDebug()<<"updateTopicParams";
    Json::Value parameter_server;
    Json::Reader reader;
    reader.parse(msg.toStdString(), parameter_server); // LidarParam.LidarParam0.IP

    //mqtt
    LM_line_edit_SendPort->setText(QString::fromStdString( parameter_server["mqtt"]["SendPort"].asString()).left(15));
    LM_line_edit_3d_lidar_id->setText(QString::fromStdString( parameter_server["mqtt"]["3d_lidar_id"].asString()).left(15));
    LM_line_edit_SendAddress->setText(QString::fromStdString( parameter_server["mqtt"]["SendAddress"].asString()).left(15));
    LM_line_edit_info_topic->setText(QString::fromStdString( parameter_server["mqtt"]["info_topic"].asString()).left(15));
    LM_line_edit_status_topic->setText(QString::fromStdString( parameter_server["mqtt"]["status_topic"].asString()).left(15));

    //web
    LM_line_edit_ServerAddress->setText(QString::fromStdString( parameter_server["web"]["ServerAddress"].asString()).left(15));
    LM_line_edit_ServerPort->setText(QString::fromStdString( parameter_server["web"]["ServerPort"].asString()).left(15));
    LM_line_edit_UploadDataAddress->setText(QString::fromStdString( parameter_server["web"]["UploadDataAddress"].asString()).left(15));
    LM_line_edit_UplodaDeviceId->setText(QString::fromStdString( parameter_server["web"]["UplodaDeviceId"].asString()).left(15));


    //preprocessor
    LM_line_Area_height_down->setText(QString::fromStdString( parameter_server["preprocessor"]["Area_height_down"].asString()).left(8));
    LM_line_Area_height_top->setText(QString::fromStdString( parameter_server["preprocessor"]["Area_height_top"].asString()).left(8));
    LM_line_edit_K->setText(QString::fromStdString( parameter_server["preprocessor"]["K"].asString()).left(8));
    LM_line_euclidean_disatance->setText(QString::fromStdString( parameter_server["preprocessor"]["euclidean_disatance"].asString()).left(8));
    LM_line_interpolation_interval->setText(QString::fromStdString( parameter_server["preprocessor"]["interpolation_interval"].asString()).left(8));
    LM_line_m_grid_x->setText(QString::fromStdString( parameter_server["preprocessor"]["m_grid_x"].asString()).left(8));
    LM_line_m_grid_y->setText(QString::fromStdString( parameter_server["preprocessor"]["m_grid_y"].asString()).left(8));
    LM_line_m_grid_z->setText(QString::fromStdString( parameter_server["preprocessor"]["m_grid_z"].asString()).left(8));
    LM_line_resolution->setText(QString::fromStdString( parameter_server["preprocessor"]["resolution"].asString()).left(8));
    LM_line_start_dist->setText(QString::fromStdString( parameter_server["preprocessor"]["start_dist"].asString()).left(8));

    LM_line_cloudMapFrame->setText(QString::fromStdString( parameter_server["preprocessor"]["cloudMapFrame"].asString()).left(8));
    RB_line_save_bclold_isOpen->setChecked(std::stoi(parameter_server["preprocessor"]["save_bclold_isOpen"].asString()));
//    RB_line_save_bclold_isOpen->setText(QString::fromStdString( parameter_server["preprocessor"]["save_bclold_isOpen"].asString()).left(8));
    LM_line_save_bclold_hour->setText(QString::fromStdString( parameter_server["preprocessor"]["save_bclold_hour"].asString()).left(8));
    LM_line_save_bclold_min->setText(QString::fromStdString( parameter_server["preprocessor"]["save_bclold_min"].asString()).left(8));
    LM_line_roi_limit->setText(QString::fromStdString( parameter_server["preprocessor"]["roi_limit"].asString()).left(8));

//    LM_line_detect_text_size, "detect_text_size");


    //Detector
    LM_line_edit_Tolerance->setText(QString::fromStdString( parameter_server["Detector"]["Tolerance"].asString()).left(8));
    LM_line_edit_maxSize->setText(QString::fromStdString( parameter_server["Detector"]["maxSize"].asString()).left(8));
    LM_line_edit_minSize->setText(QString::fromStdString( parameter_server["Detector"]["minSize"].asString()).left(8));


    //Lidar
    LM_line_edit_lidar_IP->setText(QString::fromStdString( parameter_server["Lidar"]["device_ip"].asString()).left(15));
    LM_line_edit_lidar_device_port->setText(QString::fromStdString( parameter_server["Lidar"]["device_port"].asString()).left(15));
    LM_line_edit_lidar_data_port->setText(QString::fromStdString( parameter_server["Lidar"]["data_port"].asString()).left(15));
    LM_line_edit_lidar_x->setText(QString::fromStdString( parameter_server["Lidar"]["x_offset"].asString()).left(10));
    LM_line_edit_lidar_y->setText(QString::fromStdString( parameter_server["Lidar"]["y_offset"].asString()).left(10));
    LM_line_edit_lidar_z->setText(QString::fromStdString( parameter_server["Lidar"]["z_offset"].asString()).left(10));
    LM_line_edit_lidar_picth->setText(QString::fromStdString( parameter_server["Lidar"]["setXAngle"].asString()).left(10));
    LM_line_edit_lidar_roll->setText(QString::fromStdString( parameter_server["Lidar"]["setYAngle"].asString()).left(10));
    LM_line_edit_lidar_yaw->setText(QString::fromStdString( parameter_server["Lidar"]["setZAngle"].asString()).left(10));


    //Camera
    LM_line_edit_camera_IP->setText(QString::fromStdString( parameter_server["Camera"]["IP"].asString()).left(15));
    LM_line_edit_camera_ID->setText(QString::fromStdString( parameter_server["Camera"]["ID"].asString()).left(15));
    LM_line_edit_camera_Pass->setText(QString::fromStdString( parameter_server["Camera"]["Pass"].asString()).left(15));



    //    for (int i = 0; i < 14; i++)
    //    {
    //        vec_lidar_datas[2][i]->setText(QString::fromStdString( parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["IP"].asString()));
    //        vec_lidar_datas[3][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["Port"].asString()));

    //        vec_lidar_datas[2][i]->setText(QString::fromStdString( parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["x"].asString()));
    //        vec_lidar_datas[3][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["y"].asString()));
    //        vec_lidar_datas[4][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["z"].asString()));
    //        vec_lidar_datas[5][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["pitch"].asString()));
    //        vec_lidar_datas[6][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["roll"].asString()));
    //        vec_lidar_datas[7][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["yaw"].asString()));
    //    }
    //this->update();
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
    Lidar["device_ip"] = Json::Value(LM_line_edit_lidar_IP->text().toStdString());
    Lidar["device_port"] = Json::Value(LM_line_edit_lidar_device_port->text().toStdString());
    Lidar["data_port"] = Json::Value(LM_line_edit_lidar_data_port->text().toStdString());
    Lidar["x_offset"] = Json::Value(LM_line_edit_lidar_x->text().toStdString());
    Lidar["y_offset"] = Json::Value(LM_line_edit_lidar_y->text().toStdString());
    Lidar["z_offset"] = Json::Value(LM_line_edit_lidar_z->text().toStdString());
    Lidar["setXAngle"] = Json::Value(LM_line_edit_lidar_picth->text().toStdString());
    Lidar["setYAngle"] = Json::Value(LM_line_edit_lidar_roll->text().toStdString());
    Lidar["setZAngle"] = Json::Value(LM_line_edit_lidar_yaw->text().toStdString());
    root["Lidar"] = Json::Value(Lidar);

    Json::Value Camera;
    Camera["IP"] = Json::Value(LM_line_edit_camera_IP->text().toStdString());
    Camera["ID"] = Json::Value(LM_line_edit_camera_ID->text().toStdString());
    Camera["Pass"] = Json::Value(LM_line_edit_camera_Pass->text().toStdString());
    root["Camera"] = Json::Value(Camera);

    //    root["SumParams"] = Json::Value(json_dat);
    QString final_data = QString::fromStdString( root.toStyledString() );
    emit sigSavePushButton(final_data);

    //        dat->
    //        json_dat["IP"] = Json::Value(dat->text().toStdString());
    //        // 子节点挂到根节点上
    //        LidarParams["LidarParam" + std::to_string(i)] = Json::Value(json_dat);

    //    for (int i = 0; i < 14; i++)
    //    {
    //        // 子节点
    //        Json::Value LidarParam1;
    //        // 子节点属性
    //        LidarParam1["IP"] = Json::Value(msg[0][i]->text().toStdString());
    //        LidarParam1["Port"] = Json::Value(msg[1][i]->text().toStdString());
    //        LidarParam1["x"] = Json::Value(msg[2][i]->text().toStdString());
    //        LidarParam1["y"] = Json::Value(msg[3][i]->text().toStdString());
    //        LidarParam1["z"] = Json::Value(msg[4][i]->text().toStdString());
    //        LidarParam1["pitch"] = Json::Value(msg[5][i]->text().toStdString());
    //        LidarParam1["roll"] = Json::Value(msg[6][i]->text().toStdString());
    //        LidarParam1["yaw"] = Json::Value(msg[7][i]->text().toStdString());
    //        // 子节点挂到根节点上
    //        LidarParams["LidarParam" + std::to_string(i)] = Json::Value(LidarParam1);
    //    }

    //    root["LidarParam"] = Json::Value(LidarParams);

    //    std_msgs::msg::String str;
    //    str.data = root.toStyledString();


    //    emit sigSavePushButton(vec_lidar_datas);
    //    qDebug() << "==================================00000000000000";
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
