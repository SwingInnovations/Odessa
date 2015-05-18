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
#include <QQueue>
#include <vector>

#include "../src/Structure/brush.h"
#include "../../Overloads.h"

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

    void setClipboardPixmap(QPixmap, QRect);
    void setClipboardPixmap(QPixmap, QPoint);

    void paintImage(QPainter &painter);
    void paintImage(QPainterPath painterPath, Brush brush); //works
    void paintImage(QVector<QPointF> pointInfo, Brush brush);//Keep
    void paintImage(QVector<QPointF> pointInfo, Brush brush, qreal tabPress, int amt);//Keep
    void setColor(const QColor color){ m_Color = color; m_Image->fill(m_Color);}

    void cutImgOp(QRect rect, QColor col);
    void cutImgOp(QRect rect, BitmapImage& img);

    void commitChanges(QPoint drawPoint, QPixmap pixmap);

    void fillImage(QPoint point, Brush brush);
    void fillRecurs(QPoint pos, QImage& img, QRgb oldColor, QRgb newColor);
    bool isVisible(){return visible;}

    void scale(double s);

    void combineLayer(BitmapImage img){
        QPixmap temp(m_pixmap.size());
        QPainter p(&temp);
        p.setCompositionMode(QPainter::CompositionMode_SourceOver);
        p.drawPixmap(getOffset(), m_pixmap);

        p.setCompositionMode(QPainter::CompositionMode_SourceOver);
        p.drawPixmap(img.getOffset(), img.getPixmap());
        p.end();
    }

    BitmapImage copy(){return BitmapImage(boundaries, m_pixmap);}
    BitmapImage copy(QRect bounds){
        BitmapImage ret(*this);
        QPixmap map = m_pixmap.copy(bounds);
        ret.setPixmap(map);
        ret.setBoundaries(QRect(boundaries.x(), boundaries.y(), map.width(), map.height()));
        return ret;
    }

    QImage *getImage(){return m_Image;}
    QPixmap getPixmap(){return m_pixmap.scaled(m_ScaleFactor * boundaries.size(), Qt::KeepAspectRatio, Qt::FastTransformation);}
    QPixmap getCompositeImage();

    QPoint getTopLeft(){return boundaries.topLeft();}
    QPoint getTopRight(){ return boundaries.topRight(); }
    QPoint getBottomLeft(){ return boundaries.bottomLeft(); }
    QPoint getBottomRight(){ return boundaries.bottomRight(); }

    QColor getColor(){ return m_Color; }
    QPoint getOffset(){return offset;}
protected:
    Object *myParent;

private:
    QPoint offset;
    bool visible;
    QPixmap m_pixmap;
    QImage *m_Image;
    QRect boundaries;
    QRect modifiedRect;
    QColor m_Color;
    double m_ScaleFactor;
    double m_ScaleFactorInv;

    //handle history
    int m_MaxSizeOfHistory;
};

#endif // BITMAPIMAGE_H
