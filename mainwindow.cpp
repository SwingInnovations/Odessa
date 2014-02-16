#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1024, 768);

    mEditor = new Editor(this);
    setCentralWidget(mEditor);
    mEditor->setStyleSheet("background-color: grey;");

    newDialogWin = new OdessaNewDocDialog();
    brushDockWidget = new BrushDockWidget(this);
    brushDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    addLayerAct = new QAction(this);
    addLayerAct->setText("AddLayer");
    newAct = new QAction("&New", this);
    aboutAct = new QAction("&About", this);
    closeAct = new QAction("&Close", this);
    closeAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    fileMenu = this->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(addLayerAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    helpMenu = this->menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAct);

    connect(newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    //connect(addLayerAct, SIGNAL(triggered()), mEditor, SLOT(addLayer()));
    connect(newDialogWin, SIGNAL(newProject(int,int,int,int)), mEditor, SLOT(newProject(int,int,int,int)));
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
    connect(closeAct, SIGNAL(triggered()), SLOT(close()));

    addDockWidget(Qt::RightDockWidgetArea, brushDockWidget);

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
    msgbox.setText("Odessa Ver. 0.0.16<br>Swing Innovations<br><a href=\"http://www.swinginnovations.com\">Swing Innovations Website</a>""<br>Copyright 2014 <br> Test Build || Use at your own risk!");
    msgbox.exec();
}
