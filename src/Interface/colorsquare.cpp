#include "colorsquare.h"

ColorSquare::ColorSquare(QWidget *parent) : QLabel(parent)
{
    m_toggleAlt = false;
}

void ColorSquare::paintEvent(QPaintEvent *p)
{
    Q_UNUSED(p);

}

void ColorSquare::mousePressEvent(QMouseEvent *ev)
{

}

void ColorSquare::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    if(m_MouseDown)
    {
        m_MouseDown = false;
    }
}

void ColorSquare::mouseMoveEvent(QMouseEvent *ev)
{

}

QColor ColorSquare::getColorFromPoint(QPoint point)
{
    QPixmap pic = QWidget::grab();
    QImage img = pic.toImage();
    return QColor(img.pixel(point));
}
