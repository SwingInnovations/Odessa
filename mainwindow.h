#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "Structure/editor.h"
#include "Interface/dialogwindows.h"
#include "Interface/dockwidgets.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showNewDocWin();
    void toggleShowBrushDock(bool);
    void toggleShowColorDock(bool);
    void toggleShowTimelineDock(bool);
    void about();

private:
    Editor *mEditor;
    OdessaNewDocDialog *newDialogWin;
    BrushDockWidget *brushDockWidget;
    ColorDockWidget *colorDockWidget;
    TimelineDockWidget *timelineDockWidget;

    bool isModified;

    //temporary action
    QAction *addLayerAct;
    QAction *newAct;
    QAction *closeAct;

    QAction *showBrushDockWinAct;
    QAction *showColorDockWinAct;
    QAction *showTimeDockWinAct;
    QAction *preferenceAct;

    QAction *aboutAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *dockWinMenu;
    QMenu *helpMenu;

};

#endif // MAINWINDOW_H
