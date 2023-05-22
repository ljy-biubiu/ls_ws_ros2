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

    //    /******************************************** 加载启动动画 ********************************************/
    QPixmap pixmap(":/images/logo.jpg");
    screen = new QSplashScreen(pixmap);
    screen->show();

    usleep(1000*1000);
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
}

void MainWindow::mainEventCallback()
{

    my_timer = new QTimer(this);
    my_timer->start(100);
    connect(my_timer, &QTimer::timeout, [=]()
    {
        if(paint_area != nullptr && setROI != nullptr)
        {
            paint_area_2setROI();
        } });
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
    static PointCloudTPtr msg;
    msg.reset(new PointCloudT);

    // this->params_event->getTotalParams().drive.lidar_drive.get_lidar_data(msg);

    paint_area->xCloud->clear();
    *paint_area->xCloud = *msg;
    paint_area->update();

    std::string name = "All_cloud";
    this->viewer->removePointCloud(name);
    this->viewer->addPointCloud(msg, name);
    this->viewer->updatePointCloud(msg, name);

    this->viewer->getRenderWindow()->GetInteractor()->Render();
    qvtkOpenglNativeWidget->update();
}

// 0 other
// 2 AMR
// 1 people

void MainWindow::show_dect_data(DectData msg)
{
    //    return;
    paint_area->xCloud->clear();
    *paint_area->xCloud = *msg.Origin_Cloud;
    paint_area->update();

    this->viewer->removeAllPointClouds();
    this->viewer->removeAllShapes();

    std::string ori_cloud_name = "ori_cloud";
    this->viewer->addPointCloud(msg.Origin_Cloud, ori_cloud_name);

    int i{0};
    for (auto dat : msg.ObjCloud_vec)
    {
        // *dat;
        std::string det_cloud_name = "det_cloud_" + std::to_string(i);
        this->viewer->addPointCloud(dat, det_cloud_name);
        i++;
    }

    for (auto dat : msg.Data_vec)
    {
        std::string cube = "box" + std::to_string(i);
        Eigen::Vector3f translation(dat.center_x, dat.center_y, dat.center_z);
        Eigen::Quaternionf rotation(1, 0, 0, 0); //_cluster.heading * M_PI / 180.0
        this->viewer->addCube(translation, rotation, dat.length, dat.width, dat.height, cube);
        this->viewer->setRepresentationToWireframeForAllActors();

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
            classify_name = "other";
            break;
        case 2:
            classify_name = "AMR";
            break;
        case 1:
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

        if (task_list_ui->RB_line_show_distance->isChecked())
        {
            sum_text = sum_text + trimDecimal(std::to_string(dat.distance)) + "\n";
        }

        if (task_list_ui->RB_line_show_classify->isChecked())
        {
            sum_text = sum_text + "classify : " + classify_name + "\n";
        }

        if (task_list_ui->RB_line_show_velocity->isChecked())
        {
            sum_text = sum_text + "speed : " + trimDecimal(std::to_string(dat.speed)) + "\n";
        }

        if (!task_list_ui->RB_line_show_is_open->isChecked())
        {
            sum_text = std::string();
        }

        this->viewer->addText3D(sum_text, linesLCenterPoint,
                                std::stod(task_list_ui->LM_line_show_box_size->text().toStdString() == std::string() ? std::string("1") : task_list_ui->LM_line_show_box_size->text().toStdString()),
                                1, 1, 0, "line1Text3D_" + std::to_string(i));
        this->viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, 0.4, cube);
        i++;
    }

    // 2D paint
    vector<vector<PointT>> areaPoints;
    for (int i{0}; AREAS > i; i++)
    {
        vector<PointT> linePoints;
        //        Point.x = this->paint_area->area[i].Area2D_point_T.x;
        //        LinePoints.push_back(this->paint_area->area[i].Area2D_point_T);
        for (int j{0}; this->paint_area->area[i].Area2D_point_T.size() > j; j++)
        {
            PointT point;
            point.x = this->paint_area->area[i].Area2D_point_T[j].x;
            point.y = this->paint_area->area[i].Area2D_point_T[j].y;
            point.z = this->paint_area->area[i].Area2D_point_T[j].z;
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

    this->viewer->getRenderWindow()->GetRenderers()->GetFirstRenderer()->Render();
    this->viewer->getRenderWindow()->Render();
    qvtkOpenglNativeWidget->update();
    // std::cout << "*******************************" << std::endl;
}

void MainWindow::receive_lidar_driver(PointCloudTPtr msg)
{

    paint_area->xCloud->clear();
    *paint_area->xCloud = *msg;
    paint_area->update();

    std::string name = "All_cloud";
    this->viewer->removePointCloud(name);
    this->viewer->addPointCloud(msg, name);
    this->viewer->updatePointCloud(msg, name);

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
    QObject::connect(ros_talk, SIGNAL(emit_camera_drive(QPixmap,QString)), camera_viewer, SLOT(setCameraMat(QPixmap,QString)));
    QObject::connect(ros_talk, SIGNAL(emit_camera_drive(QPixmap,QString)), camera_viewer2, SLOT(setCameraMat(QPixmap,QString)));
    QObject::connect(task_list_ui->block_camera_mode, SIGNAL(buttonClicked(int)), camera_viewer, SLOT(setViewerMode(int)));
    QObject::connect(task_list_ui->block_camera_mode, SIGNAL(buttonClicked(int)), camera_viewer2, SLOT(setViewerMode(int)));

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
    //    this->add_lidar->show();
    //    task_list_ui->show();
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
