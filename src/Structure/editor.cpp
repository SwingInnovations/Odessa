#include "editor.h"

Editor::Editor(QWidget *parent):QLabel(parent)
{
    m_DeviceDown = false;
    m_TabletInUse = false;
    m_Modified = false;

    m_CurrentIndex = 0;
    m_CurrentFrame = 0;

    m_RedVal = 0;
    m_GreenVal = 0;
    m_BlueVal = 0;
    m_OpacityVal = 100;

    m_Brush = Brush();
    m_Brush.setColor(Qt::black);
    m_Brush.setBrush(QBrush(Qt::SolidPattern));
    m_Brush.setWidth(5);
    m_Brush.SetOpacity(m_OpacityVal);
    m_Brush.setSpacing(1);
    m_CurrentTool = m_Brush;
    m_ToolType = BRUSH_TOOL;

    m_Eraser = Brush();
    m_Eraser.setWidth(5);
    m_Eraser.setColor(Qt::white);
    m_Eraser.setBrush(QBrush(Qt::SolidLine));

    m_BackupIndex = 0;
    m_ScaleFactor = 1.0;

    setScaledContents(true);
    setAlignment(Qt::AlignCenter);
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    if(!m_Layers.isEmpty() && event->button() == Qt::LeftButton)
    {
        switch(m_ToolType)
        {
        case BRUSH_TOOL:
            m_DeviceDown = true;
            m_DrawPath[0] = m_DrawPath[1] = m_DrawPath[2] = event->pos();
            if(!m_MousePath.isEmpty())
            {
                m_MousePath.clear();
                m_MousePath.append(event->pos());
            }
            backup();
            break;
        case ERASER_TOOL:
            m_DeviceDown = true;
            m_DrawPath[0] = m_DrawPath[1] = m_DrawPath[2] = event->pos();
            backup();
            break;
        case EYEDROPPER_TOOL:
        {
            m_Pix = QPixmap::grabWidget(this);
            QImage m_Img = m_Pix.toImage();
            QColor color(m_Img.pixel(event->pos()));
            emit redChanged(color.red());
            emit greenChanged(color.green());
            emit blueChanged(color.blue());
        }
            break;
       case RECT_SELECT_TOOL:
            {
                m_DeviceDown = true;
                if(!m_MousePath.isEmpty()){
                    m_MousePath.clear();
                    m_MousePath.push_back(event->pos());
                }
            }
            break;
       case FILL_TOOL:{
            m_DeviceDown = true;
            m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->fillImage(event->pos(), m_CurrentTool);
            backup();
        }
            break;
       defualt:
            break;
        }
    }

    update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(m_DeviceDown)
    {
        m_DeviceDown = false;
    }

    if(m_ToolType == RECT_SELECT_TOOL){
        m_MousePath.push_back(event->pos());
        //Reorder the layer array
    }

    if(!m_Layers.empty())
    {
//        m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->optimizeImage(m_CurrentTool);
    }
    update();
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_Layers.isEmpty())
    {

        switch(m_ToolType)
        {
        case BRUSH_TOOL:
            if(m_DeviceDown)
            {
                m_MousePath.append(event->pos());
                if(m_MousePath.size() > 2)
                {
                    m_MousePath.removeFirst();
                }

                m_CurrentTool.setPressureVal(m_Pressure);

                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(m_MousePath, m_CurrentTool);
                setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
            }
            break;
        case ERASER_TOOL:
            if(m_DeviceDown)
            {
                m_MousePath.append(event->pos());
                if(m_MousePath.size() > 2){
                    m_MousePath.removeFirst();
                }
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(m_MousePath, m_CurrentTool);
                setPixmap(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
            }
            break;
        default:
            break;
        }
    }
    qDebug() << "Pressure:" << m_Pressure << endl;
    update();
}

void Editor::setBrush(Brush b){
    m_CurrentTool.SetStencil(b.getStencil());
    if(m_ToolType == BRUSH_TOOL){
        m_Brush.setSWidth(b.getSWidth());
        m_Brush.setSHeight(b.getSHeight());
        m_Brush.SetStencil(b.getStencil());
    }else if(m_ToolType == ERASER_TOOL){
        m_Eraser = b;
    }else{

    }
}

void Editor::tabletEvent(QTabletEvent *event)
{
    if(!m_Layers.isEmpty())
    {
        switch(event->type())
        {
        case QEvent::TabletPress:
           if(m_DeviceDown)
           {
               m_TabletInUse = true;
               m_Pressure = event->pressure();
               m_CurrentTool.setPressureVal(m_Pressure);
               m_XTilt = event->xTilt();
               m_YTilt = event->yTilt();
           }
            break;
        case QEvent::TabletMove:
            if(m_DeviceDown)
            {
                m_Pressure = event->pressure();
                m_CurrentTool.setPressureVal(m_Pressure);
                m_XTilt = event->xTilt();
                m_YTilt = event->yTilt();
            }
            break;
         case QEvent::TabletRelease:
            if(m_DeviceDown)
            {
                m_DeviceDown = false;
            }
            break;
        }
   }
    update();
}

/*Paint Image*/

void Editor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(!m_Layers.isEmpty())
    {
        QPixmap drawnPixmap(m_Layers.at(0)->getFrame(0)->getPixmap().size());
        QSize imageSize = m_Layers.at(0)->getFrame(0)->getPixmap().size();
        drawnPixmap = drawnPixmap.scaled(imageSize.width() * m_ScaleFactor, imageSize.height() * m_ScaleFactor);
        QPainter p(&drawnPixmap);
        for(int i = 0; i < m_Layers.size(); i++){
           if(m_Layers.at(i)->getFrame(m_CurrentFrame-1)->isVisible()){
               m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(painter);
               QPixmap tPixmap = m_Layers.at(i)->getFrame(m_CurrentFrame-1)->getPixmap().scaled(imageSize.width() * m_ScaleFactor, imageSize.height() * m_ScaleFactor);
               p.setCompositionMode(QPainter::CompositionMode_SourceOver);
               p.drawPixmap(0, 0, tPixmap);
           }
        }
        p.end();
        setAlignment(Qt::AlignCenter);
        setPixmap(drawnPixmap);
    }

    if(m_ToolType == BRUSH_TOOL){
        this->setCursor(QCursor(Qt::CrossCursor));
        painter.setPen(Qt::darkGray);
        painter.drawPoint(this->mapFromGlobal(QCursor::pos()));
        painter.drawEllipse(this->mapFromGlobal(QCursor::pos()), m_CurrentTool.getSize()-3, m_CurrentTool.getSize()-3);
        painter.end();
    }else if(m_ToolType == ERASER_TOOL){
        this->setCursor(QCursor(Qt::CrossCursor));
        painter.setPen(Qt::darkGray);
        painter.drawPoint(this->mapFromGlobal(QCursor::pos()));
        painter.drawEllipse(this->mapFromGlobal(QCursor::pos()), m_CurrentTool.getSize()-3, m_CurrentTool.getSize()-3);
        painter.end();
    }else if(m_ToolType == EYEDROPPER_TOOL){
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void Editor::newProject(ProjectInfo &info){
    if(!m_Layers.isEmpty()){
        m_Layers.clear();
        m_CurrentIndex = 0;
        m_CurrentFrame = 0;
    }else{
        switch(info.getType()){
            case 0:
                m_CurrentIndex = 1;
                m_CurrentFrame = 1;
                m_Layers.push_back(new Layer(Layer::Bitmap, info.getWidth(), info.getHeight()));
                break;
        default:
            break;
        }
    }
    backup();
    update();
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
    backup();
    update();
}

void Editor::addLayer()
{
    if(!m_Layers.isEmpty())
    {
        int width = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size().width();
        int height = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size().height();
        m_CurrentIndex += 1;
        m_Layers.push_back(new Layer(Layer::Bitmap_Blank, width, height));
    }
}

void Editor::addFrame()
{

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

void Editor::setBrushStencil(QPixmap pixmap){
    m_CurrentTool.SetStencil(pixmap);
    switch(m_ToolType){
    case BRUSH_TOOL:
        m_Brush.SetStencil(pixmap);
        break;
    case ERASER_TOOL:
        m_Eraser.SetStencil(pixmap);
        break;
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

void Editor::setBrushSpacing(int val)
{
    m_CurrentTool.setSpacing(val);
    switch(m_ToolType){
    case BRUSH_TOOL:
        m_Brush.setSpacing(val);
        break;
    case ERASER_TOOL:
        m_Eraser.setSpacing(val);
        break;
    default:
        break;
    }
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
    //m_PrimaryColor.setAlpha(m_OpacityVal);
    m_PrimaryColor.setAlpha(val);
    m_CurrentTool.SetOpacity(val);
}

void Editor::setOpacityTransfer(int val)
{

}

void Editor::processCanvas(){
    if(this->pixmap()->size().width() < this->size().width() && this->pixmap()->size().height() < this->size().height()){
        qDebug() << "Can resize to be centered:" << endl;
    }else{
        qDebug() << "Can remain the same size" << endl;
    }
}

void Editor::setSizeTransfer(int val)
{
    m_CurrentTool.setTransferSize(val);
    switch(m_ToolType)
    {
    case BRUSH_TOOL:
        m_Brush.setTransferSize(val);
        break;
    case ERASER_TOOL:
        m_Eraser.setTransferSize(val);
        break;
    default:
        break;
    }
}

void Editor::backup()
{
    if(!m_Layers.isEmpty())
    {
        backup(m_CurrentIndex-1, m_CurrentFrame-1);
    }
}

void Editor::scale(double scaleVal)
{
    m_ScaleFactor = scaleVal;
    update();
}

void Editor::backup(int backupLayer, int backupFrame)
{
    while(m_HistoryStack.size()-1 > m_BackupIndex && m_HistoryStack.size() > 0)
    {
        delete m_HistoryStack.takeLast();
    }
        BitmapHistoryStack* element = new BitmapHistoryStack();
        element->m_Layer = backupLayer;
        element->m_Frame = backupFrame;
        BitmapImage* bitmapImage = m_Layers.at(backupLayer)->getFrame(backupFrame);
        if(bitmapImage != NULL)
        {
            element->m_Bitmap = bitmapImage->copy();
            m_HistoryStack.append(element);
            m_BackupIndex++;
        }
}

void Editor::undo()
{
    m_BackupIndex--;
    HistoryStack* lastElement = m_HistoryStack[m_BackupIndex];
    BitmapHistoryStack* lastBitmapHist = (BitmapHistoryStack*)lastElement;
    m_Layers.at(lastBitmapHist->m_Layer)->getFrame(lastBitmapHist->m_Frame)->setPixmap(lastBitmapHist->m_Bitmap.getPixmap());
}

void Editor::redo()
{
    if(m_BackupIndex > -1 && m_BackupIndex < m_HistoryStack.size() -1)
    {
        m_BackupIndex++;
        HistoryStack* lastElement = m_HistoryStack[m_BackupIndex];
        BitmapHistoryStack* lastBitmapHist = (BitmapHistoryStack*)lastElement;
        m_Layers.at(lastBitmapHist->m_Layer)->getFrame(lastBitmapHist->m_Frame)->setPixmap(lastBitmapHist->m_Bitmap.getPixmap());
    }
}

