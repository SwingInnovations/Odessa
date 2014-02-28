#include "editor.h"

Editor::Editor(QWidget *parent): QWidget(parent), currentFrame(0), currentIndex(0), numOfFramesPerSecond(24)
{
    deviceDown = false;
    setAutoFillBackground(true);
    brush = Brush();
    redVal = 0;
    greenVal = 0;
    blueVal = 0;
    opacityVal = 255;
    brush.setColor(Qt::black);
    brush.setBrush(QBrush(Qt::SolidPattern));
    brush.setWidth(5);
    currentTool = brush;
    eraser = Brush();
    eraser.setWidth(5);
    eraser.setColor(QColor(Qt::white));
    eraser.setBrush(QBrush(Qt::SolidLine));
    toolType = BRUSH_TOOL;
}

void Editor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!mIndex.isEmpty())
    {
        mIndex.at(currentIndex-1)->getImage()->paintImage(painter);
    }

    if(!rIndex.isEmpty())
    {
        rIndex.at(currentFrame-1)->getImage()->paintImage(painter);
    }

    qDebug() << currentIndex << endl;
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    if(!mIndex.isEmpty() || !rIndex.isEmpty())
    {
        deviceDown = true;
        drawPath[0] = drawPath[1] = drawPath[2] = event->pos();
    }
    qDebug() << "Mouse Pressed" << endl;
    update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    if(deviceDown)
    {
        deviceDown = false;
    }
    update();
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{

    drawPath[2] = drawPath[1];
    drawPath[1] = drawPath[0];
    drawPath[0] = event->pos();

    if(deviceDown)
    {
        mIndex.at(0)->getImage()->paintImage(event, currentTool, drawPath);
    }
    update();
}

void Editor::tabletEvent(QTabletEvent *event)
{

    switch(event->type())
    {
    case QEvent::TabletPress:
        if(!deviceDown)
        {
            deviceDown = true;
            drawPath[0] = drawPath[1] = drawPath[2] = event->pos();
        }  

        break;
    case QEvent::TabletRelease:
        if(deviceDown)
        {
            deviceDown = false;
        }

        break;
    case QEvent::TabletMove:

        drawPath[2] = drawPath[1];
        drawPath[1] = drawPath[0];
        drawPath[0] = event->pos();

        if(deviceDown)
        {
            //currentTool.setColor(primaryColor);
            mIndex.at(currentIndex-1)->getImage()->paintImage(event, currentTool, drawPath);
        }

    default:
        break;
        qDebug() << "Nothing Happening" << endl;
    }

    update();
}

void Editor::addLayer(int width, int height)
{
    mIndex.append(new Layer(Layer::Bitmap, currentIndex, width, height));
    currentIndex++;
}

void Editor::newProject(int type, int width, int height, int dpi)
{

    if(!mIndex.isEmpty())
    {
        mIndex.clear();
        currentIndex = 0;
    }else{
        switch(type)
        {
        case 0:
            //create Standard Image
            mIndex.append(new Layer(Layer::Bitmap, currentIndex, width, height));
            currentIndex++;
            break;
        case 1:
            //create Animation
            break;
        case 2:
            //create SpriteSheet
            break;
        default:
            break;
        }
    }
    update();
}

void Editor::setBrush(ToolType type)
{
    toolType = type;
    switch(type)
    {
    case BRUSH_TOOL:
        currentTool = brush;
        currentTool.setColor(primaryColor);
        emit brushSizeChanged(brush.getSize());
        break;
    case ERASER_TOOL:
        currentTool = eraser;
        emit brushSizeChanged(eraser.getSize());
    default:
        break;
    }
}

void Editor::setBrushSize(int val)
{
    currentTool.setWidth(val);
    switch(toolType)
    {
    case BRUSH_TOOL:
        qDebug() << "Setting Brush Width" << endl;
        brush.setWidth(val);
        break;
    case ERASER_TOOL:
        eraser.setWidth(val);
        break;
    default:
        break;
    }
}

void Editor::setBrushFeather(int val)
{

}

void Editor::setBrushSpacing(int val)
{

}

void Editor::setRedValue(int val)
{
    redVal = val;
    primaryColor.setRed(redVal);
    currentTool.setColor(primaryColor);
    if(primaryColor.isValid())
    {
        qDebug() << "I am valid!" << endl;
    }else{
        qDebug() << "No Longer Valid" << endl;
    }
}

void Editor::setGreenValue(int val)
{
    greenVal = val;
    primaryColor.setGreen(greenVal);
    currentTool.setColor(primaryColor);
    if(primaryColor.isValid())
    {
        qDebug() << "I am valid!" << endl;
    }else{
        qDebug() << "No Longer Valid" << endl;
    }
}

void Editor::setBlueValue(int val)
{
    blueVal = val;
    primaryColor.setBlue(blueVal);
    currentTool.setColor(primaryColor);
    if(primaryColor.isValid())
    {
        qDebug() << "I am valid!" << endl;
    }else{
        qDebug() << "No Longer Valid" << endl;
    }
}

void Editor::setOpacity(int val)
{
    opacityVal = val;
    primaryColor.setAlpha(opacityVal);
    currentTool.setColor(primaryColor);
    if(primaryColor.isValid())
    {
        qDebug() << "I am valid!" << endl;
    }else{
        qDebug() << "No Longer Valid" << endl;
    }
}

void Editor::setOpacityTransfer(int val)
{

}

void Editor::setSizeTransfer(int val)
{
    if(val == NULL)
    {
        val = 0;
    }else{
        currentTool.setTransferWidthAmount(val);
        switch(toolType)
        {
        case BRUSH_TOOL:
            brush.setTransferWidthAmount(val);
            break;
        case ERASER_TOOL:
            eraser.setTransferWidthAmount(val);
            break;
        default:
            break;
        }
    }
}
