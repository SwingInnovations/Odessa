#ifndef DOCKWIDGETS_H
#define DOCKWIDGETS_H

#include <QDockWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QWidget>
#include <QTabWidget>

//handling the Brush System
class BrushDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    BrushDockWidget(QWidget *parent = 0);
    virtual ~BrushDockWidget();
signals:
    void mSizeChanged(int);
    void mFeatherChanged(int);
    void mSpacingChanged(int);
private slots:
    void set_mSizeLE(int);
    void set_mFeatherLE(int);
    void set_mSpacingLE(int);

    void set_mSizeSlider(QString);
    void set_mFeatherSlider(QString);
    void set_mSpacingSlider(QString);
private:
    QLabel* mSizeLabel;
    QLabel* mFeatherLabel;
    QLabel* mSpacingLabel;

    QSlider* mSizeSlider;
    QSlider* mFeatherSlider;
    QSlider* mSpacingSlider;

    QLineEdit* mSizeLE;
    QLineEdit* mFeatherLE;
    QLineEdit* mSpacingLE;

    QHBoxLayout* mSizeLayout;
    QHBoxLayout* mFeatherLayout;
    QHBoxLayout* mSpacingLayout;

    QVBoxLayout* primaryBrushControlLayout;

    QGroupBox* pressureContainer;
    QGridLayout* pressureLayout;
    QCheckBox* usePressure;
    QCheckBox* transferOpacity;
    QCheckBox* transferWidth;
    QSlider* transferWidthSlider;

};

class ColorDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    ColorDockWidget(QWidget *parent = 0);
    virtual ~ColorDockWidget();
private:
    QTabWidget* colorModeTab;

    //for RGB
    QLabel* m_RLabel;
    QLabel* m_GLabel;
    QLabel* m_BLabel;
    QSlider* m_RSlider;
    QSlider* m_GSlider;
    QSlider* m_BSlider;
    QLineEdit* m_RLineEdit;
    QLineEdit* m_GLineEdit;
    QLineEdit* m_BLineEdit;

    QHBoxLayout* RLayout;
    QHBoxLayout* GLayout;
    QHBoxLayout* BLayout;
    QVBoxLayout* masterRGBLayout;

    QLabel* m_HLabel;
    QLabel* m_SLabel;
    QLabel* m_VLabel;
    QSlider* m_HSlider;
    QSlider* m_SSLider;
    QSlider* m_VSlider;
    QLineEdit* m_HLineEdit;
    QLineEdit* m_SLineEdit;
    QLineEdit* m_VLineEdit;

    QHBoxLayout* HLayout;
    QHBoxLayout* SLayout;
    QHBoxLayout* VLayout;
    QVBoxLayout* masterHSVLayout;
};

class TimelineDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    TimelineDockWidget(QWidget *parent = 0);
    virtual ~TimelineDockWidget();
};

class ColorWheelWidget : public QWidget
{
    Q_OBJECT
public:
    ColorWheelWidget(QWidget *parent = 0);
    virtual ~ColorWheelWidget();
};

#endif // DOCKWIDGETS_H
