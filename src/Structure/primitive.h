#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include <QVector>
#include <QPoint>

#include "brush.h"

class SWPoint{
public:
    SWPoint(){
        _id = 0;
        _x = 0;
        _y = 0;
    }
    SWPoint(int i, int x, int y){
        _id = i;
        _x = x;
        _y = y;
    }

    QPoint toQPoint()const{ return QPoint(_x, _y); }
    int getID()const {return _id;}
    int getX()const{ return _x; }
    int getY()const{ return _y; }
    void setID(int id){ _id = id; }
    void setX(int x){ _x = x; }
    void setY(int y){ _y = y; }
private:
    int _id;
    int _x;
    int _y;
};

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
    bool isConcave(){ return m_isConcave; }
    int getWidth()const{ return m_Width; }
    int getHeight()const{ return m_Height; }
    QPen getPen()const{ return m_Pen; }
    QBrush getBrush()const{ return m_Brush; }
    QPainterPath getShapePath()const{ return m_Path; }
private:

    int m_shapeType;

    void generateShapePoints();

    QVector<SWPoint> points;
    QPoint m_CenterP;
    int m_pointCount;
    int m_Width;
    int m_Height;
    bool m_isConcave;
    QPainterPath m_Path;
    QColor m_fillColor;
    QPen m_Pen;
    QBrush m_Brush;
};

#endif // PRIMITIVE_H
