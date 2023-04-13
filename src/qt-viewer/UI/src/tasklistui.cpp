#include "tasklistui.h"
#include "qdebug.h"
#include "QHBoxLayout"
// #include "allstylesheets.h"

TaskListUi::TaskListUi(QWidget *parent)
{

    QVBoxLayout *mainLayout_H = new QVBoxLayout();
    QTreeWidget *mainTreeWidget = new QTreeWidget(this);
    // this->setWindowFlags(Qt::FramelessWindowHint);
    // this->setWindowModality(Qt::WindowModal);
    // setModal(true);

    QLabel *head_label = new QLabel();
    head_label->setText("参数配置");
    mainLayout_H->addWidget(head_label);
    mainLayout_H->addWidget(mainTreeWidget);

    this->setLayout(mainLayout_H);
    //    QStringList headers;
    //    headers<<"name";
    mainTreeWidget->setColumnCount(2);
    // mainTreeWidget->setMinimumSize(400,800);
    QHeaderView *head = mainTreeWidget->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    // mainTreeWidget->autoScrollMargin();

    //    mainTreeWidget->setColumnWidth(0,170);
    mainTreeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // mainTreeWidget->setStyleSheet(myStyleSheets::myTree::tasklistUiTree);
    mainTreeWidget->setHeaderHidden(true);
    // mainTreeWidget->setAutoFillBackground(true);

    // tool
    QTreeWidgetItem *Tool = new QTreeWidgetItem();
    // Tool->setIcon(0,QIcon(":/res/images/painter.png"));
    //     mainTreeWidget->addTopLevelItem(Tool);
    //     Tool->setText(0,QString("工具"));

    auto check_box = new QCheckBox(this);
    auto check_box2 = new QCheckBox(this);

    getQCheckBoxItem(mainTreeWidget, Tool, check_box, "vmap-tool:");
    getQCheckBoxItem(mainTreeWidget, Tool, check_box2, "lanelet-tool:");

    //
    QTreeWidgetItem *lidarParams = new QTreeWidgetItem();
    mainTreeWidget->addTopLevelItem(lidarParams);
    lidarParams->setText(0, QString("雷达参数"));

    for (int i = 0; i < 14; i++)
    {
        QTreeWidgetItem *lidarParams_1 = new QTreeWidgetItem();
        lidarParams->addChild(lidarParams_1); ///
        lidarParams_1->setText(0, QString("雷达 ") + QString::number(i + 1));

        auto LM_line_edit_IP = new QLineEdit(this);
        auto LM_line_edit_Port = new QLineEdit(this);
        auto LM_line_edit_x = new QLineEdit(this);
        auto LM_line_edit_y = new QLineEdit(this);
        auto LM_line_edit_z = new QLineEdit(this);
        auto LM_line_edit_picth = new QLineEdit(this);
        auto LM_line_edit_roll = new QLineEdit(this);
        auto LM_line_edit_yaw = new QLineEdit(this);


        vec_line_edit_ip.push_back(LM_line_edit_IP);
        vec_line_edit_port.push_back(LM_line_edit_Port);

        vec_LM_line_edit_x.push_back(LM_line_edit_x);
        vec_LM_line_edit_y.push_back(LM_line_edit_y);
        vec_LM_line_edit_z.push_back(LM_line_edit_z);
        vec_LM_line_edit_picth.push_back(LM_line_edit_picth);
        vec_LM_line_edit_roll.push_back(LM_line_edit_roll);
        vec_LM_line_edit_yaw.push_back(LM_line_edit_yaw);

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_IP, "IP");
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_Port, "Port");

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_x, "x");
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_y, "y");
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_z, "z");

        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_picth, "pitch");
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_roll, "roll");
        getQLineEditItem(mainTreeWidget, lidarParams_1, LM_line_edit_yaw, "yaw");

    }

    vec_lidar_datas.push_back(vec_line_edit_ip);
    vec_lidar_datas.push_back(vec_line_edit_port);
    vec_lidar_datas.push_back(vec_LM_line_edit_x);
    vec_lidar_datas.push_back(vec_LM_line_edit_y);
    vec_lidar_datas.push_back(vec_LM_line_edit_z);
    vec_lidar_datas.push_back(vec_LM_line_edit_picth);
    vec_lidar_datas.push_back(vec_LM_line_edit_roll);
    vec_lidar_datas.push_back(vec_LM_line_edit_yaw);

    comfire_button = new QPushButton(this);
    comfire_button->setText("保存");
    comfire_button->setMaximumSize(200, 50);
    comfire_button->setMinimumSize(200, 50);
    getQPushButtonItem(mainTreeWidget, lidarParams, comfire_button, " ");

    //    QTreeWidgetItem *lidarParams=new QTreeWidgetItem();
    //    mainTreeWidget->addTopLevelItem(lidarParams);
    //    lidarParams->setText(0,QString("雷达参数"));

    //    //mode
    //    QTreeWidgetItem *Mode=new QTreeWidgetItem();
    //    //Mode->setIcon(0,QIcon(":/res/images/param-mode.png"));
    //    mainTreeWidget->addTopLevelItem(Mode);
    //    Mode->setText(0,QString("类型"));

    //    auto combo_box = new QComboBox(this);
    //    auto spin_box = new QSpinBox(this);

    //    getQComboBoxItem(mainTreeWidget,Mode,combo_box,"类型:");
    //    getQSpinBoxItem(mainTreeWidget,Mode,spin_box,"数量:");

    //    //vmap-param
    //    QTreeWidgetItem *Point=new QTreeWidgetItem();
    //    //Point->setIcon(0,QIcon(":/res/images/Point.png"));
    //    mainTreeWidget->addTopLevelItem(Point);
    //    Point->setText(0,QString("点"));

    //    auto line_edit = new QLineEdit(this);
    //    auto line_edit2 = new QLineEdit(this);
    //    auto line_edit3 = new QLineEdit(this);
    //    auto line_edit4 = new QLineEdit(this);
    //    auto line_edit5 = new QLineEdit(this);
    //    auto line_edit6 = new QLineEdit(this);

    //    getQLineEditItem(mainTreeWidget,Point,line_edit,"x:");
    //    getQLineEditItem(mainTreeWidget,Point,line_edit2,"y:");
    //    getQLineEditItem(mainTreeWidget,Point,line_edit3,"z:");
    //    getQLineEditItem(mainTreeWidget,Point,line_edit4,"w-dir:");
    //    getQLineEditItem(mainTreeWidget,Point,line_edit5,"lat:");
    //    getQLineEditItem(mainTreeWidget,Point,line_edit6,"lon:");

    //    //point-type
    //    QTreeWidgetItem *Point_type=new QTreeWidgetItem();
    //    //Point_type->setIcon(0,QIcon(":/res/images/type.png"));
    //    mainTreeWidget->addTopLevelItem(Point_type);
    //    Point_type->setText(0,QString("属性"));

    //    auto combo_box3 = new QComboBox(this);
    //    auto combo_box4 = new QComboBox(this);
    //    auto combo_box5 = new QComboBox(this);
    //    auto combo_box6 = new QComboBox(this);
    //    auto combo_box7 = new QComboBox(this);
    //    auto combo_box8 = new QComboBox(this);
    //    auto combo_box9 = new QComboBox(this);
    //    auto combo_box10 = new QComboBox(this);

    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box3,"道路:");
    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box4,"场景:");
    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box5,"避障:");
    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box6,"方向:");
    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box7,"宽窄:");
    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box8,"坡度:");
    //    getQComboBoxItem(mainTreeWidget,Point_type,combo_box9,"室内外:");

    //    //parameter
    //    QTreeWidgetItem *Parameter=new QTreeWidgetItem();
    //    //Parameter->setIcon(0,QIcon(":/res/images/Link.png"));
    //    mainTreeWidget->addTopLevelItem(Parameter);
    //    Parameter->setText(0,QString("参数"));

    //    auto line_edit7 = new QLineEdit(this);
    //    //auto line_edit8 = new QLineEdit(this);
    //    auto line_edit9 = new QLineEdit(this);
    //    auto line_edit10 = new QLineEdit(this);

    //    getQLineEditItem(mainTreeWidget,Parameter,line_edit7,"限速/编号:");
    //    getQComboBoxItem(mainTreeWidget,Parameter,combo_box10,"链接:");
    //    getQLineEditItem(mainTreeWidget,Parameter,line_edit9,"链接号:");
    //    getQLineEditItem(mainTreeWidget,Parameter,line_edit10,"laneletid/楼层:");

    //    //info
    //    QTreeWidgetItem *infomessage=new QTreeWidgetItem();
    //    //infomessage->setIcon(0,QIcon(":/res/images/infomessage.png"));
    //    mainTreeWidget->addTopLevelItem(infomessage);
    //    infomessage->setText(0,QString("信息"));

    //    auto my_label = new QLabel(this);
    //    auto my_label2 = new QLabel(this);

    //    getQLabelItem(mainTreeWidget,infomessage,my_label,"vmap总数:");
    //    getQLabelItem(mainTreeWidget,infomessage,my_label2,"lanelet2总数:");

    //    //pcd-z
    //    // QTreeWidgetItem *Point_z=new QTreeWidgetItem();
    //    // Point_z->setIcon(0,QIcon(":/res/images/Point.png"));
    //    // mainTreeWidget->addTopLevelItem(Point_z);
    //    // Point_z->setText(0,QString("高度"));

    //    // getQLineEditItem(mainTreeWidget,Point_z,mainwindow_->pcdzmax_edit,"z-max:");
    //    // getQLineEditItem(mainTreeWidget,Point_z,mainwindow_->pcdzmin_edit,"z-min:");
    //    // getQPushButtonItem(mainTreeWidget,Point_z,mainwindow->reload_pBtn,"刷新:");

    //    //
    //    QTreeWidgetItem *laneletInfo=new QTreeWidgetItem();
    //    // laneletInfo->setIcon(0,QIcon(":/res/images/.png"));
    //    mainTreeWidget->addTopLevelItem(laneletInfo);
    //    laneletInfo->setText(0,QString("信息"));

    //    auto line_edit11 = new QLineEdit(this);

    //    getQLineEditItem(mainTreeWidget,laneletInfo,line_edit11,"规则ID:");

    mainTreeWidget->expandAll();

    this->setMinimumSize(400, 800);
    this->setMaximumSize(400, 800);
    //    this->setWindowFlags(Qt::FramelessWindowHint);

    QObject::connect(this->comfire_button, &QPushButton::clicked, this, &TaskListUi::savePushButton);
}

void TaskListUi::updateTopicParams(QString msg)
{
    //    vec_lidar_datas

    qDebug()<<"999999999999999999999999999999999999";
    Json::Value parameter_server;
    Json::Reader reader;
    reader.parse(msg.toStdString(), parameter_server); // LidarParam.LidarParam0.IP

    for (int i = 0; i < 14; i++)
    {
        vec_lidar_datas[2][i]->setText(QString::fromStdString( parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["IP"].asString()));
        vec_lidar_datas[3][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["Port"].asString()));
        
        vec_lidar_datas[2][i]->setText(QString::fromStdString( parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["x"].asString()));
        vec_lidar_datas[3][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["y"].asString()));
        vec_lidar_datas[4][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["z"].asString()));
        vec_lidar_datas[5][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["pitch"].asString()));
        vec_lidar_datas[6][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["roll"].asString()));
        vec_lidar_datas[7][i]->setText(QString::fromStdString(parameter_server["LidarParam"]["LidarParam" + std::to_string(i)]["yaw"].asString()));
    }
}

void TaskListUi::savePushButton()
{

    // QVector<QVector<QString>> dat;
    // for (int i = 0; i < 14; i++)
    // {
    //     qDebug() << vec_lidar_datas[0][i]->text();
    //     qDebug() << vec_lidar_datas[1][i]->text();
    //     qDebug() << vec_lidar_datas[2][i]->text();
    //     qDebug() << vec_lidar_datas[3][i]->text();
    //     qDebug() << vec_lidar_datas[4][i]->text();
    //     qDebug() << vec_lidar_datas[5][i]->text();
    //     qDebug() << vec_lidar_datas[6][i]->text();
    //     qDebug() << vec_lidar_datas[7][i]->text();
    // }

    emit sigSavePushButton(vec_lidar_datas);
    qDebug() << "==================================00000000000000";
}

void TaskListUi::getQRadiobuttonItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QRadioButton *&radiobutton, const QString &info)
{
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, radiobutton);
}
void TaskListUi::getQCheckBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QCheckBox *&checkbox, const QString &info)
{
    // checkbox->setStyleSheet(myStyleSheets::myCheckBox::tasklistUiCheckBox);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, checkbox);
}
void TaskListUi::getQLineEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QLineEdit *&lineedit, const QString &info)
{
    // lineedit->setStyleSheet(myStyleSheets::myLineEdit::tasklistUiLineEdit);
    lineedit->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, lineedit);
}
void TaskListUi::getQComboBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QComboBox *&combobox, const QString &info)
{
    // combobox->setStyleSheet(myStyleSheets::myCombox::tasklistUiComboBox);
    combobox->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, combobox);
}
void TaskListUi::getQSpinBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QSpinBox *&spinbox, const QString &info)
{
    // spinbox->setStyleSheet(myStyleSheets::mySpinBox::tasklistUiSpinBox);
    spinbox->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, spinbox);
}
void TaskListUi::getQLabelItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QLabel *&label, const QString &info)
{
    // spinbox->setStyleSheet(myStyleSheets::myLabel::tasklistUiComboBox);
    // label->adjustSize();
    label->setFixedSize(155, 39);
    // label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, label);
}
void TaskListUi::getQPushButtonItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, QPushButton *&pushbutton, const QString &info)
{
    pushbutton->setMaximumWidth(150);
    // pushbutton->setAlignment(Qt::AlignCenter);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, pushbutton);
}

QCheckBox *TaskListUi::creteQCheckBoxItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info)
{
    QCheckBox *modeBox = new QCheckBox;
    modeBox->setDisabled(true);
    // modeBox->setStyleSheet(myStyleSheets::myCheckBox::tasklistUiCheckBox);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, modeBox);
    return modeBox;
}

QLineEdit *TaskListUi::creteQlineEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info)
{
    QLineEdit *LineEdit = new QLineEdit("255;255;255");
    LineEdit->setDisabled(true);
    // LineEdit->setStyleSheet(myStyleSheets::myLineEdit::tasklistUiLineEdit);
    LineEdit->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, LineEdit);
    return LineEdit;
}

QComboBox *TaskListUi::creteQComboBoxEditItem(QTreeWidget *&mainTreeWidget, QTreeWidgetItem *&mainItem, const QString &info, const QStringList &list)
{
    QComboBox *comboBox = new QComboBox();
    // comboBox->setStyleSheet(myStyleSheets::myCombox::tasklistUiComboBox);
    comboBox->setDisabled(true);
    for (int i = 0; i < list.size(); i++)
    {
        comboBox->addItem(list.at(i));
    }
    comboBox->setMaximumWidth(150);
    QTreeWidgetItem *Item = new QTreeWidgetItem(QStringList() << info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item, 1, comboBox);
    return comboBox;
}
