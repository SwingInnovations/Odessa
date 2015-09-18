#include "brush.h"

Brush::Brush() : m_hardness(0),
    m_size(0),
    m_Opacity(0),
    m_Spacing(1),
    s_Width(0),
    s_Height(0),
    m_rotate(0),
    m_TSize(0),
    m_TOpacity(0)
{
    m_Brush = QBrush();
    myPen = QPen();
    myPen.setCapStyle(Qt::RoundCap);
    m_Name = "";
    m_toolType = 0;
    m_Stencil = QPixmap();
    m_Color = QColor(Qt::black);
    m_brushShape = CIRCLE_SHAPE;
}

void Brush::generatePixmap(){
    QPoint midPoint(s_Width/2, s_Height/2);
    m_Stencil = QPixmap(s_Width, s_Height);
    m_Stencil.fill(Qt::transparent);
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
