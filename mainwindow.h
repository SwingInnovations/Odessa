#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QScrollArea>
#include <QScrollBar>
#include <QShortcut>
#include <QStatusBar>
#include <QLabel>
#include <QSlider>

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
    void zoomIn();
    void zoomOut();
    void about();

private:
    void scaleImage(double);
    void adjustScrollBar(QScrollBar* scrollBar, double factor);
    int scaleFactor = 1;

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

    QScrollArea *imageArea;

    QToolBar* toolBar;

    QStatusBar* mStatBar;
    QLabel* activeToolLabel;
    QSlider* zoomSlider;
    QAction* zoomInAct;
    QAction* zoomOutAct;
};

#endif // MAINWINDOW_H
