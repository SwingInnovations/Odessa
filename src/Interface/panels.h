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
#include <QColor>
#include <QDataStream>
#include <QFile>
#include <QPaintEvent>

#include "../Structure/brush.h"
#include "../Overloads.h"
#include "../Structure/editor.h"
//TODO Move color wheel to its own widget panel.
#include "colorwheel.h"

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
    Brush getStartingBrush()const;
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

//Color specific properties
/**
 * @brief The ColorCell class
 * Holds the color, assigns it to active brush in Editor
 */
class ColorCell : public QWidget
{
    Q_OBJECT
public:
    ColorCell(QColor color, QWidget* parent, Editor* editor = 0);
    void SetColor(QColor color);
    inline QColor GetColor()const{ return m_color; }
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    Editor*     m_editor;
    QColor      m_color;
};

/**
 * @brief The ColorPalleteInfo struct Contains Color Pallete info that can be saved/Loaded from disk
 */
struct ColorPalleteInfo {
    uint    numColors = -1;
    QColor  colors[256];
    uint    rows = 0;
    uint    cols = 0;

    /**
     * @brief operator <<
     * @param out
     * @param colorPallete
     * @return
     */
    friend inline QDataStream &operator <<(QDataStream& out, const ColorPalleteInfo& colorPallete)
    {
        out << colorPallete.numColors;
        out << colorPallete.rows;
        out << colorPallete.cols;
        for(const QColor& color : colorPallete.colors)
        {
            out << color;
        }
        return out;
    }

    /**
     * @brief operator >>
     * @param in
     * @param colorPallete
     * @return read file
     */
    friend inline QDataStream &operator >>(QDataStream& in, ColorPalleteInfo& colorPallete)
    {
        QColor color;

        in >> colorPallete.numColors;
        in >> colorPallete.rows;
        in >> colorPallete.cols;
        for(uint i = 0; i < colorPallete.numColors; i++)
        {
            in >> color;
            colorPallete.colors[i] = color;
        }

        return in;
    }
};

/**
 * @brief The ColorConfigPanel class
 * Revamped Color panel
 */
class ColorConfigPanel : public QWidget
{
    Q_OBJECT
public:
    enum ColorConfigOrientation : char {
        Vertical,
        Horizontal
    };
    ColorConfigPanel(QWidget* parent = 0, Editor* editor = 0, ColorConfigOrientation orientation = ColorConfigOrientation::Horizontal);
    virtual ~ColorConfigPanel();
signals:
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);

public slots:
    /**
     * @brief updateColorFromEditor
     * @param color
     */
    void updateColorFromEditor(QColor);
private slots:
    void updateRed(qreal);
    void updateGreen(qreal);
    void updateBlue(qreal);
    void updateColor(QColor);
    void loadColorPalleteAct();
    void saveColorPalleteAct();
    void toggleColorPicker();
private:
    void updateHSV(QColor);
    void initGui(ColorConfigOrientation orientation);
    void readFromLastPallette();
    void loadPallete(QString filePath);
    void savePallete(QString filePath);
    Editor* m_editor;
    ColorWheel* m_colorWheel;

    SlideEdit*  m_RSlider;
    SlideEdit*  m_GSlider;
    SlideEdit*  m_BSlider;

    SlideEdit*  m_HSlider;
    SlideEdit*  m_SSlider;
    SlideEdit*  m_VSlider;

    QString     m_currentPalletString;
    ColorPalleteInfo m_currentPallete;
    bool        m_colorPalleteLoaded;
    uint        m_rows;
    uint        m_cols;

};

#endif // PANELS_H
