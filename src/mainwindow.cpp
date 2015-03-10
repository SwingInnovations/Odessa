#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    resize(1024, 768);

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
        qDebug() << projectPath << endl;
        QDir dir(projectPath);
        dir.mkpath("Brush");
    }
    
    mEditor = new Editor(this);
    mEditor->setAlignment(Qt::AlignCenter);
    mEditor->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mEditor->setScaledContents(true);

    imageArea = new QScrollArea(this);
    imageArea->setAlignment(Qt::AlignCenter);
    imageArea->setWidget(mEditor);
    setCentralWidget(imageArea);

    mEditor->setStyleSheet("background-color: rgb(53, 53, 53);");

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
    mEditor->setBrush(brushDockWidget->getStartBrush());

    colorDockWidget = new ColorDockWidget(this);
    colorDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    timelineDockWidget = new TimelineDockWidget(this);
    timelineDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    layerDockWidget = new LayerDockWidget(this);
    layerDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

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

    /*
    *
    * Temporarily disable
    *
    */
    textTool->setEnabled(false);
    primitiveTool->setEnabled(false);

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
    copyAct = new QAction(this);
    copyAct->setText("&Copy");
    pasteAct = new QAction(this);
    pasteAct->setText("&Paste");

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
    showBrushDockWinAct = new QAction("Show BrushDock", this);
    showBrushDockWinAct->setCheckable(true);
    showBrushDockWinAct->setChecked(true);
    showColorDockWinAct = new QAction("Color", this);
    showColorDockWinAct->setCheckable(true);
    showColorDockWinAct->setChecked(true);
    showTimeDockWinAct = new QAction("Timeline", this);
    showTimeDockWinAct->setCheckable(true);
    showTimeDockWinAct->setChecked(true);
    zoomInAct = new QAction("&Zoom In",this);
    zoomOutAct = new QAction("&Zoom Out", this);

    fileMenu = this->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    exportMenu = new QMenu("&Export", this);
    exportMenu->addAction(exportImgAct);
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

    //select Menu
    selectMenu = this->menuBar()->addMenu("&Select");
    selectMenu->addAction(selectRegionAct);
    selectMenu->addAction(selectAllAct);
    selectMenu->addAction(deselectAct);

    viewMenu = this->menuBar()->addMenu("&View");
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addSeparator();
    dockWinMenu = viewMenu->addMenu("Dock Windows");
    dockWinMenu->addAction(showBrushDockWinAct);
    dockWinMenu->addAction(showColorDockWinAct);
    dockWinMenu->addAction(showTimeDockWinAct);
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
    activeToolLabel->setText("FOO");
    mStatBar->addWidget(activeToolLabel);
    mStatBar->addAction(zoomInAct);
    mStatBar->addAction(zoomOutAct);

    connect(newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    connect(preferenceAct, SIGNAL(triggered()),SLOT(showPrefWin()));
    connect(undoAct, SIGNAL(triggered()), mEditor, SLOT(undo()));
    connect(redoAct, SIGNAL(triggered()), mEditor, SLOT(redo()));
    connect(brushTool, SIGNAL(triggered()), SLOT(assignBrushTool()));
    connect(eraserTool, SIGNAL(triggered()), SLOT(assignEraserTool()));
    connect(textTool, SIGNAL(triggered()), SLOT(assignTextTool()));
    connect(primitiveTool, SIGNAL(triggered()), SLOT(assignPrimitiveTool()));
    connect(newDialogWin, SIGNAL(newProject(int,int,int,int)), mEditor, SLOT(newProject(int,int,int,int)));
    connect(prefDialog, SIGNAL(projectPathChanged(QString)), SLOT(setProjectPath(QString)));
    connect(exportImgAct, SIGNAL(triggered()), SLOT(exportImage()));
    connect(zoomInAct, SIGNAL(triggered()), SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), SLOT(zoomOut()));
    connect(showBrushDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowBrushDock(bool)));
    connect(showColorDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowColorDock(bool)));
    connect(showTimeDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowTimelineDock(bool)));
    connect(brushDockWidget, SIGNAL(brushSizeChanged(int)), mEditor, SLOT(setBrushSize(int)));
    connect(brushDockWidget, SIGNAL(brushOpacityChanged(int)), mEditor, SLOT(setOpacity(int)));
    connect(brushDockWidget, SIGNAL(brushStencilChanged(QPixmap)), mEditor, SLOT(setBrushStencil(QPixmap)));
    connect(brushDockWidget, SIGNAL(brushSpacingChanged(int)), mEditor, SLOT(setBrushSpacing(int)));
    connect(brushDockWidget, SIGNAL(brushTransferSizeChanged(int)), mEditor, SLOT(setSizeTransfer(int)));
    connect(brushDockWidget, SIGNAL(brushTransferOpacityChanged(int)), mEditor, SLOT(setOpacityTransfer(int)));
    connect(colorDockWidget, SIGNAL(redChanged(int)), mEditor, SLOT(setRedValue(int)));
    connect(colorDockWidget, SIGNAL(greenChanged(int)), mEditor, SLOT(setGreenValue(int)));
    connect(colorDockWidget, SIGNAL(blueChanged(int)), mEditor, SLOT(setBlueValue(int)));
    connect(mEditor, SIGNAL(brushSizeChanged(int)), brushDockWidget, SLOT(updateSize(int)));
    connect(mEditor, SIGNAL(brushOpacityChanged(int)), brushDockWidget, SLOT(updateOpacity(int)));
    connect(mEditor, SIGNAL(redChanged(int)), colorDockWidget, SLOT(updateRed(int)));
    connect(mEditor, SIGNAL(greenChanged(int)), colorDockWidget, SLOT(updateGreen(int)));
    connect(mEditor, SIGNAL(blueChanged(int)), colorDockWidget, SLOT(updateBlue(int)));
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

    isModified = false;
    resize(1024,768);
    mEditor->setGeometry(this->centralWidget()->rect());
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
    msgbox.setText("Odessa Ver. 0.0.72<br>Swing Innovations<br><a href=\"http://www.swinginnovations.com\">Swing Innovations Website</a>""<br>Copyright 2014 <br> Test Build || Use at your own risk!");
    msgbox.exec();
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

    }else{

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

void MainWindow::assignBrushTool()
{
    mEditor->setBrush(Editor::BRUSH_TOOL);
}

void MainWindow::assignEraserTool()
{
    mEditor->setBrush(Editor::ERASER_TOOL);
}

void MainWindow::assignTextTool()
{
    mEditor->setBrush(Editor::TEXT_TOOL);
}

void MainWindow::assignPrimitiveTool()
{
    mEditor->setBrush(Editor::PRIMITIVE_TOOL);
}

void MainWindow::assignFillTool(){
    mEditor->setBrush(Editor::FILL_TOOL);
}

void MainWindow::assignEyeDropperTool()
{
    mEditor->setBrush(Editor::EYEDROPPER_TOOL);
    qDebug() << "Zing";
}

void MainWindow::setProjectPath(QString val){
    projectPath = val;
}

void MainWindow::zoomIn()
{
    scaleImage(1.5);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::exportImage(){
    QString saveName = QFileDialog::getSaveFileName(this, "Save File.", QDir::currentPath(), ".png");
    mEditor->pixmap()->save(saveName);
}

void MainWindow::sendFeedBack(){
    QDesktopServices::openUrl(QUrl("mailto:swinginnovations@gmail.com?subject=Odessa-Feedback"));
}

void MainWindow::scaleImage(double val)
{
    scaleFactor *= val;
    mEditor->scale(scaleFactor);
    adjustScrollBar(imageArea->horizontalScrollBar(), val);
    adjustScrollBar(imageArea->verticalScrollBar(), val);

    qDebug() << "Image Size" << mEditor->getPixmapSize() << endl;
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::readSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    projectPath = settings.value("projectPath").toString();
}

void MainWindow::writeSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    qDebug()<<"Project Path" << projectPath+"/Brush/" << endl;
    settings.setValue("projectPath", projectPath);
}

