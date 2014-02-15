#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mEditor = new Editor(this);
    setCentralWidget(mEditor);

    addLayerAct = new QAction(this);
    addLayerAct->setText("AddLayer");
    fileMenu = this->menuBar()->addMenu("FileMenu");
    fileMenu->addAction(addLayerAct);

    connect(addLayerAct, SIGNAL(triggered()), mEditor, SLOT(addLayer()));
}

MainWindow::~MainWindow()
{

}
