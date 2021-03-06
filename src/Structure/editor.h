#ifndef EDITOR_H
#define EDITOR_H

#include <QLabel>
#include <QVector>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QDebug>
#include <QPoint>
#include <QPixmap>
#include <QPointer>
#include <QMimeData>
#include <QClipboard>
#include <QApplication>
#include <QFontMetrics>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>
#include <QTimer>

#include "../Interface/dialogwindows.h"
#include "layer.h"
#include "brush.h"
#include "primitive.h"
#include "canvasthread.h"

#ifdef Q_OS_WIN
#include <wingdi.h>
#endif

class Editor;
class ProjectInfo;

class HistoryStack : public QObject
{
    Q_OBJECT
public:
    enum ActivityType{UNDEFINED, BITMAP_CHANGE};
    virtual int type(){return UNDEFINED;}
    virtual void restore(Editor*){}
};

class BitmapHistoryStack : public HistoryStack
{
  Q_OBJECT
public:
    int m_Layer, m_Frame;
    BitmapImage m_Bitmap;
    int type() override
    {
        return BITMAP_CHANGE;
    }
    void restore(Editor*) override {}
};

class Editor : public QWidget
{
    Q_OBJECT
public:
    enum ToolType
    {
      BRUSH_TOOL = 0,
      ERASER_TOOL,
      TEXT_TOOL,
      PRIMITIVE_TOOL,
      EYEDROPPER_TOOL,
      RECT_SELECT_TOOL,
      FILL_TOOL,
      TRANSFORM_TRANSLATE,
      TRANSFORM_ROTATE,
      TRANSFORM_SCALE,
      CURSOR_TOOL
    };

    Editor(QWidget *parent = 0);
    ~Editor();

    void setBrush(Brush b);
    void setBrush(ToolType type);
    int getHistoryStep()const{ return m_HistorySteps; }
    int getRealWidth()const;
    int getRealHeight()const;
    inline ProjectInfo getProjectInfo()const{ return m_Info; }
    QPixmap getSelectionPixmap();
    inline QSize getPixmapSize() const
    {
        if(!m_Layers.isEmpty())
        {
            return m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size();
        }else{
            return QSize();
        }
    }

    QPixmap getCurrentImage();
    void setBrushColor(const QColor& color);
    QColor getCurrentBrushColor() const;
signals:
    void mousePositionChanged(QPoint);
    void brushPressureChanged(qreal);
    void curToolPressureChanged(qreal);
    void brushSizeChanged(int);
    void brushFeatherChanged(int);
    void brushOpacityChanged(int);
    void brushSpacingChanged(int);
    void brushToolSelected();
    void eraserToolSelected();
    void cursorToolSelected();
    void currentIndexChanged(int);
    void currentFrameChanged(int);

    void layerPreviewChanged(int, QPixmap);

    void boldToggled();
    void italicToggled();
    void underlineToggled();

    void currentColorChanged(QColor);
    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);

    void clipTranslateChanged(int, int);
    void clipRotateChanged(int);
    void clipScaleChanged(int, int);

    void toolChanged(int);
    void commitAction();

    void historyLimitChanged(int);
    void historySizeChanged(int);

    void submitCanvasThreadJob(CanvasWorker::CanvasJobParam JobParam);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
public slots:
    void newProject(ProjectInfo&);

    void addLayer();
    void setLayerIndex(int);
    void setLayerOpacity(int);
    void setLayerCompositionMode(int);
    void setLayerVisible(int);
    void setLayerVisible(bool);
    void deleteLayer(int);
    void addFrame();

    void backup();
    void backup(int backupLayer,int backupFrame);

    void deselect();

    void undo();
    void redo();

    void cut();
    void copy();
    void paste();

    void setHistoryLimit(int);

    void scale(double scaleVal);
    void resetScale();

    void setBrushStencil(QPixmap);

    void setBrushSize(int);
    void setBrushSpacing(int);

    void setSizeTransfer(int);
    void setOpacityTransfer(int);

    void setRedValue(int);
    void setGreenValue(int);
    void setBlueValue(int);
    void setOpacity(int);

    void setClipTranslate(int, int);
    void setClipRotate(int);
    void setClipScale(int, int);

    void setFont(QFont);
    void setFontSize(int);
    void setBold(bool);
    void setItalic(bool);
    void setUnderline(bool);
    void commitChanges();

    void setClipOffsetX(int);
    void setClipOffsetY(int);
    void useWorldTransform(bool);

    /**
     * @brief useWindowsPenAPI
     * @param flag
     */
    void useWindowsPenAPI(bool);

    void alternateTBlinker();

    /**
     * @brief canvasJobComplete
     * @param ResultParam
     */
    void canvasJobComplete(CanvasWorker::CanvasJobResultParam& ResultParam);
private:
    /*-Control mode, for use with either full view of sprite sheet or normal use
     *  0 - Normal mode
     *  1 - Spritesheet overview mode
     * -*/
    int m_ControlMode = 0;

    void shiftLayerForward();
    void shiftLayerBack();

    void increaseOpacity();
    void decreaseOpacity();

    void increaseBrushSize();
    void decreaseBrushSize();

    void handleJobSubmission(CanvasWorker::CanvasJobParam& JobParam);

    QPixmap generateShapePixmap(Primitive);

    bool m_DeviceDown;
    bool m_TabletInUse;
    bool m_Modified;
    bool m_SelectActive;

    QString addText(int, QChar);
    QString addText(int, QString);

    Brush m_CurrentTool;
    Brush m_Brush;
    Brush m_Eraser;
    Primitive m_Primitive;

    QPainter::CompositionMode m_CompMode;

    QPoint m_DrawPoint;
    QVector<QPointF> m_MousePath;
    QPainterPath* m_PainterPath;
    QRect m_SelectRect;

    qreal m_Pressure;
    qreal m_XTilt;
    qreal m_YTilt;

    double m_ScaleFactor;

    int m_CurrentFrame;
    int m_CurrentIndex;
    int m_LastIndex;
    QVector<Layer*> m_Layers;

    ToolType m_ToolType;
    QPixmap m_Pix;

    int m_RedVal, m_GreenVal, m_BlueVal, m_OpacityVal;

    //Local Pimary and secondary color.
    QColor m_PrimaryColor;
    QColor m_SecondaryColor;

    QVector<HistoryStack*> m_HistoryStack;
    int m_HistorySteps;
    int m_BackupIndex;

//Other Keyboard things
    int m_keyEntry[2];
    bool m_useCustomCombo;

//Clipboard stuff
    QString m_Text;
    bool m_isBold;
    bool m_isItalic;
    bool m_isUnderline;
    bool m_acceptTextInput;
    bool m_ShiftEnabled;
    QFont m_Font;
    int m_FontSize;
    int m_textCursorPos;
    QPixmap generateTextPixmap();

//New TextEditor tools
    QTextDocument *m_textDocument;
    QTextCursor m_textCursor;
    QTextCharFormat m_fmt;

    QTimer *m_tCursorBlinker;
    bool m_tCursorBlink;

    //Clipboard stuff.
    bool m_ClipWorldTransform;
    QPoint m_ClipOffsetPoint;
    QPoint m_ClipScale;
    double m_ClipScaleFactor;
    int m_ClipRotateAngle;
    QPixmap m_ClipboardPixmap;
    bool m_ClipboardPresent;
    bool m_AlternatePattern;

    ProjectInfo m_Info;

    int m_realWidth;
    int m_realHeight;

    QPixmap             m_tempDrawPixmap;
    QRect               m_tempDrawArea;

    CanvasWorker*       m_canvasWorker;
    QThread             m_canvasThread;
#ifdef Q_OS_WIN32
    bool m_useWinInkAPI = false;
#endif
    long m_startTime,m_endTime;
};

#endif // EDITOR_H
