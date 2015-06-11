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
    m_Width = width;
    m_Height = height;
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

void Primitive::setWidth(int width){
    m_Width = width;
}

void Primitive::setHeight(int height){
    m_Height = height;
}

void Primitive::movePoint(QPoint pos){
    for(int i = 0; i < cPoints.size(); i++){
        if(cPoints.at(i).getPolygon().contains(pos)){
//            cPoints.at(i).setLineColor(QColor(Qt::red));
//            cPoints.at(i).setPos(pos);
        }
    }
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
            cPoints.push_back(ControlPoint(5, QPoint(pX, pY)));
        }
    }else{

    }
}

Primitive::~Primitive()
{

}

ControlPoint::ControlPoint(){
    radius = 5;
    m_point = QPoint(0, 0);
}

ControlPoint::ControlPoint(int r, QPoint p){
    radius = r;
    m_point = p;
    int cx = p.x();
    int cy = p.y();
    for(int i = 0; i < POINT_COUNT; i++){
        int px = cx + radius*cos(2.0 * 3.1415 * i/POINT_COUNT);
        int py = cy + radius*sin(2.0 * 3.1415 * i/POINT_COUNT);
        m_circle.push_back(QPoint(px, py));
    }
    m_fillColor = QColor(Qt::white);
    m_lineColor = QColor(Qt::black);
}

ControlPoint::ControlPoint(int r, int x, int y){
    radius = r;
    m_point = QPoint(x, y);
    int cx = x;
    int cy = y;
    for(int i = 0; i < POINT_COUNT; i++){
        int px = cx + radius*cos(2.0 * 3.1415 * i/POINT_COUNT);
        int py = cy + radius*sin(2.0 * 3.1415 * i/POINT_COUNT);
        m_circle.push_back(QPoint(px, py));
    }
    m_fillColor = QColor(Qt::white);
    m_lineColor = QColor(Qt::black);
}

void ControlPoint::setPos(QPoint& pos){
    m_point = pos;
    m_circle.clear();
    for(int i = 0; i < POINT_COUNT; i++){
        int px = pos.x() + radius*cos(2.0 * 3.1415 * i/POINT_COUNT);
        int py = pos.y() + radius*sin(2.0 * 3.1415 * i/POINT_COUNT);
        m_circle.push_back(QPoint(px, py));
    }
}

void ControlPoint::setLineColor(QColor col){
    m_lineColor = col;
}

void ControlPoint::setFillColor(QColor col){
    m_fillColor = col;
}
