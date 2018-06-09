#include "canvas.h"

Canvas::Canvas(QWidget *parent)
{
    m_mouseDown = false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == 0 && !m_mouseDown){
        m_mouseDown = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{

}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == 0 && m_mouseDown){
        m_mouseDown = false;
    }
}

void Canvas::tabletEvent(QTabletEvent *event)
{

}
