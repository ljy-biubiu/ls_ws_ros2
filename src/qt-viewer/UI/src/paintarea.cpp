#include <QPainter>
#include "QDebug"
#include <qapplication.h>
#include "paintarea.h"
#include <QCursor>
#include <pcl/filters/passthrough.h>
#define range 150000

using namespace std;

bool flagAllCloud;
bool flagPartCloud;


PaintArea::PaintArea()/*区域绘图初始化*/
{
    setMouseTracking(true);
    move = false;
    zoom = 1;               /*放大比例初始化为1*/
    paint = false;
    leftsel = false;
    dragPropor = false;     /*没有选中三角形*/
    dragPoint = false;
    removePoint = false;
    moveStart = false;
    curPos = -1;
    area_index = 0;
    setGeometry(0,0,PAINT_SIZE+1,PAINT_SIZE+1);//setGeometry是相对于父窗体来说的一种对子窗体进行位置设置的方法;
    curPolygonPos = 1;
    centerPoint.setX(PAINT_SIZE/2);
    centerPoint.setY(( PAINT_SIZE/2));
    spliceflag = false;
    for(int i = 0; i < 3; i++){
        warning_type[i] = 0;
    }

    LidarInstance.lidar_Radius = Radius; //测量距离(通过添加雷达实现)

    LidarInstance.inPolygon.clear();
    for(int i = 0; i < 3; i++){
        LidarInstance.Polygon[i].clear();

    }
    for(int i =0;i<AREAS;i++)
    {
        box_cloud[i].reset(new pcl::PointCloud<Box_Cloud>);
        Area2d_point[i].clear();
        zmax[i] =0;
        zmin[i] =0;

    }
    tCloud.reset(new pcl::PointCloud<PointT>);

    xCloud.reset(new pcl::PointCloud<PointT>);

    for(int i=0;i<AREAS;i++)
    {
        area[i].id =i;
        area[i].Obstacle_times =1;
        area[i].Area_height_down=0;
        area[i].Area_height_top =0;
        area[i].Area2D_point.clear();
    }
    this->setFocusPolicy(Qt::ClickFocus);
}

void PaintArea::setCentralArea(const int& x,const int& y)
{
//    static int cur_x = PAINT_SIZE ;
//    static int cur_y = PAINT_SIZE ;

//    cur_x = cur_x + x;
//    cur_y = cur_y + y;

//    centerPoint.setX(x);
//    centerPoint.setY(y);
}

void PaintArea::setAreaSize(int radius)
{
    LidarInstance.lidar_Radius = radius;
}


void PaintArea::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    int i;
    QPainter painter(this);
    painter.scale(zoom,zoom);
    float kPaintSize = LidarInstance.lidar_Radius*2;
    painter.setPen(QPen(Qt::darkGray, 30/(zoom/0.1)));
    QFont font;
    font.setPointSize(100/(zoom/0.1));
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    painter.setFont(font);


    for (i=0;i<=col;i++){/*绘图区域绘制网格及显示坐标值*/
        if (i==0){
            painter.setPen(QPen(Qt::darkGray, 0));
            painter.drawLine(0,i*PAINT_SIZE/col,PAINT_SIZE,i*PAINT_SIZE/col);
            painter.drawLine(i*PAINT_SIZE/col,0,i*PAINT_SIZE/col,PAINT_SIZE+0);

            painter.setPen(QPen(Qt::darkGray, 30));
            painter.drawText(PAINT_SIZE/2 + 5, i*PAINT_SIZE/col+0,
                             QString::number((kPaintSize/2 - i*kPaintSize/col)));
            painter.drawText(i*PAINT_SIZE/col, PAINT_SIZE/2 + 10+0,
                             QString::number((i*kPaintSize/col - kPaintSize/2)));
        }
        else if(i==col)
        {
            painter.setPen(QPen(Qt::darkGray, 0));
            painter.drawLine(0,i*PAINT_SIZE/col-1,PAINT_SIZE,i*PAINT_SIZE/col-1);
            painter.drawLine(i*PAINT_SIZE/col-1,0,i*PAINT_SIZE/col-1,PAINT_SIZE+0);

            painter.drawText(i*PAINT_SIZE/col, PAINT_SIZE/2 + 10+0,
                             QString::number((i*kPaintSize/col - kPaintSize/2)));
            painter.drawText(PAINT_SIZE/2 + 5, i*PAINT_SIZE/col+0,
                             QString::number(-(kPaintSize/2 - (col - i)*kPaintSize/col)));

        }
        else
        {
            painter.setPen(QPen(Qt::darkGray, 0));
            painter.drawLine(0,i*PAINT_SIZE/col+0,PAINT_SIZE,i*PAINT_SIZE/col+0);
            painter.drawLine(i*PAINT_SIZE/col,0,i*PAINT_SIZE/col,PAINT_SIZE+0);

            painter.drawText(i*PAINT_SIZE/col, PAINT_SIZE/2 + 10+0,
                             QString::number((i*kPaintSize/col - kPaintSize/2)));
            painter.drawText(PAINT_SIZE/2 + 5, i*PAINT_SIZE/col+0,
                             QString::number(-(kPaintSize/2 - (col - i)*kPaintSize/col)));
        }
    }

    font.setPointSize(150/(zoom/0.1));
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    painter.setFont(font);
    float x1 = (mousemovepoint.x() -PAINT_SIZE/2)*LidarInstance.lidar_Radius/(PAINT_SIZE/2);
    float y1= (PAINT_SIZE/2-mousemovepoint.y())*LidarInstance.lidar_Radius/(PAINT_SIZE/2);
    QString text =QString("(%1,%2)").arg(x1).arg(y1);
    painter.drawText(mousemovepoint.x(),mousemovepoint.y(),text);
    /*绘制中间的黑线*/
    painter.setPen(QPen(Qt::darkGreen, 0));
    painter.drawLine(0,PAINT_SIZE/2+0,PAINT_SIZE,PAINT_SIZE/2+0);
    painter.drawLine(PAINT_SIZE/2,0,PAINT_SIZE/2,PAINT_SIZE+0);
    drawArea(painter,area_index);
    //绘制雷达数据  区域数据 区域内点云数据
    //坐标
    float msx = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    float msy = PAINT_SIZE/2  /LidarInstance.lidar_Radius;
    QPainter painter1(this);


    qreal rx,ry;
    rx = centerPoint.rx();
    ry = centerPoint.ry();

    QPointF p1;


    // std::cout<<"00000000000000000000000000000000000000000000"<<std::endl;
    // std::cout<<"flagAllCloud"<<std::endl;
    // std::cout<<flagAllCloud<<std::endl;
    // std::cout<<"00000000000000000000000000000000000000000000"<<std::endl;
    // std::cout<<"00000000000000000000000000000000000000000000"<<std::endl;

    //全部点云
    if(flagAllCloud == true)
    {
        painter1.setPen(QPen(Qt::white, 2)); //设置画笔的颜色/点云的颜色
        for(size_t i=0;i < tCloud->size();i++)
        {
            p1.setX(tCloud->points[i].x*msx);
            p1.setY(tCloud->points[i].y*msy*(-1.0));
            //坐标的转换
            qreal x = p1.rx()*zoom + rx;
            qreal y = p1.ry()*zoom + ry;
            painter1.drawPoint(QPointF(x,y));
        }
    }
    //防护区域内点云
    else if(true)
    {
        painter1.setPen(QPen(Qt::white, 2));//设置画笔的颜色/点云的颜色

        for(size_t j = 0;j < xCloud->size();j++)
        {
            QPointF p2;
            p2.setX(xCloud->points[j].x*msx);
            p2.setY(xCloud->points[j].y*msy*(-1.0));

            qreal x = p2.rx()*zoom + rx;
            qreal y = p2.ry()*zoom + ry;

            painter1.drawPoint(QPointF(x,y));
        }

    }


}


void PaintArea::drawArea(QPainter &painter, int index)
{
    Q_UNUSED(index);

    qreal rx = PAINT_SIZE/2;
    qreal ry = PAINT_SIZE/2;

    painter.resetTransform(); //重置scale变换
    painter.scale(zoom, zoom);
    for(int i = 0; i < 3; i++)
    {//绘制区域
        QList<PointT> tmp = area[i].Area2D_point;
        if(i==0)
            painter.setPen(QPen(Qt::red, 2/zoom));
        else if(i==1)
             painter.setPen(QPen(Qt::darkRed, 2/zoom));
        else if(i==2)
             painter.setPen(QPen(Qt::yellow, 2/zoom));
        for(int k = 0; k < tmp.size(); k++)
        {
            if(tmp.size() == 1)break;
            if(k == tmp.size()-1) break;
            QPointF p1, p2;
            p1 = QPointF(tmp[k].x+rx, tmp[k].y + ry);
            p2 = QPointF(tmp[(k+1)%tmp.size()].x+rx, tmp[(k+1)%tmp.size()].y + ry);
            painter.drawLine(QLineF(p1,p2));
        }

        for(int j = 0; j < tmp.size(); j++)
        {
            painter.setPen(QPen(Qt::yellow, 8/zoom));
            painter.drawPoint(tmp[j].x+rx, tmp[j].y + ry);
            painter.setPen(QPen(Qt::yellow, 0));
            painter.drawText(QPointF(tmp[j].x+rx, tmp[j].y + ry),QString::number(j+1));
        }
    }

}

void PaintArea::wheelEvent(QWheelEvent *event)/*鼠标滚轮事件*/
{
    int x,y,rx,ry;
    int cc =(int)(zoom/0.1*10);
    cc=(int)(cc/10+0.5)*10;
    if(!(300%cc))
        col =cc;
    if(col>=300) col =300;


     areaList_T_transform();

     x = event->x()/zoom;
    y = event->y()/zoom;

    if(event->delta()>0){

            if(zoom < 3)
                zoom += 0.1;
            else
                goto out;

    }else{
        if(zoom > 0.2){
            zoom -= 0.1;

        }else
            goto out;
    }
    if(zoom <=0.2) zoom =0.2;
    resize((PAINT_SIZE+1)*zoom,(PAINT_SIZE+1)*zoom);/*按照放大倍数放大绘图部件的大小*/
    rx = scroll->horizontalScrollBar()->maximum()-scroll->horizontalScrollBar()->minimum();/*进度条的最大值-最小值*/
    ry = scroll->verticalScrollBar()->maximum()- scroll->verticalScrollBar()->minimum();/*进度条的最大值-最小值*/
    scroll->verticalScrollBar()->setValue(ry* y/(PAINT_SIZE+0));/*保证放大后鼠标的相对位置不变*/
    scroll->horizontalScrollBar()->setValue(rx* x/PAINT_SIZE);//
    centerPoint.setX(PAINT_SIZE/2*zoom);
    centerPoint.setY(( PAINT_SIZE/2)*zoom);
out:
    event->accept();/*????我的理解应该属于事件忽略*/

}

void PaintArea::mousePressEvent(QMouseEvent *event)/*鼠标按键事件*/
{

    qreal rx,ry;
    rx = centerPoint.rx();
    ry = centerPoint.ry();
    if(event->button()== Qt::RightButton)// 右键删除坐标点
    {
        for(int i = 0; i < area[curPolygonPos-1].Area2D_point.size(); i++){// for(int i = 0; i < area[curPolygonPos-1].Area2D_point.size(); i++)
            PointT p = area[curPolygonPos-1].Area2D_point.at(i);

            qreal x = p.x*zoom + rx;
            qreal y = p.y*zoom + ry;
            if(qAbs(x - event->pos().rx())<5 && qAbs(y - event->pos().ry())< 5){
                area[curPolygonPos-1].Area2D_point.removeAt(i);
                area[curPolygonPos-1].Area2D_point_T.removeAt(i);
            //    updataPoint(curPolygonPos,area[curPolygonPos-1].Area2D_point);
                paint = true;
                emit sigShowData();
                update();
                return;
            }
        }
    }
    else if(event->button() == Qt::LeftButton  ) // 左键选择坐标
    {

        // std::cout<<"+++++++++++++++++++++++++++++++++"<<std::endl;
        // std::cout<<curPolygonPos<<std::endl;

        leftsel = true;
        for(int i = 0; i <  area[curPolygonPos-1].Area2D_point.size(); i++)
        {
            PointT p = area[curPolygonPos-1].Area2D_point.at(i);
            qreal x = p.x*zoom + rx;
            qreal y = p.y*zoom + ry;
            if(qAbs(x - event->pos().rx())<5 && qAbs(y - event->pos().ry())< 5)
            {
                dragPoint = true;
                selectPoint = i;
            }
        }

        if(!dragPoint )
        {
            moveStart = true;
            mvStartPt.setX(event->globalX());
            mvStartPt.setY(event->globalY());
            setCursor(Qt::ClosedHandCursor);/*设置鼠标样式为握拳*/
        }

    }

}

void PaintArea::mouseMoveEvent(QMouseEvent *event)/*鼠标移动事件*/
{

    qreal rx = centerPoint.rx();
    qreal ry = centerPoint.ry();

    mousemovepoint.setX(event->x()/zoom);
    mousemovepoint.setY(event->y()/zoom);


    //在点附近变十字 按键后拖
    setCursor(Qt::ArrowCursor);/*设置鼠标样式*/
    for(int i = 0; i < area[curPolygonPos-1].Area2D_point.size(); i++)
    {
        PointT p = area[curPolygonPos-1].Area2D_point.at(i);
        qreal x = p.x*zoom + rx;
        qreal y = p.y*zoom + ry;
        if(qAbs(x - event->pos().rx())<5 && qAbs(y - event->pos().ry())< 5)
        {
            setCursor(Qt::CrossCursor);/*设置鼠标样式为十字形*/

        }
    }
    // 当没选中点时拖动情况
    if(moveStart )
    {
        setCursor(Qt::ClosedHandCursor);/*设置鼠标样式为握拳*/
        int offsetx = event->globalX()- mvStartPt.x();
        int offsety = event->globalY()- mvStartPt.y();

        scroll->horizontalScrollBar()->setValue(scroll->horizontalScrollBar()->value() - offsetx);
        scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value() - offsety);

        mvStartPt.setX(event->globalX());
        mvStartPt.setY(event->globalY());
    }
    else  if(dragPoint ) //限制只有展示在按下ctrl与左键时才能拖动
    {
        qreal x  = (event->pos().rx() - rx)/zoom;
        qreal y = (event->pos().ry() - ry)/zoom;
        area[curPolygonPos-1].Area2D_point[selectPoint].x = x;
        area[curPolygonPos-1].Area2D_point[selectPoint].y = y;
        update();
        move = true;

    }

}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)/*鼠标释放事件*/
{

    int index;
    qreal rx = centerPoint.rx();
    qreal ry = centerPoint.ry();
    //(QApplication::keyboardModifiers()== Qt::ControlModifier)&&


    if((QApplication::keyboardModifiers()== Qt::ControlModifier)&&(event->button() == Qt::LeftButton) && move == false){
        QPointF tmp;
        tmp.setX(event->pos().rx());
        tmp.setY(event->pos().ry());
        qreal x = (tmp.rx() - rx)/zoom;
        qreal y = (tmp.ry() - ry)/zoom;
        qDebug()<<"x"<<x<<"y"<<y<<"   curPolygonPos=" <<curPolygonPos;

        index = area[curPolygonPos-1].Area2D_point.size();
        PointT pt,pt_T;
        pt.x =x;pt.y =y;pt.z=0;pt.r=255;pt.g =0;pt.b=0;
        area[curPolygonPos-1].Area2D_point.insert(index,pt);

        pt_T = areapoint2d_transform(pt);
        area[curPolygonPos-1].Area2D_point_T.insert(index,pt_T);
        emit sigShowData();


//        updataPoint(curPolygonPos,area[curPolygonPos-1].Area2D_point);

        update();


    }
    else if((event->button() == Qt::LeftButton) && move ==true)
    {
        QPointF tmp;
        tmp.setX(event->pos().rx());
        tmp.setY(event->pos().ry());
        qreal x = (tmp.rx() - rx)/zoom;
        qreal y = (tmp.ry() - ry)/zoom;

        PointT pt,pt_T;
        pt.x=x;
        pt.y=y;
        pt_T = areapoint2d_transform(pt);
        area[curPolygonPos-1].Area2D_point[selectPoint].x =x;
        area[curPolygonPos-1].Area2D_point[selectPoint].y = y;

        area[curPolygonPos-1].Area2D_point_T[selectPoint].x =pt_T.x;
        area[curPolygonPos-1].Area2D_point_T[selectPoint].y = pt_T.y;

        emit sigShowData();

        update();


    }
    move = false;

    moveStart = false;
    dragPoint = false;
    dragPropor =false;
    removePoint = false;
    addPoint = false;
    setCursor(Qt::ArrowCursor); //设置鼠标的样式
}

void PaintArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    qreal x,y;
    PointT p2;
    int tsize;
    if(event->button() == Qt::LeftButton)
    {
        qreal rx = centerPoint.rx();
        qreal ry = centerPoint.ry();
        for(int i = 0; i < area[curPolygonPos-1].Area2D_point.size(); i++)
        {
            PointT p = area[curPolygonPos-1].Area2D_point.at(i);
            qreal x = p.x*zoom + rx;
            qreal y = p.y*zoom + ry;
            if(qAbs(x - event->pos().rx())<5*zoom && qAbs(y - event->pos().ry())< 5*zoom)
            {

                tsize = area[curPolygonPos-1].Area2D_point.size();
                if(tsize<=1)
                {
                    return;
                }
                p2 = area[curPolygonPos-1].Area2D_point.at((i+1)%tsize);
                x = (p2.x + p.x)/2;
                y = (p2.y + p.y)/2;
                PointT pt,pt_T;
                pt.x =x;pt.y =y;pt.z=0;pt.r=255;pt.g =0;pt.b=0;
                area[curPolygonPos-1].Area2D_point.insert((i+1)%tsize,pt);
                pt_T =areapoint2d_transform(pt);
                area[curPolygonPos-1].Area2D_point_T.insert((i+1)%tsize,pt_T);

                paint = true;
                update();
                emit sigShowData();
              //  updataPoint(curPolygonPos,area[curPolygonPos-1].Area2D_point);
                return;
            }
        }
    }
}

void PaintArea::keyPressEvent(QKeyEvent *event) //键盘按下事件
{
    if(event->key() == Qt::Key_Delete)
    {
        area[curPolygonPos-1].Area2D_point.clear();
        area[curPolygonPos-1].Area2D_point_T.clear();
    //    updataPoint(curPolygonPos,area[curPolygonPos-1].Area2D_point);
        paint = true;
        emit sigShowData();
        update();
        return;
    }
}


QList<PointT> PaintArea::getIndexPoints(int index)
{
    return area[index-1].Area2D_point;
}

void PaintArea::setPaintPoint(QList<QPointF> &Srcp)
{

}

void PaintArea::updataPointFunc()
{
    emit sigShowData();
   // updataPoint(curPolygonPos,area[curPolygonPos-1].Area2D_point);
}

void PaintArea::setPaintSlot(QList<QPointF> tmp,int index)
{
#if 0
    LidarMap[index].inPolygon = tmp;
    if(index==curPos){
        paint = true;
        update();
    }
#endif
}

void PaintArea::setSplice(int index)
{
    if(index){
        spliceflag = true;
    }
    else
        spliceflag = false;
}

void PaintArea::updataPoint(int index, QList<PointT> ps)
{

    float msx = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    float msy = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    area[index-1].Area2D_point_T.clear();
    PointT point;
    for(int i = 0; i < ps.size(); i++){
        point.x = ps[i].x/msx;
        point.y = ps[i].y/msy*(-1.0);
        area[index-1].Area2D_point_T.push_back(point);
    }

    emit sigShowData();
}



void PaintArea::UpdateArea_index(int index)
{
    area_index = index;
    curPolygonPos = index+1;
}


PointT PaintArea::areapoint2d_transform(PointT pt)//绘图坐标系转换到真实坐标系
{
    float msx = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    float msy = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    PointT point;
    point.x =pt.x/msx;
    point.y =pt.y/msy*(-1.0);
    return point;

}

void PaintArea::areaList_T_transform()//绘图坐标系转换到真实坐标系
{
    float msx = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    float msy = PAINT_SIZE/2 /LidarInstance.lidar_Radius;
    for(int index =0;index<3;index++){

        area[index].Area2D_point.clear();
        for(int i = 0;i < area[index].Area2D_point_T.size();i++)
        {
            qreal x = area[index].Area2D_point_T[i].x*msx;
            qreal y = area[index].Area2D_point_T[i].y/(-1.0)*msy;
            PointT point;
            point.x =x;point.y=y;
            area[index].Area2D_point.push_back(point);
        }
    }
}

