#ifndef MAINDEAL_H
#define MAINDEAL_H

#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "ros_talk.h"


class Maindeal
{
public:
    Maindeal(int my_argc_,char **my_argv_);

    const std::shared_ptr<QApplication> getApp();
    void initUI();

private:

    void initRos();

    int my_argc{0};
    char **my_argv;
    std::shared_ptr<QApplication> app;
    std::shared_ptr<QDesktopWidget> deskwindow;
    std::shared_ptr<MainWindow> mainwindow;
};

#endif // MAINDEAL_H
