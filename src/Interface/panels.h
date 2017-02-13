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

private slots:
    void updateBrushSize(qreal);
    void updateBrushOpacity(qreal);
    void updateBrushSpacing(qreal);
    void updateTransferSize(qreal);
    void updateTransferOpacity(qreal);
    void toggleTransferSize(bool);
    void toggleTransferOpacity(bool);
private:
    void initGUI();
    void updateStencilPreview();        //TODO Implement this
    QLineEdit*      m_nameLE;
    QLabel*         m_StencilPrvwLbl;
    QLabel*         m_StrokePrvwLbl;
    QPushButton*    m_openDockBtn;

    QListWidget*    m_brushListWidget;
    SlideEdit*      m_brushSizeSE;
    SlideEdit*      m_opacitySE;
    SlideEdit*      m_spacingSE;
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
    QAction*        m_LoadStencilAct;
    QAction*        m_SaveStencilAct;

    /*-Stencil Class-*/
    QLabel*         m_StencilPreviewLbl;
    SlideEdit*      m_StencilWidthSE;
    SlideEdit*      m_StencilHeightSE;
    SlideEdit*      m_HardnessSE;
    SlideEdit*      m_RotateSE;
    QGroupBox*      m_transferWidget;

    BrushShape      m_currentBrushShape;
};

class ColorConfigPanel : public QWidget{
public:
    ColorConfigPanel(QWidget* parent = 0);
    virtual ~ColorConfigPanel();
};

#endif // PANELS_H
