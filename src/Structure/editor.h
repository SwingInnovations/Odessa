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

#include "../Interface/dialogwindows.h"
#include "layer.h"
#include "brush.h"

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
    int type(){return BITMAP_CHANGE;}
    void restore(Editor*){}
};

class Editor : public QLabel
{
    Q_OBJECT
public:

    enum ToolType{BRUSH_TOOL,
                  ERASER_TOOL,
                  TEXT_TOOL,
                  PRIMITIVE_TOOL,
                  EYEDROPPER_TOOL,
                  RECT_SELECT_TOOL,
                  FILL_TOOL,
                  TRANSFORM_TRANSLATE,
                  TRANSFORM_ROTATE,
                  TRANSFORM_SCALE };

    Editor(QWidget *parent = 0);

    void setBrush(Brush b);
    void setBrush(ToolType type);
    int getHistoryStep()const{ return m_HistorySteps; }
    ProjectInfo getProjectInfo()const{ return m_Info; }
    QSize getPixmapSize(){
        if(!m_Layers.isEmpty())
        {
            return m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size();
        }else{
            return QSize();
        }
    }

signals:
    void brushSizeChanged(int);
    void brushFeatherChanged(int);
    void brushOpacityChanged(int);
    void brushSpacingChanged(int);

    void redChanged(int);
    void greenChanged(int);
    void blueChanged(int);

    void clipTranslateChanged(int, int);
    void clipRotateChanged(int);
    void clipScaleChanged(int, int);

    void toolChanged(int);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);

public slots:
    void newProject(ProjectInfo&);

    void addLayer();
    void addFrame();

    void backup();
    void backup(int backupLayer,int backupFrame);

    void deselect();

    void undo();
    void redo();

    void cut();
    void copy();
    void paste();

    void setHistoyStep(int);

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

    void commitChanges();

    void setClipOffsetX(int);
    void setClipOffsetY(int);
    void useWorldTransform(bool);
private:

    void shiftLayerForward();
    void shiftLayerBack();

    bool m_DeviceDown;
    bool m_TabletInUse;
    bool m_Modified;
    bool m_SelectActive;

    Brush m_CurrentTool;
    Brush m_Brush;
    Brush m_Eraser;

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
    QVector<Layer*> m_Layers;

    ToolType m_ToolType;
    QPixmap m_Pix;

    int m_RedVal, m_GreenVal, m_BlueVal, m_OpacityVal;

    QColor m_PrimaryColor;
    QColor m_SecondaryColor;

    QVector<HistoryStack*> m_HistoryStack;
    int m_HistorySteps;
    int m_BackupIndex;

//Clipboard stuff
    QFont m_Font;
    int m_FontSize;
    bool m_ClipWorldTransform;
    QPoint m_ClipOffsetPoint;
    QPoint m_ClipScale;
    double m_ClipScaleFactor;
    int m_ClipRotateAngle;
    QPixmap m_ClipboardPixmap;
    bool m_ClipboardPresent;
    bool m_AlternatePattern;

    ProjectInfo m_Info;
};

#endif // EDITOR_H
