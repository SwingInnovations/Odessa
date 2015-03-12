#include "mainwindow.h"
#include "projectinfo.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Odessa");
    a.setApplicationVersion("0.0.70");
    a.setOrganizationName("SwingInnovations");
    a.setOrganizationDomain("www.swinginnovations.com");
    a.setStyle(QStyleFactory::create("fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);

    palette.setColor(QPalette::Highlight, QColor(144,216,255).darker());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    a.setPalette(palette);
    a.setStyleSheet("QSeperator { foreground-color: white }");
    MainWindow w;
    w.show();

    return a.exec();
}
