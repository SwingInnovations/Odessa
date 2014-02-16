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
    void setColor(QColor color){ myColor = color; myBrush.setColor(myColor); }

    void setPressure(bool val){ pressure = val; }
    void setFeather(bool val){ feather = val; }

    QPen getPen(){return myPen;}
    QBrush getBrush(){ return myBrush; }
    QColor getColor() { return myColor; }

private:
    BrushType brushType;

    QPen myPen;
    QBrush myBrush;
    QColor myColor;

    bool pressure;
    bool feather;
    int featherAmount;
};

#endif // BRUSH_H
