#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class ImageWidget :public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);

    QColor m_StyleColor;

    void setStyleColor(QColor color);
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // GROUNDBACK_H
