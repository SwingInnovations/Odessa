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
#include <QStackedWidget>
#include <QStackedLayout>
#include <QPainter>
#include <QComboBox>
#include <QListWidget>
#include <QMouseEvent>
#include <QToolButton>
#include <QFileDialog>
#include <QAction>
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
    void BrushSizeChanged(int);
    void BrushOpacityChanged(int);
    void BrushTransferSizeChanged(int);
    void BrushTransferOpacityChanged(int);
    void BrushStencilChanged(QPixmap);
private slots:
    void UpdateSize(int);
    void UpdateSize(QString);
    void UpdateOpacity(int);
    void UpdateOpacity(QString);
    void UpdateTransferSize(int);
    void UpdateTransferSize(QString);
    void UpdateTransferOpacity(int);
    void UpdateTransferOpacity(QString);
    void ToggleTransferSize(bool);
    void ToggleTransferOpacity(bool);
private:
    QStackedLayout* m_BrushStack;
    QTabWidget* m_BrushAttrib;
    QAction* m_OpenBrushAct;
    QAction* m_OpenBrushLibAct;
    QAction* m_ExportBrushAct;
    QAction* m_ExportBrushLibAct;
    QMenu* m_BrushMenu;
    //Actions here

    /*Widgets under the General Brush Tab*/
    QToolButton* m_BrushToolButton; //Menu for other brush options
    QLabel* m_BrushPreviewLbl;
    QListView* m_BrushLibView;

    /* General Size Related */
    QLabel* m_SizeLabel;
    QSlider* m_SizeSlider;
    QLineEdit* m_SizeLE;

    /* General Opacity Related */
    QLabel* m_OpacityLabel;
    QSlider* m_OpacitySlider;
    QLineEdit* m_OpacityLE;

    /* Transfer Size Related */
    QCheckBox* m_TransferSizeCheck;
    QSlider* m_TransferSizeSlider;
    QLineEdit* m_TransferSizeLE;

    /* Transfer Opacity Related */
    QCheckBox* m_TransferOpacityCheck;
    QSlider* m_TransferOpacitySlider;
    QLineEdit* m_TransferOpacityLE;

    /* Advanced Brush WorkArea */
    QLabel* m_BrushWorkArea;
    QPixmap m_brushPreview;
    int m_BrushWidth, m_BrushHeight;

    /*Advanced Brush Related*/


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
