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
#include <QTime>
#include <vector>

#include "../../Structure/brush.h"
#include "../../Structure/primitive.h"
#include "../../Overloads.h"

/**
 * @brief The BitmapImage class
 * Handles Anything pertaining to Bitmap Images
 */
class BitmapImage
{

class Object;

public:
    BitmapImage();
    BitmapImage(const BitmapImage &image);
    BitmapImage(Object* parent, QRect m_boundaries, QColor color);
    BitmapImage(Object* parent, QRect m_boundaries, QImage image);
    BitmapImage(QRect m_boundaries, QColor color);
    BitmapImage(QRect m_boundaries, QPixmap pixMap);

    static QImage DrawStrokeAsync(QVector<QPoint>& DrawPoints, Brush& brush, QImage& sourceImage);

    void setBoundaries(const QRect& bounds){this->m_boundaries = bounds;}

    void setPixmap(QPixmap pixmap){m_pixmap = pixmap;}
    void setVisible(bool val){m_visible = val;}

    void setClipboardPixmap(QPixmap, QRect);
    void setClipboardPixmap(QPixmap, QPoint);

    void paintImage(QPainter &painter);
    void paintImage(QPainterPath painterPath, Brush brush); //works
    void paintImage(QPoint point, Brush brush);//Keep
    void paintImage(QVector<QPointF> pointInfo, Brush brush);
    /**
     * @brief paintImage
     * @param pointInfo
     * @param brush
     * @param isInputFinish
     */
    void paintImage(QVector<QPointF>& pointInfo, Brush brush, bool isInputFinish);
    void paintImage(QVector<QPointF>* points, Brush brush);
    void paintImage(QVector<QPointF> pointInfo, Brush brush, qreal tabPress, int amt);//Keep
    void setColor(const QColor color){ m_Color = color; m_Image->fill(m_Color);}

    void cutImgOp(QRect rect, QColor col);
    void cutImgOp(QRect rect, BitmapImage& img);

    void commitChanges(QPoint drawPoint, QPixmap pixmap);

    void fillImage(QPoint point, Brush brush);
    void fillRecurs(QPoint pos, QImage& img, QRgb oldColor, QRgb newColor);
    bool isVisible(){return m_visible;}

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

    BitmapImage copy(){return BitmapImage(m_boundaries, m_pixmap);}
    BitmapImage copy(QRect bounds){
        BitmapImage ret(*this);
        QPixmap map = m_pixmap.copy(bounds);
        ret.setPixmap(map);
        ret.setBoundaries(QRect(m_boundaries.x(), m_boundaries.y(), map.width(), map.height()));
        return ret;
    }

    QImage *getImage(){return m_Image;}
    QPixmap getPixmap(){return m_pixmap.scaled(m_ScaleFactor * m_boundaries.size(), Qt::KeepAspectRatio, Qt::FastTransformation);}
    QPixmap getCompositeImage();

    QPoint getTopLeft(){return m_boundaries.topLeft();}
    QPoint getTopRight(){ return m_boundaries.topRight(); }
    QPoint getBottomLeft(){ return m_boundaries.bottomLeft(); }
    QPoint getBottomRight(){ return m_boundaries.bottomRight(); }

    QColor getColor(){ return m_Color; }
    QPoint getOffset(){return m_offset;}
protected:
    Object *myParent;

private:
    void    drawStroke(const QPointF& startPoint, const QPointF& endPoint, const qreal &spacing, QPixmap& stencil);
    QPoint  m_offset;
    bool    m_visible;
    qreal   m_inc;
    QPixmap m_pixmap;
    QImage *m_Image;
    QRect   m_boundaries;
    QRect   m_modifiedRect;
    QColor  m_Color;
    double  m_ScaleFactor;
    double  m_ScaleFactorInv;

    //handle history
    int m_MaxSizeOfHistory;
};

#endif // BITMAPIMAGE_H
