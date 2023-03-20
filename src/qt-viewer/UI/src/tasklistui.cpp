#include "tasklistui.h"
#include "qdebug.h"
#include "QHBoxLayout"
//#include "allstylesheets.h"

TaskListUi::TaskListUi(QWidget *parent)
{

    QHBoxLayout * mainLayout_H = new QHBoxLayout();
    QTreeWidget * mainTreeWidget = new QTreeWidget(this);
    mainLayout_H->addWidget(mainTreeWidget);

    this->setLayout(mainLayout_H);
    QStringList headers;
    headers<<"name";
    mainTreeWidget->setColumnCount(2);
    //mainTreeWidget->setMinimumSize(400,800);
    QHeaderView *head=mainTreeWidget->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    //mainTreeWidget->autoScrollMargin();


    //    mainTreeWidget->setColumnWidth(0,170);
    mainTreeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //mainTreeWidget->setStyleSheet(myStyleSheets::myTree::tasklistUiTree);
    mainTreeWidget->setHeaderHidden(true);
    //mainTreeWidget->setAutoFillBackground(true);

    //tool
    QTreeWidgetItem *Tool=new QTreeWidgetItem();
    //Tool->setIcon(0,QIcon(":/res/images/painter.png"));
    //    mainTreeWidget->addTopLevelItem(Tool);
    //    Tool->setText(0,QString("工具"));

    auto check_box = new QCheckBox(this);
    auto check_box2 = new QCheckBox(this);

    getQCheckBoxItem(mainTreeWidget,Tool,check_box,"vmap-tool:");
    getQCheckBoxItem(mainTreeWidget,Tool,check_box2,"lanelet-tool:");

    //mode
    QTreeWidgetItem *Mode=new QTreeWidgetItem();
    //Mode->setIcon(0,QIcon(":/res/images/param-mode.png"));
    mainTreeWidget->addTopLevelItem(Mode);
    Mode->setText(0,QString("类型"));

    auto combo_box = new QComboBox(this);
    auto spin_box = new QSpinBox(this);


    getQComboBoxItem(mainTreeWidget,Mode,combo_box,"类型:");
    getQSpinBoxItem(mainTreeWidget,Mode,spin_box,"数量:");

    //vmap-param
    QTreeWidgetItem *Point=new QTreeWidgetItem();
    //Point->setIcon(0,QIcon(":/res/images/Point.png"));
    mainTreeWidget->addTopLevelItem(Point);
    Point->setText(0,QString("点"));

    auto line_edit = new QLineEdit(this);
    auto line_edit2 = new QLineEdit(this);
    auto line_edit3 = new QLineEdit(this);
    auto line_edit4 = new QLineEdit(this);
    auto line_edit5 = new QLineEdit(this);
    auto line_edit6 = new QLineEdit(this);

    getQLineEditItem(mainTreeWidget,Point,line_edit,"x:");
    getQLineEditItem(mainTreeWidget,Point,line_edit2,"y:");
    getQLineEditItem(mainTreeWidget,Point,line_edit3,"z:");
    getQLineEditItem(mainTreeWidget,Point,line_edit4,"w-dir:");
    getQLineEditItem(mainTreeWidget,Point,line_edit5,"lat:");
    getQLineEditItem(mainTreeWidget,Point,line_edit6,"lon:");

    //point-type
    QTreeWidgetItem *Point_type=new QTreeWidgetItem();
    //Point_type->setIcon(0,QIcon(":/res/images/type.png"));
    mainTreeWidget->addTopLevelItem(Point_type);
    Point_type->setText(0,QString("属性"));

    auto combo_box3 = new QComboBox(this);
    auto combo_box4 = new QComboBox(this);
    auto combo_box5 = new QComboBox(this);
    auto combo_box6 = new QComboBox(this);
    auto combo_box7 = new QComboBox(this);
    auto combo_box8 = new QComboBox(this);
    auto combo_box9 = new QComboBox(this);
    auto combo_box10 = new QComboBox(this);

    getQComboBoxItem(mainTreeWidget,Point_type,combo_box3,"道路:");
    getQComboBoxItem(mainTreeWidget,Point_type,combo_box4,"场景:");
    getQComboBoxItem(mainTreeWidget,Point_type,combo_box5,"避障:");
    getQComboBoxItem(mainTreeWidget,Point_type,combo_box6,"方向:");
    getQComboBoxItem(mainTreeWidget,Point_type,combo_box7,"宽窄:");
    getQComboBoxItem(mainTreeWidget,Point_type,combo_box8,"坡度:");
    getQComboBoxItem(mainTreeWidget,Point_type,combo_box9,"室内外:");

    //parameter
    QTreeWidgetItem *Parameter=new QTreeWidgetItem();
    //Parameter->setIcon(0,QIcon(":/res/images/Link.png"));
    mainTreeWidget->addTopLevelItem(Parameter);
    Parameter->setText(0,QString("参数"));

    auto line_edit7 = new QLineEdit(this);
    //auto line_edit8 = new QLineEdit(this);
    auto line_edit9 = new QLineEdit(this);
    auto line_edit10 = new QLineEdit(this);

    getQLineEditItem(mainTreeWidget,Parameter,line_edit7,"限速/编号:");
    getQComboBoxItem(mainTreeWidget,Parameter,combo_box10,"链接:");
    getQLineEditItem(mainTreeWidget,Parameter,line_edit9,"链接号:");
    getQLineEditItem(mainTreeWidget,Parameter,line_edit10,"laneletid/楼层:");

    //info
    QTreeWidgetItem *infomessage=new QTreeWidgetItem();
    //infomessage->setIcon(0,QIcon(":/res/images/infomessage.png"));
    mainTreeWidget->addTopLevelItem(infomessage);
    infomessage->setText(0,QString("信息"));

    auto my_label = new QLabel(this);
    auto my_label2 = new QLabel(this);

    getQLabelItem(mainTreeWidget,infomessage,my_label,"vmap总数:");
    getQLabelItem(mainTreeWidget,infomessage,my_label2,"lanelet2总数:");

    //pcd-z
    // QTreeWidgetItem *Point_z=new QTreeWidgetItem();
    // Point_z->setIcon(0,QIcon(":/res/images/Point.png"));
    // mainTreeWidget->addTopLevelItem(Point_z);
    // Point_z->setText(0,QString("高度"));

    // getQLineEditItem(mainTreeWidget,Point_z,mainwindow_->pcdzmax_edit,"z-max:");
    // getQLineEditItem(mainTreeWidget,Point_z,mainwindow_->pcdzmin_edit,"z-min:");
    // getQPushButtonItem(mainTreeWidget,Point_z,mainwindow->reload_pBtn,"刷新:");

    //
    QTreeWidgetItem *laneletInfo=new QTreeWidgetItem();
    // laneletInfo->setIcon(0,QIcon(":/res/images/.png"));
    mainTreeWidget->addTopLevelItem(laneletInfo);
    laneletInfo->setText(0,QString("信息"));

    auto line_edit11 = new QLineEdit(this);

    getQLineEditItem(mainTreeWidget,laneletInfo,line_edit11,"规则ID:");

    mainTreeWidget->expandAll();
}

void TaskListUi::getQRadiobuttonItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QRadioButton * & radiobutton,const QString &info)
{
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,radiobutton);
}
void TaskListUi::getQCheckBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QCheckBox * & checkbox,const QString &info)
{
    //checkbox->setStyleSheet(myStyleSheets::myCheckBox::tasklistUiCheckBox);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,checkbox);
}
void TaskListUi::getQLineEditItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QLineEdit * & lineedit,const QString &info)
{
    //lineedit->setStyleSheet(myStyleSheets::myLineEdit::tasklistUiLineEdit);
    lineedit->setMaximumWidth(150);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,lineedit);
}
void TaskListUi::getQComboBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QComboBox * & combobox,const QString &info)
{
    //combobox->setStyleSheet(myStyleSheets::myCombox::tasklistUiComboBox);
    combobox->setMaximumWidth(150);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,combobox);
}
void TaskListUi::getQSpinBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QSpinBox * & spinbox,const QString &info)
{
    //spinbox->setStyleSheet(myStyleSheets::mySpinBox::tasklistUiSpinBox);
    spinbox->setMaximumWidth(150);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,spinbox);
}
void TaskListUi::getQLabelItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QLabel * & label,const QString &info)
{
    // spinbox->setStyleSheet(myStyleSheets::myLabel::tasklistUiComboBox);
    // label->adjustSize();
    label->setFixedSize(155, 39);
    // label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,label);
}
void TaskListUi::getQPushButtonItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,QPushButton * & pushbutton,const QString &info)
{
    pushbutton->setMaximumWidth(150);
    // pushbutton->setAlignment(Qt::AlignCenter);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,pushbutton);
}

QCheckBox* TaskListUi::creteQCheckBoxItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,const QString &info)
{
    QCheckBox* modeBox=new QCheckBox;
    modeBox->setDisabled(true);
    //modeBox->setStyleSheet(myStyleSheets::myCheckBox::tasklistUiCheckBox);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,modeBox);
    return modeBox;
}

QLineEdit* TaskListUi::creteQlineEditItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,const QString &info)
{
    QLineEdit* LineEdit=new QLineEdit("255;255;255");
    LineEdit->setDisabled(true);
    //LineEdit->setStyleSheet(myStyleSheets::myLineEdit::tasklistUiLineEdit);
    LineEdit->setMaximumWidth(150);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,LineEdit);
    return LineEdit;
}

QComboBox* TaskListUi::creteQComboBoxEditItem(QTreeWidget* & mainTreeWidget,QTreeWidgetItem* & mainItem,const QString &info ,const QStringList &list)
{
    QComboBox* comboBox=new QComboBox();
    //comboBox->setStyleSheet(myStyleSheets::myCombox::tasklistUiComboBox);
    comboBox->setDisabled(true);
    for(int i =0;i<list.size();i++)
    {
        comboBox->addItem(list.at(i));
    }
    comboBox->setMaximumWidth(150);
    QTreeWidgetItem *Item=new QTreeWidgetItem(QStringList()<<info);
    mainItem->addChild(Item);
    mainTreeWidget->setItemWidget(Item,1,comboBox);
    return comboBox;
}
