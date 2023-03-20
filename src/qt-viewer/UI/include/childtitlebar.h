/*****************************************
 * 作者: YYC
 * 日期: 2020-04-26
 * 功能：主标题栏，内含有窗体最大化，最小化，关闭
 * 以及窗口的Title，以及名称
 * ***************************************/
#ifndef CHILDTITLEBAR_H
#define CHILDTITLEBAR_H

#include <QWidget>
#include "titlebar.h"

namespace Ui {
class ChildTitleBar;
}

class ChildTitleBar : public TitleBar
{
    Q_OBJECT

public:
    explicit ChildTitleBar(QWidget *parent = 0);
    ~ChildTitleBar();
    void setTitleName(QString titleName);
private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::ChildTitleBar *ui;

};

#endif // CHILDTITLEBAR_H
