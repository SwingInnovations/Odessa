#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Odessa");
    a.setApplicationVersion("0.0.31");
    a.setOrganizationName("SwingInnovations");
    a.setOrganizationDomain("www.swinginnovations.com");
    a.setStyle("fusion");
    MainWindow w;
    w.show();

    return a.exec();
}
