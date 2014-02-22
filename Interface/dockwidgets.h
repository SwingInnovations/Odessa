#ifndef DOCKWIDGETS_H
#define DOCKWIDGETS_H

#include <QDockWidget>
#include <QWidget>

class BrushDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    BrushDockWidget(QWidget *parent = 0);
    virtual ~BrushDockWidget();
private:

};

class ColorDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    ColorDockWidget(QWidget *parent = 0);
    virtual ~ColorDockWidget();
private:

};

class TimelineDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    TimelineDockWidget(QWidget *parent = 0);
    virtual ~TimelineDockWidget();
};

#endif // DOCKWIDGETS_H
