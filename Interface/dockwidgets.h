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
#include <QFile>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QPushButton>
#include <QScrollArea>
#include <QTemporaryFile>
#include <QImage>
#include <QRgb>
#include <QMap>
#include <QVector>
#include <QDataStream>
#include <QSettings>
#include <QMessageBox>
#include <QSpinBox>

#include "../Structure/brush.h"
#include "Overloads.h"

//handling the Brush System

class ColorWheelWidget;
class BrushShapeWidget;
class GeneralBrushWidget;
class CustomBrushWidget;

class BrushDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    enum BrushShape{CIRCLE_SHAPE, SQUARE_SHAPE, CUSTOM};
    BrushDockWidget(QWidget *parent = 0);
    void setDirectory(QString dir);
    virtual ~BrushDockWidget();
    Brush getStartBrush();
protected:
    void resizeEvent(QResizeEvent*);
signals:
    void brushSizeChanged(int);
    void brushOpacityChanged(int);
    void brushSpacingChanged(int);
    void brushTransferSizeChanged(int);
    void brushTransferOpacityChanged(int);
    void brushHardnessChanged(int);
    void stencilWidthChanged(int);
    void stencilHeightChanged(int);
    void stencilRotateChanged(int);
    void brushStencilChanged(QPixmap);
    void brushStencilPathChanged(QString);
    void stencilBaseShapeChanged(BrushShape);
private slots:
    void setCurrentIndex(int);
    void updateSize(int);
    void updateSize(QString);
    void updateSpacing(int);
    void updateSpacing(QString);
    void updateOpacity(int);
    void updateOpacity(QString);
    void updateTransferSize(int);
    void updateTransferSize(QString);
    void updateTransferOpacity(int);
    void updateTransferOpacity(QString);
    void toggleTransferSize(bool);
    void toggleTransferOpacity(bool);
    void updateStencil(QPixmap);
    void updateStencilPath(QString);
    void updateBrushName(QString);
    void toggleTransferVisibility(bool);
    void loadStencilAct();
    void loadBrushAct();
    void loadBrushSetAct();
    void saveStencilAct();
    void saveBrushAct();
    void saveBrushSetAct();
    void deleteBrushAct();
private:
    void readSettings();
    void writeSettings();
    Brush loadBrush(QString filePath);
    QVector<Brush> loadBrushLib(QString filePath);
    void saveBrushLib(QString filePath);

    QString mBrushLib;
    QString mProjectPath;
    int mCurrentBrushIndex;
    QTabWidget* mTabWidget;

    /*--General Parameters--*/
    GeneralBrushWidget* mGenBrushWidget;

    /*-Size-*/
    QLabel* mSizeLabel;
    QSlider* mSizeSlider;
    QSpinBox* mSizeLE;

    /*-Opacity-*/
    QLabel* mOpacityLabel;
    QSlider* mOpacitySlider;
    QSpinBox* mOpacityLE;

    /*-Spacing-*/
    QLabel* mSpacingLabel;
    QSlider* mSpacingSlider;
    QSpinBox* mSpacingLE;

    /*--Transfer--*/
    QGroupBox* transGrpBox;
    /*-TransferSize-*/
    QCheckBox* mTransferSizeToggle;
    QSlider* mTransferSizeSlider;
    QSpinBox* mTransferSizeLE;

    /*-TransferOpacity-*/
    QCheckBox* mTransferOpacityToggle;
    QSlider* mTransferOpacitySlider;
    QSpinBox* mTransferOpacityLE;

    /*--Custom--*/
    CustomBrushWidget* mStencilWidget;

    /*-Data-*/
    QVector<Brush> mTempBrushList;
    QVector<Brush> mActualBrushList;

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

class GeneralBrushWidget : public QWidget
{
    Q_OBJECT
public:
    GeneralBrushWidget();
    virtual ~GeneralBrushWidget();
    void addBrush(int iD, Brush brush);
    void addBrush(Brush brush);
    int setBrushIndex(int val){this->mCurrentBrushIndex = val;}
    void setDir(QString dir){this->mDir = dir;}
    int getBrushIndex(){return this->mCurrentBrushIndex;}
    QString getDir(){return this->mDir;}
signals:
    void loadStencilTriggered();
    void loadBrushTriggered();
    void loadBrushSetTriggered();
    void saveStencilTriggered();
    void saveBrushTriggered();
    void saveBrushSetTriggered();
    void deleteBrushTriggered();
    void brushLibIndexChanged(int);
    void brushNameChanged(QString);
public slots:
    void updateLoadStencil(){emit loadStencilTriggered();}
    void updateLoadBrush(){emit loadBrushTriggered();}
    void updateLoadBrushSet(){emit loadBrushSetTriggered();}
    void updateSaveStencil(){emit saveStencilTriggered();}
    void updateSaveBrush(){emit saveBrushTriggered();}
    void updateSaveBrushSet(){emit saveBrushSetTriggered();}
    void updateDeleteBrush(){emit deleteBrushTriggered();}
    void updateBrushLibIndex(int val){mCurrentBrushIndex = val; emit brushLibIndexChanged(val);}
    void updateStencil(QPixmap);
    void updateName(QListWidgetItem* item);
private:
    unsigned int mCurrentBrushIndex;
    QString mDir;
    QPixmap mStrokePreview;
    QLabel* mStrokePreviewLabel;
    QListWidget* mBrushIndex;
    QToolButton* mToolBtn;
    QMenu* mToolMenu;
    QAction* mLoadStencilAct;
    QAction* mLoadBrushAct;
    QAction* mLoadBrushSetAct;
    QAction* mSaveStencilAct;
    QAction* mSaveBrushAct;
    QAction* mSaveBrushSetAct;
    QAction* mDeleteBrushAct;
};

class CustomBrushWidget : public QWidget
{
    Q_OBJECT
public:
    enum BrushShape{LINE_SHAPE, CIRCLE_SHAPE, SQUARE_SHAPE, CUSTOM};
    CustomBrushWidget();
    virtual ~CustomBrushWidget();
    void SetDir(QString dir){this->mDir = dir;}
    void TempSave(QPixmap);
    QString GetDir(){return this->mDir;}
    QPixmap GetPixmap(){return mStencilPreview;}
    QPixmap GeneratePixmap();
protected:
    void paintEvent(QPaintEvent*);
signals:
    void loadStencilTriggered();
    void loadBrushTriggered();
    void loadBrushSetTriggered();
    void saveStencilTriggered();
    void saveBrushTriggered();
    void saveBrushSetTriggered();
    void deleteBrushTriggered();
    void StencilWidthChanged(int);
    void stencilHeightChanged(int);
    void brushHardnessChanged(int);
    void rotateChanged(int);
    void stencilChanged(QPixmap);
    void stencilPathChanged(QString);
public slots:
    void updateLoadStencil(){emit loadStencilTriggered();}
    void updateLoadBrush(){emit loadBrushTriggered();}
    void updateLoadBrushSet(){emit loadBrushSetTriggered();}
    void updateSaveStencil(){emit saveStencilTriggered();}
    void updateSaveBrush(){emit saveBrushTriggered();}
    void updateSaveBrushSet(){emit saveBrushSetTriggered();}
    void updateDeleteBrush(){emit deleteBrushTriggered();}
    void updateStencilWidth(int);
    void updateStencilWidth(QString);
    void updateStencilHeight(int);
    void updateStencilHeight(QString);
    void updateBrushHardness(int);
    void updateBrushHardness(QString);
    void updateStencilRotate(int);
    void updateStencilRotate(QString);
    void updateStencil(QPixmap);
    void updateBrushShape_Circle();
    void updateBrushShape_Square();
    void updateBrushShape_Polygon();
    void updateStencilTexture();
    void updateStencilTextureLE(QString);
private:

    QString mDir;

    /*--Custom--*/
    QLabel* mStencilLabel;
    QPixmap mStencilPreview;
    QPixmap mStencilTexture;
    bool hasTexture;

    /*-Width-*/
    QLabel* mWidthLabel;
    QSlider* mWidthSlider;
    QLineEdit* mWidthLE;

    /*-Height-*/
    QLabel* mHeightLabel;
    QSlider* mHeightSlider;
    QLineEdit* mHeightLE;

    /*-Hardness-*/
    QLabel* mHardnessLabel;
    QSlider* mHardnessSlider;
    QLineEdit* mHardnessLE;

    /*-Rotate-*/
    QLabel* mRotateLabel;
    QSlider* mRotateSlider;
    QLineEdit* mRotateLE;

    /*-SelectShape-*/
    BrushShape mBrushShape;
    QPushButton* mCircleButton;
    QPushButton* mSquareButton;
    QPushButton* mCustomButton;

    QLabel* mTextureLabel;
    QLineEdit* mTextureFileLE;
    QPushButton* mTextureBtn;

    /*-Tool_Menu-*/
    QToolButton* mToolBtn;
    QMenu* mToolMenu;
    QAction* mLoadStencilAct;
    QAction* mLoadBrushAct;
    QAction* mLoadBrushSetAct;
    QAction* mSaveStencilAct;
    QAction* mSaveBrushAct;
    QAction* mSaveBrushSetAct;
    QAction* mDeleteBrushAct;
    /*-File Stuff-*/
    QTemporaryFile tempFile;
};

#endif // DOCKWIDGETS_H
