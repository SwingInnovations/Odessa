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
#include <QGradient>
#include <QRadialGradient>
#include <QConicalGradient>
#include <QPainter>

//handling the Brush System

class ColorWheelWidget;

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
    void mOpacityChanged(int);
    void mTransferOpacityChanged(int);
    void mTransferSizeChanged(int);

private slots:
    void set_mSizeLE(int);
    void set_mFeatherLE(int);
    void set_mSpacingLE(int);
    void set_mOpacityLE(int);
    void set_mTransferOpacity(int);
    void set_mTransferSize(int);

    void set_mSizeSlider(QString);
    void set_mFeatherSlider(QString);
    void set_mSpacingSlider(QString);
    void set_mOpacitySlider(QString);
    void set_mTransferOpacitySlider(QString);
    void set_mTransferSizeSlider(QString);
    void toggleTransferOpacity(bool);
    void toggleTransferSize(bool);
private:
    QLabel* mSizeLabel;
    QLabel* mFeatherLabel;
    QLabel* mSpacingLabel;
    QLabel* mOpacityLabel;

    QSlider* mSizeSlider;
    QSlider* mFeatherSlider;
    QSlider* mSpacingSlider;
    QSlider* mOpacitySlider;

    QLineEdit* mSizeLE;
    QLineEdit* mFeatherLE;
    QLineEdit* mSpacingLE;
    QLineEdit* mOpacityLE;

    QHBoxLayout* mSizeLayout;
    QHBoxLayout* mFeatherLayout;
    QHBoxLayout* mSpacingLayout;
    QHBoxLayout* mOpacityLayout;

    QVBoxLayout* primaryBrushControlLayout;
    QVBoxLayout* secondaryBrushControlLayout;

    QGroupBox* mPressureContainer;

    QHBoxLayout* mTransferOpacityLayout;
    QCheckBox* mTransferOpacity;
    QSlider* mTransferOpacityAmt;
    QLineEdit* mTransferOpacityLE;

    QHBoxLayout* mTransferWidthLayout;
    QCheckBox* mTransferWidth;
    QSlider* mTransferWidthSlider;
    QLineEdit* mTransferWidthLE;

};

class ColorDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    ColorDockWidget(QWidget *parent = 0);
    virtual ~ColorDockWidget();

    int getRed(){return red;}
    int getGreen(){return green;}
    int getBlue(){return blue;}
    int getHue(){return hue;}
    int getSaturation(){return saturation;}
    int getValue(){return value;}
signals:
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);
    void hueChanged(int);
    void saturationChanged(int);
    void valueChanged(int);
public slots:
    void set_RLE(int);
    void set_GLE(int);
    void set_BLE(int);
    void set_HLE(int);
    void set_SLE(int);
    void set_VLE(int);

    void set_RSlider(QString);
    void set_GSlider(QString);
    void set_BSlider(QString);
    void set_HSlider(QString);
    void set_SSlider(QString);
    void set_VSlider(QString);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QTabWidget* colorModeTab;

    QLabel* colorDisplayLabel;
    QPixmap colorWheelPixmap;

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

    QGroupBox* m_ColorWheelContainer;

    int red;
    int green;
    int blue;
    int hue;
    int saturation;
    int value;
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
    void setSize(int x, int y, int w, int h){
        boundaries.setX(x);
        boundaries.setY(y);
        boundaries.setWidth(w);
        boundaries.setHeight(h);
        this->resize(w, h);
        this->setGeometry(boundaries);
        update();
    }

    void Draw(QPaintEvent* event){
        this->paintEvent(event);
    }

    QPixmap getPixmap(){return pixmap;}

    virtual ~ColorWheelWidget();
protected:
    void paintEvent(QPaintEvent *event);
private:
    QRect boundaries;
    QPixmap pixmap;
};

class BrushShapeWidget : public QWidget
{
  Q_OBJECT
public:
    BrushShapeWidget(QWidget *parent = 0);
    virtual ~BrushShapeWidget();
};

#endif // DOCKWIDGETS_H
