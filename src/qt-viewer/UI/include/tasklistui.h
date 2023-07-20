#ifndef TASKLISTUI_H
#define TASKLISTUI_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "QCheckBox"
#include "QLineEdit"
#include "QComboBox"
#include "QRadioButton"
#include "QButtonGroup"
#include "QSpinBox"
#include "QHeaderView"
#include "QPushButton"
#include "QLabel"
#include "QVector"
#include <jsoncpp/json/json.h>


static bool isNumeric(const QString &str)
{
    try
    {
        int num = stoi(str.toStdString());
        // 如果转换成功且没有抛出异常，则说明是数字
        return true;
    }
    catch (const std::exception &e)
    { // 捕获任何转换错误的异常
        return false;
    }
}

class TaskListUi : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListUi(QWidget *parent = 0);

    const double get_plane_D_data()
    {
        if (this->LM_line_edit_plane_D->text() == QString() || !isNumeric(this->LM_line_edit_plane_D->text()) )
            return 0;
        return std::stod(this->LM_line_edit_plane_D->text().toStdString());
    }

    const double get_show_box_size()
    {
        if (this->LM_line_show_box_size->text() == QString()  || !isNumeric(this->LM_line_show_box_size->text()))
            return 0;
        return std::stod(this->LM_line_show_box_size->text().toStdString());
    }

    const double get_show_lidar_height_min()
    {
        if (this->LM_line_edit_lidar_show_height_min->text() == QString() || !isNumeric(this->LM_line_edit_lidar_show_height_min->text()))
            return 0;
        return std::stod(this->LM_line_edit_lidar_show_height_min->text().toStdString());
    }

    const double get_show_lidar_height_max()
    {
        if (this->LM_line_edit_lidar_show_height_max->text() == QString() || !isNumeric(this->LM_line_edit_lidar_show_height_max->text()))
            return 0;
        return std::stod(this->LM_line_edit_lidar_show_height_max->text().toStdString());
    }

    const double get_show_distance()
    {
        return this->RB_line_show_distance->isChecked();
    }

    const double get_show_classify()
    {
        return this->RB_line_show_classify->isChecked();
    }

    const double get_show_velocity()
    {
        return this->RB_line_show_velocity->isChecked();
    }

    const double get_show_is_open()
    {
        return this->RB_line_show_is_open->isChecked();
    }

private:
    void getQRadiobuttonItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QRadioButton *&radiobutton, const QString &info);
    void getQCheckBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QCheckBox *&checkbox, const QString &info);
    void getQLineEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QLineEdit *&lineedit, const QString &info);
    void getQComboBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QComboBox *&combobox, const QString &info);
    void getQSpinBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QSpinBox *&spinbox, const QString &info);
    void getQLabelItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QLabel *&label, const QString &info);
    void getQPushButtonItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QPushButton *&pushbutton, const QString &info);

    QCheckBox *creteQCheckBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info);
    QLineEdit *creteQlineEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info);
    QComboBox *creteQComboBoxEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info, const QStringList &list);

    void initConnect();

private:
    QLineEdit *LM_line_edit_ServerAddress;
    QLineEdit *LM_line_edit_ServerPort;
    QLineEdit *LM_line_edit_UploadDataAddress;
    QLineEdit *LM_line_edit_UplodaDeviceId;

    QLineEdit *LM_line_Area_height_down;
    QLineEdit *LM_line_Area_height_top;
    QLineEdit *LM_line_edit_K;
    QLineEdit *LM_line_euclidean_disatance;
    QLineEdit *LM_line_interpolation_interval;
    QLineEdit *LM_line_m_grid_x;
    QLineEdit *LM_line_m_grid_y;
    QLineEdit *LM_line_m_grid_z;
    QLineEdit *LM_line_resolution;
    QLineEdit *LM_line_difference_threshold;
    QLineEdit *LM_line_start_dist;
    QLineEdit *LM_line_cloudMapFrame;
    QCheckBox *RB_line_save_bclold_isOpen;
    QLineEdit *LM_line_save_bclold_hour;
    QLineEdit *LM_line_save_bclold_min;
    QLineEdit *LM_line_roi_limit;
    QLineEdit *LM_line_detect_text_size;

    QLineEdit *LM_line_edit_Tolerance;
    QLineEdit *LM_line_edit_maxSize;
    QLineEdit *LM_line_edit_minSize;
    QLineEdit *LM_line_edit_groundThickness;
    QLineEdit *LM_line_edit_roiHeight;
    QLineEdit *LM_line_edit_voxelLength;
    QLineEdit *LM_line_edit_plane_A;
    QLineEdit *LM_line_edit_plane_B;
    QLineEdit *LM_line_edit_plane_C;
    QLineEdit *LM_line_edit_plane_D;

    // double A{};
    // double B{};
    // double C{};
    // double D{};
    // Plane plane;// 地面平面参数
    // double groundThickness;//地面厚度
    // double roiHeight;//ROI范围中高度范围，即地面以上一定高度值以下内的点

    QVector<QLineEdit *> LM_line_edit_lidar_IP;
    QVector<QLineEdit *> LM_line_edit_lidar_device_port;
    QVector<QLineEdit *> LM_line_edit_lidar_data_port;
    QVector<QLineEdit *> LM_line_edit_lidar_x;
    QVector<QLineEdit *> LM_line_edit_lidar_y;
    QVector<QLineEdit *> LM_line_edit_lidar_z;
    QVector<QLineEdit *> LM_line_edit_lidar_picth;
    QVector<QLineEdit *> LM_line_edit_lidar_roll;
    QVector<QLineEdit *> LM_line_edit_lidar_yaw;

    QVector<QLineEdit *> LM_line_edit_camera_IP;
    QVector<QLineEdit *> LM_line_edit_camera_ID;
    QVector<QLineEdit *> LM_line_edit_camera_Pass;
    QVector<QLineEdit *> LM_line_edit_camera_Rtsp;
    QVector<QLineEdit *> LM_line_edit_camera_Calibrationdistance;
    QVector<QLineEdit *> LM_line_edit_camera_CameraHeading;
    QVector<QLineEdit *> LM_line_edit_camera_CameraHeight;
    QVector<QLineEdit *> LM_line_edit_camera_CameraPitch;
    QVector<QLineEdit *> LM_line_edit_camera_CameraRoll;
    QVector<QLineEdit *> LM_line_edit_camera_CameraWidth;
    QVector<QLineEdit *> LM_line_edit_camera_CameraX;
    QVector<QLineEdit *> LM_line_edit_camera_CameraY;
    QVector<QLineEdit *> LM_line_edit_camera_CameraZ;
    QVector<QLineEdit *> LM_line_edit_camera_Cx;
    QVector<QLineEdit *> LM_line_edit_camera_Cy;
    QVector<QLineEdit *> LM_line_edit_camera_Fx;
    QVector<QLineEdit *> LM_line_edit_camera_Fy;
    QVector<QLineEdit *> LM_line_edit_camera_K1;
    QVector<QLineEdit *> LM_line_edit_camera_K2;
    QVector<QLineEdit *> LM_line_edit_camera_Linethickness;
    QVector<QLineEdit *> LM_line_edit_camera_P1;
    QVector<QLineEdit *> LM_line_edit_camera_P2;

    QVector<QLineEdit *> LM_line_edit_zeroDegreeH;
    QVector<QLineEdit *> LM_line_edit_zeroDegreeV;
    QVector<QLineEdit *> LM_line_edit_zoomDist;

    //    QLineEdit* LM_line_edit_camera_IP ;
    //    QLineEdit* LM_line_edit_camera_ID ;
    //    QLineEdit* LM_line_edit_camera_Pass ;

    QLineEdit *LM_line_edit_3d_lidar_id;
    QLineEdit *LM_line_edit_SendAddress;
    QLineEdit *LM_line_edit_SendPort;
    QLineEdit *LM_line_edit_info_topic;
    QLineEdit *LM_line_edit_status_topic;

    QLineEdit *LM_line_edit_lidar_show_height_max;
    QLineEdit *LM_line_edit_lidar_show_height_min;

    QPushButton *comfire_button;
    QTreeWidgetItem *buttonItem;
    QVector<QLineEdit *> vec_LM_line_edit_sum;

public:
    QCheckBox *RB_line_show_is_open;
    QCheckBox *RB_line_show_classify;
    QCheckBox *RB_line_show_distance;
    QCheckBox *RB_line_show_velocity;
    QLineEdit *LM_line_show_box_size;
    QButtonGroup *block_camera_mode; // 分组
    QRadioButton *multi_camera;
    QRadioButton *solo_camera;

    QButtonGroup *type_camera_mode; // 分组
    QRadioButton *orignal_camera;
    QRadioButton *algorithm_camera;

    QButtonGroup *ptz_camera_mode; // 分组
    QRadioButton *ptz_camera_on;
    QRadioButton *ptz_camera_off;

    QButtonGroup *type_lidar_mode; // 分组
    QRadioButton *orignal_lidar;
    QRadioButton *algorithm_lidar;

signals:
    void sigSavePushButton(QString);

private slots:
    void savePushButton();
    void updateTopicParams(QString);

    // public slots:
};

#endif // TASKLISTUI_H
