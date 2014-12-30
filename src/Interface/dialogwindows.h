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
#include <QListWidget>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QSpinBox>

//handle the dialog windows
class GeneralPrefPage;

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

class OdessaPrefDialog : public QDialog
{
    Q_OBJECT
public:
    OdessaPrefDialog();
    ~OdessaPrefDialog();
signals:
    void projectPathChanged(QString);

public slots:
    void updateProjectPath(QString);
private:
    QListWidget* contentWidget;
    QStackedWidget* pagesWidget;
    GeneralPrefPage* genPref;
    QPushButton* m_OkButton;
    QPushButton* m_ApplyButton;
    QPushButton* m_CancelButton;
};

class GeneralPrefPage : public QWidget
{
    Q_OBJECT
public:
    GeneralPrefPage(QWidget* parent = 0);
    ~GeneralPrefPage();
signals:
    void projectPathChanged(QString);
    void historyStepsChanged(int);

public slots:
    void changeProjectPath();
    void changeHistorySteps(int);
private:
    /*-Project Path-*/
    QLabel* mProjectPathLbl;
    QLineEdit* mProjectPathLE;
    QPushButton* mChangeProjectPathBtn;

    /*-History stack settings-*/
    QLabel* mHistoryLbl;
    QSpinBox* mStepsBox;
};



#endif // DIALOGWINDOWS_H
