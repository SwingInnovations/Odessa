#ifndef BITMAPIMAGE_H
#define BITMAPIMAGE_H

#include <QtGui>
#include <QImage>
#include <QPixmap>
#include <QPainterPath>
#include <QDebug>
#include <QPoint>
#include <QPointF>
#include <QVector>

#include "../src/Structure/brush.h"

class BitmapImage
{

class Object;

public:
    BitmapImage();
    BitmapImage(const BitmapImage &image);
    BitmapImage(Object* parent, QRect boundaries, QColor color);
    BitmapImage(Object* parent, QRect boundaries, QImage image);
    BitmapImage(QRect boundaries, QColor color);
    BitmapImage(QRect boundaries, QPixmap pixMap);

    void setBoundaries(const QRect& bounds){this->boundaries = bounds;}

    void setPixmap(QPixmap pixmap){m_pixmap = pixmap;}
    void setVisible(bool val){visible = val;}

    void paintImage(QPainter &painter);
    void paintImage(QMouseEvent *event, Brush brush, QPoint points[]);//Deprecate
    void paintImage(QTabletEvent *event, Brush brush, QPoint points[]);//Deprecate
    void paintImage(QPainterPath painterPath, Brush brush); //works
    void paintImage(QVector<QPointF> pointInfo, Brush brush);//Keep
    void paintImage(QVector<QPointF> pointInfo, Brush brush, qreal tabPress, int amt);//Keep
    void setColor(const QColor color){ m_Color = color; m_Image->fill(m_Color);}

    void fillImage(QPoint point, Brush brush);
    bool isVisible(){return visible;}

    BitmapImage copy(){return BitmapImage(boundaries, m_pixmap);}
    BitmapImage copy(QRect bounds){
        BitmapImage ret(*this);
        QPixmap map = m_pixmap.copy(bounds);
        ret.setPixmap(map);
        ret.setBoundaries(QRect(boundaries.x(), boundaries.y(), map.width(), map.height()));
        return ret;
    }

    QImage *getImage(){return m_Image;}
    QPixmap getPixmap(){
                       QPixmap ret = m_pixmap.scaled((int)(m_pixmap.width() * m_WScaleFactor), (int)(m_pixmap.height() * m_HScaleFactor));
                       return ret;}
    QPixmap getCompositeImage();

    QPoint getTopLeft(){return boundaries.topLeft();}
    QPoint getTopRight(){ return boundaries.topRight(); }
    QPoint getBottomLeft(){ return boundaries.bottomLeft(); }
    QPoint getBottomRight(){ return boundaries.bottomRight(); }

    QColor getColor(){ return m_Color; }

protected:
    Object *myParent;

private:
    bool visible;
    QPixmap m_pixmap;
    QImage *m_Image;
    QRect boundaries;
    QColor m_Color;
    double m_WScaleFactor;
    double m_HScaleFactor;

    //handle history
    int m_MaxSizeOfHistory;
};

#endif // BITMAPIMAGE_H
