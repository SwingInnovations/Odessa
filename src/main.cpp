#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Odessa --- INDEV");
    a.setApplicationVersion("0.0.74");
    a.setOrganizationName("SwingInnovations");
    a.setOrganizationDomain("www.swinginnovations.com");
    a.setWindowIcon(QIcon(":/icon/resource/icon.svg"));
    a.setStyle(QStyleFactory::create("fusion"));
    QSettings settings("SwingInnovations", "Odessa");
    QPalette palette;
    QString theme = settings.value("theme").toString();
    QString target = "light";
    if(theme != target){
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
        palette.setColor(QPalette::HighlightedText, Qt::white);
        a.setPalette(palette);
        a.setStyleSheet("QSeperator { foreground-color: white }");
    }
    MainWindow w;
    w.show();

    return a.exec();
}
