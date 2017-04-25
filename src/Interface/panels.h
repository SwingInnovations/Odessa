#ifndef PANELS_H
#define PANELS_H


#include <QWidget>
#include <QWidgetAction>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <QStackedWidget>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QGroupBox>
#include <QCheckBox>
#include <QTabWidget>
#include <QComboBox>
#include <QFile>
#include <QSettings>
#include <QMessageBox>

#include "../Structure/brush.h"
#include "../Overloads.h"

#include "slideedit.h"

/**
 * @brief The BrushConfigPanel class
 *
 */
class BrushConfigPanel : public QWidget
{
    Q_OBJECT
public:
    enum BrushShape{CIRCLE, SQUARE, CUSTOM};
    BrushConfigPanel(QWidget* parent = 0);
signals:
    void brushWidthChanged(int);
    void brushOpacityChanged(int);
    void brushSpacingChanged(qreal);
    void brushTransferSizeChanged(int);
    void brushTransferOpacityChanged(int);
    void stencilChanged(QPixmap);

public slots:
    void updateBrushSize(int);
    void updateBrushSize(qreal);
    void updateBrushOpacity(int);
    void updateBrushOpacity(qreal);
    void updateBrushSpacing(qreal);
    void updateTransferSize(qreal);
    void updateTransferOpacity(qreal);
    void toggleTransferSize(bool);
    void toggleTransferOpacity(bool);

private slots:
    void updateCurrentBrushIndex(int newInd);
    void loadBrushAct();
    void loadbrushLibAct();
    void saveBrushAct();
    void saveBrushLibAct();
    void updateStencilWidth(qreal);
    void updateStencilHeight(qreal);
    void updateStencilHardness(qreal);
    void updateStencilRotate(qreal);
    void updateBrushShape(int);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    void initGUI();
    void updateStencilPreview();        //TODO Implement this
    bool            m_inCustom;
    QLineEdit*      m_nameLE;
    QLabel*         m_StencilPrvwLbl;
    QLabel*         m_StrokePrvwLbl;
    QPushButton*    m_openDockBtn;

    QListWidget*    m_brushListWidget;
    SlideEdit*      m_brushSizeSE;
    SlideEdit*      m_opacitySE;
    SlideEdit*      m_spacingSE;
    QComboBox*      m_drawModeCmbx;
    QCheckBox*      m_transferSizeCB;
    SlideEdit*      m_transferSizeSE;
    QCheckBox*      m_transferOpacityCB;
    SlideEdit*      m_transferOpacitySE;

    QCheckBox*      m_steadyStroke;
    QGroupBox*      m_steadyStrokeSettings;

    QTabWidget*     m_WorkSpaceWidget;

    QPushButton*    m_AddBrushBtn;
    QPushButton*    m_RemoveBrushBtn;
    QToolButton*    m_OtherOptBtn;
    QMenu*          m_OptMenu;
    QAction*        m_LoadBrushLibraryAct;
    QAction*        m_SaveBrushLibraryAct;
    QAction*        m_LoadBrushAct;
    QAction*        m_SaveBrushAct;
    QAction*        m_LoadStencilAct;
    QAction*        m_SaveStencilAct;

    /*-Stencil Class-*/
    QLabel*         m_StencilPreviewLbl;
    SlideEdit*      m_StencilWidthSE;
    SlideEdit*      m_StencilHeightSE;
    SlideEdit*      m_HardnessSE;
    SlideEdit*      m_RotateSE;
    QGroupBox*      m_transferWidget;
    QComboBox*      m_StencilShapeCmbx;

    BrushShape      m_currentBrushShape;

    unsigned int    m_currentBrushIndex;

    QPixmap         m_currentStencil;
    QPixmap         m_StrokePreview;
    QPixmap         m_stencilPreview;

    void            GenerateStencilPreview();

    void readSettings();
    void writeSettings();

    QString m_ProjectPath;
    QString m_BrushLib;

    Brush loadBrush(QString filePath);
    void saveBrushLib(QString filePath);
    QVector<Brush> loadBrushLib(QString filePath);

    void list_addBrush(Brush brush);


    //Internal File stuff
    QVector<Brush> m_TempBrushList;
    QVector<Brush> m_ActualBrushList;
    void generateStrokePreview();
};

class ColorConfigPanel : public QWidget{
public:
    ColorConfigPanel(QWidget* parent = 0);
    virtual ~ColorConfigPanel();
};

#endif // PANELS_H