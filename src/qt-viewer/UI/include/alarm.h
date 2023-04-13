#ifndef ALARM_H
#define ALARM_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QDebug>


union SystemStatus {
    uint8_t data{255};
    struct {
        uint8_t localizer: 1; // 1:已定位 0： 未定位
        uint8_t unused1: 1;
        uint8_t unused2: 1;
        uint8_t unused3: 1;
        uint8_t unused4: 1;
        uint8_t unused5: 1;
        uint8_t unused6: 1;
        uint8_t unused7: 1;
    } bits;
};

union WorkStatus {
    uint8_t data{255};
    struct {
        uint8_t localizer: 1; // 1:已定位 0： 未定位
        uint8_t unused1: 1;
        uint8_t unused2: 1;
        uint8_t unused3: 1;
        uint8_t unused4: 1;
        uint8_t unused5: 1;
        uint8_t unused6: 1;
        uint8_t unused7: 1;
    } bits;
};

union CommunicateStatus {
    uint8_t data{255};
    struct {
        uint8_t camera: 1; // 1:已定位 0： 未定位
        uint8_t lidar_drive: 1;
        uint8_t plc: 1;
        uint8_t unused3: 1;
        uint8_t unused4: 1;
        uint8_t unused5: 1;
        uint8_t unused6: 1;
        uint8_t unused7: 1;
    } bits;
};

struct AlarmStatus {
    SystemStatus system_status;
    WorkStatus work_status;
    CommunicateStatus communicate_status;
};



struct LEDSTATUS
{
    int communicion_led_color[2]= {5,5};
    int work_led_color[2]= {5,5};
    int system_led_color[2]= {5,5};
    int other_led_color[2]= {5,5};
};

namespace Ui {
class Alarm;
}

class Alarm : public QWidget
{
    Q_OBJECT

public:
    explicit Alarm(QWidget *parent = nullptr);
    ~Alarm();

    void setLED(QLabel* label, int color, int size ,int width,int cnt_);
    QTimer *my_timer;
    void setLEDStatus( const AlarmStatus& msg  );

private:
    Ui::Alarm *ui;
    LEDSTATUS led_status;
    AlarmStatus alarm_status;
    QVector<int> led_dat;
    //    AlarmStatus alarm_status;

private slots:
    void lidar_derect_result(QVector<int>);
};

#endif // ALARM_H
