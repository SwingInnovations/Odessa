#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QVector>
#include <QPoint>

#include "brush.h"

class Primitive : public Brush
{
public:
    Primitive();
    Primitive(int width, int height);
    ~Primitive();

    void setPointCount(int);
    void setConcanve(bool);
    void setPen(QPen);
    void setPenWidth(int);
    void setBrush(QBrush);
    void setColor(QColor);

    int getPointCount()const{ return m_pointCount; }
    void isConcave(){ return m_isConcave; }
    QPen getPen()const{ return m_Pen; }
    QBrush getBrush()const{ return m_Brush; }
private:
    QPoint m_CenterP;
    int m_pointCount;
    bool m_isConcave;
    QPainterPath m_Path;
    QColor m_fillColor;
    QPen m_Pen;
    QBrush m_Brush;
};

#endif // PRIMITIVE_H
