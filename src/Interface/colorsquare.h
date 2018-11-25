#ifndef COLORSQUARE_H
#define COLORSQUARE_H

#include <QColor>
#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>

/**
 * @brief The ColorSquare class More traditional color input
 */
class ColorSquare : public QLabel
{
    Q_OBJECT
public:
    ColorSquare(QWidget* parent = 0);
signals:
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);
    void colorChanged(QColor);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
private:
    QColor  getColorFromPoint(QPoint);
    QColor  m_primaryColor;
    QColor  m_altColor;
    int     m_hue;
    int     m_saturation;
    int     m_value;
    double  m_rotationAngle;
    bool    m_MouseDown;
    bool    m_toggleAlt;        //Toggle use of alternative color;
    QRect   m_primaryColorRect, m_altColorRect, m_mainColorRect;
};

#endif // COLORSQUARE_H
