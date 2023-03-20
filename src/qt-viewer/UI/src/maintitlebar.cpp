/*****************************************
 * 作者: YYC
 * 日期: 2020-04-26
 * 功能：主标题栏，内含有窗体最大化，最小化，关闭
 * 以及窗口的Title，以及名称
 * ***************************************/
#include "maintitlebar.h"
#include "ui_maintitlebar.h"
#include "Version.h"

MainTitleBar::MainTitleBar(QWidget *parent) :
    TitleBar(parent),
    ui(new Ui::MainTitleBar)
{
    ui->setupUi(this);
    ui->pushButtonNormalMax->setStyleSheet("QPushButton{border-image: url(:/images/max_normal.png);}"
                                           "QPushButton:hover{border-image: url(:/images/max_hover.png);}");
    ui->labelTitleName->setAlignment(Qt::AlignCenter);
    ui->labelTitleName->setStyleSheet("font-size:18pt; color:#ffffff;");
    ui->labelTitleName->setText(PRODUCT_NAME);
}

MainTitleBar::~MainTitleBar()
{
    delete ui;
}

void MainTitleBar::on_pushButtonClose_clicked()
{
    if(parentWidget)
    {
        parentWidget->close();
    }
}

void MainTitleBar::on_pushButtonMin_clicked()
{
    if(parentWidget)
    {
        parentWidget->showMinimized();
    }
}


void MainTitleBar::on_pushButtonNormalMax_clicked()
{
    if(parentWidget == nullptr) return;
    if (parentWidget->isMaximized())
    {
        parentWidget->showNormal();
        ui->pushButtonNormalMax->setStyleSheet("QPushButton{border-image: url(:/images/normal_normal.png);}"
                                               "QPushButton:hover{border-image: url(:/images/normal_hover.png);}");
    }
    else
    {
        parentWidget->showMaximized();
        ui->pushButtonNormalMax->setStyleSheet("QPushButton{border-image: url(:/images/max_normal.png);}"
                                               "QPushButton:hover{border-image: url(:/images/max_hover.png);}");
    }
}

void MainTitleBar::on_pushButtonAbout_clicked()
{
    emit sig_about_clicked();
}
