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
//Project Info
class ProjectInfo
{
public:
    ProjectInfo();
    ProjectInfo(const ProjectInfo &other);
    ~ProjectInfo();

    void setWidth(int w);
    void setHeight(int h);
    void setType(int t);
    void setDPI(int d);
    void setFrameCount(int fc);
    void setFPS(int fps);
    void setSpriteCount_Row(int row);
    void setSpriteCount_Col(int col);

    int getWidth()const{return width;}
    int getHeight()const{return height;}
    int getDPI()const{return dpi;}
    int getType()const{return type;}
    int getFrameCount()const{return frameCount;}
    int getFPS()const{return fps;}
    int getSpriteCount_Row()const{ return spriteCount_Row; }
    int getSpriteCount_Col()const{ return spriteCount_Col; }

private:
    int width, height;
    int spriteCount_Row;
    int spriteCount_Col;
    int dpi;
    int type;
    int frameCount;
    int fps;
};
Q_DECLARE_METATYPE(ProjectInfo);

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
    void newProject(ProjectInfo& info);
protected:

private slots:
    void newProjectSlot();
    void setDocType(int);
    void setPresetSize(int);
private:
    int width, height, dpi;
    ProjectInfo info;
    QString parameterInfo;

    QComboBox* m_TypeComboBox;
    QComboBox* m_CanvasSizeComboBox;

    QLabel* m_WidthLabel;
    QLineEdit* m_WidthLE;
    QLabel* m_HeightLabel;
    QLineEdit* m_HeightLE;
    QLabel* m_DPILabel;
    QLineEdit* m_DPILE;

    /*Sprite Sheet specific*/
    QLabel* m_SpriteCount_RowLabel;
    QLineEdit* m_SpriteCount_RowLE;
    QLabel* m_SpriteCount_ColLabel;
    QLineEdit* m_SpriteCount_ColLE;
    QVBoxLayout* m_SpriteLayout;

    /*Animation Specific*/
    QLabel* m_FrameCountLabel;
    QLineEdit* m_FrameCountLE;
    QLabel* m_FpsLabel;
    QLineEdit* m_FpsLE;
    QVBoxLayout* m_AnimLayout;

    QGroupBox* m_InformationGrpBox;
    QLabel* m_InformationGrpLbl;

    QPushButton* m_OkBtn;
    QPushButton* m_CloseBtn;

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
