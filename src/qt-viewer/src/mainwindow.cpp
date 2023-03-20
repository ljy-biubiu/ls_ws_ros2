#include "mainwindow.h"

MainWindow::MainWindow(QApplication *my_app_, QWidget *parent)
    : QMainWindow(parent), my_app(my_app_)
{
    qRegisterMetaType<PointCloudTPtr>("PointCloudTPtr");

    setWindowTitle(tr("PortMonitor"));

    initObeject();
    initConnect();
    initPointCShow();
    initMenu();
    initToolBar();
    mainLayOut();
    mainEventCallback();

    /******************************************** 设置qss样式表 ********************************************/
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

    // auto aaa = std::make_unique<TaskListUi>(this);
    // aaa->show();
}

void MainWindow::initObeject()
{
    ros_talk = new RosTalk();
    imageWidget = new ImageWidget();
    imageWidget2 = new ImageWidget();
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

    camera_viewer = new CameraViewer();
    camera_viewer2 = new CameraViewer();
    web_ui = new WebUi();
    add_lidar = new AddLidar();
}

void MainWindow::mainEventCallback()
{
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
    // cv::Mat cur_image;
    // if (!this->cameraDriveInterface->get_camera_data(cur_image))
    // {
    //     return;
    // }

    // this->camera_viewer->setCameraMat(cur_image);
    // this->camera_viewer2->setCameraMat(cur_image);
}

void MainWindow::updateAlgPointCould()
{
}

void MainWindow::updatePointCould()
{
    //
    static PointCloudTPtr msg;
    msg.reset(new PointCloudT);

    //this->params_event->getTotalParams().drive.lidar_drive.get_lidar_data(msg);

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
//PointCloudTPtr

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
    this->left_body_layout = new QVBoxLayout();
    this->right_body_layout = new QVBoxLayout();

    this->right_camera_layout = new QHBoxLayout();
    this->right_data_layout = new QHBoxLayout();
    this->right_table_layout = new QHBoxLayout();

    this->vtkLayout = new QVBoxLayout();
    this->cameraLayout = new QVBoxLayout();

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
    imageWidget2->setLayout(cameraLayout);

    ///////////////////////////////////////////////////////////////////////////////

    auto a = new QWidget();
    auto b = new QWidget();

    // 设置背景黑色
    QPalette palBackGround(a->palette());
    palBackGround.setColor(QPalette::Background, QColor(23, 23, 23));
    a->setAutoFillBackground(true);
    a->setPalette(palBackGround);

    // 设置背景黑色
    QPalette palBackGround_b(b->palette());
    palBackGround_b.setColor(QPalette::Background, QColor(23, 23, 23));
    b->setAutoFillBackground(true);
    b->setPalette(palBackGround_b);

    right_body_layout->setMargin(0);
    right_camera_layout->setMargin(0);
    right_body_layout->setSpacing(0);
    right_camera_layout->setSpacing(0);

    ////////////////////////////////////////////////////////////////////////////////

    right_camera_layout->addWidget(a);
    right_camera_layout->addWidget(camera_viewer);
    right_camera_layout->addWidget(b);

    right_camera_layout->setStretchFactor(a, 1);
    right_camera_layout->setStretchFactor(camera_viewer, 7);
    right_camera_layout->setStretchFactor(b, 1);

    right_data_layout->addWidget(diary);
    right_data_layout->addWidget(alarm);
    right_data_layout->setStretchFactor(diary, 7);
    right_data_layout->setStretchFactor(alarm, 5);

    //    right_body_layout->addWidget(camera_viewer);
    right_body_layout->addLayout(right_camera_layout);
    right_body_layout->addLayout(right_data_layout);
    right_body_layout->addLayout(right_table_layout);
    right_body_layout->setStretchFactor(right_camera_layout, 1);
    right_body_layout->setStretchFactor(right_data_layout, 1);
    right_body_layout->setStretchFactor(right_table_layout, 1);

    //    layoutBottomMargin

    right_table_layout->addWidget(web_ui);

    imageWidget->setLayout(vtkLayout);
    vtkLayout->addWidget(qvtkOpenglNativeWidget);
    left_body_layout->addWidget(imageWidget);
    // left_body_layout->addWidget(camera_viewer);
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
    view_mode = new QAction(tr("&Mode"), this);
    view_mode->setShortcut(tr("ctrl+O"));
    view1_mode = new QAction(tr("&Mode1"), this);
    view1_mode->setShortcut(tr("ctrl+P"));
    view2_mode = new QAction(tr("&Mode2"), this);
    view2_mode->setShortcut(tr("ctrl+Q"));

    param_set = new QAction(tr("&Params"), this);
    lidar_area_set = new QAction(tr("&Areas"), this);

    connect(view_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode_Action()));
    connect(view1_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode1_Action()));
    connect(view2_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode2_Action()));
    connect(param_set, SIGNAL(triggered(bool)), this, SLOT(param_set_Action()));
    connect(lidar_area_set, SIGNAL(triggered(bool)), this, SLOT(lidar_area_set_Action()));
}

void MainWindow::initToolBar()
{
    // add a toolbar and add its actions
    fileToolBar = new QToolBar(this);

    fileToolBar->addAction(view_mode);
    fileToolBar->addAction(view1_mode);
    fileToolBar->addAction(view2_mode);

    fileToolBar->addSeparator();

    fileToolBar->addAction(param_set);
    fileToolBar->addAction(lidar_area_set);

    // addToolBar(Qt::LeftToolBarArea,fileToolBar);
    addToolBar(Qt::BottomToolBarArea, fileToolBar);
    //    addToolBarBreak(Qt::BottomToolBarArea);
    //    addToolBar(Qt::BottomToolBarArea, toolBar);
}

void MainWindow::initConnect()
{
    QObject::connect(add_lidar, SIGNAL(SendSet(QString)), this, SLOT(params_set(QString)));
    QObject::connect(setROI, SIGNAL(sigChangeArea_index(int)), paint_area, SLOT(UpdateArea_index(int)));
    QObject::connect(setROI, SIGNAL(sigSaveAreaData()), this, SLOT(getAreaDatas()));
    QObject::connect(ros_talk, SIGNAL(emitTopicParams(QString)), this, SLOT(updateTopicParams(QString)));
    QObject::connect(this, SIGNAL(emitTopicSetParams(QString)), ros_talk, SLOT(saveTopicParams(QString)));
    QObject::connect(ros_talk, SIGNAL(emit_camera_drive(QPixmap)), camera_viewer, SLOT(setCameraMat(QPixmap)));
    QObject::connect(ros_talk, SIGNAL(emit_camera_drive(QPixmap)), camera_viewer2, SLOT(setCameraMat(QPixmap)));
    QObject::connect(ros_talk, SIGNAL(emit_lidar_drive(PointCloudTPtr)), this, SLOT(receive_lidar_driver(PointCloudTPtr)));
    QObject::connect(this, SIGNAL(uploadLog(QMultiMap<QString, QString>)), this, SLOT(receive_lidar_driver(QMultiMap<QString, QString>)));
    QObject::connect(ros_talk, SIGNAL(emit_show_log(QString)), diary, SLOT(show_log(QString)));
    
}

void MainWindow::createActions()
{
}

void MainWindow::param_set_Action()
{
    this->add_lidar->show();
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

    left_body_layout->addWidget(imageWidget);
}

void MainWindow::view_mode1_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(imageWidget);
}

void MainWindow::view_mode2_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(imageWidget2);
}

CameraViewer *MainWindow::getCameraWidget()
{
    return this->camera_viewer;
}

void MainWindow::getAreaDatas()
{
}

void MainWindow::updateTopicParams(QString msg)
{
    // qDebug() << "updateTopicParams:" << msg;
    add_lidar->ShowData(msg);
}

void MainWindow::params_set(QString msg)
{
    emit emitTopicSetParams(msg);
    //   qDebug() << "updateTopicParams:" << msg;
    //   add_lidar->ShowData(msg);
}

// implement slot functions
// void MainWindow::open()
//{

//}

// void MainWindow::print()
//{

//}

// void MainWindow::exit()
//{

//}

// void MainWindow::zoomIn()
//{

//}

// void MainWindow::zoomOut()
//{

//}

// void MainWindow::normalSize()
//{

//}

// void MainWindow::fitToWindow()
//{

//}

// void MainWindow::about()
//{

//}

// void MainWindow::aboutQt()
//{

//}
