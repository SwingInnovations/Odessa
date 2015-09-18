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

    void setBrush(QBrush brush){ m_Brush = brush; }
    void setPen(QPen pen){ myPen = pen; }
    void SetStencil(QPixmap pixmap){ m_Stencil = pixmap; }
    void setColor(QColor color){ m_Color = color; m_Brush.setColor(m_Color); myPen.setColor(m_Color); }
    void setWidth(int val){
        //mSize = val + (mTSize * m_PressureVal);
        m_size = val;
        myPen.setWidth(m_size); }
    void SetName(QString name){
        m_Name = name;
    }

    void generatePixmap();

    void setWidth(qreal val){
        m_size = val + (m_TSize * m_PressureVal );
        myPen.setWidthF(m_size);
    }

    void setSpacing(int val){   m_Spacing = val; }

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
        s_Width = val;
    }

    void setSHeight(int val){
        s_Height = val;
    }

    void SetRotate(int val){m_rotate = val;}

    void setToolType(int);

    int getHardness()const{return m_hardness;}
    int getRotate()const{return m_rotate;}
    void setOpacity(int val){m_Opacity = val;}
    void setTransferSize(int val){m_TSize = val;}
    void setTransferOpacity(int val){m_TOpacity = val;}

    qreal getPressureVal(){return m_PressureVal;}

    void setPressure(bool val){ m_Pressure = val; }
    void setHardness(int val){ m_hardness = val; }

    void setBrushShape(BrushShape shape){ m_brushShape = shape; }
    bool isType(int);

    //color Centric
    void setRed(int val){m_Color.setRed(val);}
    void setGreen(int val){m_Color.setGreen(val);}
    void setBlue(int val){m_Color.setBlue(val);}

    QPen getPen()const{return myPen;}
    QBrush getBrush()const{ return m_Brush; }
    QColor getColor()const{ return m_Color; }

    QString getName()const{return m_Name;}

    int getSWidth()const{return s_Width;}
    int getSHeight()const{return s_Height;}
    int getSpacing()const{return m_Spacing;}
    int getSize()const{return m_size;}
    int getTransferSize()const{return m_size + m_TSize;}
    int getTransferOpacity()const{return m_Opacity + m_TOpacity;}
    int getOpacity()const{return m_Opacity;}
    QPixmap getStencil()const{return m_Stencil;}

    /*-Variables-*/

    BrushShape m_brushShape;
    QString m_Name;

    QPen myPen;
    QBrush m_Brush;
    QColor m_Color;

    bool m_Pressure;
    int m_hardness;
    unsigned int m_size;
    int m_Opacity;//responsible for Opacity
    int m_Spacing;

    int s_Width, s_Height;

    unsigned int m_TSize;
    unsigned int m_TOpacity;

    int m_rotate;

    qreal m_PressureVal;
    qreal m_xTilt;
    qreal m_yTilt;

    QPixmap m_Stencil;

    int m_toolType;
};

#endif // BRUSH_H
