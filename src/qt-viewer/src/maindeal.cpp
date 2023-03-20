#include "maindeal.h"
#include <QTextCodec>

//using namespace imu;

Maindeal::Maindeal(int my_argc_, char **my_argv_) : my_argc(my_argc_), my_argv(my_argv_)
{
    /******************************************** 初始化UI **************************************************/
    initUI();
    initRos();
}

void Maindeal::initRos()
{

}

void Maindeal::initUI()
{
    // app = new QApplication(this->my_argc, this->my_argv);
    // dw = new QDesktopWidget();
    // w = new MainWindow(qApp);
    // this->w->showMaximized();
    
    //解决汉字乱码问题
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    app = std::make_shared<QApplication>(this->my_argc, this->my_argv);
    deskwindow = std::make_shared<QDesktopWidget>();
    mainwindow = std::make_shared<MainWindow>(qApp);
    usleep(1000 * 1000 * 2);
    this->mainwindow->getqSplashScreen()->close(); // 关闭启动动画
    mainwindow->showMaximized();
}

const std::shared_ptr<QApplication> Maindeal::getApp()
{
    return app;
}


