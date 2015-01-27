#include "bitmapimage.h"

BitmapImage::BitmapImage()
{
    m_Image = NULL;
    visible = true;
    qDebug() << "Image drawn!" << endl;
    m_WScaleFactor = 1.0;
    m_HScaleFactor = 1.0;
}

BitmapImage::BitmapImage(const BitmapImage &image)
{
    m_pixmap = image.m_pixmap;
    boundaries = image.boundaries;
    m_Color = image.m_Color;
    m_WScaleFactor = 1.0;
    m_HScaleFactor = 1.0;
}

BitmapImage::BitmapImage(Object *parent, QRect boundaries, QColor color)
{
    myParent = parent;
    this->boundaries = boundaries;
    m_Image = new QImage(boundaries.size(), QImage::Format_ARGB32_Premultiplied);
    m_Image->fill(color.rgba());
    visible = true;
    m_WScaleFactor = 1.0;
    m_HScaleFactor = 1.0;
}

BitmapImage::BitmapImage(Object *parent, QRect boundaries, QImage image)
{
    myParent = parent;
    this->boundaries = boundaries;
    m_Image = new QImage(image);
    if(m_Image->width() != boundaries.width() && m_Image->height() != boundaries.height()) qDebug() << "Error 0001: Failed to load Image" << endl;
    visible = true;
    m_WScaleFactor = 1.0;
    m_HScaleFactor = 1.0;
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
    visible = true;
    m_WScaleFactor = 1.0;
    m_HScaleFactor = 1.0;
}

BitmapImage::BitmapImage(QRect boundaries, QPixmap pixMap)
{
    this->boundaries = boundaries;
    m_pixmap = pixMap;
    visible = true;
    m_WScaleFactor = 1.0;
    m_HScaleFactor = 1.0;
}

void BitmapImage::paintImage(QPainter &painter)
{
    painter.drawPixmap(0, 0, m_pixmap);
}

void BitmapImage::paintImage(QTabletEvent *event, Brush brush, QPoint points[])
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    brush.setWidth(brush.getSize() + (event->pressure() * brush.getTransferSize()));
    painter.setBrush(brush.getBrush());
    painter.setPen(Qt::NoPen);
    painter.setPen(brush.getPen());
    painter.drawLine(points[1], event->pos());
}
/*-FLAG - Deprecate-*/
void BitmapImage::paintImage(QMouseEvent *event, Brush brush, QPoint points[])
{
    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush.getBrush());
    painter.setPen(Qt::NoPen);
    painter.setPen(brush.getPen());
    painter.drawLine(points[2], points[1]);
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
    int brushWidth = brush.getSize() + (brush.getPressureVal() * brush.getTransferSize());
    /*-Prepare Stencil-*/
    QImage stencilBase = brush.getStencil().toImage();
    stencilBase.invertPixels(QImage::InvertRgb);
    stencilBase.createAlphaMask();
    stencilBase.convertToFormat(QImage::Format_RGB888, Qt::AutoColor);
    QImage stencilImage = QImage(stencilBase);
    QColor color = brush.getColor();
    color.setAlpha(brush.getOpacity() + (brush.getPressureVal() * brush.getTransferOpacity()));
    stencilImage.fill(color);
    stencilImage.setAlphaChannel(stencilBase);
    QPixmap stencil = QPixmap::fromImage(stencilImage.scaled(brushWidth, brushWidth, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPointF point, drawPoint;
    point = pointInfo.last() - pointInfo.first();
    int length = point.manhattanLength();
    double xInc, yInc;
    xInc = point.x() / length;
    yInc = point.y() / length;
    drawPoint = pointInfo.first();
    for(unsigned int i = 0; i < length; i++){
        drawPoint.setX(drawPoint.x() + (xInc * brush.getSpacing() ));
        drawPoint.setY(drawPoint.y() + (yInc * brush.getSpacing() ));
        painter.drawPixmap(QPoint(drawPoint.x() - stencil.width() / 2, drawPoint.y() - stencil.height()/2), stencil);
    }
}

void BitmapImage::paintImage(QVector<QPointF> pointInfo, Brush brush, qreal tabPress, int amt)
{
    int brushWidth = brush.getSize() + (amt * tabPress);
    /*-Prepare Stencil-*/
    QImage stencilBase = brush.getStencil().toImage();
    stencilBase.invertPixels(QImage::InvertRgb);
    stencilBase.createAlphaMask();
    stencilBase.convertToFormat(QImage::Format_RGB888, Qt::AutoColor);
    QImage stencilImage = QImage(stencilBase);
    QColor color = brush.getColor();
    color.setAlpha(brush.getOpacity());
    stencilImage.fill(color);
    stencilImage.setAlphaChannel(stencilBase);
    QPixmap stencil = QPixmap::fromImage(stencilImage.scaled(brushWidth, brushWidth, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPointF point, drawPoint;
    point = pointInfo.last() - pointInfo.first();
    int length = point.manhattanLength();
    double xInc, yInc;
    xInc = point.x() / length;
    yInc = point.y() / length;
b      drawPoint = pointInfo.first();
    for(int i = 0; i < length; i++){
        drawPoint.setX(drawPoint.x() + (xInc * brush.getSpacing() ));
        drawPoint.setY(drawPoint.y() + (yInc * brush.getSpacing() ));
        painter.drawPixmap(QPoint(drawPoint.x() - stencil.width() / 2, drawPoint.y() - stencil.height()/2), stencil);
    }
}

void BitmapImage::fillImage(QPoint point, Brush brush){
    QImage img = m_pixmap.toImage();
    QRgb oldColor = img.pixel(point);
    if(oldColor == brush.getColor().rgb()){
        return;
    }else{
        if(point.x() >= 0){
            QPainter p(&img);
            p.setPen(brush.getColor());
            p.setBrush(brush.getColor());
            p.drawPoint(point);
            p.end();

            m_pixmap = QPixmap::fromImage(img);
            fillImage(QPoint(point.x() + 1, point.y()), brush);

        }else if(point.x() < img.width()){
            QPainter p(&img);
            p.setPen(brush.getColor());
            p.setBrush(brush.getColor());
            p.drawPoint(point);
            p.end();

            m_pixmap = QPixmap::fromImage(img);
            fillImage(QPoint(point.x()-1, point.y()), brush);
        }else{

        }

        if(point.y() >= 0){
            QPainter p(&img);
            p.setPen(brush.getColor());
            p.setBrush(brush.getColor());
            p.drawPoint(point);
            p.end();

            m_pixmap = QPixmap::fromImage(img);
            fillImage(QPoint(point.x(), point.y() + 1), brush);
        }else if(point.y() < img.height()){
            QPainter p(&img);
            p.setPen(brush.getColor());
            p.setBrush(brush.getColor());
            p.drawPoint(point);
            p.end();

            m_pixmap = QPixmap::fromImage(img);
            fillImage(QPoint(point.x(), point.y()-1), brush);
        }else{

        }
        return;
    }
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