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
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>

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
    void sendFeedBack();
    void assignBrushTool();
    void assignEraserTool();
    void assignTextTool();
    void assignPrimitiveTool();
    void assignEyeDropperTool();
    void assignRectSelectTool();
    void assignFillTool();
    void showNewDocWin();
    void showPrefWin();
    void toggleShowBrushDock(bool);
    void toggleShowColorDock(bool);
    void toggleShowTimelineDock(bool);
    void exportImage();
    void setProjectPath(QString);
    void zoomIn();
    void zoomOut();
    void about();
    void readSettings();
    void writeSettings();
private:
    void scaleImage(double);
    void adjustScrollBar(QScrollBar* scrollBar, double factor);

    int scaleFactor = 1;

    Editor *m_Editor;
    OdessaNewDocDialog *newDialogWin;
    OdessaPrefDialog *prefDialog;
    BrushDockWidget *brushDockWidget;
    ColorDockWidget *colorDockWidget;
    TimelineDockWidget *timelineDockWidget;
    LayerDockWidget *layerDockWidget;

    bool isModified;

    QAction *addLayerAct;
    /*-File Menu-*/
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QMenu *exportMenu;
    QAction *exportImgAct;
    QAction *exportSpriteSheetAct;
    QAction *exportImgSeqAct;
    QAction *exportAnimAct;
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
    QAction *showLayersDockAct;
    QAction *preferenceAct;

    //basic Tools
    QAction *brushTool;
    QAction *eraserTool;
    QAction *textTool;
    QAction *primitiveTool;
    QAction *eyeDropperTool;
    QAction *fillTool;

    QShortcut* eyeDropper;

    QAction *sendFeedbackAct;
    QAction *updateAct;
    QAction *aboutAct;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectMenu;
    QMenu *viewMenu;
    QMenu *dockWinMenu;
    QMenu *helpMenu;

    QScrollArea *imageArea;

    QToolBar* toolBar;
    QComboBox* mToolQuickSelect;

    QStatusBar* mStatBar;
    QLabel* activeToolLabel;
    QSlider* zoomSlider;
    QAction* zoomInAct;
    QAction* zoomOutAct;

    QString projectPath;
};

#endif // MAINWINDOW_H
