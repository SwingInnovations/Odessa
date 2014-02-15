#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "Structure/editor.h"
#include "Interface/dialogwindows.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showNewDocWin();
    void about();

private:
    Editor *mEditor;
    OdessaNewDocDialog *newDialogWin;

    //temporary action
    QAction *addLayerAct;
    QAction *newAct;
    QAction *aboutAct;

    QMenu *fileMenu;
    QMenu *helpMenu;

};

#endif // MAINWINDOW_H
