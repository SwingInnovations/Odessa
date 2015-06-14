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
#include <QComboBox>
#include <QSettings>
#include <QColorDialog>
#include <QCheckBox>

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
    void setStartColor(QColor col);

    int getWidth()const{return width;}
    int getHeight()const{return height;}
    int getDPI()const{return dpi;}
    int getType()const{return type;}
    int getFrameCount()const{return frameCount;}
    int getFPS()const{return fps;}
    int getSpriteCount_Row()const{ return spriteCount_Row; }
    int getSpriteCount_Col()const{ return spriteCount_Col; }
    QColor getStartColor()const{ return startColor; }

private:
    int width, height;
    int spriteCount_Row;
    int spriteCount_Col;
    int dpi;
    int type;
    int frameCount;
    int fps;
    QColor startColor;
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
    void setNewColor();
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

    QLabel* m_ColorLabel;
    QPushButton* m_ColorBtn;
    QColor m_backgroundColor;

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
    void historyStepsChanged(int);
    void uiScaleChanged(double);
public slots:
    void updateProjectPath(QString);
    void applyChanges();
    void okChanges();
private:
    QListWidget* m_ContentWidget;
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
    void applyChanges();
    ~GeneralPrefPage();
signals:
    void projectPathChanged(QString);
    void historyStepsChanged(int);
    void uiScaleChanged(double);
public slots:
    void changeProjectPath();
    void changeHistorySteps(int);
    void updateUIScale(QString);
private:
    /*-Theme-*/
    QLabel* m_ThemeLbl;
    QComboBox* m_ThemeCombobox;

    /*-Project Path-*/
    QLabel* mProjectPathLbl;
    QLineEdit* mProjectPathLE;
    QPushButton* mChangeProjectPathBtn;

    /*-History stack settings-*/
    QLabel* mHistoryLbl;
    QSpinBox* mStepsBox;

    /*-UI Scaling option-*/
    QLabel* m_ScaleLbl;
    QComboBox* m_ScaleComboBox;

    QLabel* m_HardwareAccLbl;
    QCheckBox* m_HardwareAccChk;

    double ui_scale = 1.0;
};

class DebugWindow : public QDialog{
    Q_OBJECT

public:
    DebugWindow();
    ~DebugWindow();
public slots:

private:

};

#endif // DIALOGWINDOWS_H
