#ifndef DIALOGWINDOWS_H
#define DIALOGWINDOWS_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>

//handle the dialog windows

//new Document
class OdessaNewDocDialog : public QDialog
{
    Q_OBJECT
public:
    OdessaNewDocDialog();
    ~OdessaNewDocDialog();

    int getWidth()const{ return width; }
    int getHeight()const{ return height; }
    int getDPI()const{ return dpi; }

signals:
    void newProject(int type, int width, int height, int dpi);
protected:

private slots:
    void newProjectSlot();

private:
    int width, height, dpi;
    QComboBox *optionsComboBox;
    QLabel *m_WidthLabel;
    QLabel *m_HeightLabel;
    QLabel *m_dpiLabel;
    QLineEdit *m_widthLineEdit;
    QLineEdit *m_heightLineEdit;
    QLineEdit *m_dpiLineEdit;

    QPushButton *createButton;
    QPushButton *cancelButton;

    QGroupBox *descripGroupBox;

    QVBoxLayout *labelLayout;
    QVBoxLayout *lineEditLayout;
    QHBoxLayout *labelAndLineLayout;
    QVBoxLayout *totalLayout;
    QVBoxLayout *finalLayout;

    QHBoxLayout *buttonLayout;
};

#endif // DIALOGWINDOWS_H
