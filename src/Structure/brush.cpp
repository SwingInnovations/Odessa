#include "brush.h"

Brush::Brush() : mHardness(0),
    mSize(0),
    mOpacity(0),
    mSpacing(1),
    sWidth(0),
    sHeight(0),
    mRotate(0),
    mTSize(0),
    mTOpacity(0)
{
    myBrush = QBrush();
    myPen = QPen();
    myPen.setCapStyle(Qt::RoundCap);
    m_Name = "";
    m_toolType = 0;
    mStencil = QPixmap();
    myColor = QColor(Qt::black);
    brushShape = CIRCLE_SHAPE;
}

void Brush::generatePixmap(){
    QPoint midPoint(sWidth/2, sHeight/2);
    mStencil = QPixmap(sWidth, sHeight);
    mStencil.fill(Qt::transparent);
    qreal hardness = 78 * getHardness()/100;
    QRadialGradient radGrad(midPoint, midPoint.x());
    radGrad.setColorAt(midPoint.x(), Qt::black);
    radGrad.setFocalRadius(hardness);
    //TODO finish this implementation
}

void Brush::setToolType(int t){
    m_toolType = t;
}

bool Brush::isType(int t){
    return (m_toolType == t);
}
