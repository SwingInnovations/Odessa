#ifndef BRUSH_H
#define BRUSH_H

#include <QBrush>
#include <QPen>
#include <QColor>
#include <QDebug>
#include <QPixmap>
#include <QFile>

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

    void SetSpacing(int val){
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

    void SetStencilPath(QString fileName){
        mStencilPath = fileName;
    }

    void LoadBrush(QString filePath){
        stencilInput = new QFile(filePath);
        stencilInput->open(QIODevice::ReadOnly);
        QDataStream in;
        in.setDevice(stencilInput);
        int size = stencilInput->size();

        brushProto = new char[size];
        in.readRawData(brushProto, size);
        brushData = new uchar[size];

        for(unsigned int i = 0; i < size; i++){
            brushData[i] = (uchar)brushProto[i];
        }

        QImage tempStencil(brushData, 160, 160, QImage::Format_Indexed8);
        QVector<QRgb> vecCol(256);
        for(unsigned int i = 0; i < 256; i++){
            vecCol[i] = qRgb(i, i, i);
        }
        tempStencil.setColorTable(vecCol);

        mStencil = QPixmap::fromImage(tempStencil);

        delete[] brushProto;
        delete[] brushData;
        delete stencilInput;
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

    int GetSpacing(){return mSpacing;}
    int GetSize(){return mSize;}
    int GetTransferSize(){return mTSize;}
    int GetTransferOpacity(){return mTOpacity;}
    int getOpacity(){return mOpacity;}

    QPixmap GetStencil(){return mStencil;}
    QString GetStencilPath(){return mStencilPath;}

private:

    QFile* stencilInput;
    char* brushProto;
    uchar* brushData;

    BrushShape brushShape;

    QPen myPen;
    QBrush myBrush;
    QColor myColor;

    bool mPressure;
    bool mHardness;
    unsigned int mSize;
    int mOpacity;
    int mSpacing;

    unsigned int mTSize;
    unsigned int mTOpacity;

    qreal m_PressureVal;
    qreal m_xTilt;
    qreal m_yTilt;

    QPixmap mStencil;
    QString mStencilPath;
};

#endif // BRUSH_H
