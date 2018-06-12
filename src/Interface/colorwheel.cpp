#include "colorwheel.h"

/*- Color wheel -*/
ColorWheel::ColorWheel(QWidget *parent) : QLabel(parent)
{
    m_Pixmap = QPixmap(250, 200);
    m_Pixmap.fill(QColor(53, 53, 53));
    setPixmap(m_Pixmap);

    m_PrimaryRed = 0;
    m_PrimaryGreen = 0;
    m_PrimaryBlue = 0;
    m_AltRed = 255;
    m_AltGreen = 255;
    m_AltBlue = 255;

    m_RotationAngle = 0.0;

    m_PrimaryColorRect = QRect(210, 160, 20, 20);
    m_AltColorRect = QRect(220, 170, 20, 20);
    QRect referenceRect(72, 47,105, 105);

    m_Points.reserve(3);
    m_Points.push_back(QPoint(referenceRect.topLeft().x() + referenceRect.width()/2, referenceRect.top() - 20));
    m_Points.push_back(referenceRect.bottomLeft());
    m_Points.push_back(referenceRect.bottomRight());

    m_CenterRectPoint = QPoint(m_Points.at(0).x(), 100);

    m_ColorRangeTri.moveTo(m_Points.at(0));
    m_ColorRangeTri.lineTo(m_Points.at(1));
    m_ColorRangeTri.lineTo(m_Points.at(2));
    m_ColorRangeTri.lineTo(m_Points.at(0));

    m_PrimaryBasePoint = QPoint(125, 15);
    m_AltBasePoint = QPoint(125, 185);
    m_toggleAlt = false;
    QColor col(m_PrimaryRed, m_PrimaryGreen, m_PrimaryBlue);
    m_Hue = col.hue();
    m_Saturation = col.saturation();
    m_Value = col.value();
}

QColor ColorWheel::getColorFromPoint(QPoint point){
    QPixmap pic = QWidget::grab();
    QImage img = pic.toImage();
    return QColor(img.pixel(point));
}

void ColorWheel::setActualColor(QColor col){
    m_ActualRed = col.red();
    m_ActualGreen = col.green();
    m_ActualBlue = col.blue();
    update();
}

QColor ColorWheel::getColor(){
    QColor ret(m_ActualRed, m_ActualGreen, m_ActualBlue);
    return ret;
}

void ColorWheel::setRed(int r){
    m_ActualRed = r;
    repaint();
}

void ColorWheel::setGreen(int g){
    m_ActualGreen = g;
    repaint();
}

void ColorWheel::setBlue(int b){
    m_ActualBlue = b;
    repaint();
}

void ColorWheel::processHSV(QColor col){
    m_Hue = col.hslHue();
    m_Saturation = col.saturation();
    m_Value = col.value();
}

void ColorWheel::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
        if(m_PrimaryColorRect.contains(ev->pos())){
            QColor color = QColorDialog::getColor(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
            if(color.isValid()){
                m_ActualRed = color.red();
                m_ActualGreen = color.green();
                m_ActualBlue = color.blue();
            }
            emit redChanged(m_ActualRed);
            emit greenChanged(m_ActualGreen);
            emit blueChanged(m_ActualBlue);
            emit colorChanged(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
            repaint();
            return;
        }

        if(m_AltColorRect.contains(ev->pos())){
            emit redChanged(m_AltRed);
            emit greenChanged(m_AltGreen);
            emit blueChanged(m_AltBlue);
            repaint();
            return;
        }

        if(m_ColorRangeTri.contains(ev->pos())){
            //set the color
            m_PreciseColor = ev->pos();
            QColor newColor = getColorFromPoint(ev->pos());
            m_ActualRed = newColor.red();
            m_ActualGreen = newColor.green();
            m_ActualBlue = newColor.blue();
            emit redChanged(m_ActualRed);
            emit greenChanged(m_ActualGreen);
            emit blueChanged(m_ActualBlue);
            emit colorChanged(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
            return;
        }
        if(!m_MouseDown && !m_ColorRangeTri.contains(ev->pos())) m_MouseDown = true;
        if(m_MouseDown){
            QPoint centerPoint(175, 100);
            QPoint dPoint = centerPoint - ev->pos();
            m_RotationAngle = atan2(dPoint.x(), dPoint.y());
            m_RotationAngle = m_RotationAngle * (180.0 / ODESSA_PI);
            processBaseMovePoint();
        }
    }


    if(ev->button() == Qt::RightButton){
        int swapRed = 0, swapGreen = 0, swapBlue = 0;
        swapRed = m_ActualRed;
        swapGreen = m_ActualGreen;
        swapBlue = m_ActualBlue;
        m_ActualRed = m_AltRed;
        m_ActualGreen = m_AltGreen;
        m_ActualBlue = m_AltBlue;
        m_AltRed = swapRed;
        m_AltGreen = swapGreen;
        m_AltBlue = swapBlue;
        emit redChanged(m_ActualRed);
        emit greenChanged(m_ActualGreen);
        emit blueChanged(m_ActualBlue);
        emit colorChanged(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
        repaint();
        return;
    }


    if(ev->button() == Qt::MidButton){
        m_toggleAlt =! m_toggleAlt;
        if(m_toggleAlt){
            QColor newColor = getColorFromPoint(m_AltBasePoint);
            m_PrimaryRed = newColor.red();
            m_PrimaryGreen = newColor.green();
            m_PrimaryBlue = newColor.blue();
            m_RotationAngle+= 180.0f;
        }else{
            QColor newColor = getColorFromPoint(m_PrimaryBasePoint);
            m_PrimaryRed = newColor.red();
            m_PrimaryGreen = newColor.green();
            m_PrimaryBlue = newColor.blue();
            m_RotationAngle+= 180.0f;
        }
    }
    repaint();
}

void ColorWheel::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(53, 53, 53));
    painter.drawRect(0, 0, 250, 200);
    QConicalGradient externalColor;
    externalColor.setCenter(100, 100);
    externalColor.setColorAt(0, Qt::green);
    externalColor.setColorAt(0.175, Qt::yellow);
    externalColor.setColorAt(0.35, Qt::red);
    externalColor.setColorAt(0.525, Qt::magenta);
    externalColor.setColorAt(0.65, Qt::blue);
    externalColor.setColorAt(0.8253, Qt::cyan);
    externalColor.setColorAt(1.0, Qt::green);
    painter.setBrush(externalColor);
    painter.drawEllipse(25, 0, 200, 200);

    QPoint ctrPoint(125, 100);
    QPoint pbp = QPoint(m_PrimaryBasePoint.x(), m_PrimaryBasePoint.y());
    QPoint abp = QPoint(m_AltBasePoint.x(), m_AltBasePoint.y());

    QLine line;
    line.setP1(QPoint(125,23));
    line.setP2(QPoint(125, 177));
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.translate(ctrPoint);
    painter.rotate(-m_RotationAngle);
    painter.translate(-ctrPoint);
    painter.drawLine(line);
    painter.resetTransform();

    painter.setBrush(Qt::transparent);
    painter.drawEllipse(pbp, 8, 8);
    painter.drawEllipse(abp, 8, 8);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(53, 53, 53));
    painter.drawEllipse(ctrPoint, 75, 75);

    //Color Rect
    QColor primaryColor(m_PrimaryRed, m_PrimaryGreen, m_PrimaryBlue);
    QColor altColor(m_AltRed, m_AltGreen, m_AltBlue);
    painter.setPen(Qt::black);
    painter.setBrush(altColor);
    painter.drawRect(m_AltColorRect);
    QColor actualColor(m_ActualRed, m_ActualGreen, m_ActualBlue);
    painter.setBrush(actualColor);
    painter.drawRect(m_PrimaryColorRect);

    QConicalGradient colorGrad;
    colorGrad.setCenter(m_CenterRectPoint);
    colorGrad.setAngle(90);
    //colorGrad.setColorAt(0, Qt::white);
    colorGrad.setColorAt(0.0, primaryColor);
    colorGrad.setColorAt(0.40, Qt::black);
    colorGrad.setColorAt(0.60, Qt::white);
    colorGrad.setColorAt(1.0, primaryColor);

    painter.setBrush(colorGrad);
    painter.translate(m_CenterRectPoint);
    painter.rotate(-m_RotationAngle);
    painter.translate(-m_CenterRectPoint);
    painter.drawPath(m_ColorRangeTri);
    painter.resetTransform();
    painter.end();
}

void ColorWheel::mouseMoveEvent(QMouseEvent *e){
    if(m_MouseDown){
        QPoint centerPoint(175, 100);
        QPoint dPoint = centerPoint - e->pos();
        m_RotationAngle = atan2(dPoint.x(), dPoint.y());
        m_RotationAngle = m_RotationAngle * (180.0 / ODESSA_PI);
        qDebug() << "Rotation Angle: " << m_RotationAngle << endl;
        processBaseMovePoint();

        //Adjust the primary color
        if(!m_toggleAlt){
            QColor color = getColorFromPoint(m_PrimaryBasePoint);
            m_PrimaryRed = color.red();
            m_PrimaryGreen = color.green();
            m_PrimaryBlue = color.blue();
        }else{
            QColor color = getColorFromPoint(m_AltBasePoint);
            m_PrimaryRed = color.red();
            m_PrimaryGreen = color.green();
            m_PrimaryBlue = color.blue();
            m_RotationAngle += 180.0f;
        }
    }
    repaint();
}

void ColorWheel::mouseReleaseEvent(QMouseEvent *ev){
    Q_UNUSED(ev)
    if(m_MouseDown){
        m_MouseDown = false;
    }
}

void ColorWheel::processBaseMovePoint(){
    QTransform transform;
    QPoint ctrPoint(125, 100);
    m_PrimaryBasePoint = QPoint(125, 15);
    m_AltBasePoint = QPoint(125, 185);
    transform.translate(ctrPoint.x(), ctrPoint.y());
    transform.rotate(-m_RotationAngle);
    transform.translate(-ctrPoint.x(), -ctrPoint.y());
    m_PrimaryBasePoint = transform.map(m_PrimaryBasePoint);
    m_AltBasePoint = transform.map(m_AltBasePoint);
}
