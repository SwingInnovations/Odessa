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
    void assignDeselectTool();
    void assignRectSelectTool();
    void assignFillTool();
    void assignTransformTool();
    void assignCursorTool();
    void showNewDocWin();
    void showPrefWin();
    void changeStatusMessage(QString);
    void toggleShowBrushDock(bool);
    void toggleShowColorDock(bool);
    void toggleShowTimelineDock(bool);
    void toggleShowToolsDock(bool);
    void showDebugWin();
    void exportImage();
    void exportSelection();
    void newProject(ProjectInfo&);
    void setProjectPath(QString);
    void zoomIn();
    void zoomOut();
    void about();
    void readSettings();
    void writeSettings();
    void selectToStencil();
private:
    void scaleImage(double);
    void adjustScrollBar(QScrollBar* scrollBar, double factor);

    double scaleFactor = 1.0;

    Editor *m_Editor;
    OdessaNewDocDialog *newDialogWin;
    OdessaPrefDialog *prefDialog;
    BrushDockWidget *brushDockWidget;
    ColorDockWidget *colorDockWidget;
    TimelineDockWidget *timelineDockWidget;
    DebugWindow *debugWin;
    LayerDockWidget *layerDockWidget;
    ToolsPanel* toolPanelWidget;

    bool isModified;

    QAction *addLayerAct;
    /*-File Menu-*/
    QAction *m_newAct;
    QAction *m_openAct;
    QAction *m_saveAct;
    QAction *m_saveAsAct;
    QMenu *exportMenu;
    QAction *exportSelectionAct;
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
    QAction *convertSelToStenAct;

    //show dock widgets
    QAction *showBrushDockWinAct;
    QAction *showColorDockWinAct;
    QAction *showTimeDockWinAct;
    QAction *showLayersDockAct;
    QAction *showToolsDockAct;
    QAction *preferenceAct;

    //Transform stuff
    QAction *translateAct;
    QAction *rotateAct;
    QAction *scaleAct;

    //basic Tools
    QAction *cursorTool;
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
    QAction* resetZoomAct;

    QAction* debugWinAct;

    QString projectPath;
};

#endif // MAINWINDOW_H
