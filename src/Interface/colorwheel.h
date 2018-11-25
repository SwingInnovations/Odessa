#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include <QColor>
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QColorDialog>
#include <QPainter>
#include <QDebug>

#define ODESSA_PI 3.141592

/**
 * @brief The ColorWheel class
 * Custom color picker widget
 */
class ColorWheel : public QLabel
{
    Q_OBJECT
public:
    ColorWheel(QWidget* parent = 0);
    void setRed(int);
    void setGreen(int);
    void setBlue(int);
    void setActualColor(QColor);
    QColor getColor();
    void setHue(int);
    void setSaturation(int);
    void setValue(int);
signals:
    void redChanged(int);
    void blueChanged(int);
    void greenChanged(int);
    void colorChanged(QColor);
protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    void processHSV(QColor col);
    QColor getColorFromPoint(QPoint);
    void processBaseMovePoint();
    QPixmap m_Pixmap;
    int m_Hue;
    int m_Saturation;
    int m_Value;

    int m_ActualRed;
    int m_ActualGreen;
    int m_ActualBlue;

    int m_PrimaryRed;
    int m_PrimaryBlue;
    int m_PrimaryGreen;

    int m_AltRed;
    int m_AltGreen;
    int m_AltBlue;

    QRect m_PrimaryColorRect, m_AltColorRect;
    QPoint m_PreciseColor;
    QPoint m_PrimaryBasePoint, m_AltBasePoint, m_CenterRectPoint;
    QVector<QPoint>m_Points;
    QPainterPath m_ColorRangeTri;
    double m_RotationAngle;
    bool m_MouseDown;
    bool m_toggleAlt;
};

#endif // COLORWHEEL_H
