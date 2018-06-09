#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QTabletEvent>
#include <QVector>
#include <QPointF>
#include <QWidget>

/**
 * @brief The Canvas class
 * Handles Drawing new objects on the screen.
 */
class Canvas : public QGraphicsScene, public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget* parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event)  override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void tabletEvent(QTabletEvent* event);
private:
    bool m_mouseDown;
    QVector<QPointF> m_mousePath;
    QRect m_mouseRect;

#ifdef Q_OS_WIN
    bool    m_useWinInkAPI;
#endif

};

#endif // CANVAS_H
