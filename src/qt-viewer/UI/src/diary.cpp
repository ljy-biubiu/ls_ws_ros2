#include "diary.h"
#include "ui_diary.h"

#include <QCalendarWidget>
#include <QHeaderView>

Diary::Diary(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Diary)
{
    ui->setupUi(this);

    // 设置背景黑色
    QPalette palBackGround(this->palette());
    palBackGround.setColor(QPalette::Background, QColor(34, 34, 34));
    this->setAutoFillBackground(true);
    this->setPalette(palBackGround);

    TableWidget = new QTableWidget();

    TableWidget->setColumnCount(3);
    TableWidget->setRowCount(log_size);

    //    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //    TableWidget->setSortingEnabled( false );
    //    TableWidget->verticalHeader()->hide();
    //    TableWidget->setWordWrap( false );
    //    TableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    //    TableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //    TableWidget->setShowGrid( false );
    //    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    TableWidget->horizontalHeader()->setHighlightSections( false );
    ////    TableWidget->setItemDelegate( new  NoFocusDelegate());
    ////    TableWidget->setModel(m_proxyModel);
    //    TableWidget->setAlternatingRowColors( true );   // alternative colors
    //    TableWidget->setFrameShape(QFrame::NoFrame);

    TableWidget->verticalHeader()->setVisible(false);
    //        TableWidget->horizontalHeader()->setVisible(false);

    // 设置表格中每一行的表头
    TableWidget->setHorizontalHeaderLabels(QStringList() << "日期"
                                                         << "等級"
                                                         << "信息");
    // 设置表格数据区内的所有单元格都不允许编辑
    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TableWidget->horizontalHeader()->setMinimumHeight(20);

    // 隔行变色
    TableWidget->setAlternatingRowColors(true);

    TableWidget->setColumnWidth(0, 90);
    TableWidget->setColumnWidth(1, 50);
    TableWidget->setColumnWidth(2, 220);

    table_widget_item_date = new QTableWidgetItem();
    table_widget_item_level = new QTableWidgetItem();
    table_widget_item_data = new QTableWidgetItem();

    // 设置表格中每一行的内容
    //    TableWidget->setItem(0,0,new QTableWidgetItem("22/12/20-12:30")); //向下复制一行 ctrl+alt+down
    //    TableWidget->setItem(0,1,new QTableWidgetItem("Critical"));
    //    TableWidget->setItem(0,2,new QTableWidgetItem("设置表格中每一行的内容设置表格中每一行的内容"));
    //    TableWidget->setItem(1,0,new QTableWidgetItem("22/12/20-12:30"));
    //    TableWidget->setItem(1,1,new QTableWidgetItem("Info"));
    //    TableWidget->setItem(1,2,new QTableWidgetItem("设置表格中每一行的内容设置表格中每一行的内容"));
    //    TableWidget->setItem(2,0,new QTableWidgetItem("22/12/20-12:30")); //向下复制一行 ctrl+alt+down
    //    TableWidget->setItem(2,1,new QTableWidgetItem("Critical"));
    //    TableWidget->setItem(2,2,new QTableWidgetItem("设置表格中每一行的内容设置表格中每一行的内容"));
    //    TableWidget->setItem(3,0,new QTableWidgetItem("22/12/20-12:30"));
    //    TableWidget->setItem(3,1,new QTableWidgetItem("Info"));
    //    TableWidget->setItem(3,2,new QTableWidgetItem("设置表格中每一行的内容设置表格中每一行的内容"));
    //    TableWidget->setItem(4,0,new QTableWidgetItem("22/12/20-12:30")); //向下复制一行 ctrl+alt+down
    //    TableWidget->setItem(4,1,new QTableWidgetItem("Critical"));
    //    TableWidget->setItem(4,2,new QTableWidgetItem("设置表格中每一行的内容设置表格中每一行的内容"));
    //    TableWidget->setItem(5,0,new QTableWidgetItem("22/12/20-12:30"));
    //    TableWidget->setItem(5,1,new QTableWidgetItem("Info"));
    //    TableWidget->setItem(5,2,new QTableWidgetItem("设置表格中每一行的内容设置表格中每一行的内容"));

    ui->verticalLayout_4->addWidget(TableWidget);

    //    auto previewLayout = new QGridLayout();
    //    auto calendar = new QCalendarWidget();
    //    previewLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);

    //    ui->tableWidget->setColumnWidth(0,60);
    //    ui->tableWidget->setColumnWidth(1,170);

    //    //QString add_text = u8"添加文字";
    //    // 第一种方式: append(const QString &text)   --最普通的添加方式，在文本内容后面添加新的文本内容

    //    ui->tableWidget->setItem(0,0,new QTableWidgetItem("水浒传"));
    //    ui->tableWidget->setItem(0,1,new QTableWidgetItem("水浒传"));
    //    ui->tableWidget->setItem(1,0,new QTableWidgetItem("水浒传"));
    //    ui->tableWidget->setItem(1,1,new QTableWidgetItem("水浒传"));
    //    ui->tableWidget->setItem(2,0,new QTableWidgetItem("水浒传"));
    //    ui->tableWidget->setItem(2,1,new QTableWidgetItem("水浒传"));

    //    ui->tableWidget->re

    //    //    logs
    //    std::string str1{"111111"};
    //    std::string str2{"222222"};
    //    std::string str3{"333333"};
    //    std::string str4{"444444"};
    //    std::string str5{"555555"};

    //    this->logs.push_back(str1);
    //    this->logs.push_back(str2);
    //    this->logs.push_back(str3);
    //    this->logs.push_back(str4);
    //    this->logs.push_back(str5);

    //    for(auto msg : logs)
    //    {
    //        ui->textEdit->append(add_text);
    //        ui->textEdit->append("      ");
    //    }

    //    ui->textEdit->append(add_text);
    //    ui->textEdit->append(add_text);
    //    ui->textEdit->append(add_text);
    //    ui->textEdit->append(add_text);

    // this->ui->textEdit->setStyleSheet("background-image:url(:/bmp/DSCN1604.JPG)");
    // this->ui->textEdit->setStyleSheet(QString("font-size:13px;border：1px solid black; background：#8c9092"));
    // setStyleSheet("font-size:13px;border：1px solid black; background：#8c9092");

    //        ui->textEdit->setStyleSheet("body {background-color: #aaa}");
}

void Diary::show_log(QString log)
{

    for (auto dat : logs)
    {
        if (log.toStdString() == dat.msg)
        {
            return;
        }
    }

    Log mylog;
    mylog.msg = log.toStdString();
    mylog.date = MyUtil::getCurDate();
    pushLogData(mylog);
}

void Diary::pushLogData(const Log &msg)
{
    std::lock_guard<std::mutex> LockGuard(my_lock);
    if (logs.size() > log_size)
    {
        logs.pop_back();
    }
    logs.push_front(msg);

    int cnt{0};

    for (auto msg : logs)
    {
        table_widget_item_level = new QTableWidgetItem("Critical");
        table_widget_item_date = new QTableWidgetItem(QString::fromStdString(msg.date));
        table_widget_item_data = new QTableWidgetItem(QString::fromStdString(msg.msg));

        TableWidget->setItem(cnt, 0, table_widget_item_date); // 向下复制一行 ctrl+alt+down
        TableWidget->setItem(cnt, 1, table_widget_item_level);
        TableWidget->setItem(cnt, 2, table_widget_item_data);

        table_widget_item_data->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        cnt++;
    }
}

Diary::~Diary()
{
    delete ui;
}
