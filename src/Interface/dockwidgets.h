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
#include <QRadioButton>
#include <QDataStream>
#include <QSettings>
#include <QMessageBox>
#include <QSpinBox>
#include <QTransform>
#include <QColorDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QButtonGroup>
#include <QFontComboBox>
#include <QHeaderView>

#include "../src/Structure/brush.h"
#include "../src/Structure/editor.h"
#include "../Overloads.h"

//handling the Brush System

class ColorWheel;
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
    void brushPressureActive(bool);
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
    void updateStencilWidth(int);
    void updateStencilHeight(int);
    void updateStencilHardness(int);
    void updateStencilRotate(int);
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
    QComboBox* mDrawModeComboBox;
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

class GeneralBrushWidget : public QWidget
{
    Q_OBJECT
public:
    GeneralBrushWidget();
    virtual ~GeneralBrushWidget();
    void addBrush(int iD, Brush brush);
    void addBrush(Brush brush);
    void setBrushIndex(int val){this->mCurrentBrushIndex = val;}
    void setDir(QString dir){this->mDir = dir;}
    int getBrushIndex(){return this->mCurrentBrushIndex;}
    QString getDir(){return this->mDir;}
    void setStencilPixmap(QPixmap);
    void activateUsePressureWidth(bool);
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
    void showStencil(bool);
    void showStroke(bool);
protected:
    void resizeEvent(QResizeEvent *);
private:
    void generateStrokePreview();
    bool m_usePressureWidth;
    unsigned int mCurrentBrushIndex;
    QString mDir;
    QPixmap m_StrokePreview;
    QPixmap m_StencilPreview;
    qreal m_minSize;
    qreal m_maxSize;
    QPushButton* m_showStencilBtn;
    QPushButton* m_showStrokeBtn;
    QLabel* m_PreviewLabel;
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

class BrushShapeWidget : public QLabel
{
  Q_OBJECT
public:
    BrushShapeWidget(QWidget *parent = 0);
    virtual ~BrushShapeWidget();
    void toggleStroke(bool);
    void setMaxSize(qreal);
    void setMinSize(qreal);
    void setBrush(Brush);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPixmap brushPreviewPixmap;
    bool m_ShowStroke;
    qreal m_MaxPressure;
    qreal m_MinSize;
    Brush m_brush;
};


class ColorDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    ColorDockWidget(QWidget *parent = 0);
public slots:
    void updateColor(QColor);
    void updateRed(int);
    void updateRed(QString);
    void updateGreen(int);
    void updateGreen(QString);
    void updateBlue(int);
    void updateBlue(QString);
    void updateHue(int);
    void updateHue(QString);
    void updateSat(int);
    void updateSat(QString);
    void updateVal(int);
    void updateVal(QString);
signals:
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);
private:
    ColorWheel* mColorWheel;
    QTabWidget* mColorTabs;

    /*-RGB Parameters-*/
    QLabel *mRLabel;
    QSlider *mRSlider;
    QSpinBox *mRSpinBox;

    QLabel *mGLabel;
    QSlider *mGSlider;
    QSpinBox *mGSpinBox;

    QLabel *mBLabel;
    QSlider *mBSlider;
    QSpinBox *mBSpinBox;

    /*-HSV Parameters-*/
    QLabel *mHLabel;
    QSlider *mHSlider;
    QSpinBox *mHSpinBox;

    QLabel *mSLabel;
    QSlider *mSSlider;
    QSpinBox *mSSpinBox;

    QLabel * mVLabel;
    QSlider *mVSlider;
    QSpinBox *mVSpinBox;
};



class ColorWheel : public QLabel
{
    Q_OBJECT
public:
    ColorWheel(QWidget* parent = 0);
    void setRed(int);
    void setGreen(int);
    void setBlue(int);
    void setActualColor(QColor);
    QColor getColor();
    void setHue(int);
    void setSaturation(int);
    void setValue(int);
signals:
    void redChanged(int);
    void blueChanged(int);
    void greenChanged(int);
    void colorChanged(QColor);
protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    void processHSV(QColor col);
    QColor getColorFromPoint(QPoint);
    void processBaseMovePoint();
    QPixmap mPixmap;
    int mHue;
    int mSaturation;
    int mValue;
    int actualRed;
    int actualGreen;
    int actualBlue;
    int primaryRed;
    int primaryBlue;
    int primaryGreen;
    int altRed;
    int altGreen;
    int altBlue;
    QRect primaryColorRect, altColorRect;
    QPoint preciseColor;
    QPoint primaryBasePoint, altBasePoint, centerRectPoint;
    QVector<QPoint>points;
    QPainterPath colorRangeTri;
    double rotationAngle;
    bool mouseDown;
    bool toggleAlt;
};

class TimelineDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    TimelineDockWidget(QWidget *parent = 0);
    virtual ~TimelineDockWidget();
};

class LayerDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    LayerDockWidget(QWidget* parent = 0);
    virtual ~LayerDockWidget();
signals:
    void layerAdded();
    void layerChanged(QTreeWidgetItem*,int);
    void layerChanged(int);
    void compositionModeChanged(int);
    void opacityChanged(int);
public slots:
    void reset();
    void setCompositionMode(int);
    void addLayer();
    void duplicateLayer();
    void groupLayers();
    void ungroupLayers();
    void updateOpacity(int);
    void updateOpacity(QString);
    void addChildLayer(QTreeWidgetItem* parent);
private slots:
    void updateLayer(QTreeWidgetItem*, int);
    void updateCompositonMode(int);
private:
    int m_layerCount;
    QComboBox* m_compositionMode;
    QTreeWidget* m_layerManager;
    QToolButton* m_layerOptionsBtn;
    QLabel* m_opacityLbl;
    QSlider* m_opacitySlider;
    QSpinBox* m_opacitySpinbox;

    QMenu* m_layerOptionsMenu;
    QAction* m_addLayerAct;
    QAction* m_duplicateLayerAct;
    QAction* m_deleteLayerAct;
    QAction* m_groupAct;
    QAction* m_ungroupAct;
};

class DefaultToolPanel : public QWidget{
    Q_OBJECT
public:
    DefaultToolPanel(QWidget* parent = 0);
    ~DefaultToolPanel();
private:
    QString infoString;
};

class TransformTools : public QWidget{
    Q_OBJECT
public:
    TransformTools(QWidget* parent = 0);
    ~TransformTools();
    int getGetTransformMode() const{ return transformMode; }
signals:
    void translateChanged(int, int);
    void rotateChanged(int);
    void scaleChanged(int, int);
    void transformModeChanged(int);
    void useWorldTransform(bool);
    void actionCommitted();
private slots:
    void activateLink(bool);
    void setTransformMode(int);
    void changeToTrans(bool);
    void changeToRot(bool);
    void changeToScal(bool);
    void updateTranslate();
    void updateRotate();
    void updateScale();
    void syncTransX(int);
    void syncTransY(int);
    void syncScalX(int);
    void syncScalY(int);
    void updateWorldTransformUse(bool);
private:
    QRadioButton* m_TranslateBtn;
    QRadioButton* m_RotateBtn;
    QRadioButton* m_ScaleBtn;

    /*-Refinement for transforms-*/

    //Translate
    QLabel* m_TransXLbl;
    QSpinBox* m_TransXSB;
    QLabel* m_TransYLbl;
    QSpinBox* m_TransYSB;
    //Rotate
    QLabel* m_RotLbl;
    QSpinBox* m_RotSB;

    //scale
    QLabel* m_ScalXLbl;
    QSpinBox* m_ScalXSB;
    QLabel* m_ScalYLbl;
    QSpinBox* m_ScalYSB;

    QPushButton* m_LinkTransformBtn;
    bool m_Link4Trans;
    bool m_Link4Rot;
    bool m_Link4Scal;

    QRadioButton* m_WorldTransformBtn;
    QRadioButton* m_LocalTransformBtn;

    QPoint m_Displacement;
    int transformMode;

    QPushButton* m_CommitButton;
};

class TextPanel : public QWidget{
    Q_OBJECT
public:
    TextPanel(QWidget* parent = 0);
    ~TextPanel();
signals:
    void fontChanged(QFont);
    void fontSizeChanged(int);
    void fontBoldChanged(bool);
    void fontItalicChanged(bool);
    void fontUnderlineChanged(bool);
    void actionCommited();
private slots:
    void changeFont(QFont);
    void changeFontSize(int);
    void updateFontBold(bool);
    void updateFontItalic(bool);
    void updateFontUnderline(bool);
    void commitChanges();
private:
    QFont m_Font;
    int m_FontSize;
    QFontComboBox* m_FontComboBox;
    QSpinBox* m_FontSizeSB;
    QPushButton* m_CommitButton;
    QPushButton* m_BoldBtn;
    QPushButton* m_ItalicBtn;
    QPushButton* m_UnderlineBtn;
};

/*Manage the primitive panel*/
class PrimitivePanel : public QWidget{
    Q_OBJECT
public:
    PrimitivePanel(QWidget* parent = 0);
    ~PrimitivePanel();
signals:
    void widthChanged(int);
    void heightChanged(int);
    void penWidthChanged(int);
    void pointCountChanged(int);
    int shapeModeChanged(int);
    void actionCommited();
public slots:
    void changeWidth(int);
    void changeHeight(int);
private slots:
    void updateWidth(int);
    void updateWidth(QString);
    void updateHeight(int);
    void updateHeight(QString);
    void updatePenWidth(int);
    void updatePointCount(int);
    void commitChanges();
    /*
    *
    *   Note
    *
    * Shape diffrentiation is determined by the following codes
    *  0 - Line Mode
    *  1 - Concave Mode
    *  2 - Convex Mode
    *
    */
    void setLineMode(bool);
    void setConcaveMode(bool);
    void setConvexMode(bool);
private:
    QRadioButton* m_isLineBtn;
    QRadioButton* m_isConcaveBtn;
    QRadioButton* m_isConvexBtn;
    QButtonGroup* m_concaveGrp;

    QLabel* m_PointCountLbl;
    QSpinBox* m_PointSB;

    QLabel* m_PenWidthLbl;
    QSpinBox* m_PenWidthSB;

    QLabel* m_WidthLbl;
    QSlider* m_WidthSlider;
    QSpinBox* m_WidthSB;

    QLabel* m_HeightLbl;
    QSlider* m_HeightSlider;
    QSpinBox* m_HeightSB;

    QPushButton* m_CommitBtn;
};

/*Brush related additional options*/
class BrushPanel : public QWidget{
    Q_OBJECT
public:
    BrushPanel(QWidget* parent = 0);
    ~BrushPanel();
private:
    QCheckBox* m_SteadyStrokeChbx;
};

/*-Tools Panel-*/
class ToolsPanel : public QDockWidget{
    Q_OBJECT
public:
   ToolsPanel(QWidget* parent = 0);
   ~ToolsPanel();
signals:
   void translateChanged(int, int);
   void rotateChanged(int);
   void scaleChanged(int, int);
   void transformModeChanged(int);
   void useWorldTransform(bool);
   void fontChanged(QFont);
   void fontSizeChanged(int);
   void fontBoldChanged(bool);
   void fontItalicChanged(bool);
   void fontUnderlineChanged(bool);
   void actionCommitted();
public slots:
   void setMode(int);
   void updateTranslate(int, int);
   void updateRotate(int);
   void updateScale(int, int);
   void updateTransformMode(int);
   void updateWorldTransform(bool);
   void updateFont(QFont);
   void updateFontSize(int);
   void updateFontBold(bool);
   void updateFontItalic(bool);
   void updateFontUnderline(bool);
   void updateActionCommit();
private:
   TransformTools* transTools;
   DefaultToolPanel* defTools;
   TextPanel* textPanel;
   PrimitivePanel* primPanel;
   QStackedWidget* panelSpace;
};



#endif // DOCKWIDGETS_H
