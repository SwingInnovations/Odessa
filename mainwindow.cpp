#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mEditor = new Editor(this);
    setCentralWidget(mEditor);
}

MainWindow::~MainWindow()
{

}
