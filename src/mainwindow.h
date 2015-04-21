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
    void showNewDocWin();
    void showPrefWin();
    void toggleShowBrushDock(bool);
    void toggleShowColorDock(bool);
    void toggleShowTimelineDock(bool);
    void toggleShowToolsDock(bool);
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

    double scaleFactor = 1.0;

    Editor *m_Editor;
    OdessaNewDocDialog *newDialogWin;
    OdessaPrefDialog *prefDialog;
    BrushDockWidget *brushDockWidget;
    ColorDockWidget *colorDockWidget;
    TimelineDockWidget *timelineDockWidget;
    LayerDockWidget *layerDockWidget;
    ToolsPanel* toolPanelWidget;

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
    QAction *showToolsDockAct;
    QAction *preferenceAct;

    //Transform stuff
    QAction *translateAct;
    QAction *rotateAct;
    QAction *scaleAct;

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
    QAction* resetZoomAct;

    QString projectPath;

    /*Key Input*/
    QAction* key_accent;
    QAction* key_1;
    QAction* key_2;
    QAction* key_3;
    QAction* key_4;
    QAction* key_5;
    QAction* key_6;
    QAction* key_7;
    QAction* key_8;
    QAction* key_9;
    QAction* key_0;
    QAction* key_minus;
    QAction* key_equals;

    QAction* key_a;
    QAction* key_b;
    QAction* key_c;
    QAction* key_d;
    QAction* key_e;
    QAction* key_f;
    QAction* key_g;
    QAction* key_h;
    QAction* key_i;
    QAction* key_j;
    QAction* key_k;
    QAction* key_l;
    QAction* key_m;
    QAction* key_n;
    QAction* key_o;
    QAction* key_p;
    QAction* key_q;
    QAction* key_r;
    QAction* key_s;
    QAction* key_t;
    QAction* key_u;
    QAction* key_v;
    QAction* key_w;
    QAction* key_x;
    QAction* key_y;
    QAction* key_z;

    QAction* key_space;
    QAction* key_shift;
};

#endif // MAINWINDOW_H
