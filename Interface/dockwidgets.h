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
#include <QComboBox>
#include <QListWidget>
#include <QMouseEvent>
#include <QToolButton>
#include <QMenu>
#include <QDebug>

//handling the Brush System

class ColorWheelWidget;
class BrushShapeWidget;

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

    QTabWidget* brushOptions;

    BrushShapeWidget* brushShape;
    QTabWidget* brushContainer;

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

    QRect getColorZoneRect(){return refineColorRect;}

signals:
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);
    void actualRedChanged(int);
    void actualBlueChanged(int);
    void actualGreenChanged(int);
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

    void setRed(int val){this->red = val;}
    void setGreen(int val){this->green = val;}
    void setBlue(int val){this->blue = val;}

    void setActualColor(QColor);
    void setActualColorPos(QPoint);

protected:
    void paintEvent(QPaintEvent* event);
private:
    QTabWidget* colorModeTab;

    QLabel* colorDisplayLabel;
    ColorWheelWidget* colorWheel;
    QPixmap colorWheelPixmap;
    QImage tempImage;

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

    int actualRed;
    int actualBlue;
    int actualGreen;

    int hue;
    int saturation;
    int value;

    //color wheel
    QPoint primaryColorPos;
    QPoint complementColorPos;
    QPoint actualColorPos;
    QRect refineColorRect;
};

class TimelineDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    TimelineDockWidget(QWidget *parent = 0);
    virtual ~TimelineDockWidget();
};

class BrushShapeWidget : public QLabel
{
  Q_OBJECT
public:
    BrushShapeWidget(QWidget *parent = 0);
    virtual ~BrushShapeWidget();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPixmap brushPreviewPixmap;
};

class ColorWheelWidget : public QLabel
{
    Q_OBJECT
public:
    ColorWheelWidget(QWidget *parent = 0);
    virtual ~ColorWheelWidget();

    void setRefineRect(QRect rect){ refineColorRect = rect; }
signals:
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);

    void actualRedChanged(int);
    void actualGreenChanged(int);
    void actualBlueChanged(int);

    void colorChanged(QColor);
    void actualColorPoint(QPoint);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QPixmap pixmap;
    QRect refineColorRect;
    QPoint primaryColorPos;
    QPoint complementColorPos;
    QPoint actualColorPos;
};

class LayerDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    LayerDockWidget(QWidget* parent = 0);
    virtual ~LayerDockWidget();
private:
    QComboBox* compositionMode;
    QListWidget* layerManager;
    QToolButton* layerOptionsButton;
    QMenu* layerOptionsMenu;
};

#endif // DOCKWIDGETS_H
