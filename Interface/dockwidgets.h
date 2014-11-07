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
    void SetDirectory(QString dir);
    virtual ~BrushDockWidget();
    Brush GetStartBrush();
protected:
    void resizeEvent(QResizeEvent*);
signals:
    void BrushSizeChanged(int);
    void BrushOpacityChanged(int);
    void BrushSpacingChanged(int);
    void BrushTransferSizeChanged(int);
    void BrushTransferOpacityChanged(int);
    void BrushHardnessChanged(int);
    void StencilWidthChanged(int);
    void StencilHeightChanged(int);
    void StencilRotateChanged(int);
    void BrushStencilChanged(QPixmap);
    void BrushStencilPathChanged(QString);
    void StencilBaseShapeChanged(BrushShape);
private slots:
    void SetCurrentIndex(int);
    void UpdateSize(int);
    void UpdateSize(QString);
    void UpdateSpacing(int);
    void UpdateSpacing(QString);
    void UpdateOpacity(int);
    void UpdateOpacity(QString);
    void UpdateTransferSize(int);
    void UpdateTransferSize(QString);
    void UpdateTransferOpacity(int);
    void UpdateTransferOpacity(QString);
    void ToggleTransferSize(bool);
    void ToggleTransferOpacity(bool);
    void UpdateStencil(QPixmap);
    void UpdateStencilPath(QString);
    void LoadStencilAct();
    void LoadBrushAct();
    void LoadBrushSetAct();
    void SaveStencilAct();
    void SaveBrushAct();
    void SaveBrushSetAct();
    void DeleteBrushAct();
private:
    void ReadSettings();
    void WriteSettings();
    Brush LoadBrush(QString filePath);
    QVector<Brush> LoadBrushLib(QString filePath);
    void SaveBrushLib(QString filePath);

    QString mBrushLib;
    QString mProjectPath;
    int mCurrentBrushIndex;
    QTabWidget* mTabWidget;

    /*--General Parameters--*/
    GeneralBrushWidget* mGenBrushWidget;
    GeneralBrushWidget* mTransBrushWidget;

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

    /*-TransferSize-*/
    QCheckBox* mTransferSizeToggle;
    QSlider* mTransferSizeSlider;
    QLineEdit* mTransferSizeLE;

    /*-TransferOpacity-*/
    QCheckBox* mTransferOpacityToggle;
    QSlider* mTransferOpacitySlider;
    QLineEdit* mTransferOpacityLE;

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
    void AddBrush(int iD, Brush brush);
    void AddBrush(Brush brush);
    int SetBrushIndex(int val){this->mCurrentBrushIndex = val;}
    void SetDir(QString dir){this->mDir = dir;}
    int GetBrushIndex(){return this->mCurrentBrushIndex;}
    QString GetDir(){return this->mDir;}
signals:
    void LoadStencilTriggered();
    void LoadBrushTriggered();
    void LoadBrushSetTriggered();
    void SaveStencilTriggered();
    void SaveBrushTriggered();
    void SaveBrushSetTriggered();
    void DeleteBrushTriggered();
    void BrushLibIndexChanged(int);
public slots:
    void UpdateLoadStencil(){emit LoadStencilTriggered();}
    void UpdateLoadBrush(){emit LoadBrushTriggered();}
    void UpdateLoadBrushSet(){emit LoadBrushSetTriggered();}
    void UpdateSaveStencil(){emit SaveStencilTriggered();}
    void UpdateSaveBrush(){emit SaveBrushTriggered();}
    void UpdateSaveBrushSet(){emit SaveBrushSetTriggered();}
    void UpdateDeleteBrush(){emit DeleteBrushTriggered();}
    void UpdateBrushLibIndex(int val){mCurrentBrushIndex = val; emit BrushLibIndexChanged(val);}
    void UpdateStencil(QPixmap);
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
    void LoadStencilTriggered();
    void LoadBrushTriggered();
    void LoadBrushSetTriggered();
    void SaveStencilTriggered();
    void SaveBrushTriggered();
    void SaveBrushSetTriggered();
    void DelteBrushTriggered();
    void StencilWidthChanged(int);
    void StencilHeightChanged(int);
    void BrushHardnessChanged(int);
    void RotateChanged(int);
    void StencilChanged(QPixmap);
    void StencilPathChanged(QString);
public slots:
    void UpdateLoadStencil(){emit LoadStencilTriggered();}
    void UpdateLoadBrush(){emit LoadBrushTriggered();}
    void UpdateLoadBrushSet(){emit LoadBrushSetTriggered();}
    void UpdateSaveStencil(){emit SaveStencilTriggered();}
    void UpdateSaveBrush(){emit SaveBrushTriggered();}
    void UpdateSaveBrushSet(){emit SaveBrushSetTriggered();}
    void UpdateDeleteBrush(){emit DelteBrushTriggered();}
    void UpdateStencilWidth(int);
    void UpdateStencilWidth(QString);
    void UpdateStencilHeight(int);
    void UpdateStencilHeight(QString);
    void UpdateBrushHardness(int);
    void UpdateBrushHardness(QString);
    void UpdateStencilRotate(int);
    void UpdateStencilRotate(QString);
    void UpdateStencil(QPixmap);
    void UpdateBrushShape_Circle();
    void UpdateBrushShape_Square();
    void UpdateBrushShape_Polygon();
    void UpdateStencilTexture();
    void UpdateStencilTextureLE(QString);
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
