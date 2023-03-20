#ifndef SETROI_H
#define SETROI_H

#include <QWidget>
#include <QScrollArea>

#include <QLayout>
#include "qtablewidget.h"
#include "paintarea.h"
#include "common.h"
extern bool changindex ;

struct tableRow2{
    QTableWidgetItem itemx;
    QTableWidgetItem itemy;

};

namespace Ui {
class SetROI;
}

class SetROI : public QWidget
{
    Q_OBJECT

public:
    explicit SetROI(QWidget *parent = 0);
    ~SetROI();


    QScrollArea * scrollarea;
    QList<struct tableRow2>list_tableItem;
    int tableRowcount;
    void showPoint();

    Area area[AREAS];



public slots:

signals:

    void sigalareasize(int);
    void sigalareapaint();
    void sigaltablepaint();
    //   void sigalareaindex(int index);
    void sigChangeArea_index(int);
    void sigSaveAreaData();


private slots:
    void on_tableWidget_cellChanged(int row, int column);

    void on_comboBox_activated(int index);

    void on_lineEdit_times_textChanged(const QString &arg1);

    void on_lineEdit_Area_height_max_textChanged(const QString &arg1);

    void on_lineEdit_Area_height_min_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_comfire_clicked();

private:
    Ui::SetROI *ui;
    int area_index =0;
};

#endif // SETROI_H
