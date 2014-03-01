#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QShortcut>

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
    void assignBrushTool();
    void assignEraserTool();
    void assignTextTool();
    void assignPrimitiveTool();
    void assignEyeDropperTool();
    void showNewDocWin();
    void showPrefWin();
    void toggleShowBrushDock(bool);
    void toggleShowColorDock(bool);
    void toggleShowTimelineDock(bool);
    void about();

private:
    Editor *mEditor;
    OdessaNewDocDialog *newDialogWin;
    OdessaPrefDialog *prefDialog;
    BrushDockWidget *brushDockWidget;
    ColorDockWidget *colorDockWidget;
    TimelineDockWidget *timelineDockWidget;

    bool isModified;

    QAction *addLayerAct;
    QAction *newAct;
    QAction *closeAct;

    //edit menu actions
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    //select menu actions
    QAction *selectRegionAct;
    QAction *selectAllAct;
    QAction *deselectAct;

    //show dock widgets
    QAction *showBrushDockWinAct;
    QAction *showColorDockWinAct;
    QAction *showTimeDockWinAct;
    QAction *preferenceAct;

    //basic Tools
    QAction *brushTool;
    QAction *eraserTool;
    QAction *textTool;
    QAction *primitiveTool;
    QAction *eyeDropperTool;

    QShortcut* eyeDropper;

    QAction *aboutAct;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectMenu;
    QMenu *viewMenu;
    QMenu *dockWinMenu;
    QMenu *helpMenu;

    QToolBar* toolBar;

};

#endif // MAINWINDOW_H
