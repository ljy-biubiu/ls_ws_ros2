#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QDateTime>
#include "Version.h"
aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
//    QFont ft;
//    ft.setPointSize(13);
//    ui->label_4->setFont(ft);
    ui->widget_childTitle->setParentWidget(this);
    ui->widget_childTitle->setTitleName("关于我们");
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    ui->label_title->setText(PRODUCT_NAME_CHILD);
    ui->label_title->setAlignment(Qt::AlignCenter);
    ui->label_title->setStyleSheet("font-size:18pt; font-weight:600;");
    ui->label_copyright->setText(PRODUCT_COPYRIGHT);
    ui->label_copyright->setAlignment(Qt::AlignCenter);
    ui->label_copyright->setStyleSheet("font-size:14pt;");
    ui->label_version->setText(PRODUCT_VERSION);
    ui->label_version->setAlignment(Qt::AlignCenter);
    ui->label_version->setStyleSheet("font-size:14pt;");
    QString current_date = buildDateTime().toString("yyyy.MM.dd");
    ui->label_time->setText(current_date);
    ui->label_time->setAlignment(Qt::AlignCenter);
    ui->label_time->setStyleSheet("font-size:14pt;");

}

aboutDialog::~aboutDialog()
{
    delete ui;
}

const QDateTime aboutDialog::buildDateTime()
{
    QString dateTime;
    dateTime.clear();
    dateTime += __DATE__;
    dateTime += __TIME__;
    dateTime.replace("  "," 0");//注意" "是两个空格，用于日期为单数时需要转成“空格+0”
    return QLocale(QLocale::English).toDateTime(dateTime,"MMM dd yyyyhh:mm:ss");
}





void aboutDialog::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.leishen-lidar.com/"));
}
