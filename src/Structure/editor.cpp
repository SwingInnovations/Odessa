#include "editor.h"

Editor::Editor(QWidget *parent):QLabel(parent)
{
    m_DeviceDown = false;
    m_TabletInUse = false;
    m_Modified = false;
    m_SelectActive = false;
    m_AlternatePattern = false;
    m_ShiftEnabled = false;

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
    m_Brush.setOpacity(m_OpacityVal);
    m_Brush.setSpacing(1);
    m_CurrentTool = m_Brush;
    m_ToolType = BRUSH_TOOL;

    m_Eraser = Brush();
    m_Eraser.setWidth(5);
    m_Eraser.setColor(Qt::white);
    m_Eraser.setBrush(QBrush(Qt::SolidLine));

    m_BackupIndex = 0;
    m_ScaleFactor = 1.0;
    m_HistorySteps = 24;

    m_SelectRect = QRect(0, 0, 0, 0);
    m_Font = QFont();
    m_FontSize = 7;

    m_ClipScaleFactor = 1.0;
    m_ClipRotateAngle = 0.0;

    m_Text = "";
    m_acceptTextInput = false;
}

void Editor::setHistoyStep(int h){
    m_HistorySteps = h;
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    if(!m_Layers.isEmpty() && event->button() == Qt::LeftButton)
    {
        switch(m_ToolType)
        {
        case BRUSH_TOOL:
            m_DeviceDown = true;
            if(m_SelectActive) m_SelectActive = false;
            if(!m_MousePath.isEmpty())
            {
                m_MousePath.clear();
                m_MousePath.append(event->pos());
            }
            backup();
            break;
        case ERASER_TOOL:
            m_DeviceDown = true;
            if(m_SelectActive) m_SelectActive = false;
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
                if(!m_SelectActive) m_SelectActive = true;
                m_SelectRect.setTopLeft(QPoint(0, 0));
                m_SelectRect.setBottomRight(QPoint(0,0));
                m_SelectRect.setTopLeft(event->pos());
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

    if(!m_Layers.empty())
    {
//        m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->optimizeImage(m_CurrentTool);
            if(m_SelectActive){
                m_SelectRect.setBottomRight(event->pos());
                //setBrush(TRANSFORM_TRANSLATE);
            }
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

                if(m_TabletInUse) m_CurrentTool.setPressureVal(m_Pressure); else{ m_CurrentTool.setPressureVal(0.0); }
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(m_MousePath, m_CurrentTool);
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
            }
            break;
        case RECT_SELECT_TOOL:
            if(m_DeviceDown && m_SelectActive){
                m_SelectRect.setBottomRight(event->pos());
            }
            break;
        default:
            break;
        }
    }
    qDebug() << " SelectActive: " << m_SelectActive << endl;
    update();
}

void Editor::deselect(){
    m_SelectActive = false;
    m_SelectRect.setTopLeft(QPoint(0, 0));
    m_SelectRect.setBottomRight(QPoint(0, 0));
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
        QPainter p(&drawnPixmap);
        for(int i = 0; i < m_Layers.size(); i++){
           if(m_Layers.at(i)->getFrame(m_CurrentFrame-1)->isVisible()){
               m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(painter);
               //QPixmap tPixmap = m_Layers.at(i)->getFrame(m_CurrentFrame-1)->getPixmap().scaled(m_ScaleFactor * imageSize, Qt::KeepAspectRatio, Qt::FastTransformation);
               QPixmap tPixmap = m_Layers.at(i)->getFrame(m_CurrentFrame-1)->getPixmap();
               p.setCompositionMode(QPainter::CompositionMode_SourceOver);
               p.drawPixmap(0, 0, tPixmap);
           }
        }
        p.end();
        setPixmap(drawnPixmap);
        painter.drawPixmap(0, 0, drawnPixmap);
        this->resize(imageSize);
    }

    qDebug() << "Painting the selection rect." << endl;
    if(m_SelectActive){
        if(m_AlternatePattern){ painter.setPen(Qt::DotLine); m_AlternatePattern = false; }else{  painter.setPen(Qt::DashDotLine); m_AlternatePattern = true; }
        painter.setBrush(Qt::transparent);
        painter.drawRect(m_SelectRect);
        painter.end();
    }

    if(m_ClipboardPresent){
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.drawPixmap(m_ClipOffsetPoint, m_ClipboardPixmap);
        painter.end();
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
    m_Info = info;
    if(!m_Layers.isEmpty()){
        m_Layers.clear();
        m_CurrentIndex = 0;
        m_CurrentFrame = 0;
    }
    if(m_Layers.isEmpty()){
        switch(info.getType()){
            case 0:
                m_CurrentIndex = 1;
                m_CurrentFrame = 1;
                m_Layers.push_back(new Layer(Layer::Bitmap, info.getWidth(), info.getHeight()));
                this->resize(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size());
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
        emit toolChanged(0);
        break;
    case ERASER_TOOL:
        m_CurrentTool = m_Eraser;
        emit brushSizeChanged(m_Eraser.getSize());
        emit toolChanged(1);
    case TEXT_TOOL:
        emit toolChanged(2);
        break;
    case EYEDROPPER_TOOL:
        break;
    case TRANSFORM_TRANSLATE:
        emit toolChanged(7);
        break;
    default:
        emit toolChanged(0);
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
    m_CurrentTool.setOpacity(val);
    switch(m_ToolType){
    case BRUSH_TOOL:
        m_Brush.setOpacity(val);
        break;
    case ERASER_TOOL:
        m_Eraser.setOpacity(val);
        break;
    default:
        break;
    }
}

void Editor::setOpacityTransfer(int val)
{
    m_CurrentTool.setTransferOpacity(val);
    switch(m_ToolType){
    case BRUSH_TOOL:
        m_Brush.setTransferOpacity(val);
        break;
    case ERASER_TOOL:
        m_Eraser.setTransferOpacity(val);
        break;
    default:
        break;
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

void Editor::setFont(QFont font){
    m_Font = font;
}

void Editor::setFontSize(int font){
    m_FontSize = font;
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
    for(int i = 0; i < m_Layers.size(); i++){
        m_Layers.at(i)->getFrame(m_CurrentFrame-1)->scale(m_ScaleFactor);
    }
    update();
}

void Editor::resetScale(){
    m_ScaleFactor = 1.0;
}

void Editor::backup(int backupLayer, int backupFrame)
{
    while(m_HistoryStack.size() > m_HistorySteps && m_HistoryStack.size() > 0)
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

void Editor::cut(){
    QClipboard* clip = QApplication::clipboard();
    QPixmap cutPix = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->copy(m_SelectRect).getPixmap();
    clip->setPixmap(cutPix);
    //Do something to clear the old Image;
    backup();
}

void Editor::copy(){
    QClipboard* clip = QApplication::clipboard();
    QPixmap copyPix = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->copy(m_SelectRect).getPixmap();
    clip->setPixmap(copyPix);
    backup();
}

void Editor::paste(){
    QClipboard* clip = QApplication::clipboard();
    const QMimeData* mimeData = clip->mimeData();

    if(!m_ClipboardPresent) m_ClipboardPresent = true;
    if(mimeData->hasText()){
        //deal with the text
        setBrush(ToolType::TEXT_TOOL);
    }else if(mimeData->hasImage()){
        m_ClipboardPixmap = clip->pixmap();
        m_ClipOffsetPoint = QPoint( (this->pixmap()->width()/2 - m_ClipboardPixmap.width()/2), (this->pixmap()->height()/2 - m_ClipboardPixmap.height()/2) );
        setBrush(ToolType::TRANSFORM_TRANSLATE);
    }
    backup();
}

void Editor::setClipTranslate(int x, int y){
    m_ClipOffsetPoint = QPoint(x, y);
}

void Editor::setClipRotate(int a){
    m_ClipRotateAngle = a;
}

void Editor::setClipScale(int w, int h){
    m_ClipScale = QPoint(w, h);
}

void Editor::setClipOffsetX(int x){
    m_ClipOffsetPoint.setX(x);
}

void Editor::setClipOffsetY(int y){
    m_ClipOffsetPoint.setY(y);
}

void Editor::useWorldTransform(bool val){
    m_ClipWorldTransform = val;
}

void Editor::commitChanges(){
    if(!m_ClipboardPixmap.isNull()){
        m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->commitChanges(m_ClipOffsetPoint, m_ClipboardPixmap);
    }
}

void Editor::enableShift(){
    m_ShiftEnabled =! m_ShiftEnabled;
    if(m_ShiftEnabled){ m_ShiftEnabled = false; }
}

void Editor::clearText(){
    if(m_acceptTextInput) m_Text = "";
}

void Editor::append_0(){
    if(m_acceptTextInput){
        m_Text += '0';
    }
}

void Editor::append_1(){
    if(m_acceptTextInput){
        m_Text += '1';
    }
}

void Editor::append_2(){
    if(m_acceptTextInput){
        m_Text += '2';
    }
}

void Editor::append_3(){
    if(m_acceptTextInput){
        m_Text += '3';
    }
}

void Editor::append_4(){
    if(m_acceptTextInput){
        m_Text += '4';
    }
}

void Editor::append_5(){
    if(m_acceptTextInput){
        m_Text += '5';
    }
}

void Editor::append_6(){
    if(m_acceptTextInput){
        m_Text += '6';
    }
}

void Editor::append_7(){
    if(m_acceptTextInput){
        m_Text += '7';
    }
}

void Editor::append_8(){
    if(m_acceptTextInput){
        m_Text += '8';
    }
}

void Editor::append_9(){
    if(m_acceptTextInput){
        m_Text += '9';
    }
}

void Editor::append_a(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'A';
        }else{
            m_Text += 'a';
        }
    }
}

void Editor::append_b(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'B';
        }else{
            m_Text += 'b';
        }
    }
}

void Editor::append_c(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'C';
        }else{
            m_Text += 'c';
        }
    }
}

void Editor::append_d(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'D';
        }else{
            m_Text += 'd';
        }
    }
}

void Editor::append_e(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'E';
        }else{
            m_Text += 'e';
        }
    }
}

void Editor::append_f(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'F';
        }else{
            m_Text += 'f';
        }
    }
}

void Editor::append_g(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'G';
        }else{
            m_Text += 'g';
        }
    }
}

void Editor::append_h(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'H';
        }else{
            m_Text += 'h';
        }
    }
}


void Editor::append_i(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'I';
        }else{
            m_Text += 'i';
        }
    }
}

void Editor::append_j(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'J';
        }else{
            m_Text += 'j';
        }
    }
}

void Editor::append_k(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'K';
        }else{
            m_Text += 'k';
        }
    }
}

void Editor::append_l(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'L';
        }else{
            m_Text += 'l';
        }
    }
}

void Editor::append_m(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'M';
        }else{
            m_Text += 'm';
        }
    }
}

void Editor::append_n(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'N';
        }else{
            m_Text += 'n';
        }
    }
}

void Editor::append_o(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'O';
        }else{
            m_Text += 'o';
        }
    }
}

void Editor::append_p(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'P';
        }else{
            m_Text += 'p';
        }
    }
}

void Editor::append_q(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'Q';
        }else{
            m_Text += 'q';
        }
    }
}

void Editor::append_r(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'R';
        }else{
            m_Text += 'r';
        }
    }
}

void Editor::append_s(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'S';
        }else{
            m_Text += 's';
        }
    }
}

void Editor::append_t(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'T';
        }else{
            m_Text += 't';
        }
    }
}

void Editor::append_u(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'U';
        }else{
            m_Text += 'u';
        }
    }
}

void Editor::append_v(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'V';
        }else{
            m_Text += 'v';
        }
    }
}

void Editor::append_w(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'W';
        }else{
            m_Text += 'w';
        }
    }
}

void Editor::append_x(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'X';
        }else{
            m_Text += 'x';
        }
    }
}

void Editor::append_y(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'Y';
        }else{
            m_Text += 'y';
        }
    }
}

void Editor::append_z(){
    if(m_acceptTextInput){
        if(m_ShiftEnabled){
            m_Text += 'Z';
        }else{
            m_Text += 'z';
        }
    }
}
