#ifndef BRUSH_H
#define BRUSH_H

#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>
#include <QPixmap>

class Brush
{
public:

    enum BrushShape{LINE_SHAPE, CIRCLE_SHAPE, SQUARE_SHAPE, CUSTOM_SHAPE};

    Brush();

    void setBrush(QBrush brush){ myBrush = brush; }
    void setPen(QPen pen){ myPen = pen; }
    void SetStencil(QPixmap pixmap){ mStencil = pixmap; }
    void setColor(QColor color){ myColor = color; myBrush.setColor(myColor); myPen.setColor(myColor); }
    void setWidth(int val){
        mSize = val + (mTSize * m_PressureVal);
        myPen.setWidth(mSize); }
    void setWidth(qreal val){
        mSize = val + (mTSize * m_PressureVal );
        myPen.setWidthF(mSize);
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

    void SetOpacity(int val){mOpacity = val;}
    void SetTransferSize(int val){mTSize = val;}
    void SetTransferOpacity(int val){mTOpacity = val;}

    qreal GetPressureVal(){return m_PressureVal;}

    void SetPressure(bool val){ mPressure = val; }
    void SetHardness(bool val){ mHardness = val; }

    void SetBrushShape(BrushShape shape){ brushShape = shape; }

    //color Centric
    void setRed(int val){myColor.setRed(val);}
    void setGreen(int val){myColor.setGreen(val);}
    void setBlue(int val){myColor.setBlue(val);}

    QPen getPen(){return myPen;}
    QBrush getBrush(){ return myBrush; }
    QColor getColor() { return myColor; }

    int GetSize(){return mSize;}
    int GetTransferSize(){return mTSize;}
    int GetTransferOpacity(){return mTOpacity;}
    int getOpacity(){return mOpacity;}

private:

    BrushShape brushShape;

    QPen myPen;
    QBrush myBrush;
    QColor myColor;

    bool mPressure;
    bool mHardness;
    unsigned int mSize;
    int mOpacity;

    unsigned int mTSize;
    unsigned int mTOpacity;

    qreal m_PressureVal;
    qreal m_xTilt;
    qreal m_yTilt;

    QPixmap mStencil;
};

#endif // BRUSH_H
