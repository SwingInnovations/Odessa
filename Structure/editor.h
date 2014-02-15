#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QList>
#include <QListIterator>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include "layer.h"

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);
public slots:
    void addLayer();

private:
    int currentFrame;
    int currentIndex;
    int numOfFramesPerSecond;
    QList<Layer*> mIndex;
    QList<Layer*> rIndex;
};

#endif // EDITOR_H
