#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mEditor = new Editor(this);
    setCentralWidget(mEditor);

    newDialogWin = new OdessaNewDocDialog();

    addLayerAct = new QAction(this);
    addLayerAct->setText("AddLayer");
    newAct = new QAction("&New", this);

    fileMenu = this->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(addLayerAct);

    connect(newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    connect(addLayerAct, SIGNAL(triggered()), mEditor, SLOT(addLayer()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::showNewDocWin()
{
    newDialogWin->exec();
}
