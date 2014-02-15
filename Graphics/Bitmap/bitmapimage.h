#ifndef BITMAPIMAGE_H
#define BITMAPIMAGE_H

#include <QtGui>
#include <QImage>
#include <QDebug>

class BitmapImage
{

class Object;

public:
    BitmapImage();
    BitmapImage(const BitmapImage &image);
    BitmapImage(Object* parent, QRect boundaries, QColor color);
    BitmapImage(Object* parent, QRect boundaries, QImage image);
    BitmapImage(QRect boundaries, QColor color);

    void setBoundaries(const QRect& bounds){this->boundaries = bounds;}

    void paintImage(QPainter &painter);
    void setColor(const QColor color){ m_Color = color; m_Image->fill(m_Color);}

    QPoint getTopLeft(){return boundaries.topLeft();}
    QPoint getTopRight(){ return boundaries.topRight(); }
    QPoint getBottomLeft(){ return boundaries.bottomLeft(); }
    QPoint getBottomRight(){ return boundaries.bottomRight(); }

    QColor getColor(){ return m_Color; }

protected:
    Object *myParent;

private:
    QImage *m_Image;
    QRect boundaries;
    QColor m_Color;
};

#endif // BITMAPIMAGE_H
