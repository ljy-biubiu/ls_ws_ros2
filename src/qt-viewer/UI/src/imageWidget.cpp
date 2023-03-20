#include "imageWidget.h"
#include <QGradient>
#include <QPainter>
ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    m_StyleColor(QColor(30, 95, 219, 100))
{

}

void ImageWidget::setStyleColor(QColor color)
{
    m_StyleColor = color;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //绘制上边框
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient Linear(0,0,0,20);

    Linear.setColorAt(0,m_StyleColor);
    Linear.setColorAt(1,QColor(255,255,255,0));

    painter.setBrush(Linear);
    painter.setPen(QPen(QColor(255,255,255,0)));
    painter.drawRect(20,0,this->width()-40,20);

    //绘制下边框
    Linear.setStart(0,this->height());
    Linear.setFinalStop(0,this->height()-20);

    painter.setBrush(Linear);
    painter.drawRect(20,0,this->width()-40,this->height());

    //绘制左边框
    Linear.setStart(0,0);
    Linear.setFinalStop(20,0);

    painter.setBrush(Linear);
    painter.drawRect(0,20,this->width(),this->height()-40);

    //绘制右边框
    Linear.setStart(this->width(),0);
    Linear.setFinalStop(this->width()-20,0);

    painter.setBrush(Linear);
    painter.drawRect(0,20,this->width(),this->height()-40);

    QRadialGradient Radial(20,20,20,20,20);
    Radial.setColorAt(0,QColor(255,255,255,0));
    Radial.setColorAt(1,m_StyleColor);

    painter.setBrush(Radial);
    painter.drawPie(0,0,40,40,90 * 16,90 * 16);

    Radial.setCenter(this->width()-20,20);
    Radial.setFocalPoint(this->width()-20,20);
    painter.setBrush(Radial);
    painter.drawPie(this->width()-40,0,40,40,0 * 16,90 * 16);

    Radial.setCenter(20,this->height()-20);
    Radial.setFocalPoint(20,this->height()-20);
    painter.setBrush(Radial);
    painter.drawPie(0,this->height()-40,40,40,180 * 16,90 * 16);

    Radial.setCenter(this->width()-20,this->height()-20);
    Radial.setFocalPoint(this->width()-20,this->height()-20);
    painter.setBrush(Radial);
    painter.drawPie(this->width()-40,this->height()-40,40,40,270 * 16,90 * 16);
}
