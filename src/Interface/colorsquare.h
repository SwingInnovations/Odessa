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
    ColorSquare();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
private:
    QColor  m_primaryColor;
    QColor  m_altColor;
    QRect   m_primaryColorRect, m_altColorRect, m_mainColorRect;
};

#endif // COLORSQUARE_H
