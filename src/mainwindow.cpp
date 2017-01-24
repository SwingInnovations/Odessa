#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    readSettings();
    m_useDark = true;
    if(m_projectPath.isEmpty()){
        QMessageBox projectMsgBx;
        projectMsgBx.setText("No Project Path set");
        projectMsgBx.setInformativeText("You must set a project path.");
        projectMsgBx.setStandardButtons(QMessageBox::Ok);
        projectMsgBx.setDefaultButton(QMessageBox::Ok);
        resize(1024, 768);
        int ret = projectMsgBx.exec();
        switch(ret){
            case QMessageBox::Ok:
                m_projectPath = QFileDialog::getExistingDirectory(this, "Set Project Path", QDir::currentPath());
                break;
        default:
            break;
        }
    }else{
        QDir dir(m_projectPath);
        dir.mkpath("Brush");
    }
    
    m_Editor = new Editor(this);
    //m_Editor->setAlignment(Qt::AlignCenter);
    m_Editor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_Editor->setFocusPolicy(Qt::ClickFocus);
    //m_Editor->setScaledContents(true);

    m_workArea = new QScrollArea(this);
    m_workArea->setAlignment(Qt::AlignCenter);
    m_workArea->setWidget(m_Editor);
    setCentralWidget(m_workArea);

    m_Editor->setStyleSheet("background-color: rgb(53, 53, 53);");

    m_toolBar = this->addToolBar("Tools");
    m_toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::TopToolBarArea);

    m_newDiag = new OdessaNewDocDialog();
    m_prefDiag = new OdessaPrefDialog();
    m_prefDiag->setProjectPath(m_projectPath);
    m_brushDock = new BrushDockWidget(this);
    m_brushDock->setWindowTitle("Brush");
    m_brushDock->setDirectory(m_projectPath+"/Brush/");
    m_brushDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_Editor->setBrush(m_brushDock->getStartBrush());

    m_colorDock = new ColorDockWidget(this);
    m_colorDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_timeDock = new TimelineDockWidget(this);
    m_timeDock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    m_timeDock->setVisible(false);

    m_layerDock = new LayerDockWidget(this);
    m_layerDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    m_debugWin = new DebugWindow();
    m_debugWin->setModal(false);

    m_toolPanel = new ToolsPanel(this);
    m_toolPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_toolPanel->setVisible(false);
    m_cursorTool = new QAction("Cursor", this);
    m_cursorTool->setShortcut(QKeySequence(Qt::Key_Escape));
    m_brushTool = new QAction(this);
    m_brushTool->setText("Brush");
    m_brushTool->setIcon(QPixmap(":/icon/resource/brush_lite.png"));
    m_eraserTool = new QAction(this);
    m_eraserTool->setText("Eraser");
    m_eraserTool->setIcon(QPixmap(":/icon/resource/eraser_lite.png"));
    m_textTool = new QAction(this);
    m_textTool->setText("Text");
    m_textTool->setIcon(QPixmap(":icon/resource/Text_lite.png"));
    m_primTool = new QAction(this);
    m_primTool->setText("Primitive");
    m_primTool->setIcon(QPixmap(":icon/resource/primitive_lite.png"));
    m_eyedropTool = new QAction(this);
    m_eyedropTool->setText("EyeDropper");
    m_eyedropTool->setIcon(QPixmap(":/icon/resource/eyeDropper.png"));
    m_fillTool = new QAction("Fill", this);
    m_fillTool->setIcon(QPixmap(":/icon/resource/fill_lite.png"));

    m_scaleFactor = 1.0;

    /*-File Menu Actions-*/
    m_newAct = new QAction("&New", this);
    m_newAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    m_newAct->setIcon(QIcon(":/icon/resource/temp_New.png"));
    m_openAct = new QAction("&Open", this);
    m_openAct->setIcon(QIcon(":/icon/resource/temp_Open.png"));
    m_openAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    m_saveAct = new QAction("&Save", this);
    m_saveAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    m_saveAsAct = new QAction("&Save As...", this);
    m_saveAsAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    m_exportImgAct = new QAction("&Image", this);
    m_exportSelAct = new QAction("&Selection", this);
    m_exportSSAct = new QAction("&Sprite Sheet", this);
    m_exportImgSeqAct = new QAction("&Sequence", this);
    m_exportAnimAct = new QAction("&Animation", this);
    m_aboutAct = new QAction("&About", this);
    m_closeAct = new QAction("&Close", this);
    m_closeAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    //edit Actions
    m_undoAct = new QAction(this);
    m_undoAct->setText("&Undo");
    m_undoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    m_undoAct->setIcon(QPixmap(":icon/resource/undo_lite.png"));
    m_redoAct = new QAction(this);
    m_redoAct->setText("&Redo");
    m_redoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    m_redoAct->setIcon(QPixmap(":icon/resource/redo_lite.png"));
    m_cutAct = new QAction(this);
    m_cutAct->setText("&Cut");
    m_cutAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    m_copyAct = new QAction(this);
    m_copyAct->setText("&Copy");
    m_copyAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    m_pasteAct = new QAction(this);
    m_pasteAct->setText("&Paste");
    m_pasteAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));

    m_sendFeedbackAct = new QAction(this);
    m_sendFeedbackAct->setText("&Send Feedback");

    m_updateAct = new QAction(this);
    m_updateAct->setText("&Check for updates...");

    //Select Menu
    m_selRegionAct = new QAction(this);
    m_selRegionAct->setText("&Select Region");
    m_selAllAct = new QAction(this);
    m_selAllAct->setText("&Select All");
    m_deSelAct = new QAction(this);
    m_deSelAct->setText("&Deselect");
    m_convertToStenAct = new QAction("Convert to Stencil", this);

    m_preferenceAct = new QAction("Preferences", this);
    m_preferenceAct->setIcon(QIcon(":/icon/resource/settings_lite.png"));
    m_showBrushDockWinAct = new QAction("Show BrushDock", this);
    m_showBrushDockWinAct->setCheckable(true);
    m_showBrushDockWinAct->setChecked(true);
    m_showColorDockWinAct = new QAction("Color", this);
    m_showColorDockWinAct->setCheckable(true);
    m_showColorDockWinAct->setChecked(true);
    m_showTimeDockWinAct = new QAction("Timeline", this);
    m_showTimeDockWinAct->setCheckable(true);
    m_showToolsDockAct = new QAction("Tools", this);
    m_showToolsDockAct->setCheckable(true);
    m_showToolsDockAct->setChecked(false);
    m_zoomInAct = new QAction("&Zoom In",this);
    m_zoomInAct->setShortcut(QKeySequence::ZoomIn);
    m_zoomInAct->setIcon(QIcon(":/icon/resource/zoom_In_lite.png"));
    m_zoomOutAct = new QAction("&Zoom Out", this);
    m_zoomOutAct->setShortcut(QKeySequence(QKeySequence::ZoomOut));
    m_zoomOutAct->setIcon(QIcon(":/icon/resource/zoom_Out_lite.png"));
    m_resetZoomAct = new QAction("&Reset Zoom", this);
    m_resetZoomAct->setShortcut(QKeySequence(Qt::Key_Home));

    m_translateAct = new QAction("&Translate", this);
    m_rotateAct = new QAction("&Rotate", this);
    m_scaleAct = new QAction("&Scale", this);

    m_fileMenu = this->menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_newAct);
    m_fileMenu->addAction(m_openAct);
    m_fileMenu->addAction(m_saveAct);
    m_fileMenu->addAction(m_saveAsAct);
    m_fileMenu->addSeparator();
    m_exportMenu = new QMenu("&Export", this);
    m_exportMenu->addAction(m_exportImgAct);
    m_exportMenu->addAction(m_exportSelAct);
    m_exportMenu->addAction(m_exportSSAct);
    m_exportMenu->addAction(m_exportImgSeqAct);
    m_exportMenu->addAction(m_exportAnimAct);
    m_fileMenu->addMenu(m_exportMenu);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_closeAct);

    //edit Menu
    m_editMenu = this->menuBar()->addMenu("&Edit");
    m_editMenu->addAction(m_undoAct);
    m_editMenu->addAction(m_redoAct);
    m_editMenu->addSeparator();
    m_editMenu->addAction(m_cutAct);
    m_editMenu->addAction(m_copyAct);
    m_editMenu->addAction(m_pasteAct);
    m_editMenu->addSeparator();
    QMenu* transform = m_editMenu->addMenu("&Transform");
    transform->addAction(m_translateAct);
    transform->addAction(m_rotateAct);
    transform->addAction(m_scaleAct);

    //select Menu
    m_selectMenu = this->menuBar()->addMenu("&Select");
    m_selectMenu->addAction(m_selRegionAct);
    m_selectMenu->addAction(m_selAllAct);
    m_selectMenu->addAction(m_deSelAct);
    m_selectMenu->addSeparator();
    m_selectMenu->addAction(m_convertToStenAct);

    m_showDebugWinAct = new QAction("Debug", this);

    m_viewMenu = this->menuBar()->addMenu("&View");
    m_viewMenu->addAction(m_zoomInAct);
    m_viewMenu->addAction(m_zoomOutAct);
    m_viewMenu->addAction(m_resetZoomAct);
    m_viewMenu->addSeparator();
    m_dockWinMenu = m_viewMenu->addMenu("Dock Windows");
    m_dockWinMenu->addAction(m_showBrushDockWinAct);
    m_dockWinMenu->addAction(m_showColorDockWinAct);
    m_dockWinMenu->addAction(m_showTimeDockWinAct);
    m_dockWinMenu->addAction(m_showToolsDockAct);
    m_viewMenu->addSeparator();
    m_viewMenu->addAction(m_preferenceAct);

    //Help Menu
    m_helpMenu = this->menuBar()->addMenu("&Help");
    m_helpMenu->addAction(m_sendFeedbackAct);
    m_helpMenu->addAction(m_showDebugWinAct);
#ifdef Q_OS_WIN32
    m_helpMenu->addAction(m_updateAct);
#endif
    m_helpMenu->addSeparator();
    m_helpMenu->addAction(m_aboutAct);

    m_eyeDropper = new QShortcut(QKeySequence(Qt::ALT), this);

    m_toolBar->addAction(m_undoAct);
    m_toolBar->addAction(m_redoAct);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_eyedropTool);
    m_toolBar->addAction(m_brushTool);
    m_toolBar->addAction(m_eraserTool);
    m_toolBar->addAction(m_textTool);
    m_toolBar->addAction(m_primTool);
    m_toolBar->addAction(m_fillTool);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_zoomInAct);
    m_toolBar->addAction(m_zoomOutAct);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_preferenceAct);

    m_StatBar = this->statusBar();
    this->setStatusBar(m_StatBar);
    m_activeToolLabel = new QLabel(this);
    m_activeToolLabel->setText("Odessa");
    m_StatBar->addWidget(m_activeToolLabel);
    m_StatBar->addAction(m_zoomInAct);
    m_StatBar->addAction(m_zoomOutAct);

    connect(m_newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    connect(m_openAct, SIGNAL(triggered()), SLOT(openProject()));
    connect(m_preferenceAct, SIGNAL(triggered()),SLOT(showPrefWin()));
    connect(m_undoAct, SIGNAL(triggered()), m_Editor, SLOT(undo()));
    connect(m_redoAct, SIGNAL(triggered()), m_Editor, SLOT(redo()));
    connect(m_copyAct, SIGNAL(triggered()), m_Editor, SLOT(copy()));
    connect(m_cutAct, SIGNAL(triggered()), m_Editor, SLOT(cut()));
    connect(m_pasteAct, SIGNAL(triggered()), m_Editor, SLOT(paste()));
    connect(m_selRegionAct, SIGNAL(triggered()), SLOT(assignRectSelectTool()));
    connect(m_deSelAct, SIGNAL(triggered()), SLOT(assignDeselectTool()));
    connect(m_cursorTool, SIGNAL(triggered()), SLOT(assignCursorTool()));
    connect(m_brushTool, SIGNAL(triggered()), SLOT(assignBrushTool()));
    connect(m_eraserTool, SIGNAL(triggered()), SLOT(assignEraserTool()));
    connect(m_textTool, SIGNAL(triggered()), SLOT(assignTextTool()));
    connect(m_translateAct, SIGNAL(triggered()), SLOT(assignTransformTool()));
    connect(m_rotateAct, SIGNAL(triggered()), SLOT(assignTransformTool()));
    connect(m_scaleAct, SIGNAL(triggered()), SLOT(assignTransformTool()));
    connect(m_primTool, SIGNAL(triggered()), SLOT(assignPrimitiveTool()));
    connect(m_newDiag, SIGNAL(newProject(ProjectInfo&)), m_Editor, SLOT(newProject(ProjectInfo&)));
    connect(m_newDiag, SIGNAL(newProject(ProjectInfo&)), SLOT(newProject(ProjectInfo&)));
    connect(m_prefDiag, SIGNAL(projectPathChanged(QString)), SLOT(setProjectPath(QString)));
    connect(m_prefDiag, SIGNAL(historyStepsChanged(int)), m_Editor, SLOT(setHistoyStep(int)));
    connect(m_exportImgAct, SIGNAL(triggered()), SLOT(exportImage()));
    connect(m_exportSelAct, SIGNAL(triggered()), SLOT(exportSelection()));
    connect(m_zoomInAct, SIGNAL(triggered()), SLOT(zoomIn()));
    connect(m_zoomOutAct, SIGNAL(triggered()), SLOT(zoomOut()));
    connect(m_resetZoomAct, SIGNAL(triggered()), m_Editor, SLOT(resetScale()));
    connect(m_showBrushDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowBrushDock(bool)));
    connect(m_showColorDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowColorDock(bool)));
    connect(m_showTimeDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowTimelineDock(bool)));
    connect(m_showToolsDockAct, SIGNAL(toggled(bool)), SLOT(toggleShowToolsDock(bool)));
    connect(m_prefDiag, SIGNAL(historyStepsChanged(int)), m_Editor, SLOT(setHistoryLimit(int)));
    connect(m_brushDock, SIGNAL(brushSizeChanged(int)), m_Editor, SLOT(setBrushSize(int)));
    connect(m_brushDock, SIGNAL(brushOpacityChanged(int)), m_Editor, SLOT(setOpacity(int)));
    connect(m_brushDock, SIGNAL(brushStencilChanged(QPixmap)), m_Editor, SLOT(setBrushStencil(QPixmap)));
    connect(m_brushDock, SIGNAL(brushSpacingChanged(int)), m_Editor, SLOT(setBrushSpacing(int)));
    connect(m_brushDock, SIGNAL(brushTransferSizeChanged(int)), m_Editor, SLOT(setSizeTransfer(int)));
    connect(m_brushDock, SIGNAL(brushTransferOpacityChanged(int)), m_Editor, SLOT(setOpacityTransfer(int)));
    connect(m_colorDock, SIGNAL(redChanged(int)), m_Editor, SLOT(setRedValue(int)));
    connect(m_colorDock, SIGNAL(greenChanged(int)), m_Editor, SLOT(setGreenValue(int)));
    connect(m_colorDock, SIGNAL(blueChanged(int)), m_Editor, SLOT(setBlueValue(int)));
    connect(m_layerDock, SIGNAL(layerAdded()), m_Editor, SLOT(addLayer()));
    connect(m_layerDock, SIGNAL(layerChanged(int)), m_Editor, SLOT(setLayerIndex(int)));
    connect(m_layerDock, SIGNAL(opacityChanged(int)), m_Editor, SLOT(setLayerOpacity(int)));
    connect(m_layerDock, SIGNAL(toggleLayerVisible(bool)), m_Editor, SLOT(setLayerVisible(bool)));
    connect(m_toolPanel, SIGNAL(useWorldTransform(bool)), m_Editor, SLOT(useWorldTransform(bool)));
    connect(m_toolPanel, SIGNAL(translateChanged(int,int)), m_Editor, SLOT(setClipTranslate(int,int)));
    connect(m_toolPanel, SIGNAL(rotateChanged(int)), m_Editor, SLOT(setClipRotate(int)));
    connect(m_toolPanel, SIGNAL(scaleChanged(int,int)), m_Editor, SLOT(setClipScale(int,int)));
    connect(m_toolPanel, SIGNAL(actionCommitted()), m_Editor, SLOT(commitChanges()));
    connect(m_toolPanel, SIGNAL(fontChanged(QFont)), m_Editor, SLOT(setFont(QFont)));
    connect(m_toolPanel, SIGNAL(fontSizeChanged(int)), m_Editor, SLOT(setFontSize(int)));
    connect(m_toolPanel, SIGNAL(fontBoldChanged(bool)), m_Editor, SLOT(setBold(bool)));
    connect(m_toolPanel, SIGNAL(fontItalicChanged(bool)), m_Editor, SLOT(setItalic(bool)));
    connect(m_toolPanel, SIGNAL(fontUnderlineChanged(bool)), m_Editor, SLOT(setUnderline(bool)));
    connect(m_Editor, SIGNAL(brushSizeChanged(int)), m_brushDock, SLOT(updateSize(int)));
    connect(m_Editor, SIGNAL(brushOpacityChanged(int)), m_brushDock, SLOT(updateOpacity(int)));
    connect(m_Editor, SIGNAL(redChanged(int)), m_colorDock, SLOT(updateRed(int)));
    connect(m_Editor, SIGNAL(greenChanged(int)), m_colorDock, SLOT(updateGreen(int)));
    connect(m_Editor, SIGNAL(blueChanged(int)), m_colorDock, SLOT(updateBlue(int)));
    connect(m_Editor, SIGNAL(clipTranslateChanged(int,int)), m_toolPanel, SLOT(updateTranslate(int,int)));
    connect(m_Editor, SIGNAL(clipRotateChanged(int)), m_toolPanel, SLOT(updateRotate(int)));
    connect(m_Editor, SIGNAL(clipScaleChanged(int,int)), m_toolPanel, SLOT(updateScale(int,int)));
    connect(m_Editor, SIGNAL(toolChanged(int)), m_toolPanel, SLOT(setMode(int)));
    connect(m_Editor, SIGNAL(boldToggled()), m_toolPanel, SLOT(toggleBold()));
    connect(m_Editor, SIGNAL(italicToggled()), m_toolPanel, SLOT(toggleItalic()));
    connect(m_Editor, SIGNAL(underlineToggled()), m_toolPanel, SLOT(toggleUnderline()));
    connect(m_Editor, SIGNAL(mousePositionChanged(QPoint)), m_debugWin, SLOT(updateMousePosition(QPoint)));
    connect(m_Editor, SIGNAL(brushPressureChanged(qreal)), m_debugWin, SLOT(updateActualPressure(qreal)));
    connect(m_Editor, SIGNAL(currentIndexChanged(int)), m_debugWin, SLOT(updateCurrentIndex(int)));
    connect(m_Editor, SIGNAL(currentFrameChanged(int)), m_debugWin, SLOT(updateCurrentFrame(int)));
    connect(m_Editor, SIGNAL(curToolPressureChanged(qreal)), m_debugWin, SLOT(updateActualPressure(qreal)));
    connect(m_Editor, SIGNAL(historyLimitChanged(int)), m_debugWin, SLOT(updateHistoryLimit(int)));
    connect(m_Editor, SIGNAL(historySizeChanged(int)), m_debugWin, SLOT(updateHistoryStack(int)));
    connect(m_Editor, SIGNAL(brushToolSelected()), SLOT(assignBrushTool()));
    connect(m_Editor, SIGNAL(eraserToolSelected()), SLOT(assignEraserTool()));
    connect(m_Editor, SIGNAL(cursorToolSelected()), SLOT(assignCursorTool()));
    connect(m_Editor, SIGNAL(layerPreviewChanged(int,QPixmap)), m_layerDock, SLOT(updateLayerPreview(int,QPixmap)));
    connect(m_eyedropTool, SIGNAL(triggered()), SLOT(assignEyeDropperTool()));
    connect(m_eyeDropper, SIGNAL(activated()), SLOT(assignEyeDropperTool()));
    connect(m_showDebugWinAct, SIGNAL(triggered()), SLOT(showDebugWin()));
    connect(m_fillTool, SIGNAL(triggered()), SLOT(assignFillTool()));
    connect(m_sendFeedbackAct, SIGNAL(triggered()), SLOT(sendFeedBack()));
    connect(m_aboutAct, SIGNAL(triggered()), SLOT(about()));
    connect(m_closeAct, SIGNAL(triggered()), SLOT(close()));

    addDockWidget(Qt::RightDockWidgetArea, m_brushDock);
    addDockWidget(Qt::RightDockWidgetArea, m_colorDock);
    tabifyDockWidget(m_brushDock, m_colorDock);
    addDockWidget(Qt::BottomDockWidgetArea, m_timeDock);
    addDockWidget(Qt::RightDockWidgetArea, m_layerDock);
    addDockWidget(Qt::RightDockWidgetArea, m_toolPanel);
    tabifyDockWidget(m_layerDock, m_toolPanel);

    m_isModified = false;
}

void MainWindow::setUseDark(bool v){
    m_useDark = v;
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::openProject(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", m_projectPath);
    if(fileName.isNull()){
        QMessageBox msgBox(this);
        msgBox.exec();
    }
    //Open File if it is legitimate

}

void MainWindow::saveProjectAs(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save Project", m_projectPath);
    if(fileName.isNull()){
        QMessageBox msgBox(this);
        msgBox.exec();
    }
}

void MainWindow::saveProject(){

}

void MainWindow::showNewDocWin()
{
    m_newDiag->exec();
}

void MainWindow::showPrefWin()
{
    m_prefDiag->exec();
}

void MainWindow::about()
{
    QMessageBox msgbox(this);
    msgbox.setTextFormat(Qt::RichText);
    msgbox.setText("Odessa Ver. 0.0.90<br>Swing Innovations<br><a href=\"http://www.swinginnovations.com\">Swing Innovations Website</a>""<br>Copyright &copy; 2015 <br> Test Build || Use at your own risk!");
    msgbox.exec();
}

void MainWindow::newProject(ProjectInfo &info){
    m_layerDock->reset();
    if(info.getType() != 2){
        m_showTimeDockWinAct->setChecked(false);
        m_timeDock->close();
    }
}

void MainWindow::changeStatusMessage(QString message){
   m_activeToolLabel->setText(message);
}

void MainWindow::toggleShowBrushDock(bool val)
{
    if(val)
    {
        m_brushDock->show();
    }else{
        m_brushDock->close();
    }
}

void MainWindow::toggleShowColorDock(bool val)
{
    if(val)
    {
        m_colorDock->show();
    }else{
        m_colorDock->close();
    }
}

void MainWindow::toggleShowTimelineDock(bool val)
{
    if(val)
    {
        m_timeDock->show();
    }else{
        m_timeDock->hide();
    }
}

void MainWindow::toggleShowToolsDock(bool s){
    m_toolPanel->setVisible(s);
}

void MainWindow::assignBrushTool()
{
    m_Editor->setBrush(Editor::BRUSH_TOOL);
    changeStatusMessage("Current Tool: Brush");
    m_debugWin->updateCurrentTool("Brush");
}

void MainWindow::assignEraserTool()
{
    m_Editor->setBrush(Editor::ERASER_TOOL);
    changeStatusMessage("Current Tool: Eraser");
    m_debugWin->updateCurrentTool("Eraser");
}

void MainWindow::assignTextTool()
{
    m_Editor->setBrush(Editor::TEXT_TOOL);
    changeStatusMessage("Current Tool: Text");
    m_debugWin->updateCurrentTool("Text");
    if(m_toolPanel->isHidden()) m_toolPanel->show();
}

void MainWindow::assignPrimitiveTool()
{
    m_Editor->setBrush(Editor::PRIMITIVE_TOOL);
    changeStatusMessage("Current Tool: Primitive");
    m_debugWin->updateCurrentTool("Primitive");
    if(m_toolPanel->isHidden()) m_toolPanel->show();
}

void MainWindow::assignFillTool(){
    m_Editor->setBrush(Editor::FILL_TOOL);
    changeStatusMessage("Current Tool: Fill");
    m_debugWin->updateCurrentTool("Fill");
}

void MainWindow::assignDeselectTool(){

}

void MainWindow::assignTransformTool(){
    m_Editor->setBrush(Editor::TRANSFORM_TRANSLATE);
    changeStatusMessage("Current Tool: Transform");
    m_debugWin->updateCurrentTool("Transform");
    if(m_toolPanel->isHidden()) m_toolPanel->show();
}

void MainWindow::assignRectSelectTool(){
    changeStatusMessage("Current Tool: Select");
    m_debugWin->updateCurrentTool("Select");
    m_Editor->setBrush(Editor::RECT_SELECT_TOOL);
}

void MainWindow::assignEyeDropperTool()
{
    changeStatusMessage("Current Tool: Eyedropper");
    m_Editor->setBrush(Editor::EYEDROPPER_TOOL);
    m_debugWin->updateCurrentTool("Eye Dropper");
}

void MainWindow::assignCursorTool(){
    changeStatusMessage("Current Tool: Cursor");
    m_Editor->setBrush(Editor::CURSOR_TOOL);
    m_debugWin->updateCurrentTool("Cursor");
}

void MainWindow::setProjectPath(QString val){
    m_projectPath = val;
}

void MainWindow::zoomIn()
{
    m_scaleFactor += 0.1;
    scaleImage(m_scaleFactor);
}

void MainWindow::zoomOut()
{
    m_scaleFactor -= 0.1;
    scaleImage(m_scaleFactor);
}

void MainWindow::exportImage(){
    QString saveName = QFileDialog::getSaveFileName(this, "Save File.", QDir::currentPath(), ".png");
    QImage pix = m_Editor->getCurrentImage().toImage();
    int DPI = m_Editor->getProjectInfo().getDPI();
    pix.setDotsPerMeterX(DPI);
    pix.setDotsPerMeterY(DPI);
    pix.save(saveName);
}

void MainWindow::exportSelection(){
    QString saveName = QFileDialog::getSaveFileName(this, "Save File.", QDir::currentPath(), ".png");
    QImage img = m_Editor->getSelectionPixmap().toImage();
    img.setDotsPerMeterX(m_Editor->getProjectInfo().getDPI());
    img.setDotsPerMeterY(m_Editor->getProjectInfo().getDPI());
    img.save(saveName);
}

void MainWindow::sendFeedBack(){
    QDesktopServices::openUrl(QUrl("mailto:swinginnovations@gmail.com?subject=Odessa-Feedback"));
}

void MainWindow::scaleImage(double val)
{
    //Q_ASSERT(m_Editor->pixmap());
    m_Editor->scale(m_scaleFactor);
    adjustScrollBar(m_workArea->horizontalScrollBar(), val);
    adjustScrollBar(m_workArea->verticalScrollBar(), val);
}

void MainWindow::showDebugWin(){
    m_debugWin->show();
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::readSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    m_projectPath = settings.value("projectPath").toString();
    restoreGeometry(settings.value("windowGeom").toByteArray());
}

void MainWindow::writeSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    qDebug()<<"Project Path" << m_projectPath+"/Brush/" << endl;
    settings.setValue("projectPath", m_projectPath);
    settings.setValue("windowGeom", saveGeometry());
}

void MainWindow::selectToStencil(){
    //Convert Selection to stencil
    QPixmap pix = m_Editor->getSelectionPixmap();
    if(!pix.isNull()){

    }
}

