#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "Structure/editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Editor *mEditor;

    //temporary action
    QAction *addLayerAct;
    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
