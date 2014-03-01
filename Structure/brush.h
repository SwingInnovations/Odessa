#ifndef BRUSH_H
#define BRUSH_H

#include <QBrush>
#include <QPen>
#include <QColor>


class Brush
{
public:

    enum BrushShape{LINE_SHAPE, CIRCLE_SHAPE, SQUARE_SHAPE};

    Brush();

    void setBrush(QBrush brush){ myBrush = brush; }
    void setPen(QPen pen){ myPen = pen; }
    void setColor(QColor color){ myColor = color; myBrush.setColor(myColor); myPen.setColor(myColor); }
    void setWidth(int val){
        width = val;
        myPen.setWidth(width); }
    void setWidth(qreal val){
        width = val;
        myPen.setWidthF(width); }

    void setPressure(bool val){ pressure = val; }
    void setFeather(bool val){ feather = val; }

    void setBrushShape(BrushShape shape){ brushShape = shape; }

    //color Centric
    void setRed(int val){myColor.setRed(val);}
    void setGreen(int val){myColor.setGreen(val);}
    void setBlue(int val){myColor.setBlue(val);}

    void setFeatherAmount(int val){ featherAmount = val; }
    void setTransferWidthAmount(int val){ widthAmount = val; }

    QPen getPen(){return myPen;}
    QBrush getBrush(){ return myBrush; }
    QColor getColor() { return myColor; }

    int getSize(){return myPen.width();}
    int getTransferWidth(){return widthAmount;}

private:

    BrushShape brushShape;

    QPen myPen;
    QBrush myBrush;
    QColor myColor;

    bool pressure;
    bool feather;
    int featherAmount;
    int widthAmount;
    int width;
};

#endif // BRUSH_H
