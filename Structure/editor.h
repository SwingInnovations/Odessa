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
    enum ToolType{BRUSH_TOOL, ERASER_TOOL, TEXT_TOOL , PRIMITIVE_TOOL};

    Editor(QWidget *parent = 0);
    void setBrush(ToolType type);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);
public slots:
    void newProject(int type, int width, int height, int dpi);
    void addLayer(int width, int height);

    void setBrushSize(int);
    void setBrushFeather(int);
    void setBrushSpacing(int);
private:
    bool deviceDown;
    QPoint knownPos;
    Brush currentTool;
    Brush brush;
    Brush eraser;
    QPoint drawPath[3];
    int currentFrame;
    int currentIndex;
    int numOfFramesPerSecond;
    QList<Layer*> mIndex;
    QList<Layer*> rIndex;
};

#endif // EDITOR_H
