#ifndef TASKLISTUI_H
#define TASKLISTUI_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "QCheckBox"
#include "QLineEdit"
#include "QComboBox"
#include "QRadioButton"
#include "QSpinBox"
#include "QHeaderView"
#include "QPushButton"
#include "QLabel"
#include "QVector"
#include <jsoncpp/json/json.h>


class TaskListUi : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListUi(QWidget *parent = 0);

private:
    void getQRadiobuttonItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QRadioButton * & radiobutton,const QString &info);
    void getQCheckBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QCheckBox * & checkbox,const QString &info);
    void getQLineEditItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QLineEdit * & lineedit,const QString &info);
    void getQComboBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QComboBox * & combobox,const QString &info);
    void getQSpinBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QSpinBox * & spinbox,const QString &info);
    void getQLabelItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QLabel * & label,const QString &info);
    void getQPushButtonItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QPushButton * & pushbutton,const QString &info);
    
    QCheckBox* creteQCheckBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,const QString &info);
    QLineEdit* creteQlineEditItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,const QString &info);
    QComboBox* creteQComboBoxEditItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,const QString &info,const QStringList &list);

private:


    QLineEdit* LM_line_edit_ServerAddress ;
    QLineEdit* LM_line_edit_ServerPort ;
    QLineEdit* LM_line_edit_UploadDataAddress ;
    QLineEdit* LM_line_edit_UplodaDeviceId ;

    QLineEdit* LM_line_Area_height_down ;
    QLineEdit* LM_line_Area_height_top ;
    QLineEdit* LM_line_edit_K ;
    QLineEdit* LM_line_euclidean_disatance ;
    QLineEdit* LM_line_interpolation_interval ;
    QLineEdit* LM_line_m_grid_x ;
    QLineEdit* LM_line_m_grid_y ;
    QLineEdit* LM_line_m_grid_z ;
    QLineEdit* LM_line_resolution ;
    QLineEdit* LM_line_start_dist ;
    QLineEdit* LM_line_cloudMapFrame;
    QCheckBox* RB_line_save_bclold_isOpen;
    QLineEdit* LM_line_save_bclold_hour;
    QLineEdit* LM_line_save_bclold_min;
    QLineEdit* LM_line_roi_limit;
    QLineEdit* LM_line_detect_text_size;


    QLineEdit* LM_line_edit_Tolerance ;
    QLineEdit* LM_line_edit_maxSize ;
    QLineEdit* LM_line_edit_minSize ;

    QLineEdit* LM_line_edit_lidar_IP ;
    QLineEdit* LM_line_edit_lidar_device_port ;
    QLineEdit* LM_line_edit_lidar_data_port ;
    QLineEdit* LM_line_edit_lidar_x ;
    QLineEdit* LM_line_edit_lidar_y ;
    QLineEdit* LM_line_edit_lidar_z ;
    QLineEdit* LM_line_edit_lidar_picth ;
    QLineEdit* LM_line_edit_lidar_roll ;
    QLineEdit* LM_line_edit_lidar_yaw ;

    QLineEdit* LM_line_edit_camera_IP ;
    QLineEdit* LM_line_edit_camera_ID ;
    QLineEdit* LM_line_edit_camera_Pass ;

    QLineEdit* LM_line_edit_3d_lidar_id;
    QLineEdit* LM_line_edit_SendAddress ;
    QLineEdit* LM_line_edit_SendPort;
    QLineEdit* LM_line_edit_info_topic;
    QLineEdit* LM_line_edit_status_topic;

    QPushButton * comfire_button;
    QTreeWidgetItem * buttonItem;
    QVector<QLineEdit*> vec_LM_line_edit_sum;

public:
    QCheckBox* RB_line_show_is_open;
    QCheckBox* RB_line_show_classify;
    QCheckBox* RB_line_show_distance;
    QCheckBox* RB_line_show_velocity;
    QLineEdit* LM_line_show_box_size;

signals:
    void sigSavePushButton(QString);

private slots:
    void savePushButton();
    void updateTopicParams(QString);

    // public slots:
};

#endif // TASKLISTUI_H
