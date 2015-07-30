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

#include "../Structure/brush.h"
#include "../Structure/editor.h"
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
    bool isFirstRun();
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

    QString m_BrushLib;
    QString m_ProjectPath;
    int m_CurrentBrushIndex;
    QTabWidget* m_TabWidget;

    /*--General Parameters--*/
    GeneralBrushWidget* m_GenBrushWidget;
    QComboBox* m_DrawModeCmbx;
    /*-Size-*/
    QLabel* m_SizeLabel;
    QSlider* m_SizeSlider;
    QSpinBox* m_SizeLE;

    /*-Opacity-*/
    QLabel* m_OpacityLabel;
    QSlider* m_OpacitySlider;
    QSpinBox* m_OpacityLE;

    /*-Spacing-*/
    QLabel* m_SpacingLabel;
    QSlider* m_SpacingSlider;
    QSpinBox* m_SpacingLE;

    /*--Transfer--*/
    QGroupBox* m_transGrpBox;
    /*-TransferSize-*/
    QCheckBox* m_TransferSizeToggle;
    QSlider* m_TransferSizeSlider;
    QSpinBox* m_TransferSizeLE;

    /*-TransferOpacity-*/
    QCheckBox* m_TransferOpacityToggle;
    QSlider* m_TransferOpacitySlider;
    QSpinBox* m_TransferOpacityLE;

    /*--Custom--*/
    CustomBrushWidget* m_StencilWidget;

    /*-Data-*/
    QVector<Brush> m_TempBrushList;
    QVector<Brush> m_ActualBrushList;

    bool m_firstTimeRun;

};

class GeneralBrushWidget : public QWidget
{
    Q_OBJECT
public:
    GeneralBrushWidget();
    virtual ~GeneralBrushWidget();
    void addBrush(int iD, Brush brush);
    void addBrush(Brush brush);
    void setBrushIndex(int val){this->m_CurrentBrushIndex = val;}
    void setDir(QString dir){this->m_Dir = dir;}
    int getBrushIndex(){return this->m_CurrentBrushIndex;}
    QString getDir(){return this->m_Dir;}
    void setStencilPixmap(QPixmap);
    void activateUsePressureWidth(bool);
    void generateStrokePreview();
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
    void updateBrushLibIndex(int val){m_CurrentBrushIndex = val; emit brushLibIndexChanged(val);}
    void updateStencil(QPixmap);
    void updateName(QListWidgetItem* item);
    void showStencil(bool);
    void showStroke(bool);
protected:
    void resizeEvent(QResizeEvent *);
private:
    bool m_usePressureWidth;
    unsigned int m_CurrentBrushIndex;
    QString m_Dir;
    QPixmap m_StrokePreview;
    QPixmap m_StencilPreview;
    qreal m_minSize;
    qreal m_maxSize;
    QPushButton* m_showStencilBtn;
    QPushButton* m_showStrokeBtn;
    QLabel* m_PreviewLabel;
    QListWidget* m_BrushIndex;
    QToolButton* m_ToolBtn;
    QMenu* m_ToolMenu;
    QAction* m_LoadStencilAct;
    QAction* m_LoadBrushAct;
    QAction* m_LoadBrushSetAct;
    QAction* m_SaveStencilAct;
    QAction* m_SaveBrushAct;
    QAction* m_SaveBrushSetAct;
    QAction* m_DeleteBrushAct;
};

class CustomBrushWidget : public QWidget
{
    Q_OBJECT
public:
    enum BrushShape{LINE_SHAPE, CIRCLE_SHAPE, SQUARE_SHAPE, CUSTOM};
    CustomBrushWidget();
    virtual ~CustomBrushWidget();
    void SetDir(QString dir){this->m_Dir = dir;}
    void TempSave(QPixmap);
    QString GetDir(){return this->m_Dir;}
    QPixmap GetPixmap(){return m_StencilPreview;}
    void setBrushSettings(Brush);
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

    QString m_Dir;

    /*--Custom--*/
    QLabel* m_StencilLbl;
    QPixmap m_StencilPreview;
    QPixmap m_StencilTexture;
    bool m_HasTexture;

    /*-Width-*/
    QLabel* m_WidthLbl;
    QSlider* m_WidthSlider;
    QLineEdit* m_WidthLE;

    /*-Height-*/
    QLabel* m_HeightLbl;
    QSlider* m_HeightSlider;
    QLineEdit* m_HeightLE;

    /*-Hardness-*/
    QLabel* m_HardnessLbl;
    QSlider* m_HardnessSlider;
    QLineEdit* m_HardnessLE;

    /*-Rotate-*/
    QLabel* m_RotateLbl;
    QSlider* m_RotateSlider;
    QLineEdit* m_RotateLE;

    /*-SelectShape-*/
    BrushShape m_BrushShape;
    QPushButton* m_CircleButton;
    QPushButton* m_SquareButton;
    QPushButton* m_CustomButton;

    QLabel* m_TextureLbl;
    QLineEdit* m_TextureFileLE;
    QPushButton* m_TextureBtn;

    /*-Tool_Menu-*/
    QToolButton* m_ToolBtn;
    QMenu* m_ToolMenu;
    QAction* m_LoadStencilAct;
    QAction* m_LoadBrushAct;
    QAction* m_LoadBrushSetAct;
    QAction* m_SaveStencilAct;
    QAction* m_SaveBrushAct;
    QAction* m_SaveBrushSetAct;
    QAction* m_DeleteBrushAct;
    /*-File Stuff-*/
    QTemporaryFile m_TempFile;
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
    ColorWheel* m_ColorWheel;
    QTabWidget* m_ColorTabs;

    /*-RGB Parameters-*/
    QLabel *m_RLabel;
    QSlider *m_RSlider;
    QSpinBox *m_RSpinBox;

    QLabel *m_GLabel;
    QSlider *m_GSlider;
    QSpinBox *m_GSpinBox;

    QLabel *m_BLabel;
    QSlider *m_BSlider;
    QSpinBox *m_BSpinBox;

    /*-HSV Parameters-*/
    QLabel *m_HLabel;
    QSlider *m_HSlider;
    QSpinBox *m_HSpinBox;

    QLabel *m_SLabel;
    QSlider *m_SSlider;
    QSpinBox *m_SSpinBox;

    QLabel* m_VLabel;
    QSlider *m_VSlider;
    QSpinBox *m_VSpinBox;
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
    QPixmap m_Pixmap;
    int m_Hue;
    int m_Saturation;
    int m_Value;
    int m_ActualRed;
    int m_ActualGreen;
    int m_ActualBlue;
    int m_PrimaryRed;
    int m_PrimaryBlue;
    int m_PrimaryGreen;
    int m_AltRed;
    int m_AltGreen;
    int m_AltBlue;
    QRect m_PrimaryColorRect, m_AltColorRect;
    QPoint m_PreciseColor;
    QPoint m_PrimaryBasePoint, m_AltBasePoint, m_CenterRectPoint;
    QVector<QPoint>m_Points;
    QPainterPath m_ColorRangeTri;
    double m_RotationAngle;
    bool m_MouseDown;
    bool m_toggleAlt;
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
    void toggleLayerVisible(bool);
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
    void updateLayerPreview(int, QPixmap);
private slots:
    void updateLayer(QTreeWidgetItem*, int);
    void updateLayerInfo(QTreeWidgetItem*, int);
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
public slots:
    void toggleBold();
    void toggleItalic();
    void toggleUnderline();
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
    void shapeModeChanged(int);
    void lineColorChanged(QColor);
    void fillColorChanged(QColor);
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
    void updateLineColor();
    void updateFillColor();
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

    QLabel* m_lineColorLbl;
    QPushButton* m_lineColorBtn;
    QColor m_lineColor;

    QLabel* m_fillColorLbl;
    QPushButton* m_fillColorBtn;
    QColor m_fillColor;

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
   void toggleBold();
   void toggleItalic();
   void toggleUnderline();
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
