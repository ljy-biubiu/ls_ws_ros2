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
    QVector<QLineEdit*> vec_line_edit_ip;
    QVector<QLineEdit*> vec_line_edit_port;
    QVector<QLineEdit*> vec_LM_line_edit_x;
    QVector<QLineEdit*> vec_LM_line_edit_y;
    QVector<QLineEdit*> vec_LM_line_edit_z;
    QVector<QLineEdit*> vec_LM_line_edit_picth;
    QVector<QLineEdit*> vec_LM_line_edit_roll;
    QVector<QLineEdit*> vec_LM_line_edit_yaw;
    QVector<QVector<QLineEdit*>> vec_lidar_datas;
    QPushButton * comfire_button;

signals:
    void sigSavePushButton(QVector<QVector<QLineEdit*>>);

private slots:
    void savePushButton();
    void updateTopicParams(QString);

    // public slots:
};

#endif // TASKLISTUI_H
