#ifndef SMSDIALOG_H
#define SMSDIALOG_H

#include <QDialog>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
class SMSDialog;
}

class SMSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMSDialog(QWidget *parent = nullptr);
    ~SMSDialog();
    std::vector<std::string> & getSmsNumbers();
    int getSmsTimeInterval();
    int getWarningDistance();
private slots:
    void on_pushButton_clicked();
    void doCustomContextMenuRequested(const QPoint &);
    void DeleteItemFunction();
    void on_pushButton_time_clicked();
private:
    bool IsValidPhoneNumber(const QString & phoneNum);
private:
    Ui::SMSDialog *ui;
    QAction *m_pact;
    std::vector <std::string> numberList;
    int smsTimeInterval;
    int g_distance;
};

#endif // SMSDIALOG_H
