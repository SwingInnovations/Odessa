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

#endif // DOCKWIDGETS_H
