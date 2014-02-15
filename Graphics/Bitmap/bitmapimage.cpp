#include "bitmapimage.h"

BitmapImage::BitmapImage()
{
    m_Image = NULL;
    qDebug() << "Image drawn!" << endl;
}

BitmapImage::BitmapImage(const BitmapImage &image)
{
    m_Image = image.m_Image;
    myParent = image.myParent;
    boundaries = image.boundaries;
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
    m_Image = new QImage(boundaries.size(), QImage::Format_ARGB32_Premultiplied);
    m_Color = color;
    m_Image->fill(m_Color.rgba());
}

void BitmapImage::paintImage(QPainter &painter)
{
    painter.drawImage(boundaries, *m_Image);
}
