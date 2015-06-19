#include "bitmapimage.h"

BitmapImage::BitmapImage()
{
    m_Image = NULL;
    visible = true;
    m_ScaleFactor = 1.0;
    qDebug() << "Image drawn!" << endl;
    m_ScaleFactorInv = 1.0;
}

BitmapImage::BitmapImage(const BitmapImage &image)
{
    m_pixmap = image.m_pixmap;
    boundaries = image.boundaries;
    m_Color = image.m_Color;
    m_ScaleFactor = 1.0;
    m_ScaleFactorInv = 1.0;
    visible = true;
}

BitmapImage::BitmapImage(Object *parent, QRect boundaries, QColor color)
{
    myParent = parent;
    this->boundaries = boundaries;
    m_Image = new QImage(boundaries.size(), QImage::Format_ARGB32_Premultiplied);
    m_Image->fill(color.rgba());
    m_ScaleFactor = 1.0;
    m_ScaleFactorInv = 1.0;
    visible = true;
}

BitmapImage::BitmapImage(Object *parent, QRect boundaries, QImage image)
{
    myParent = parent;
    this->boundaries = boundaries;
    m_Image = new QImage(image);
    if(m_Image->width() != boundaries.width() && m_Image->height() != boundaries.height()) qDebug() << "Error 0001: Failed to load Image" << endl;
    visible = true;
    m_ScaleFactor = 1.0;
    m_ScaleFactorInv = 1.0;
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
    m_ScaleFactor = 1.0;
    m_ScaleFactorInv = 1.0;
}

BitmapImage::BitmapImage(QRect boundaries, QPixmap pixMap)
{
    this->boundaries = boundaries;
    m_pixmap = pixMap;
    visible = true;
    m_ScaleFactor = 1.0;
    m_ScaleFactorInv = 1.0;
}

void BitmapImage::paintImage(QPainter &painter)
{
    painter.drawPixmap(0, 0, m_pixmap);
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

void BitmapImage::paintImage(QPoint point, Brush brush){
    int brushWidth = brush.getSize() + (brush.getPressureVal() * brush.getTransferSize());
    brushWidth += m_ScaleFactor;
    QImage stencilBase = brush.getStencil().toImage();
    stencilBase.invertPixels(QImage::InvertRgb);
    stencilBase.createAlphaMask();
    stencilBase.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    QImage stencilImage = QImage(stencilBase);
    QColor color = brush.getColor();
    color.setAlpha(brush.getOpacity() + (brush.getPressureVal() * brush.getTransferOpacity()));
    stencilImage.fill(color);
    QPixmap stencil = QPixmap::fromImage(stencilImage.scaled(brushWidth, brushWidth, Qt::IgnoreAspectRatio, Qt::FastTransformation));
    QPainter p(&m_pixmap);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawPixmap(QPoint(point.x() - stencil.width()/2, point.y() - stencil.height()/2), stencil);
}

void BitmapImage::paintImage(QVector<QPointF> pointInfo, Brush brush)
{
    int brushWidth = brush.getSize() + (brush.getPressureVal() * brush.getTransferSize());
    brushWidth *= m_ScaleFactor;
    /*-Prepare Stencil-*/
    QImage stencilBase = brush.getStencil().toImage();
    stencilBase.invertPixels(QImage::InvertRgb);
    stencilBase.createAlphaMask();
    stencilBase.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    QImage stencilImage = QImage(stencilBase);
    QColor color = brush.getColor();
    color.setAlpha(brush.getOpacity() + (brush.getPressureVal() * brush.getTransferOpacity()));
    stencilImage.fill(color);
    stencilImage.setAlphaChannel(stencilBase);
    QPixmap stencil = QPixmap::fromImage(stencilImage.scaled(brushWidth, brushWidth, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    QPainter painter(&m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.moveTo(pointInfo.first());
    path.lineTo(pointInfo.last());

    for(qreal i = 0; i < 1; i+= 0.01 * brush.getSpacing()){
        painter.drawPixmap(QPoint(path.pointAtPercent(i).x() - stencil.width()/2, path.pointAtPercent(i).y() - stencil.width()/2), stencil);
    }

    /*-Old Method-*/

//    QPointF point, drawPoint;
//    point = pointInfo.last() - pointInfo.first();
//    int length = point.manhattanLength();
//    double xInc, yInc;
//    xInc = point.x() / (double)length;
//    yInc = point.y() / (double)length;
//    drawPoint = pointInfo.first();

//    for(int i = 0; i < length; i++){
//        if(drawPoint != pointInfo.last() || drawPoint != pointInfo.first()){
//            drawPoint.setX(drawPoint.x() + (xInc / (double)brush.getSpacing() ));
//            drawPoint.setY(drawPoint.y() + (yInc / (double)brush.getSpacing() ));
//            painter.drawPixmap(QPoint(drawPoint.x() - stencil.width() / 2, drawPoint.y() - stencil.height()/2) / m_ScaleFactor, stencil);
//        }
//    }
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
    drawPoint = pointInfo.first();
    for(int i = 0; i < length; i++){
        drawPoint.setX(drawPoint.x() + (xInc * brush.getSpacing() ));
        drawPoint.setY(drawPoint.y() + (yInc * brush.getSpacing() ));
        painter.drawPixmap(QPoint(drawPoint.x() - stencil.width() / 2, drawPoint.y() - stencil.height()/2), stencil);
    }
}

void BitmapImage::fillImage(QPoint point, Brush brush){

    QImage img = m_pixmap.toImage();
    QRgb oldColor = img.pixel(point);
    QRgb newColor = brush.getColor().rgb();
    fillRecurs(point, img, oldColor, newColor);

    m_pixmap = QPixmap::fromImage(img);
}

void BitmapImage::scale(double s){
    m_ScaleFactor = s;
}

void BitmapImage::commitChanges(QPoint drawPoint, QPixmap pixmap){
    QPainter p(&m_pixmap);
    p.drawPixmap(drawPoint, pixmap);
}

/*
*
*   Implementation of this function is as close to the version in EasyPaint.
*
*/
void BitmapImage::fillRecurs(QPoint pos, QImage& img, QRgb oldColor, QRgb newColor){
    int temp_x(pos.x());
    int left_x = 0;
    while(true){
        if(img.pixel(temp_x, pos.y()) != oldColor){
            break;
        }
        img.setPixel(temp_x, pos.y(), newColor);
        if(temp_x > 0){
            temp_x--;
            left_x = temp_x;
        }else{
            break;
        }
    }

    int right_x(0);
    temp_x = pos.x() + 1;
    while(true){
        if(img.pixel(temp_x, pos.y()) != oldColor){
            break;
        }
        img.setPixel(temp_x, pos.y(), newColor);
        if(temp_x < img.width() -1){
            temp_x++;
            right_x = temp_x;
        }else{
            break;
        }
    }

    for(int x = left_x+1; x < right_x; x++){
        if(pos.y() < 1 || pos.y() >= img.height() - 1){
            break;
        }
        if(right_x > img.width()){ break; }
        QRgb currentColor = img.pixel(x, pos.y()-1);
        if(currentColor == oldColor && currentColor != newColor){
            fillRecurs(QPoint(x, pos.y() -1), img, oldColor, newColor);
        }
        currentColor = img.pixel(x, pos.y() + 1);
        if(currentColor == oldColor && currentColor != newColor){
            fillRecurs(QPoint(x, pos.y() + 1), img, oldColor, newColor);
        }
    }
}

void BitmapImage::cutImgOp(QRect rect, BitmapImage &img){
    QPainter p(&m_pixmap);

}

void BitmapImage::cutImgOp(QRect rect, QColor col){
    QPainter p(&m_pixmap);
    p.setBrush(QBrush(col));
    p.setPen(QPen(col));
    p.fillRect(rect, col);
    p.end();
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
