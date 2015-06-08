#include "primitive.h"

Primitive::Primitive()
{
    m_Pen = QPen(Qt::black);
    m_Brush = QBrush(Qt::black);

    m_isConcave = false;
}

Primitive::Primitive(Brush& brush){
    mHardness = brush.getHardness();
}

Primitive::Primitive(int width, int height){
    m_CenterP = QPoint(width/2, height/2);
    m_Pen = QPen(Qt::black);
    m_Brush = QBrush(Qt::black);

    m_isConcave = false;
}

void Primitive::setPointCount(int count){
    m_pointCount = count;
}

void Primitive::setConcanve(bool v){
    m_isConcave = v;
}

void Primitive::setPenWidth(int width){
    m_Pen.setWidth(width);
}

void Primitive::setPen(QPen p){
    m_Pen = p;
}

void Primitive::setBrush(QBrush b){
    m_Brush = b;
}

void Primitive::setColor(QColor c){
    m_fillColor = c;
}

void Primitive::generateShapePoints(){
    if(m_isConcave){
        if(!points.empty()){
            points.clear();
        }
        int cX = m_Width/2;
        int cY = m_Height/2;
        for(int i = 0; i < m_pointCount; i++){
            int pX = cX + cX*cos(2.0 * 3.1415 * i/m_pointCount);
            int pY = cY + cY*sin(2.0 * 3.1415 * i/m_pointCount);
            points.push_back(SWPoint(i, pX, pY));
        }
    }else{

    }
}

Primitive::~Primitive()
{

}

