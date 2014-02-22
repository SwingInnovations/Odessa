#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QList>
#include <QListIterator>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPoint>
#include <QPixmap>
#include "layer.h"
#include "brush.h"

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);
public slots:
    void newProject(int type, int width, int height, int dpi);
    void addLayer(int width, int height);
private:
    bool deviceDown;
    QPoint knownPos;
    Brush brush;
    QPoint drawPath[3];
    int currentFrame;
    int currentIndex;
    int numOfFramesPerSecond;
    QList<Layer*> mIndex;
    QList<Layer*> rIndex;
};

#endif // EDITOR_H
