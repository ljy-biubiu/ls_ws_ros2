#include "alarm.h"
#include "ui_alarm.h"

Alarm::Alarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Alarm)
{
    ui->setupUi(this);
    this->setLED(this->ui->label_led_4,5,20,3);
    this->setLED(this->ui->label_led_5,1,20,3);

    //this->ui->textEdit->setStyleSheet(QString("font-size:13px;border：1px solid black; background：#8c9092"));

    //设置背景黑色
    QPalette palBackGround(this->palette());
    palBackGround.setColor(QPalette::Background, QColor(34, 34, 34));
    ui->label_6->setAutoFillBackground(true);
    ui->label_6->setPalette(palBackGround);


    my_timer = new QTimer(this);
    
    my_timer->start(100);
    connect(my_timer,&QTimer::timeout,[=](){
        //        setLED()


        static bool flag{false};
        if(flag)
        {
            this->setLED(this->ui->communicate_led,led_status.communicion_led_color[0],30,5);
            this->setLED(this->ui->work_led,led_status.work_led_color[0],30,5);
            this->setLED(this->ui->system_led,led_status.system_led_color[0],30,5);
            this->setLED(this->ui->ohter_led,led_status.other_led_color[0],30,5);
            flag = false;
        }
        else {
            this->setLED(this->ui->communicate_led,led_status.communicion_led_color[1],30,5);
            this->setLED(this->ui->work_led,led_status.work_led_color[1],30,5);
            this->setLED(this->ui->system_led,led_status.system_led_color[1],30,5);
            this->setLED(this->ui->ohter_led,led_status.other_led_color[1],30,5);
            flag = true;
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
void Alarm::setLED(QLabel* label, int color, int size ,int width)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size*width);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size*width);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
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
        // 亮蓝
        background += "rgb(127,189,240)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}
