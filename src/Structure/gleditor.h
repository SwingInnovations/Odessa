#ifndef GLEDITOR_H
#define GLEDITOR_H

#include <QOpenGLWidget>
#include "editor.h"

class GLEditor : public QOpenGLWidget
{
public:
    GLEditor(QWidget* parent = 0);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void tabletEvent(QTabletEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

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
    void backup(int backupLayer, int backupFrame);

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

    void alternateTBlinker();

private:
};

#endif // GLEDITOR_H
