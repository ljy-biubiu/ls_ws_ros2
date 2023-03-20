#ifndef DIARY_H
#define DIARY_H

#include <QWidget>
#include <QList>

#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include "my_Util.h"

#include <mutex>

const int log_size = 100;

namespace Ui
{
    class Diary;
}

namespace LOGLEVEL
{
    enum
    {
        PENDING = -1,
        DEBUD = 0,
        WARM = 1,
        CRITICAL = 2,
    };
}

struct Log
{
    bool flag{false};
    int level{-1};
    std::string date;
    std::string msg;
};

class Diary : public QWidget
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent = nullptr);
    ~Diary();

    void pushLogData(const Log &msg);

private:
    Ui::Diary *ui;
    QList<Log> logs;
    QTableWidget *TableWidget;
    std::mutex my_lock;

    QTableWidgetItem *table_widget_item_date;
    QTableWidgetItem *table_widget_item_level;
    QTableWidgetItem *table_widget_item_data;

private slots:
   void show_log(QString);
    


};

#endif // DIARY_H
