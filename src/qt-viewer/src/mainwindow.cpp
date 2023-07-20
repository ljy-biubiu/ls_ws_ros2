#include "mainwindow.h"

MainWindow::MainWindow(QApplication *my_app_, QWidget *parent)
    : QMainWindow(parent), my_app(my_app_)
{
    qRegisterMetaType<PointCloudTPtr>("PointCloudTPtr");
    qRegisterMetaType<DectData>("DectData");
    qRegisterMetaType<QList<QList<PointT>>>("QList<QList<PointT>>");
    qRegisterMetaType<AlarmStatus>("AlarmStatus");

    setWindowTitle(tr("PortMonitor"));

    initObeject();
    initConnect();
    initPointCShow();
    initMenu();
    initToolBar();
    mainLayOut();
    mainEventCallback();

    /************************************************* 设置qss样式表 ********************************************/
    QFile file(":/qss/darkblue.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        my_app->setPalette(QPalette(QColor(paletteColor)));
        my_app->setStyleSheet(qss);
        file.close();
    }

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->main_title_bar->setParentWidget(this);
    this->setWindowIcon(QIcon(":/images/leishen.ico"));

    //************************************************** 加载启动动画 ********************************************/
    screen = new QSplashScreen(QPixmap(":/images/logo.jpg"));
    screen->show();
    my_app_->processEvents();

    usleep(1000 * 1000);
    ros_talk->start();
}

void MainWindow::initObeject()
{
    ros_talk = new RosTalk();
    frameWidgetLidar = new ImageWidget();
    frameWidgetCamera = new ImageWidget();
    mainImageWidget = new ImageWidget();
    // add_lidar = std::make_unique<AddLidar()
    main_title_bar = new MainTitleBar();
    paint_area = new PaintArea();
    setROI = new SetROI();

    paint_area->scroll = setROI->scrollarea;
    setROI->scrollarea->takeWidget();
    setROI->scrollarea->setWidget(paint_area);

    diary = new Diary();
    alarm = new Alarm();

    camera_viewer = new CameraViewer(CameraViewNub::CameraViewFir);
    camera_viewer2 = new CameraViewer(CameraViewNub::CameraViewSec);
    web_ui = new WebUi();
    add_lidar = new AddLidar();

    task_list_ui = new TaskListUi(this);
    camera_control = new CameraControl();
}

int lidar_cnt = 0;

void MainWindow::mainEventCallback()
{

    my_timer = new QTimer(this);
    my_timer->start(1000);
    connect(my_timer, &QTimer::timeout, [=]()
            {
                if (paint_area != nullptr && setROI != nullptr)
                {
                    paint_area_2setROI();
                }

                std::cout << "==================================" << std::endl;
                std::cout << "==================================" << std::endl;
                std::cout << "==================================" << std::endl;
                std::cout << "lidar_cnt:" << lidar_cnt << std::endl;
                lidar_cnt = 0; });
}

void MainWindow::paint_area_2setROI()
{
    for (int i = 0; i < AREAS; i++)
    {
        paint_area->area[i].Area_height_down = setROI->area[i].Area_height_down;
        paint_area->area[i].Area_height_top = setROI->area[i].Area_height_top;
        setROI->area[i].Area2D_point.clear();
        setROI->area[i].Area2D_point_T.clear();
        setROI->area[i].Area2D_point.append(paint_area->area[i].Area2D_point);
        setROI->area[i].Area2D_point_T.append(paint_area->area[i].Area2D_point_T);
    }
    setROI->showPoint();
}

void MainWindow::updateCameraImage()
{
}

void MainWindow::updateAlgPointCould()
{
}

void MainWindow::updatePointCould()
{
    //
    // static PointCloudTPtr msg;
    // msg.reset(new PointCloudT);

    // // this->params_event->getTotalParams().drive.lidar_drive.get_lidar_data(msg);

    // paint_area->xCloud->clear();
    // *paint_area->xCloud = *msg;
    // paint_area->update();

    // std::string name = "All_cloud";
    // this->viewer->removePointCloud(name);
    // pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(msg, "intensity");
    // this->viewer->addPointCloud(msg, color_handler, name);
    // this->viewer->updatePointCloud(msg, color_handler, name);

    // this->viewer->getRenderWindow()->GetInteractor()->Render();
    // qvtkOpenglNativeWidget->update();
}

// 0 other
// 2 AMR
// 1 people

// void RenderColor(PointCloudTPtr &msg)
// {
//     // 计算点云的高度范围
//     double min_height = std::numeric_limits<double>::max();
//     double max_height = -std::numeric_limits<double>::max();
//     for (size_t i = 0; i < msg->points.size(); ++i)
//     {
//         if (msg->points[i].z < min_height)
//         {
//             min_height = msg->points[i].z;
//         }
//         if (msg->points[i].z > max_height)
//         {
//             max_height = msg->points[i].z;
//         }
//     }

//     // // 设置点云颜色
//     // for (size_t i = 0; i < msg->points.size(); ++i)
//     // {
//     //     // 根据高度信息计算颜色值
//     //     msg->points[i].r = 0;
//     //     msg->points[i].g = 100 * (msg->points[i].z - min_height) / (max_height - min_height);
//     //     msg->points[i].b = 255 * (msg->points[i].z - min_height) / (max_height - min_height); // 使用科技蓝作为主色调
//     // }
// }

pcl::PointCloud<pcl::PointXYZRGBA>::Ptr RenderColor(pcl::PointCloud<pcl::PointXYZI>::Ptr msg)
{
    int i{0};
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr color_cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    color_cloud->resize(msg->size());

    for (auto &point : msg->points)
    {
        color_cloud->points[i].x = msg->points[i].x;
        color_cloud->points[i].y = msg->points[i].y;
        color_cloud->points[i].z = msg->points[i].z;
        i++;
    }
    return color_cloud;

    // // ... 在cloud_input中加载或生成PointXYZI点云数据 ...

    // pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_output(new pcl::PointCloud<pcl::PointXYZRGBA>);

    // // 计算强度的最大值和最小值
    // float intensity_min = std::numeric_limits<float>::max();
    // float intensity_max = std::numeric_limits<float>::min();

    // for (const auto &point_i : cloud_input->points)
    // {
    //     if (point_i.intensity < intensity_min)
    //         intensity_min = point_i.intensity;

    //     if (point_i.intensity > intensity_max)
    //         intensity_max = point_i.intensity;
    // }

    // // 定义颜色映射范围
    // uint8_t r_min = 0;   // 最小强度值对应的红色通道值
    // uint8_t r_max = 255; // 最大强度值对应的红色通道值

    // // 将每个点转换并添加到新的点云中，并给定对应的RGB颜色值
    // for (const auto &point_i : cloud_input->points)
    // {
    //     pcl::PointXYZRGBA point_rgba;

    //     // 设置点的坐标
    //     point_rgba.x = point_i.x;
    //     point_rgba.y = point_i.y;
    //     point_rgba.z = point_i.z;

    //     // 计算强度值在颜色映射范围内的归一化值
    //     float normalized_intensity = (point_i.intensity - intensity_min) / (intensity_max - intensity_min);

    //     // 根据归一化强度值设置RGB颜色
    //     point_rgba.r = static_cast<uint8_t>(r_min + normalized_intensity * (r_max - r_min));
    //     point_rgba.g = 0; // 绿色通道设为0
    //     point_rgba.b = 0; // 蓝色通道设为0

    //     cloud_output->push_back(point_rgba);
    // }

    // return cloud_output;
}

// #include "chrono.h"
#include <chrono>
// auto start_time = std::chrono::steady_clock::now();
// end_time = std::chrono::steady_clock::now();
// elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
// std::cout << "画框  elapsed time: " << elapsed_time.count() << " ms" << std::endl;

void MainWindow::show_dect_data(DectData msg)
{

    lidar_cnt++;

    auto start_time = std::chrono::steady_clock::now();

    paint_area->xCloud->clear();
    *paint_area->xCloud = *msg.Origin_Cloud;
    paint_area->update();

    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "paint_area 1 elapsed time: " << elapsed_time.count() << " ms" << std::endl;

    this->viewer->removeAllPointClouds();
    this->viewer->removeAllShapes();

    end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "removeAllPointClouds elapsed time: " << elapsed_time.count() << " ms" << std::endl;

    std::string ori_cloud_name = "ori_cloud";
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_color(new pcl::PointCloud<pcl::PointXYZRGBA>);
    *cloud_color = *RenderColor(msg.Origin_Cloud);

    end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "RenderColor elapsed time: " << elapsed_time.count() << " ms" << std::endl;

    // 将点云的高度属性与点的颜色值关联起来
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZRGBA> handler(cloud_color, "z");
    // 添加点云到可视化窗口
    this->viewer->addPointCloud<pcl::PointXYZRGBA>(cloud_color, handler, ori_cloud_name);

    // pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(msg.Origin_Cloud, "intensity");
    // this->viewer->addPointCloud(msg.Origin_Cloud, color_handler, ori_cloud_name);

    // this->viewer->addPointCloud(cloud_color, ori_cloud_name);

    // 设置颜色映射表
    this->viewer->setPointCloudRenderingProperties(
        pcl::visualization::PCL_VISUALIZER_LUT_RANGE, task_list_ui->get_show_lidar_height_min(), task_list_ui->get_show_lidar_height_max(), ori_cloud_name);

    end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "颜色值关联 显示  elapsed time: " << elapsed_time.count() << " ms" << std::endl;

    int i{0};
    for (auto dat : msg.ObjCloud_vec)
    {
        pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_color_(new pcl::PointCloud<pcl::PointXYZRGBA>);
        *cloud_color_ = *RenderColor(dat);
        std::string det_cloud_name = "det_cloud_" + std::to_string(i);
        this->viewer->addPointCloud(cloud_color_, det_cloud_name);
        i++;
    }
    ///////////////////////////////////////////////////////////////

    // std::vector<SendObjectInf> Data_vec_solo;
    // for (int i{0}; msg.Data_vec.size() > i; i++)
    // {
    //     int cnt_same{0};
    //     auto cur_str = std::to_string(msg.Data_vec[i].center_x);
    //     for (int j{0}; msg.Data_vec.size() > j; j++)
    //     {
    //         if (cur_str == std::to_string(msg.Data_vec[j].center_x))
    //         {
    //             cnt_same++;
    //         }
    //     }
    //     if (cnt_same == 1)
    //     {
    //         Data_vec_solo.push_back(msg.Data_vec[i]);
    //     }
    //     if (cnt_same > 1)
    //     {
    //         int exsit{0};
    //         for (auto &dat_sma : Data_vec_solo)
    //         {
    //             if (std::to_string(dat_sma.center_x) == std::to_string(msg.Data_vec[i].center_x))
    //             {
    //                 exsit = 1;
    //                 if (dat_sma.id < msg.Data_vec[i].id)
    //                 {
    //                     dat_sma.id = msg.Data_vec[i].id;
    //                 }
    //             }
    //         }
    //         if (exsit == 0)
    //         {
    //             Data_vec_solo.push_back(msg.Data_vec[i]);
    //         }
    //     }
    // }

    ///////////////////////////////////////////////////////////////

    for (auto dat : msg.Data_vec) // Data_vec_solo  msg.Data_vec
    {

        std::string cube = "box" + std::to_string(i);
        Eigen::Vector3f translation(dat.center_x, dat.center_y, dat.center_z);
        Eigen::Quaternionf quat = Eigen::Quaternionf::Identity();

        // Eigen::Quaternionf rotation(1, 0, 0, 0); //_cluster.heading * M_PI / 180.0
        quat = Eigen::AngleAxisf(dat.heading, Eigen::Vector3f::UnitZ()) * quat;
        this->viewer->addCube(translation, quat, dat.length, dat.width, dat.height, cube);

        // 设置线条属性
        this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_WIREFRAME, cube);
        // this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, line_width, );

        // this->viewer->setRepresentationToWireframeForAllActors();
        // this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, 0.15, cube);

        if (dat.kind_risk == "clash")
        {
            this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 0, cube);
        }
        else if (dat.kind_risk == "avoidance")
        {
            this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 0, cube);
        }
        else
        {
            this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 0, cube);
        }

        PointT linesLCenterPoint;
        linesLCenterPoint.x = dat.center_x;
        linesLCenterPoint.y = dat.center_y;
        linesLCenterPoint.z = dat.center_z;

        std::string sum_text;
        std::string classify_name;
        switch (dat.classify)
        {
        case 0:
            classify_name = "none";
            break;
        case 1:
            classify_name = "vehicle";
            break;
        case 2:
            classify_name = "non-vehicle";
            break;
        case 3:
            classify_name = "people";
            break;
        default:
            classify_name = "none";
            break;
        }

        auto trimDecimal = [=](std::string str)
        {
            size_t dot_pos = str.find(".");
            if (dot_pos != std::string::npos && dot_pos < str.size() - 3)
            {
                str = str.substr(0, dot_pos + 3);
            }
            return str;
        };

        sum_text = sum_text + "id : " + std::to_string(dat.id) + "\n";

        if (task_list_ui->get_show_distance())
        {
            sum_text = sum_text + "pos : (" + trimDecimal(std::to_string(dat.center_x)) + " ," + trimDecimal(std::to_string(dat.center_y)) + " ," + trimDecimal(std::to_string(dat.center_z)) + ")\n";
        }

        if (task_list_ui->get_show_classify())
        {
            sum_text = sum_text + "type : " + classify_name + "\n";
        }

        if (task_list_ui->get_show_velocity())
        {
            sum_text = sum_text + "speed : " + trimDecimal(std::to_string(dat.speed)) + "\n";
        }

        if (!task_list_ui->get_show_is_open())
        {
            sum_text = std::string();
        }
        // this->viewer->setRepresentationToWireframeForAllActors();
        // this->viewer->setRepresentationToSurfaceForAllActors();
        this->viewer->addText3D(sum_text, linesLCenterPoint,
                                task_list_ui->get_show_box_size(),
                                1, 1, 0, "line1Text3D_" + std::to_string(i));
        this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_SURFACE, "line1Text3D_" + std::to_string(i));
        // this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, 0.2, cube);
        i++;
    }

    end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "画框  elapsed time: " << elapsed_time.count() << " ms" << std::endl;

    // 2D paint
    vector<vector<PointT>> areaPoints;
    for (int i{0}; AREAS > i; i++)
    {
        vector<PointT> linePoints;
        for (int j{0}; this->paint_area->area[i].Area2D_point_T.size() > j; j++)
        {
            PointT point;
            point.x = this->paint_area->area[i].Area2D_point_T[j].x;
            point.y = this->paint_area->area[i].Area2D_point_T[j].y;
            point.z = this->paint_area->area[i].Area2D_point_T[j].z - task_list_ui->get_plane_D_data();
            linePoints.push_back(point);
        }
        areaPoints.push_back(linePoints);
    }

    for (int i{0}; areaPoints.size() > i; i++)
    {
        if (this->paint_area->area[i].Area2D_point_T.size() < 2)
            continue;
        for (int j{0}; areaPoints[i].size() - 1 > j; j++)
        {
            this->viewer->addLine(areaPoints[i][j], areaPoints[i][j + 1], 1, 0, 0, "line:" + to_string(i) + to_string(j));
            this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 2, "line:" + to_string(i) + to_string(j));
        }
    }

    end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    // std::cout << "画线 显示  elapsed time: " << elapsed_time.count() << " ms" << std::endl;

    this->viewer->getRenderWindow()->GetRenderers()->GetFirstRenderer()->Render();
    this->viewer->getRenderWindow()->Render();
    qvtkOpenglNativeWidget->update();

    // 计算函数执行耗时
    end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "算法点云数据处理 elapsed time: " << elapsed_time.count() << " ms" << std::endl;
}

void MainWindow::receive_lidar_driver(PointCloudTPtr msg)
{
    paint_area->xCloud->clear();
    *paint_area->xCloud = *msg;
    paint_area->update();

    std::string name = "All_cloud";
    this->viewer->removeAllPointClouds();
    this->viewer->removeAllShapes();
    // this->viewer->addPointCloud(msg, name);
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(msg, "intensity");
    this->viewer->addPointCloud(msg, color_handler, name);
    this->viewer->updatePointCloud(msg, color_handler, name);

    this->viewer->getRenderWindow()->GetInteractor()->Render();
    qvtkOpenglNativeWidget->update();
}
// PointCloudTPtr

void MainWindow::initPointCShow()
{
    qvtkOpenglNativeWidget = new QVTKOpenGLNativeWidget();

    auto renderer2 = vtkSmartPointer<vtkRenderer>::New();
    auto renderWindow2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderWindow2->AddRenderer(renderer2);
    this->viewer.reset(new pcl::visualization::PCLVisualizer(renderer2, renderWindow2, "All_cloud", false));

    qvtkOpenglNativeWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(qvtkOpenglNativeWidget->GetInteractor(), qvtkOpenglNativeWidget->GetRenderWindow());
    qvtkOpenglNativeWidget->update();

    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();

    viewer->setCameraPosition(0, 0, 50, 0, 0, 0, 0, 0, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::mainLayOut()
{

    this->mainLayout = new QVBoxLayout();
    this->headLayout = new QVBoxLayout();
    this->body_frame_layout = new QVBoxLayout();
    this->body_layout = new QHBoxLayout();
    this->left_body_layout = new QHBoxLayout();
    this->right_body_layout = new QVBoxLayout();

    this->right_camera_layout = new QHBoxLayout();
    this->right_data_layout = new QHBoxLayout();
    this->right_table_layout = new QHBoxLayout();

    this->paramsListLayout = new QVBoxLayout();
    this->vtkLayout = new QVBoxLayout();
    this->cameraLayout = new QVBoxLayout();
    this->imageWidget_layout = new QVBoxLayout();

    this->right_camera_widget = new QWidget();
    this->right_data_widget = new QWidget();
    this->right_table_widget = new QWidget();

    this->main_widget = new QWidget();

    main_widget->setLayout(mainLayout);
    this->setCentralWidget(main_widget);

    mainLayout->addLayout(headLayout);
    mainLayout->addLayout(body_frame_layout);
    mainLayout->setStretchFactor(headLayout, 1);
    mainLayout->setStretchFactor(body_frame_layout, 15);

    body_frame_layout->addWidget(mainImageWidget);
    mainImageWidget->setLayout(body_layout);

    headLayout->addWidget(main_title_bar);

    body_layout->addLayout(left_body_layout);
    body_layout->addLayout(right_body_layout);
    body_layout->setStretchFactor(left_body_layout, 9);
    body_layout->setStretchFactor(right_body_layout, 6);

    cameraLayout->addWidget(camera_viewer2);
    frameWidgetCamera->setLayout(cameraLayout);

    right_camera_layout->addWidget(camera_viewer);

    right_data_layout->addWidget(diary);
    right_data_layout->addWidget(alarm);
    right_data_layout->setStretchFactor(diary, 7);
    right_data_layout->setStretchFactor(alarm, 5);

    right_body_layout->addLayout(right_camera_layout);
    right_body_layout->addLayout(right_data_layout);
    right_body_layout->addLayout(right_table_layout);
    right_body_layout->setStretchFactor(right_camera_layout, 1);
    right_body_layout->setStretchFactor(right_data_layout, 1);
    right_body_layout->setStretchFactor(right_table_layout, 1);

    //    layoutBottomMargin

    right_table_layout->addWidget(web_ui);

    frameWidgetLidar->setLayout(vtkLayout);
    vtkLayout->addWidget(qvtkOpenglNativeWidget);
    paramsListLayout->addWidget(task_list_ui);

    imageWidget_layout->addWidget(frameWidgetLidar);

    left_body_layout->addLayout(paramsListLayout);
    left_body_layout->addLayout(imageWidget_layout);

    for (int i = 0; i < paramsListLayout->count(); ++i)
    {
        QWidget *w = paramsListLayout->itemAt(i)->widget();
        if (w != NULL)
            w->setVisible(false);
    }
}

/*删除layout*/
void MainWindow::deleteItem(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        //        // setParent为NULL，防止删除之后界面不消失
        //        if (child->widget())
        //        {
        //            child->widget()->setParent(nullptr);
        //            // delete child->widget();
        //        }
        //        else if (child->layout())
        //        {
        //            deleteItem(child->layout());
        //            child->layout()->deleteLater();
        //        }
        child->widget()->setParent(nullptr);
        delete child;
    }
}

void MainWindow::initMenu()
{
    // QMenuBar *menuBar = this->menuBar();
    // add three menus
    fileMenu = new QMenu(tr("&File"), this);
    viewMenu = new QMenu(tr("&View"), this);
    helpMenu = new QMenu(tr("&About"), this);

    // add actions and add it into corresponding menu
    view_mode = new QAction(tr("&首页"), this);
    view_mode->setShortcut(tr("ctrl+O"));
    view1_mode = new QAction(tr("&雷达"), this);
    view1_mode->setShortcut(tr("ctrl+P"));
    view2_mode = new QAction(tr("&相机"), this);
    view2_mode->setShortcut(tr("ctrl+Q"));

    param_set = new QAction(tr("&参数配置"), this);
    lidar_area_set = new QAction(tr("&区域绘制"), this);
    camera_control_ac = new QAction(tr("&相机控制"), this);

    save_point_cloud = new QAction(tr("&保存点云"), this);
    svae_background_pont_cloud = new QAction(tr("&保存背景点云"), this);

    qt_version = new QAction(tr("&QT_VERSION"), this);

    connect(view_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode_Action()));
    connect(view1_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode1_Action()));
    connect(view2_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode2_Action()));
    connect(param_set, SIGNAL(triggered(bool)), this, SLOT(param_set_Action()));
    connect(lidar_area_set, SIGNAL(triggered(bool)), this, SLOT(lidar_area_set_Action()));
    connect(save_point_cloud, SIGNAL(triggered(bool)), this, SLOT(save_point_cloud_set_Action()));
    connect(svae_background_pont_cloud, SIGNAL(triggered(bool)), this, SLOT(save_point_backgourd_cloud_set_Action()));
    connect(qt_version, SIGNAL(triggered(bool)), my_app, SLOT(aboutQt()));
    connect(camera_control_ac, SIGNAL(triggered(bool)), this, SLOT(camera_control_Action()));
}

void MainWindow::initToolBar()
{
    // add a toolbar and add its actions
    fileToolBar = new QToolBar(this);
    auto my_meun = new QMenu(this);

    //    fileToolBar->men
    //    fileToolBa
    //    fileMenu

    fileToolBar->addAction(view_mode);
    fileToolBar->addAction(view1_mode);
    fileToolBar->addAction(view2_mode);

    fileToolBar->addSeparator();

    fileToolBar->addAction(param_set);
    fileToolBar->addAction(lidar_area_set);
    fileToolBar->addAction(camera_control_ac);

    fileToolBar->addSeparator();

    fileToolBar->addAction(save_point_cloud);
    fileToolBar->addAction(svae_background_pont_cloud);

    fileToolBar->addSeparator();
    fileToolBar->addAction(qt_version);

    // addToolBar(Qt::LeftToolBarArea,fileToolBar);
    addToolBar(Qt::BottomToolBarArea, fileToolBar);
    //    static QMenu *fileMenu = menuBar()->addMenu ( tr ( "&File" ) );
    //    fileMenu->addAction(view_mode);
    //    this->add
    //    addToolBarBreak(Qt::BottomToolBarArea);
    //    addToolBar(Qt::BottomToolBarArea, toolBar);
}

// void emit_alarm_data(AlarmStatus);

void MainWindow::initConnect()
{
    QObject::connect(add_lidar, SIGNAL(SendSet(QString)), this, SLOT(params_set(QString)));
    QObject::connect(setROI, SIGNAL(sigChangeArea_index(int)), paint_area, SLOT(UpdateArea_index(int)));
    QObject::connect(setROI, SIGNAL(sigalareasize(int)), paint_area, SLOT(SlotAreaSize(int)));
    QObject::connect(setROI, SIGNAL(sigSaveAreaData()), this, SLOT(getAreaDatas()));
    QObject::connect(this, SIGNAL(emitTopicSetParams(QString)), ros_talk, SLOT(saveTopicParams(QString)));
    QObject::connect(ros_talk, SIGNAL(emit_lidar_drive(PointCloudTPtr)), this, SLOT(receive_lidar_driver(PointCloudTPtr)));
    QObject::connect(ros_talk, SIGNAL(emit_show_log(QString)), diary, SLOT(show_log(QString)));
    QObject::connect(ros_talk, SIGNAL(emit_decct_data(DectData)), this, SLOT(show_dect_data(DectData)));
    QObject::connect(this->task_list_ui, SIGNAL(sigSavePushButton(QString)), ros_talk, SLOT(saveLidarDatas(QString)));
    QObject::connect(ros_talk, SIGNAL(emitTopicParams(QString)), task_list_ui, SLOT(updateTopicParams(QString)));
    QObject::connect(this, SIGNAL(emit2dlists(QList<QList<PointT>>)), ros_talk, SLOT(save2dlists(QList<QList<PointT>>)));
    QObject::connect(ros_talk, SIGNAL(ros_to_qt_area_points(QList<QList<PointT>>)), this, SLOT(setAreaDatas(QList<QList<PointT>>)));

    QObject::connect(this, SIGNAL(emit_save_point_cloud(int)), ros_talk, SLOT(save_point_cloud(int)));
    QObject::connect(this, SIGNAL(emit_save_point_backgourd_cloud(int)), ros_talk, SLOT(save_point_backgroud_cloud(int)));
    QObject::connect(ros_talk, SIGNAL(emit_alarm_data(AlarmStatus)), alarm, SLOT(setLEDStatus(AlarmStatus)));

    //    connect (m_buttonGroup, SIGNAL (buttonClicked(int)), this, SLOT(onBtnFunc(int)));void setViewerMode(int);
    QObject::connect(ros_talk, SIGNAL(emit_camera_drive(QPixmap, QString)), camera_viewer, SLOT(setCameraMat(QPixmap, QString)));
    QObject::connect(ros_talk, SIGNAL(emit_camera_drive(QPixmap, QString)), camera_viewer2, SLOT(setCameraMat(QPixmap, QString)));
    QObject::connect(task_list_ui->block_camera_mode, SIGNAL(buttonClicked(int)), camera_viewer, SLOT(setViewerMode(int)));
    QObject::connect(task_list_ui->block_camera_mode, SIGNAL(buttonClicked(int)), camera_viewer2, SLOT(setViewerMode(int)));
    QObject::connect(task_list_ui->type_camera_mode, SIGNAL(buttonClicked(int)), ros_talk, SLOT(setCameraTypeMode(int)));
    QObject::connect(task_list_ui->type_lidar_mode, SIGNAL(buttonClicked(int)), ros_talk, SLOT(setLidarTypeMode(int)));

    QObject::connect(camera_control, SIGNAL(emitCameraControlCmd(int)), ros_talk, SLOT(setCameraControlCmd(int)));

    // void setLEDStatus( const AlarmStatus& msg  );
    //    setAreaDatas(QList<QList<PointT>> msg);
}

void MainWindow::createActions()
{
}

void MainWindow::save_point_backgourd_cloud_set_Action()
{
    // QMessageBox mb(QMessageBox::NoIcon,"提示","按一下",QMessageBox::Yes|QMessageBox::No,&w);
    QMessageBox mb(this);
    mb.setWindowTitle("提示");
    mb.setText("是否保存当前背景点云");
    /*QPushButton *but1=*/mb.addButton("是", QMessageBox ::AcceptRole);
    /*QPushButton *but2=*/mb.addButton("否", QMessageBox ::RejectRole);
    mb.show();
    switch (mb.exec())

    {
    case QMessageBox::AcceptRole:
        QMessageBox::information(this, "提示", ""); // 默认是模态的
        emit emit_save_point_backgourd_cloud(1);
        break;
        //    case QMessageBox::RejectRole:
        ////        QMessageBox::critical(this,"错误","wrong");//默认是模态的
        //        break;
    }
}

void MainWindow::save_point_cloud_set_Action()
{
    // QMessageBox mb(QMessageBox::NoIcon,"提示","按一下",QMessageBox::Yes|QMessageBox::No,&w);
    QMessageBox mb(this);
    mb.setWindowTitle("提示");
    mb.setText("是否保存当前点云");
    /*QPushButton *but1=*/mb.addButton("是", QMessageBox ::AcceptRole);
    /*QPushButton *but2=*/mb.addButton("否", QMessageBox ::RejectRole);
    mb.show();
    switch (mb.exec())

    {
    case QMessageBox::AcceptRole:
        QMessageBox::information(this, "提示", ""); // 默认是模态的
        emit emit_save_point_cloud(1);
        break;
        //    case QMessageBox::RejectRole:
        ////        QMessageBox::critical(this,"错误","wrong");//默认是模态的
        //        break;
    }
}

void MainWindow::param_set_Action()
{
    for (int i = 0; i < paramsListLayout->count(); ++i)
    {
        QWidget *w = paramsListLayout->itemAt(i)->widget();
        if (w != NULL)
            w->setVisible(true);
    }
}

void MainWindow::lidar_area_set_Action()
{
    this->setROI->show();
    this->setROI->showMaximized();
}

void MainWindow::view_mode_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(mainImageWidget);
    mainImageWidget->setLayout(body_layout);
    imageWidget_layout->addWidget(frameWidgetLidar);

    camera_viewer->setInputNum(CameraViewNub::CameraViewFir);
    camera_viewer2->setInputNum(CameraViewNub::CameraViewFir);
}

void MainWindow::view_mode1_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(frameWidgetLidar);
}

void MainWindow::view_mode2_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(frameWidgetCamera);

    camera_viewer->setInputNum(CameraViewNub::CameraViewSec);
    camera_viewer2->setInputNum(CameraViewNub::CameraViewSec);
}

void MainWindow::camera_control_Action()
{
    camera_control->show();
}

CameraViewer *MainWindow::getCameraWidget()
{
    return this->camera_viewer;
}

// void MainWindow::getAreaDatas()
// { }

void MainWindow::getAreaDatas()
{

    QList<QList<PointT>> area_lists;

    for (int i{0}; AREAS > i; i++)
    {
        area_lists.push_back(this->paint_area->area[i].Area2D_point_T);
    }

    emit emit2dlists(area_lists);
}

void MainWindow::setAreaDatas(QList<QList<PointT>> msg)
{
    std::cout << "setAreaDatas" << std::endl;
    for (int i{0}; msg.size() > i; i++)
    {
        this->paint_area->area[i].Area2D_point_T = msg[i];
    }
}

void MainWindow::params_set(QString msg)
{
    emit emitTopicSetParams(msg);
    //   qDebug() << "updateTopicParams:" << msg;
    //   add_lidar->ShowData(msg);
}
