#ifndef BRUSH_H
#define BRUSH_H

#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QRadialGradient>
#include <QPoint>
#include <QFile>
#include <QDataStream>

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
        //mSize = val + (mTSize * m_PressureVal);
        mSize = val;
        myPen.setWidth(mSize); }
    void SetName(QString name){
        mName = name;
    }

    void generatePixmap();

    void setWidth(qreal val){
        mSize = val + (mTSize * m_PressureVal );
        myPen.setWidthF(mSize);
    }

    void setSpacing(int val){
        mSpacing = val;
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

    void setSWidth(int val){
        sWidth = val;
    }

    void setSHeight(int val){
        sHeight = val;
    }

    void SetRotate(int val){mRotate = val;}

    int getHardness()const{return mHardness;}
    int getRotate()const{return mRotate;}
    void SetOpacity(int val){mOpacity = val;}
    void setTransferSize(int val){mTSize = val;}
    void setTransferOpacity(int val){mTOpacity = val;}

    qreal getPressureVal(){return m_PressureVal;}

    void setPressure(bool val){ mPressure = val; }
    void setHardness(int val){ mHardness = val; }

    void setBrushShape(BrushShape shape){ brushShape = shape; }

    //color Centric
    void setRed(int val){myColor.setRed(val);}
    void setGreen(int val){myColor.setGreen(val);}
    void setBlue(int val){myColor.setBlue(val);}

    QPen getPen()const{return myPen;}
    QBrush getBrush()const{ return myBrush; }
    QColor getColor()const{ return myColor; }

    QString getName()const{return mName;}

    int getSWidth()const{return sWidth;}
    int getSHeight()const{return sHeight;}
    int getSpacing()const{return mSpacing;}
    int getSize()const{return mSize;}
    int getTransferSize()const{return mTSize;}
    int getTransferOpacity()const{return mTOpacity;}
    int getOpacity()const{return mOpacity;}
    QPixmap getStencil()const{return mStencil;}

    /*-Variables-*/

    BrushShape brushShape;
    QString mName;

    QPen myPen;
    QBrush myBrush;
    QColor myColor;

    bool mPressure;
    int mHardness;
    unsigned int mSize;
    int mOpacity;//responsible for Opacity
    int mSpacing;

    int sWidth, sHeight;

    unsigned int mTSize;
    unsigned int mTOpacity;

    int mRotate;

    qreal m_PressureVal;
    qreal m_xTilt;
    qreal m_yTilt;

    QPixmap mStencil;
};

#endif // BRUSH_H
