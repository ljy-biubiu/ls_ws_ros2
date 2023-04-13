#include "alarm.h"
#include "ui_alarm.h"
#include <unistd.h>
#include<iostream>
#include<cstdio>    //C++风格

Alarm::Alarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alarm)
{
    ui->setupUi(this);
    this->setLED(this->ui->label_led_normal,0,30,250,0);
    this->setLED(this->ui->label_led_abnormal,1,30,250,0);

    // 设置背景黑色
    QPalette palBackGround(this->palette());
    palBackGround.setColor(QPalette::Background, QColor(34, 34, 34));
    ui->label_head->setAutoFillBackground(true);
    ui->label_head->setPalette(palBackGround);

    for(auto i{0}; 16>i ;i++)
    {
        led_dat.push_back(0);
    }
    led_dat[8] = 1;
    led_dat[14] = 1;

    auto timer = new QTimer(this);
    timer->start(200);


    connect(timer,&QTimer::timeout,[=](){
        static int flag{0};

        flag++;
        if(flag == 4)
            flag = 0;

        int label_width{30};
        int label_high{60};

        if(flag == 0 || flag == 1)
        {
            this->setLED(this->ui->label_led_1,led_dat[0],label_width,label_high,0);
            this->setLED(this->ui->label_led_2,led_dat[1],label_width,label_high,0);
            this->setLED(this->ui->label_led_3,led_dat[2],label_width,label_high,0);
            this->setLED(this->ui->label_led_4,led_dat[3],label_width,label_high,0);
            this->setLED(this->ui->label_led_5,led_dat[4],label_width,label_high,0);
            this->setLED(this->ui->label_led_6,led_dat[5],label_width,label_high,0);
            this->setLED(this->ui->label_led_7,led_dat[6],label_width,label_high,0);
            this->setLED(this->ui->label_led_8,led_dat[7],label_width,label_high,0);
            this->setLED(this->ui->label_led_9,led_dat[8],label_width,label_high,0);
            this->setLED(this->ui->label_led_10,led_dat[9],label_width,label_high,0);
            this->setLED(this->ui->label_led_11,led_dat[10],label_width,label_high,0);
            this->setLED(this->ui->label_led_12,led_dat[11],label_width,label_high,0);
            this->setLED(this->ui->label_led_13,led_dat[12],label_width,label_high,0);
            this->setLED(this->ui->label_led_14,led_dat[13],label_width,label_high,0);
            this->setLED(this->ui->label_led_15,led_dat[14],label_width,label_high,0);
            this->setLED(this->ui->label_led_16,led_dat[15],label_width,label_high,0);
//            flag = false;
        }
        else {
            this->setLED(this->ui->label_led_1,led_dat[0],label_width,label_high,1);
            this->setLED(this->ui->label_led_2,led_dat[1],label_width,label_high,1);
            this->setLED(this->ui->label_led_3,led_dat[2],label_width,label_high,1);
            this->setLED(this->ui->label_led_4,led_dat[3],label_width,label_high,1);
            this->setLED(this->ui->label_led_5,led_dat[4],label_width,label_high,1);
            this->setLED(this->ui->label_led_6,led_dat[5],label_width,label_high,1);
            this->setLED(this->ui->label_led_7,led_dat[6],label_width,label_high,1);
            this->setLED(this->ui->label_led_8,led_dat[7],label_width,label_high,1);
            this->setLED(this->ui->label_led_9,led_dat[8],label_width,label_high,1);
            this->setLED(this->ui->label_led_10,led_dat[9],label_width,label_high,1);
            this->setLED(this->ui->label_led_11,led_dat[10],label_width,label_high,1);
            this->setLED(this->ui->label_led_12,led_dat[11],label_width,label_high,1);
            this->setLED(this->ui->label_led_13,led_dat[12],label_width,label_high,1);
            this->setLED(this->ui->label_led_14,led_dat[13],label_width,label_high,1);
            this->setLED(this->ui->label_led_15,led_dat[14],label_width,label_high,1);
            this->setLED(this->ui->label_led_16,led_dat[15],label_width,label_high,1);
//            flag = true;
        }
    });

}

void Alarm::setLEDStatus( const AlarmStatus& msg  )
{
    alarm_status = msg;

    if(alarm_status.work_status.data != 255)
    {
        led_status.work_led_color[0] = 1;
        led_status.work_led_color[1] = 4;
    }
    else
    {
        led_status.work_led_color[0] = 5;
        led_status.work_led_color[1] = 5;
    }

    if(alarm_status.communicate_status.data != 255)
    {
        led_status.communicion_led_color[0] = 1;
        led_status.communicion_led_color[1] = 4;
    }
    else
    {
        led_status.communicion_led_color[0] = 5;
        led_status.communicion_led_color[1] = 5;
    }

    if(alarm_status.system_status.data != 255)
    {
        led_status.system_led_color[0] = 1;
        led_status.system_led_color[1] = 4;
    }
    else
    {
        led_status.system_led_color[0] = 5;
        led_status.system_led_color[1] = 5;
    }

}


Alarm::~Alarm()
{
    delete ui;
}

// 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
// color 0:grey 1:red 2:green 3:yellow
// size  单位是像素
void Alarm::setLED(QLabel* label, int color, int size ,int width,int cnt_)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(width);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(width);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size*2/5);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";


    //    if(color == 1)
    //    {
    //        if(cnt_== 0)
    //        {
    //            background += "rgb(255,0,0)";
    //        }
    //        else
    //        {
    //            background += "rgb(255,192,203)";
    //        }

    //        const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    //        label->setStyleSheet(SheetStyle);
    //        qDebug()<<SheetStyle;
    //        return;
    //    }

    switch (color) {
    case 0:
        // 亮蓝
        background += "rgb(127,189,240)";
        break;
    case 1:
        // 红色
    {
        if(cnt_== 0)
        {
            background += "rgb(255,0,0)";
        }
        else
        {
            background += "rgb(255,192,203)";
        }
    }
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    case 4:
        // 亮粉
        background += "rgb(255,192,203)";
        break;
    case 5:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}


void Alarm::lidar_derect_result(QVector<int> msg)
{

}
