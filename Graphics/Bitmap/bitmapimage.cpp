#include "bitmapimage.h"

BitmapImage::BitmapImage()
{
    m_Image = NULL;
    qDebug() << "Image drawn!" << endl;
}

BitmapImage::BitmapImage(const BitmapImage &image)
{
    m_pixmap = image.m_pixmap;
    boundaries = image.boundaries;
    m_Color = image.m_Color;
}

BitmapImage::BitmapImage(Object *parent, QRect boundaries, QColor color)
{
    myParent = parent;
    this->boundaries = boundaries;
    m_Image = new QImage(boundaries.size(), QImage::Format_ARGB32_Premultiplied);
    m_Image->fill(color.rgba());
}

BitmapImage::BitmapImage(Object *parent, QRect boundaries, QImage image)
{
    myParent = parent;
    this->boundaries = boundaries;
    m_Image = new QImage(image);
    if(m_Image->width() != boundaries.width() && m_Image->height() != boundaries.height()) qDebug() << "Error 0001: Failed to load Image" << endl;
}

BitmapImage::BitmapImage(QRect boundaries, QColor color)
{
    this->boundaries = boundaries;
    QPixmap temp(boundaries.width(), boundaries.height());
    temp.fill(color);
    QPainter painter(&temp);
    if(!temp.isNull())
    {
        painter.drawPixmap(0, 0, temp);
    }
    painter.end();
    m_pixmap = temp;
}

void BitmapImage::paintImage(QPainter &painter)
{
    painter.drawPixmap(0, 0, m_pixmap);
}

void BitmapImage::paintImage(QPainter &painter, QPoint knownPoint, Brush brush, QPoint points[])
{
    painter.setBrush(brush.getBrush());
    painter.setPen(brush.getPen());
    qDebug() << "Brush"  << brush.getBrush() << endl;
    qDebug() << "Pen" << brush.getPen() << endl;
    painter.drawLine(points[1], knownPoint);
    qDebug() << "Color"  << brush.getColor() << endl;
    qDebug() << "Drawing In progress" << endl;
}

void BitmapImage::paintImage(QPainter &painter, QTabletEvent *event, Brush brush, QPoint points[])
{
    /*
    painter.setBrush(brush.getBrush());
    painter.setPen(brush.getPen());
    painter.drawLine(points[1], event->pos());
    */
    qDebug() << "Brush"  << brush.getBrush() << endl;
    qDebug() << "Pen" << brush.getPen() << endl;
    qDebug() << "Color"  << brush.getColor() << endl;

    //painter = QPainter(&m_pixmap);
    painter.setBrush(brush.getBrush());
    painter.setPen(brush.getPen());
    painter.drawLine(points[1], event->pos());
}

void BitmapImage::paintImage(QTabletEvent *event, Brush brush, QPoint points[])
{
    QPainter painter(&m_pixmap);
    painter.setBrush(brush.getBrush());
    painter.setPen(brush.getPen());
    painter.drawLine(points[1], event->pos());
}


