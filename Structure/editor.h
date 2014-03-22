#ifndef EDITOR_H
#define EDITOR_H

#include <QLabel>
#include <QVector>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPoint>
#include <QPixmap>
#include <QPointer>

#include "layer.h"
#include "brush.h"

class Editor : public QLabel
{
    Q_OBJECT
public:

    enum ToolType{BRUSH_TOOL, ERASER_TOOL, TEXT_TOOL, PRIMITIVE_TOOL, EYEDROPPER_TOOL, RECT_SELECT_TOOL};

    Editor(QWidget *parent = 0);

    void setBrush(ToolType type);
    QSize getPixmapSize(){
        if(!m_Layers.isEmpty())
        {
            return m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size();
        }else{

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

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);

public slots:
    void newProject(int type, int width, int height, int dpi);

    void addLayer();
    void addFrame();

    void setBrushSize(int);
    void setBrushFeather(int);
    void setBrushSpacing(int);

    void setSizeTransfer(int);
    void setOpacityTransfer(int);

    void setRedValue(int);
    void setGreenValue(int);
    void setBlueValue(int);
    void setOpacity(int);
private:

    bool m_DeviceDown;
    bool m_TabletInUse;
    Brush m_CurrentTool;
    Brush m_Brush;
    Brush m_Eraser;

    QPoint m_DrawPoint;
    QPoint m_DrawPath[3];

    int m_CurrentFrame;
    int m_CurrentIndex;
    QVector<Layer*> m_Layers;

    ToolType m_ToolType;
    QPixmap m_Pix;
    QImage m_Img;

    int m_RedVal, m_GreenVal, m_BlueVal, m_OpacityVal;

    QColor m_PrimaryColor;
    QColor m_SecondaryColor;
};

#endif // EDITOR_H
