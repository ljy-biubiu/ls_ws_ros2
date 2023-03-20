#ifndef ADDLIDAR_H
#define ADDLIDAR_H

#include <QDialog>
#include "common.h"
#include <QScrollArea>
#include <jsoncpp/json/json.h>

namespace Ui {
class AddLidar;
}

class AddLidar : public QDialog
{
    Q_OBJECT

public:
    explicit AddLidar(QWidget *parent = 0);
    ~AddLidar();
    void initcombox(QList<int>&items);
    void ShowData(const QString &str);
    SetData data;
private slots:
    void on_btn_sure_clicked();
    void on_btn_no_clicked();

signals:
    void SendSet(QString);
private:
    Ui::AddLidar *ui;
    QScrollArea* scrollArea;
};

#endif // ADDLIDAR_H
