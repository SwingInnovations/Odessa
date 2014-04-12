#ifndef BRUSH_H
#define BRUSH_H

#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>


class Brush
{
public:

    enum BrushShape{LINE_SHAPE, CIRCLE_SHAPE, SQUARE_SHAPE};

    Brush();

    void setBrush(QBrush brush){ myBrush = brush; }
    void setPen(QPen pen){ myPen = pen; }
    void setColor(QColor color){ myColor = color; myBrush.setColor(myColor); myPen.setColor(myColor); }
    void setWidth(int val){
        width = val + (widthAmount * m_PressureVal);
        myPen.setWidth(width); }
    void setWidth(qreal val){
        width = val + (widthAmount * m_PressureVal );
        myPen.setWidthF(width);
    }

    void setPressureVal(qreal val)
    {
        m_PressureVal = val;
    }

    void setxTilt(qreal val)
    {
        m_xTilt = val;
    }

    void setyTilt(qreal val)
    {
        m_yTilt = val;
    }

    void setOpacity(int val){opacity = val;}

    qreal gePressureVal(){return m_PressureVal;}

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

    int getSize(){return width;}
    int getTransferWidth(){return widthAmount;}
    int getOpacity(){return opacity;}

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

    int opacity;

    qreal m_PressureVal;
    qreal m_xTilt;
    qreal m_yTilt;
};

#endif // BRUSH_H
