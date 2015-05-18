#include "primitive.h"

Primitive::Primitive()
{
    m_Pen = QPen(Qt::black);
    m_Brush = QBrush(Qt::black);

    m_isConcave = false;
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

Primitive::~Primitive()
{

}

