#include "setroi.h"
#include "ui_setroi.h"
#include <QDebug>
bool changindex = false;
SetROI::SetROI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetROI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->widget->setParentWidget(this);
    ui->widget->setTitleName(QStringLiteral("防区设置"));
    scrollarea = new QScrollArea();
    scrollarea->setBackgroundRole(QPalette::Midlight); // 背景色
    scrollarea->setStyleSheet("QScrollArea {background-color: rgb(0, 0, 0);}");
    scrollarea->viewport()->setStyleSheet("background-color: rgb(0, 0, 0);");
    scrollarea->setAlignment(Qt::AlignCenter);  // 居中对齐
    ui->horizontalLayout->addWidget(scrollarea);

    ui->tableWidget_2->horizontalHeader()->setVisible(true);


    connect(ui->tableWidget_2, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(on_comboBox_activated(int)));

    ui->tableWidget->hide();

    for(int i=0;i<AREAS;i++)
    {
        area[i].id =i;
        area[i].Obstacle_times =1;
        area[i].Area_height_down=10;
        area[i].Area_height_top =20;

        area[i].Area2D_point_T.clear();
        area[i].Area2D_point.clear();
    }
}

SetROI::~SetROI()
{
    delete ui;
}


void  SetROI::showPoint()
{

    //

    int i = 0;
    list_tableItem.clear();

    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列均分
    ui->tableWidget_2->clearSelection();//a取消选中行

    tableRowcount = area[area_index].Area2D_point_T.size();
    ui->tableWidget_2->setRowCount(tableRowcount);

    for (i = 0; i < tableRowcount; i++)
    {
        struct tableRow2 row;
        QString text1, text2;

        text1 = QString("%1").arg(area[area_index].Area2D_point_T[i].x);
        text2 = QString("%1").arg(area[area_index].Area2D_point_T[i].y);

        row.itemx.setText(text1);
        row.itemy.setText(text2);

        list_tableItem << row;
        ui->tableWidget_2->setItem(i, 0, &list_tableItem[i].itemx);
        ui->tableWidget_2->setItem(i, 1, &list_tableItem[i].itemy);

    }
    changindex = false;

//    ui->lineEdit_times->setText(QString("%1").arg(area[area_index].Obstacle_times));
//    ui->lineEdit_max_Z->setText(QString("%1").arg(area[area_index].Area_height_top));
//    ui->lineEdit_min_Z->setText(QString("%1").arg(area[area_index].Area_height_down));

}


void SetROI::on_tableWidget_cellChanged(int row, int column)
{
    QTableWidgetItem *itm;
    QString s;
    float num,x,y;
    tableRowcount = area[area_index].Area2D_point_T.size();
    if (row >= 0)
    {
        itm = ui->tableWidget_2->item(row, column);
        s = itm->text();
        num = s.toFloat();

        if (column == 0)
        {
            area[area_index].Area2D_point_T[row].x = num;
        }

        if (column == 1)
        {
            area[area_index].Area2D_point_T[row].y = num;

        }
        x = area[area_index].Area2D_point_T[row].x ;
        y = area[area_index].Area2D_point_T[row].y;

    }
    if(!changindex)
    {
        emit sigalareapaint();

    }
    emit sigaltablepaint();
}

void SetROI:: on_comboBox_activated(int index)
{
    area_index = index;
    changindex = true;
    showPoint();

    emit sigChangeArea_index(index);



    area[area_index].Obstacle_times = ui->lineEdit_times->text().toFloat();
    area[area_index].Area_height_top = ui->lineEdit_max_Z->text().toFloat();
    area[area_index].Area_height_down =ui->lineEdit_min_Z->text().toFloat();

    //qDebug()<<"high:"<<ui->lineEdit_max_Z->text().toFloat();

    emit sigaltablepaint();

}

//void SetROI::on_lineEdit_times_textChanged(const QString &arg1)
//{
//    area[area_index].Obstacle_times = arg1.toFloat();
//}

//void SetROI::on_lineEdit_max_Z_textChanged(const QString &arg1)
//{
//    qDebug()<<"lineEdit_max_Z :"<<arg1.toFloat();
//    area[area_index].Area_height_top = arg1.toFloat();

//}

//void SetROI::on_lineEdit_min_Z_textChanged(const QString &arg1)
//{
//    qDebug()<<"lineEdit_min_Z :"<<arg1.toFloat();
//    area[area_index].Area_height_down = arg1.toFloat();
//}

//void SetROI::on_lineEdit_editingFinished(const QString &arg1)
//{
//    emit sigalareasize();
//}



void SetROI::on_lineEdit_textChanged(const QString &arg1)
{
    emit sigalareasize(arg1.toInt());
}

void SetROI::on_pushButton_comfire_clicked()
{

    area[area_index].Area_height_top = ui->lineEdit_max_Z->text().toFloat();
    area[area_index].Area_height_down = ui->lineEdit_min_Z->text().toFloat();

    qDebug()<<"lineEdit_max_Z :"<<area[area_index].Area_height_top;
    qDebug()<<"lineEdit_min_Z :"<<area[area_index].Area_height_down;

    emit sigalreflushpaint();
    emit sigToPaintSaveAreaData();
}
