#include "smsdialog.h"
#include "ui_smsdialog.h"
#include <QDebug>

SMSDialog::SMSDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMSDialog)
{
    ui->setupUi(this);
    ui->widget->setParentWidget(this);
    ui->widget->setTitleName(QStringLiteral("短信设置"));
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    ui->spinBox->setMaximum(300);
    ui->spinBox_dist->setMaximum(500);
    QRegExp regExp("0?(13|14|15|18|17)[0-9]{9}");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp, this));
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);//设置支持右键菜单
    connect(ui->treeWidget,&QTreeWidget::customContextMenuRequested,this,&SMSDialog::doCustomContextMenuRequested);
    QSettings settings(QStringLiteral("./setting/device.ini"),QSettings::IniFormat);
    settings.beginGroup(QStringLiteral("SmsNumber"));
    QStringList keys = settings.allKeys();
    for (int i = 0; i < keys.size();i++)
    {
        QString value = settings.value(keys[i]).toString();
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setFont(0,QFont("KaiTi",14));
        item->setFont(1,QFont("KaiTi",14));
        item->setText(0,QString::number(i+1));
        item->setText(1,value);
        ui->treeWidget->addTopLevelItem(item);
        numberList.emplace_back(value.toStdString());
    }
    settings.endGroup();
    settings.beginGroup(QStringLiteral("SmsTimeInterval"));
    smsTimeInterval = settings.value(QStringLiteral("Time")).toInt();
    g_distance = settings.value(QStringLiteral("Distance")).toInt();
    ui->spinBox->setValue(smsTimeInterval);
    ui->spinBox_dist->setValue(g_distance);
    settings.endGroup();
}

SMSDialog::~SMSDialog()
{
    delete ui;
}


bool SMSDialog::IsValidPhoneNumber(const QString & phoneNum)
{
    QRegExp regx("0?(13|14|15|18|17)[0-9]{9}");
    QRegExpValidator regs(regx, 0);
    QString pNum = phoneNum;
    int pos = 0;
    QValidator::State res = regs.validate(pNum, pos);
    if (QValidator::Acceptable == res) {
        return true;
    }
    else {
        return false;
    }
}

void SMSDialog::doCustomContextMenuRequested(const QPoint &)
{
    m_pact = new QAction(QStringLiteral("删除"), this);
    //QAction *pDelAction_1 = new QAction(QStringLiteral("重命名"), this);
    QMenu *popMenu = new QMenu(this);//定义右键弹出菜单
    popMenu->addAction(m_pact);//往菜单内添加QAction
    // QAction *deleAction = cmenu->addAction("Delete");//另一种创建方式
    connect(m_pact, SIGNAL(triggered()), this, SLOT(DeleteItemFunction()));
    popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
}


void SMSDialog::DeleteItemFunction()
{
    QTreeWidgetItem * currentItem = ui->treeWidget->currentItem();//获取当前节点
    if (currentItem == NULL)
    {
        return;
    }
    else
    {
        QSettings settings(QStringLiteral("./setting/device.ini"),QSettings::IniFormat);
        settings.beginGroup(QStringLiteral("SmsNumber"));
        settings.remove(QString("number_%1").arg(currentItem->text(0).toInt()));
        settings.endGroup();
        for (std::vector <std::string>::iterator it = numberList.begin();it != numberList.end(); it++)
        {
            if(*it == currentItem->text(1).toStdString())
            {
                numberList.erase(it);
                break;
            }
        }
        delete currentItem;
    }

}

void SMSDialog::on_pushButton_clicked()
{
    QString number = ui->lineEdit->text();
    if(number.isEmpty()) return;
    if(false == IsValidPhoneNumber(number))
    {
        QMessageBox msgBox;
        msgBox.setWindowFlag(Qt::FramelessWindowHint);
        msgBox.setText(QString::fromLocal8Bit(
            "请检查输入的号码是否正确！！！"
        ));
        msgBox.exec();
        return;
    }
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
          QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
          if(item->text(1).contains(number,Qt::CaseInsensitive))
          {
              QMessageBox msgBox;
              msgBox.setWindowFlag(Qt::FramelessWindowHint);
              msgBox.setText(QString::fromLocal8Bit(
                  "该号码已经存在，请重新输入！！！"
              ));
              msgBox.exec();
              return;
          }
    }
    QSettings settings(QStringLiteral("./setting/device.ini"),QSettings::IniFormat);
    settings.beginGroup(QStringLiteral("SmsNumber"));
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setFont(0,QFont("KaiTi",14));
    item->setFont(1,QFont("KaiTi",14));
    item->setText(0,QString::number(ui->treeWidget->topLevelItemCount()+1));
    item->setText(1,number);
    numberList.emplace_back(number.toStdString());
    ui->treeWidget->addTopLevelItem(item);
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
         QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
         settings.setValue(QString("number_%1").arg(item->text(0).toInt()),item->text(1));
    }
    settings.endGroup();
}

std::vector<std::string> & SMSDialog::getSmsNumbers()
{
    return numberList;
}


void SMSDialog::on_pushButton_time_clicked()
{
    smsTimeInterval = ui->spinBox->value();
    g_distance = ui->spinBox_dist->value();
    QSettings settings(QStringLiteral("./setting/device.ini"),QSettings::IniFormat);
    settings.beginGroup(QStringLiteral("SmsTimeInterval"));
    settings.setValue(QStringLiteral("Time"),smsTimeInterval);
    settings.setValue(QStringLiteral("Distance"),g_distance);
    settings.endGroup();
    QMessageBox msgBox;
    msgBox.setWindowFlag(Qt::FramelessWindowHint);
    msgBox.setText(QString::fromLocal8Bit(
        "报警时间间隔/预警距离设置成功"
    ));
    msgBox.exec();
}


int SMSDialog::getSmsTimeInterval()
{
    return smsTimeInterval;
}

int SMSDialog::getWarningDistance()
{
    return g_distance;
}

