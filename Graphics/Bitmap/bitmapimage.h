#ifndef BITMAPIMAGE_H
#define BITMAPIMAGE_H

#include <QtGui>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPoint>
#include <QPointF>
#include <QVector>
#include "Structure/brush.h"

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

    void addBackupElement();
    void removeLastBackupElement();

    void setPixmap(QPixmap pixmap){m_pixmap = pixmap;}

    void paintImage(QPainter &painter);
    void paintImage(QPainter &painter, QPoint knownPoint, Brush brush, QPoint points[]);
    void paintImage(QPainter &painter, QTabletEvent *event, Brush brush, QPoint points[]);
    void paintImage(QMouseEvent *event, Brush brush, QPoint points[]);
    void paintImage(QTabletEvent *event, Brush brush, QPoint points[]);
    void paintImage(QMouseEvent *event, Brush brush, QPoint &lastPoint);
    void paintImage(QTabletEvent *event, Brush brush, QPoint &lastPoint);
    void setColor(const QColor color){ m_Color = color; m_Image->fill(m_Color);}

    BitmapImage copy(){return BitmapImage(boundaries, m_pixmap);}

    QImage *getImage(){return m_Image;}
    QPixmap getPixmap(){return m_pixmap;}

    QPoint getTopLeft(){return boundaries.topLeft();}
    QPoint getTopRight(){ return boundaries.topRight(); }
    QPoint getBottomLeft(){ return boundaries.bottomLeft(); }
    QPoint getBottomRight(){ return boundaries.bottomRight(); }

    QColor getColor(){ return m_Color; }

protected:
    Object *myParent;

private:
    QPixmap m_pixmap;
    QImage *m_Image;
    QRect boundaries;
    QColor m_Color;

    //handle history
    int m_MaxSizeOfHistory;
    QVector<QPixmap> m_historyStack;
    QPoint startPoint, endPoint;
};

#endif // BITMAPIMAGE_H
