#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1024, 768);

    mEditor = new Editor(this);
    setCentralWidget(mEditor);

    mEditor->setStyleSheet("background-color: grey;");

    toolBar = this->addToolBar("Tools");
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::TopToolBarArea);

    newDialogWin = new OdessaNewDocDialog();
    brushDockWidget = new BrushDockWidget(this);
    brushDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    colorDockWidget = new ColorDockWidget(this);
    colorDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    timelineDockWidget = new TimelineDockWidget(this);
    timelineDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

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

    addLayerAct = new QAction(this);
    addLayerAct->setText("AddLayer");
    newAct = new QAction("&New", this);
    aboutAct = new QAction("&About", this);
    closeAct = new QAction("&Close", this);
    closeAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

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

    fileMenu = this->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    //fileMenu->addAction(addLayerAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    viewMenu = this->menuBar()->addMenu("&View");
    dockWinMenu = viewMenu->addMenu("Dock Windows");
    dockWinMenu->addAction(showBrushDockWinAct);
    dockWinMenu->addAction(showColorDockWinAct);
    dockWinMenu->addAction(showTimeDockWinAct);
    viewMenu->addSeparator();
    viewMenu->addAction(preferenceAct);

    helpMenu = this->menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAct);

    eyeDropper = new QShortcut(QKeySequence(Qt::ALT), this);

    connect(newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    //connect(addLayerAct, SIGNAL(triggered()), mEditor, SLOT(addLayer()));
    connect(brushTool, SIGNAL(triggered()), SLOT(assignBrushTool()));
    connect(eraserTool, SIGNAL(triggered()), SLOT(assignEraserTool()));
    connect(textTool, SIGNAL(triggered()), SLOT(assignTextTool()));
    connect(primitiveTool, SIGNAL(triggered()), SLOT(assignPrimitiveTool()));
    connect(newDialogWin, SIGNAL(newProject(int,int,int,int)), mEditor, SLOT(newProject(int,int,int,int)));
    connect(brushDockWidget, SIGNAL(mSizeChanged(int)), mEditor, SLOT(setBrushSize(int)));
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
    connect(eyeDropperTool, SIGNAL(triggered()), SLOT(assignEyeDropperTool()));
    connect(eyeDropper, SIGNAL(activated()), SLOT(assignEyeDropperTool()));
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
    connect(closeAct, SIGNAL(triggered()), SLOT(close()));



    addDockWidget(Qt::RightDockWidgetArea, brushDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, colorDockWidget);
    addDockWidget(Qt::BottomDockWidgetArea, timelineDockWidget);

    isModified = false;
}

MainWindow::~MainWindow()
{

}

void MainWindow::showNewDocWin()
{
    newDialogWin->exec();
}

void MainWindow::about()
{
    QMessageBox msgbox(this);
    msgbox.setTextFormat(Qt::RichText);
    msgbox.setText("Odessa Ver. 0.0.30<br>Swing Innovations<br><a href=\"http://www.swinginnovations.com\">Swing Innovations Website</a>""<br>Copyright 2014 <br> Test Build || Use at your own risk!");
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
