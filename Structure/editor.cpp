#include "editor.h"

Editor::Editor(QWidget *parent):QLabel(parent)
{
    m_DeviceDown = false;
    m_TabletInUse = false;

    m_CurrentIndex = 0;
    m_CurrentFrame = 0;

    m_RedVal = 0;
    m_GreenVal = 0;
    m_BlueVal = 0;
    m_OpacityVal = 255;

    m_Brush = Brush();
    m_Brush.setColor(QColor(m_RedVal, m_GreenVal, m_BlueVal, m_OpacityVal));
    m_Brush.setBrush(QBrush(Qt::SolidPattern));
    m_Brush.setWidth(5);
    m_CurrentTool = m_Brush;

    m_Eraser = Brush();
    m_Eraser.setWidth(5);
    m_Eraser.setColor(QColor(Qt::white));
    m_Eraser.setBrush(QBrush(Qt::SolidLine));
    m_ToolType = BRUSH_TOOL;
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    if(!m_Layers.isEmpty())
    {
        switch(m_ToolType)
        {
        case BRUSH_TOOL:
            m_DeviceDown = true;
            m_DrawPath[2] = m_DrawPath[1] = m_DrawPath[0] = event->pos();
            break;
        case ERASER_TOOL:
            m_DeviceDown = true;
            m_DrawPath[2] = m_DrawPath[1] = m_DrawPath[0] = event->pos();
            break;
        case EYEDROPPER_TOOL:
            m_Pix = QPixmap::grabWidget(this);
            m_Img = m_Pix.toImage();
            QColor color(m_Img.pixel(event->pos()));
            emit redChanged(color.red());
            emit greenChanged(color.green());
            emit blueChanged(color.blue());
            break;
//        default:
//            break;
        }
    }
    update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_DeviceDown)
    {
        m_DeviceDown = false;
    }
    update();
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_Layers.isEmpty()&& !m_TabletInUse)
    {

        switch(m_ToolType)
        {
        case BRUSH_TOOL:
            if(m_DeviceDown)
            {
                m_DrawPath[2] = m_DrawPath[1];
                m_DrawPath[1] = m_DrawPath[0];
                m_DrawPath[0] = event->pos();
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(event, m_CurrentTool, m_DrawPath);
                setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
            }
            break;
        case ERASER_TOOL:
            if(m_DeviceDown)
            {
                m_DrawPath[2] = m_DrawPath[1];
                m_DrawPath[1] = m_DrawPath[0];
                m_DrawPath[0] = event->pos();
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(event, m_CurrentTool, m_DrawPath);
                setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
            }
            break;
        default:
            break;
        }
    }
    update();
}

void Editor::tabletEvent(QTabletEvent *event)
{
    m_TabletInUse = true;
    if(!m_Layers.isEmpty() && m_TabletInUse == true)
    {
        switch(m_ToolType)
        {
        case BRUSH_TOOL:
            switch(event->type())
            {
                case QEvent::TabletPress:
                if(!m_DeviceDown)
                {
                    m_DeviceDown = true;
                    m_DrawPath[2] = m_DrawPath[1] = m_DrawPath[0] = event->pos();
                }
                break;
            case QEvent::TabletRelease:
                if(m_DeviceDown)
                {
                    m_DeviceDown = false;
                }
                if(m_TabletInUse)
                {
                    m_TabletInUse = false;
                }
                break;
            case QEvent::TabletMove:
                if(m_DeviceDown)
                {
                    m_DrawPath[2] = m_DrawPath[1];
                    m_DrawPath[1] = m_DrawPath[0];
                    m_DrawPath[0] = event->pos();
                    m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(event, m_CurrentTool, m_DrawPath);
                    setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
                }
                break;
            default:
                qDebug() << "Nothing Happened" << endl;
            }
            break;
        case ERASER_TOOL:
            switch(event->type())
            {
                case QEvent::TabletPress:
                if(!m_DeviceDown)
                {
                    m_DeviceDown = true;
                    m_DrawPath[2] = m_DrawPath[1] = m_DrawPath[0] = event->pos();
                }
                break;
            case QEvent::TabletRelease:
                if(m_DeviceDown)
                {
                    m_DeviceDown = false;
                }
                break;
            case QEvent::TabletMove:
                if(m_DeviceDown)
                {
                    m_DrawPath[2] = m_DrawPath[1];
                    m_DrawPath[1] = m_DrawPath[0];
                    m_DrawPath[0] = event->pos();
                    m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(event, m_CurrentTool, m_DrawPath);
                    setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
                }
                break;
            default:
            qDebug() << "Nothing Happened" << endl;
            }
            break;
        default:
            break;
        }
   }
    update();
}

void Editor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(!m_Layers.isEmpty())
    {
        m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(painter);
        setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
    }
}

void Editor::newProject(int type, int width, int height, int dpi)
{
    if(!m_Layers.isEmpty())
    {
        m_Layers.clear();
        m_CurrentIndex = 0;
        m_CurrentFrame = 0;
    }

    if(m_Layers.isEmpty())
    {
        switch(type)
        {
         case 0:
            m_CurrentIndex = 1;
            m_CurrentFrame = 1;
            m_Layers.push_back(new Layer(Layer::Bitmap, width, height));
            this->resize(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size());
            break;
        case 1:
            //create Animation project
            break;
        case 2:
            //create Spritesheet
            break;
        default:
            break;
        }
    }

    update();
}

void Editor::setBrush(ToolType type)
{
    m_ToolType = type;
    switch(m_ToolType)
    {
    case BRUSH_TOOL:
        m_CurrentTool = m_Brush;
        m_CurrentTool.setColor(m_PrimaryColor);
        emit brushSizeChanged(m_Brush.getSize());
        break;
    case ERASER_TOOL:
        m_CurrentTool = m_Eraser;
        emit brushSizeChanged(m_Eraser.getSize());
    case TEXT_TOOL:
        break;
    case EYEDROPPER_TOOL:
        break;
    default:
        break;
    }
}

void Editor::setBrushSize(int val)
{
    m_CurrentTool.setWidth(val);
    switch(m_ToolType)
    {
    case BRUSH_TOOL:
        m_Brush.setWidth(val);
        break;
    case ERASER_TOOL:
        m_Eraser.setWidth(val);
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
    m_RedVal = val;
    m_PrimaryColor.setRed(m_RedVal);
    m_CurrentTool.setColor(m_PrimaryColor);
}

void Editor::setGreenValue(int val)
{
    m_GreenVal = val;
    m_PrimaryColor.setGreen(m_GreenVal);
    m_CurrentTool.setColor(m_PrimaryColor);
}

void Editor::setBlueValue(int val)
{
    m_BlueVal = val;
    m_PrimaryColor.setBlue(m_BlueVal);
    m_CurrentTool.setColor(m_PrimaryColor);
}

void Editor::setOpacity(int val)
{
    m_OpacityVal = val;
    m_PrimaryColor.setAlpha(m_OpacityVal);
    m_CurrentTool.setColor(m_PrimaryColor);
}

void Editor::setOpacityTransfer(int val)
{

}

void Editor::setSizeTransfer(int val)
{
    m_CurrentTool.setTransferWidthAmount(val);
    switch(m_ToolType)
    {
    case BRUSH_TOOL:
        m_Brush.setTransferWidthAmount(val);
        break;
    case ERASER_TOOL:
        m_Eraser.setTransferWidthAmount(val);
        break;
    default:
        break;
    }
}

