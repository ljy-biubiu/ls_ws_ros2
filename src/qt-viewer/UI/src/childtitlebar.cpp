/*****************************************
 * 作者: YYC
 * 日期: 2020-04-26
 * 功能：主标题栏，内含有窗体最大化，最小化，关闭
 * 以及窗口的Title，以及名称
 * ***************************************/
#include "childtitlebar.h"
#include "ui_childtitlebar.h"
#include "Version.h"
ChildTitleBar::ChildTitleBar(QWidget *parent) :
    TitleBar(parent),
    ui(new Ui::ChildTitleBar)
{
    ui->setupUi(this);
    ui->labelTitleName->setAlignment(Qt::AlignCenter);
    ui->labelTitleName->setStyleSheet("font-size:12pt; color:#ffffff;");
    ui->labelTitleName->setText(PRODUCT_NAME);
}

ChildTitleBar::~ChildTitleBar()
{
    delete ui;
}

void ChildTitleBar::setTitleName(QString titleName)
{
    ui->labelTitleName->setText(titleName);
}

void ChildTitleBar::on_pushButtonClose_clicked()
{
    if(parentWidget)
    {
        parentWidget->close();
    }
}
