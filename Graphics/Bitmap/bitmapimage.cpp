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

BitmapImage::BitmapImage(QRect boundaries, QPixmap pixMap)
{
    this->boundaries = boundaries;
    m_pixmap = pixMap;
}

void BitmapImage::paintImage(QPainter &painter)
{
    painter.drawPixmap(0, 0, m_pixmap);
}

void BitmapImage::paintImage(QTabletEvent *event, Brush brush, QPoint points[])
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    brush.setWidth(brush.getSize() + (event->pressure() * brush.getTransferWidth()));
    painter.setBrush(brush.getBrush());
    painter.setPen(Qt::NoPen);
    painter.setPen(brush.getPen());
    painter.drawLine(points[1], event->pos());
}

void BitmapImage::paintImage(QMouseEvent *event, Brush brush, QPoint points[])
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush.getBrush());
    painter.setPen(Qt::NoPen);
    painter.setPen(brush.getPen());
    painter.drawLine(points[1], event->pos());
//    painter.drawEllipse(event->pos(), brush.getSize(), brush.getSize());
}

void BitmapImage::paintImage(QPainterPath painterPath, Brush brush)
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QPen copyPen = brush.getPen();
    if(brush.getSize() > 0)
    {
        copyPen.setBrush(brush.getBrush());
        copyPen.setWidth(brush.getSize());
        painter.setPen(copyPen);
    }else{
        copyPen.setBrush(Qt::NoBrush);
        copyPen.setWidth(0);
        painter.setPen(copyPen);
    }
    painter.drawPath(painterPath);
}

void BitmapImage::paintImage(QVector<QPointF> pointInfo, Brush brush)
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush.getBrush());
    painter.setPen(brush.getPen());
    painter.setOpacity(((float)brush.getOpacity() / 255.0));
    painter.drawPolyline(pointInfo);
    painter.end();
}

void BitmapImage::paintImage(QVector<QPointF> pointInfo, Brush brush, qreal tabPress, int amt)
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush.getBrush());
    QPen pen(brush.getPen());
    pen.setWidthF((float)brush.getSize() + (float)brush.getTransferWidth());
    painter.setPen(pen);
    painter.setOpacity((brush.getOpacity()/255.0));
    painter.drawPolyline(pointInfo);
    painter.end();

}

void BitmapImage::optimizeImage(Brush brush)
{
    QPixmap temp = this->copy().getPixmap();
    QPainter painter(&m_pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawPixmap(0,0, m_pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.setOpacity(0.1);
    painter.drawPixmap(0, 0, temp);
    painter.end();
    m_pixmap = temp;
    qDebug() << "Optimizing Image" << endl;
}

QPixmap BitmapImage::getCompositeImage()
{
    QPixmap temp = m_pixmap;
    QPainter painter(&temp);
    painter.setOpacity(0.5);
    painter.drawPixmap(0, 0, temp);
    painter.end();
    m_pixmap = temp;
    return m_pixmap;
}
