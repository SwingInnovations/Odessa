#include "brush.h"

Brush::Brush()
{
    myBrush = QBrush();
    myPen = QPen();
    myPen.setCapStyle(Qt::RoundCap);
}

void Brush::GeneratePixmap(){
    QPoint midPoint(sWidth/2, sHeight/2);
    mStencil = QPixmap(sWidth, sHeight);
    mStencil.fill(Qt::transparent);
    qreal hardness = 78 * getHardness()/100;
    QRadialGradient radGrad(midPoint, midPoint.x());
    radGrad.setColorAt(midPoint.x(), Qt::black);
    radGrad.setFocalRadius(hardness);
    //TODO finish this implementation
}
