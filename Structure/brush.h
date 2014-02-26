#ifndef BRUSH_H
#define BRUSH_H

#include <QBrush>
#include <QPen>
#include <QColor>


class Brush
{
public:
    enum BrushType { Pen, Pencil, Eraser, PaintBucket, Text };

    Brush();

    void setBrushType(BrushType type){ brushType = type; }
    void setBrush(QBrush brush){ myBrush = brush; }
    void setPen(QPen pen){ myPen = pen; }
    void setColor(QColor color){ myColor = color; myBrush.setColor(myColor); myPen.setColor(myColor); }
    void setWidth(int val){ myPen.setWidth(val); }
    void setWidth(qreal val){ myPen.setWidthF(val); }

    void setPressure(bool val){ pressure = val; }
    void setFeather(bool val){ feather = val; }

    //color Centric
    void setRed(int val){myColor.setRed(val);}
    void setGreen(int val){myColor.setGreen(val);}
    void setBlue(int val){myColor.setBlue(val);}

    QPen getPen(){return myPen;}
    QBrush getBrush(){ return myBrush; }
    QColor getColor() { return myColor; }

    int getSize(){return myPen.width();;}

private:
    BrushType brushType;

    QPen myPen;
    QBrush myBrush;
    QColor myColor;

    bool pressure;
    bool feather;
    int featherAmount;
    int pressureAmount;
};

#endif // BRUSH_H
