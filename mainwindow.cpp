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
    aboutAct = new QAction("&About", this);

    fileMenu = this->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(addLayerAct);

    helpMenu = this->menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAct);

    connect(newAct, SIGNAL(triggered()), SLOT(showNewDocWin()));
    connect(addLayerAct, SIGNAL(triggered()), mEditor, SLOT(addLayer()));
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));
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
