#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    resize(1024, 768);

    mEditor = new Editor(this);
    mEditor->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mEditor->setScaledContents(true);

    imageArea = new QScrollArea(this);
    imageArea->setWidget(mEditor);
    setCentralWidget(imageArea);

    mEditor->setStyleSheet("background-color: grey;");
    //mEditor->resize(imageArea->size());

    toolBar = this->addToolBar("Tools");
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::TopToolBarArea);

    newDialogWin = new OdessaNewDocDialog();
    prefDialog = new OdessaPrefDialog();
    brushDockWidget = new BrushDockWidget(this);
    brushDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

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

    toolBar->addAction(eyeDropperTool);
    toolBar->addAction(brushTool);
    toolBar->addAction(eraserTool);
    toolBar->addAction(textTool);
    toolBar->addAction(primitiveTool);

    newAct = new QAction("&New", this);
    newAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
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

    helpMenu = this->menuBar()->addMenu("&Help");
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
    //connect(addLayerAct, SIGNAL(triggered()), mEditor, SLOT(addLayer()));
    connect(undoAct, SIGNAL(triggered()), mEditor, SLOT(undo()));
    connect(redoAct, SIGNAL(triggered()), mEditor, SLOT(redo()));
    connect(brushTool, SIGNAL(triggered()), SLOT(assignBrushTool()));
    connect(eraserTool, SIGNAL(triggered()), SLOT(assignEraserTool()));
    connect(textTool, SIGNAL(triggered()), SLOT(assignTextTool()));
    connect(primitiveTool, SIGNAL(triggered()), SLOT(assignPrimitiveTool()));
    connect(newDialogWin, SIGNAL(newProject(int,int,int,int)), mEditor, SLOT(newProject(int,int,int,int)));
    connect(brushDockWidget, SIGNAL(mSizeChanged(int)), mEditor, SLOT(setBrushSize(int)));
    connect(zoomInAct, SIGNAL(triggered()), SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), SLOT(zoomOut()));
    connect(showBrushDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowBrushDock(bool)));
    connect(showColorDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowColorDock(bool)));
    connect(showTimeDockWinAct, SIGNAL(toggled(bool)), SLOT(toggleShowTimelineDock(bool)));

    connect(brushDockWidget, SIGNAL(mOpacityChanged(int)), mEditor, SLOT(setOpacity(int)));
    connect(brushDockWidget, SIGNAL(mTransferSizeChanged(int)), mEditor, SLOT(setSizeTransfer(int)));
    connect(colorDockWidget, SIGNAL(redChanged(int)), mEditor, SLOT(setRedValue(int)));
    connect(colorDockWidget, SIGNAL(greenChanged(int)), mEditor, SLOT(setGreenValue(int)));
    connect(colorDockWidget, SIGNAL(blueChanged(int)), mEditor, SLOT(setBlueValue(int)));
    connect(mEditor, SIGNAL(brushSizeChanged(int)), brushDockWidget, SLOT(set_mSizeLE(int)));
    connect(mEditor, SIGNAL(redChanged(int)), colorDockWidget, SLOT(set_RLE(int)));
    connect(mEditor, SIGNAL(greenChanged(int)), colorDockWidget, SLOT(set_GLE(int)));
    connect(mEditor, SIGNAL(blueChanged(int)), colorDockWidget, SLOT(set_BLE(int)));
    connect(mEditor, SIGNAL(redChanged(int)), colorDockWidget, SLOT(setRed(int)));
    connect(mEditor, SIGNAL(greenChanged(int)), colorDockWidget, SLOT(setGreen(int)));
    connect(mEditor, SIGNAL(blueChanged(int)), colorDockWidget, SLOT(setBlue(int)));
    connect(eyeDropperTool, SIGNAL(triggered()), SLOT(assignEyeDropperTool()));
    connect(eyeDropper, SIGNAL(activated()), SLOT(assignEyeDropperTool()));
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
    connect(closeAct, SIGNAL(triggered()), SLOT(close()));

    addDockWidget(Qt::RightDockWidgetArea, brushDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, colorDockWidget);
    addDockWidget(Qt::BottomDockWidgetArea, timelineDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, layerDockWidget);

    isModified = false;
    resize(1024,768);
}

MainWindow::~MainWindow()
{

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
    msgbox.setText("Odessa Ver. 0.0.51<br>Swing Innovations<br><a href=\"http://www.swinginnovations.com\">Swing Innovations Website</a>""<br>Copyright 2014 <br> Test Build || Use at your own risk!");
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

void MainWindow::assignEyeDropperTool()
{
    mEditor->setBrush(Editor::EYEDROPPER_TOOL);
    qDebug() << "Zing";
}

void MainWindow::zoomIn()
{
    scaleImage(1.5);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::scaleImage(double val)
{
    scaleFactor *= val;
    mEditor->resize(scaleFactor * mEditor->getPixmapSize());
    mEditor->adjustSize();
    adjustScrollBar(imageArea->horizontalScrollBar(), val);
    adjustScrollBar(imageArea->verticalScrollBar(), val);

    qDebug() << "Image Size" << mEditor->getPixmapSize() << endl;
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}

