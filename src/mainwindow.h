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
#include <QWidgetAction>
#include <QUrl>

#include "Structure/editor.h"
#include "Structure/gleditor.h"
#include "Interface/dialogwindows.h"
#include "Interface/dockwidgets.h"
#include "Interface/panels.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUseDark(bool v);
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
    void openProject();
    void saveProjectAs();
    void saveProject();
    void zoomIn();
    void zoomOut();
    void about();
    void readSettings();
    void writeSettings();
    void selectToStencil();
private:
    void scaleImage(double);
    void adjustScrollBar(QScrollBar* scrollBar, double factor);

    double m_scaleFactor = 1.0;
    bool m_useDark;
    bool m_useHWAcceleration;

    Editor *m_Editor;
    GLEditor *m_GLEditor;
    OdessaNewDocDialog *m_newDiag;
    OdessaPrefDialog *m_prefDiag;
    BrushDockWidget *m_brushDock;
    ColorDockWidget *m_colorDock;
    TimelineDockWidget *m_timeDock;
    DebugWindow *m_debugWin;
    LayerDockWidget *m_layerDock;
    ToolsPanel* m_toolPanel;

    BrushConfigPanel* m_brushToolPanel;
    ColorConfigPanel* m_colorConfigPanel;
    ColorConfigPanel* m_dockColorConfigPanel;

    bool m_isModified;

    QAction *m_addLayerAct;
    /*-File Menu-*/
    QAction *m_newAct;
    QAction *m_openAct;
    QAction *m_saveAct;
    QAction *m_saveAsAct;
    QMenu *m_exportMenu;
    QAction *m_exportSelAct;
    QAction *m_exportImgAct;
    QAction *m_exportSSAct;
    QAction *m_exportImgSeqAct;
    QAction *m_exportAnimAct;
    QAction *m_closeAct;

    //edit menu actions
    QAction *m_undoAct;
    QAction *m_redoAct;
    QAction *m_cutAct;
    QAction *m_copyAct;
    QAction *m_pasteAct;

    //select menu actions
    QAction *m_selRegionAct;
    QAction *m_selAllAct;
    QAction *m_deSelAct;
    QAction *m_convertToStenAct;

    //show dock widgets
    QAction *m_showBrushDockWinAct;
    QAction *m_showColorDockWinAct;
    QAction *m_showTimeDockWinAct;
    QAction *m_showLayersDockAct;
    QAction *m_showToolsDockAct;
    QAction *m_preferenceAct;

    //Transform stuff
    QAction *m_translateAct;
    QAction *m_rotateAct;
    QAction *m_scaleAct;

    //basic Tools
    QAction *m_cursorTool;
    QAction *m_brushTool;
    QAction *m_eraserTool;
    QAction *m_textTool;
    QAction *m_primTool;
    QAction *m_eyedropTool;
    QAction *m_fillTool;

    QShortcut* m_eyeDropper;

    QAction *m_sendFeedbackAct;
    QAction *m_updateAct;
    QAction *m_aboutAct;

    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_selectMenu;
    QMenu *m_viewMenu;
    QMenu *m_dockWinMenu;
    QMenu *m_helpMenu;

    QScrollArea *m_workArea;
    QToolBar* m_toolBar;
    QComboBox* m_toolQuickSelect;

    QStatusBar* m_StatBar;
    QLabel* m_activeToolLabel;
    QSlider* m_zoomSlider;
    QAction* m_zoomInAct;
    QAction* m_zoomOutAct;
    QAction* m_resetZoomAct;

    QAction* m_showDebugWinAct;

    QString m_projectPath;
};

#endif // MAINWINDOW_H
