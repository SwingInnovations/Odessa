#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    readSettings();
    if(projectPath.isEmpty()){
        QMessageBox projectMsgBx;
        projectMsgBx.setText("No Project Path set");
        projectMsgBx.setInformativeText("You must set a project path.");
        projectMsgBx.setStandardButtons(QMessageBox::Ok);
        projectMsgBx.setDefaultButton(QMessageBox::Ok);
        int ret = projectMsgBx.exec();
        switch(ret){
            case QMessageBox::Ok:
                projectPath = QFileDialog::getExistingDirectory(this, "Set Project Path", QDir::currentPath());
                break;
        default:
            break;
        }
    }else{
        QDir dir(projectPath);
        dir.mkpath("Brush");
    }
    
    m_Editor = new Editor(this);
    m_Editor->setAlignment(Qt::AlignCenter);
    m_Editor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_Editor->setFocusPolicy(Qt::ClickFocus);
    m_Editor->setScaledContents(true);

    imageArea = new QScrollArea(this);
    imageArea->setAlignment(Qt::AlignCenter);
    imageArea->setWidget(m_Editor);
    setCentralWidget(imageArea);

    m_Editor->setStyleSheet("background-color: rgb(53, 53, 53);");

    toolBar = this->addToolBar("Tools");
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::TopToolBarArea);

    mToolQuickSelect = new QComboBox(this);
    mToolQuickSelect->addItem("Brush");
    mToolQuickSelect->addItem("Eraser");
    mToolQuickSelect->addItem("Fill");

    toolBar->addWidget(mToolQuickSelect);

    newDialogWin = new OdessaNewDocDialog();
    prefDialog = new OdessaPrefDialog();
    brushDockWidget = new BrushDockWidget(this);
    brushDockWidget->setWindowTitle("Brush");
    brushDockWidget->setDirectory(projectPath+"/Brush/");
    brushDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_Editor->setBrush(brushDockWidget->getStartBrush());

    colorDockWidget = new ColorDockWidget(this);
    colorDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    timelineDockWidget = new TimelineDockWidget(this);
    timelineDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    timelineDockWidget->setVisible(false);

    layerDockWidget = new LayerDockWidget(this);
    layerDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    toolPanelWidget = new ToolsPanel(this);
    toolPanelWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    toolPanelWidget->setVisible(false);
    cursorTool = new QAction("Cursor", this);
    cursorTool->setShortcut(QKeySequence(Qt::Key_Escape));
    brushTool = new QAction(this);
    brushTool->setText("Brush");
    eraserTool = new QAction(this);
    eraserTool->setText("Eraser");
    textTool = new QAction(this);
    textTool->setText("Text");
    primitiveTool = new QAction(this);
    primitiveTool->setText("Prim");
    eyeDropperTool = new QAction(this);
    eyeDropperTool->setText("EyeDropper");
    fillTool = new QAction("Fill", this);

    toolBar->addAction(eyeDropperTool);
    toolBar->addAction(brushTool);
    toolBar->addAction(eraserTool);
    toolBar->addAction(textTool);
    toolBar->addAction(primitiveTool);
    toolBar->addAction(fillTool);

    scaleFactor = 1.0;

    /*-File Menu Actions-*/
    newAct = new QAction("&New", this);
    newAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    newAct->setIcon(QIcon(":/icon/resource/temp_New.svg"));
    openAct = new QAction("&Open", this);
    openAct->setIcon(QIcon(":/icon/resource/temp_Open.svg"));
    openAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    saveAct = new QAction("&Save", this);
    saveAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    saveAsAct = new QAction("&Save As...", this);
    saveAsAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    exportImgAct = new QAction("&Image", this);
    exportSelectionAct = new QAction("&Selection", this);
    exportSpriteSheetAct = new QAction("&Sprite Sheet", this);
    exportImgSeqAct = new QAction("&Sequence", this);
    exportAnimAct = new QAction("&Animation", this);
    aboutAct = new QAction("&About", this);
    closeAct = new QAction("&Close", this);
    closeAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    //edit Actions
    undoAct = new QAction(this);
    undoAct->setText("&Undo");
    undoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    redoAct = new QAction(this);
    redoAct->setText("&Redo");
    redoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    cutAct = new QAction(this);
    cutAct->setText("&Cut");
    cutAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    copyAct = new QAction(this);
    copyAct->setText("&Copy");
    copyAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    pasteAct = new QAction(this);
    pasteAct->setText("&Paste");
    pasteAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));

    sendFeedbackAct = new QAction(this);
    sendFeedbackAct->setText("&Send Feedback");

    updateAct = new QAction(this);
    updateAct->setText("&Check for updates...");

    //Select Menu
    selectRegionAct = new QAction(this);
    selectRegionAct->setText("&Select Region");
    selectAllAct = new QAction(this);
    selectAllAct->setText("&Select All");
    deselectAct = new QAction(this);
    deselectAct->setText("&Deselect");

    preferenceAct = new QAction("Preferences", this);
    preferenceAct->setIcon(QIcon(":/icon/resource/settings_lite.svg"));
    showBrushDockWinAct = new QAction("Show BrushDock", this);
    showBrushDockWinAct->setCheckable(true);
    showBrushDockWinAct->setChecked(true);
    showColorDockWinAct = new QAction("Color", this);
    showColorDockWinAct->setCheckable(true);
    showColorDockWinAct->setChecked(true);
    showTimeDockWinAct = new QAction("Timeline", this);
    showTimeDockWinAct->setCheckable(true);
    showToolsDockAct = new QAction("Tools", this);
    showToolsDockAct->setCheckable(true);
    showToolsDockAct->setChecked(false);
    zoomInAct = new QAction("&Zoom In",this);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setIcon(QIcon(":/icon/resource/zoom_In_lite.svg"));
    zoomOutAct = new QAction("&Zoom Out", this);
    zoomOutAct->setShortcut(QKeySequence(QKeySequence::ZoomOut));
    zoomOutAct->setIcon(QIcon(":/icon/resource/zoom_Out_lite.svg"));
    resetZoomAct = new QAction("&Reset Zoom", this);
    resetZoomAct->setShortcut(QKeySequence(Qt::Key_Home));

    translateAct = new QAction("&Translate", this);
    rotateAct = new QAction("&Rotate", this);
    scaleAct = new QAction("&Scale", this);

    fileMenu = this->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    exportMenu = new QMenu("&Export", this);
    exportMenu->addAction(exportImgAct);
    exportMenu->addAction(exportSelectionAct);
    exportMenu->addAction(exportSpriteSheetAct);
    exportMenu->addAction(exportImgSeqAct);
    exportMenu->addAction(exportAnimAct);
    fileMenu->addMenu(exportMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    //edit Menu
    editMenu = this->menuBar()->addMenu("&Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    QMenu* transform = editMenu->addMenu("&Transform");
    transform->addAction(translateAct);
    transform->addAction(rotateAct);
    transform->addAction(scaleAct);

    //select Menu
    selectMenu = this->menuBar()->addMenu("&Select");
    selectMenu->addAction(selectRegionAct);
    selectMenu->addAction(selectAllAct);
    selectMenu->addAction(deselectAct);

    viewMenu = this->menuBar()->addMenu("&View");
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(resetZoomAct);
    viewMenu->addSeparator();
    dockWinMenu = viewMenu->addMenu("Dock Windows");
    dockWinMenu->addAction(showBrushDockWinAct);
    dockWinMenu->addAction(showColorDockWinAct);
    dockWinMenu->addAction(showTimeDockWinAct);
    dockWinMenu->addAction(showToolsDockAct);
    viewMenu->addSeparator();
    viewMenu->addAction(preferenceAct);

    //Help Menu
    helpMenu = this->menuBar()->addMenu("&Help");
    helpMenu->addAction(sendFeedbackAct);
#ifdef Q_OS_WIN32
    helpMenu->addAction(updateAct);
#endif
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);

    eyeDropper = new QShortcut(QKeySequence(Qt::ALT), this);

    mStatBar = this->statusBar();
    this->setStatusBar(mStatBar);
    activeToolLabel = new QLabel(this);
    activeToolLabel->setText("Odessa");
    mStatBar->addWidget(activeToolLabel);
    mStatBar->addAction(zoomInAct);
    mStatBar->addAction(zoomOutAct);

    connect(newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    connect(preferenceAct, SIGNAL(triggered()),SLOT(showPrefWin()));
    connect(undoAct, SIGNAL(triggered()), m_Editor, SLOT(undo()));
    connect(redoAct, SIGNAL(triggered()), m_Editor, SLOT(redo()));
    connect(copyAct, SIGNAL(triggered()), m_Editor, SLOT(copy()));
    connect(cutAct, SIGNAL(triggered()), m_Editor, SLOT(cut()));
    connect(pasteAct, SIGNAL(triggered()), m_Editor, SLOT(paste()));
    connect(selectRegionAct, SIGNAL(triggered()), SLOT(assignRectSelectTool()));
    connect(deselectAct, SIGNAL(triggered()), SLOT(assignDeselectTool()));
    connect(cursorTool, SIGNAL(triggered()), SLOT(assignCursorTool()));
    connect(brushTool, SIGNAL(triggered()), SLOT(assignBrushTool()));
    connect(eraserTool, SIGNAL(triggered()), SLOT(assignEraserTool()));
    connect(textTool, SIGNAL(triggered()), SLOT(assignTextTool()));
    connect(translateAct, SIGNAL(triggered()), SLOT(assignTransformTool()));
    connect(rotateAct, SIGNAL(triggered()), SLOT(assignTransformTool()));
    connect(scaleAct, SIGNAL(triggered()), SLOT(assignTransformTool()));
    connect(primitiveTool, SIGNAL(triggered()), SLOT(assignPrimitiveTool()));
    connect(newDialogWin, SIGNAL(newProject(ProjectInfo&)), m_Editor, SLOT(newProject(ProjectInfo&)));
    connect(newDialogWin, SIGNAL(newProject(ProjectInfo&)), SLOT(newProject(ProjectInfo&)));
    connect(prefDialog, SIGNAL(projectPathChanged(QString)), SLOT(setProjectPath(QString)));
    connect(prefDialog, SIGNAL(historyStepsChanged(int)), m_Editor, SLOT(setHistoyStep(int)));
    connect(exportImgAct, SIGNAL(triggered()), SLOT(exportImage()));
    connect(exportSelectionAct, SIGNAL(triggered()), SLOT(exportSelection()));
    connect(zoomInAct, SIGNAL(triggered()), SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), SLOT(zoomOut()));
    connect(resetZoomAct, SIGNAL(triggered()), m_Editor, SLOT(resetScale()));
    connect(showBrushDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowBrushDock(bool)));
    connect(showColorDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowColorDock(bool)));
    connect(showTimeDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowTimelineDock(bool)));
    connect(showToolsDockAct, SIGNAL(toggled(bool)), SLOT(toggleShowToolsDock(bool)));
    connect(brushDockWidget, SIGNAL(brushSizeChanged(int)), m_Editor, SLOT(setBrushSize(int)));
    connect(brushDockWidget, SIGNAL(brushOpacityChanged(int)), m_Editor, SLOT(setOpacity(int)));
    connect(brushDockWidget, SIGNAL(brushStencilChanged(QPixmap)), m_Editor, SLOT(setBrushStencil(QPixmap)));
    connect(brushDockWidget, SIGNAL(brushSpacingChanged(int)), m_Editor, SLOT(setBrushSpacing(int)));
    connect(brushDockWidget, SIGNAL(brushTransferSizeChanged(int)), m_Editor, SLOT(setSizeTransfer(int)));
    connect(brushDockWidget, SIGNAL(brushTransferOpacityChanged(int)), m_Editor, SLOT(setOpacityTransfer(int)));
    connect(colorDockWidget, SIGNAL(redChanged(int)), m_Editor, SLOT(setRedValue(int)));
    connect(colorDockWidget, SIGNAL(greenChanged(int)), m_Editor, SLOT(setGreenValue(int)));
    connect(colorDockWidget, SIGNAL(blueChanged(int)), m_Editor, SLOT(setBlueValue(int)));
    connect(layerDockWidget, SIGNAL(layerAdded()), m_Editor, SLOT(addLayer()));
    connect(layerDockWidget, SIGNAL(layerChanged(int)), m_Editor, SLOT(setLayerIndex(int)));
    connect(layerDockWidget, SIGNAL(opacityChanged(int)), m_Editor, SLOT(setLayerOpacity(int)));
    connect(toolPanelWidget, SIGNAL(useWorldTransform(bool)), m_Editor, SLOT(useWorldTransform(bool)));
    connect(toolPanelWidget, SIGNAL(translateChanged(int,int)), m_Editor, SLOT(setClipTranslate(int,int)));
    connect(toolPanelWidget, SIGNAL(rotateChanged(int)), m_Editor, SLOT(setClipRotate(int)));
    connect(toolPanelWidget, SIGNAL(scaleChanged(int,int)), m_Editor, SLOT(setClipScale(int,int)));
    connect(toolPanelWidget, SIGNAL(actionCommitted()), m_Editor, SLOT(commitChanges()));
    connect(toolPanelWidget, SIGNAL(fontChanged(QFont)), m_Editor, SLOT(setFont(QFont)));
    connect(toolPanelWidget, SIGNAL(fontSizeChanged(int)), m_Editor, SLOT(setFontSize(int)));
    connect(toolPanelWidget, SIGNAL(fontBoldChanged(bool)), m_Editor, SLOT(setBold(bool)));
    connect(toolPanelWidget, SIGNAL(fontItalicChanged(bool)), m_Editor, SLOT(setItalic(bool)));
    connect(toolPanelWidget, SIGNAL(fontUnderlineChanged(bool)), m_Editor, SLOT(setUnderline(bool)));
    connect(m_Editor, SIGNAL(brushSizeChanged(int)), brushDockWidget, SLOT(updateSize(int)));
    connect(m_Editor, SIGNAL(brushOpacityChanged(int)), brushDockWidget, SLOT(updateOpacity(int)));
    connect(m_Editor, SIGNAL(redChanged(int)), colorDockWidget, SLOT(updateRed(int)));
    connect(m_Editor, SIGNAL(greenChanged(int)), colorDockWidget, SLOT(updateGreen(int)));
    connect(m_Editor, SIGNAL(blueChanged(int)), colorDockWidget, SLOT(updateBlue(int)));
    connect(m_Editor, SIGNAL(clipTranslateChanged(int,int)), toolPanelWidget, SLOT(updateTranslate(int,int)));
    connect(m_Editor, SIGNAL(clipRotateChanged(int)), toolPanelWidget, SLOT(updateRotate(int)));
    connect(m_Editor, SIGNAL(clipScaleChanged(int,int)), toolPanelWidget, SLOT(updateScale(int,int)));
    connect(m_Editor, SIGNAL(toolChanged(int)), toolPanelWidget, SLOT(setMode(int)));
    connect(eyeDropperTool, SIGNAL(triggered()), SLOT(assignEyeDropperTool()));
    connect(eyeDropper, SIGNAL(activated()), SLOT(assignEyeDropperTool()));
    connect(fillTool, SIGNAL(triggered()), SLOT(assignFillTool()));
    connect(sendFeedbackAct, SIGNAL(triggered()), SLOT(sendFeedBack()));
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
    connect(closeAct, SIGNAL(triggered()), SLOT(close()));

    addDockWidget(Qt::RightDockWidgetArea, brushDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, colorDockWidget);
    tabifyDockWidget(brushDockWidget, colorDockWidget);
    addDockWidget(Qt::BottomDockWidgetArea, timelineDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, layerDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, toolPanelWidget);
    tabifyDockWidget(layerDockWidget, toolPanelWidget);

    isModified = false;
    resize(1024,768);
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::showNewDocWin()
{
    newDialogWin->exec();
}

void MainWindow::showPrefWin()
{
    prefDialog->exec();
}

void MainWindow::about()
{
    QMessageBox msgbox(this);
    msgbox.setTextFormat(Qt::RichText);
    msgbox.setText("Odessa Ver. 0.0.90<br>Swing Innovations<br><a href=\"http://www.swinginnovations.com\">Swing Innovations Website</a>""<br>Copyright &copy; 2015 <br> Test Build || Use at your own risk!");
    msgbox.exec();
}

void MainWindow::newProject(ProjectInfo &info){
    layerDockWidget->reset();
    if(info.getType() != 2){
        showTimeDockWinAct->setChecked(false);
        timelineDockWidget->close();
    }
}

void MainWindow::changeStatusMessage(QString message){
   activeToolLabel->setText(message);
}

void MainWindow::toggleShowBrushDock(bool val)
{
    if(val)
    {
        brushDockWidget->show();
    }else{
        brushDockWidget->close();
    }
}

void MainWindow::toggleShowColorDock(bool val)
{
    if(val)
    {
        colorDockWidget->show();
    }else{
        colorDockWidget->close();
    }
}

void MainWindow::toggleShowTimelineDock(bool val)
{
    if(val)
    {
        timelineDockWidget->show();
    }else{
        timelineDockWidget->hide();
    }
}

void MainWindow::toggleShowToolsDock(bool s){
    toolPanelWidget->setVisible(s);
}

void MainWindow::assignBrushTool()
{
    m_Editor->setBrush(Editor::BRUSH_TOOL);
    changeStatusMessage("Current Tool: Brush");
}

void MainWindow::assignEraserTool()
{
    m_Editor->setBrush(Editor::ERASER_TOOL);
    changeStatusMessage("Current Tool: Eraser");
}

void MainWindow::assignTextTool()
{
    m_Editor->setBrush(Editor::TEXT_TOOL);
    changeStatusMessage("Current Tool: Text");
}

void MainWindow::assignPrimitiveTool()
{
    m_Editor->setBrush(Editor::PRIMITIVE_TOOL);
    changeStatusMessage("Current Tool: Prim");
}

void MainWindow::assignFillTool(){
    m_Editor->setBrush(Editor::FILL_TOOL);
    changeStatusMessage("Current Tool: Fill");
}

void MainWindow::assignDeselectTool(){

}

void MainWindow::assignTransformTool(){
    m_Editor->setBrush(Editor::TRANSFORM_TRANSLATE);
    changeStatusMessage("Current Tool: Transform");
    if(toolPanelWidget->isHidden()) toolPanelWidget->show();
}

void MainWindow::assignRectSelectTool(){
    changeStatusMessage("Current Tool: Select");
    m_Editor->setBrush(Editor::RECT_SELECT_TOOL);
}

void MainWindow::assignEyeDropperTool()
{
    changeStatusMessage("Current Tool: Eyedropper");
    m_Editor->setBrush(Editor::EYEDROPPER_TOOL);
}

void MainWindow::assignCursorTool(){
    changeStatusMessage("Current Tool: Cursor");
    m_Editor->setBrush(Editor::CURSOR_TOOL);
}

void MainWindow::setProjectPath(QString val){
    projectPath = val;
}

void MainWindow::zoomIn()
{
    scaleFactor += 0.1;
    scaleImage(scaleFactor);
}

void MainWindow::zoomOut()
{
    scaleFactor -= 0.1;
    scaleImage(scaleFactor);
}

void MainWindow::exportImage(){
    QString saveName = QFileDialog::getSaveFileName(this, "Save File.", QDir::currentPath(), ".png");
    QImage pix = m_Editor->pixmap()->toImage();
    pix.setDotsPerMeterX(m_Editor->getProjectInfo().getDPI());
    pix.setDotsPerMeterY(m_Editor->getProjectInfo().getDPI());
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
    Q_ASSERT(m_Editor->pixmap());
    m_Editor->scale(scaleFactor);
    adjustScrollBar(imageArea->horizontalScrollBar(), val);
    adjustScrollBar(imageArea->verticalScrollBar(), val);

    qDebug() << "Image Size" << m_Editor->pixmap()->size() << endl;
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::readSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    projectPath = settings.value("projectPath").toString();
    setGeometry(settings.value("windowGeom").toRect());
}

void MainWindow::writeSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    qDebug()<<"Project Path" << projectPath+"/Brush/" << endl;
    settings.setValue("projectPath", projectPath);
    settings.setValue("windowGeom", this->geometry());
}

