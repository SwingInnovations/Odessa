#include "editor.h"

Editor::Editor(QWidget *parent):QWidget(parent)
{
    m_DeviceDown = false;
    m_TabletInUse = false;
    m_Modified = false;
    m_SelectActive = false;
    m_AlternatePattern = false;
    m_ShiftEnabled = false;

    m_CurrentIndex = 0;
    m_LastIndex = -1;
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
    m_Brush.setToolType(0);
    m_CurrentTool = m_Brush;
    m_ToolType = BRUSH_TOOL;

    m_Eraser = Brush();
    m_Eraser.setToolType(1);
    m_Eraser.setWidth(5);
    m_Eraser.setColor(Qt::white);
    m_Eraser.setBrush(QBrush(Qt::SolidPattern));
    m_Eraser.setOpacity(m_OpacityVal);
    m_Eraser.setSpacing(1);

    m_BackupIndex = 0;
    m_ScaleFactor = 1.0;
    m_HistorySteps = 24;

    m_SelectRect = QRect(0, 0, 0, 0);
    m_Font = QFont();
    m_FontSize = 7;
    m_textCursorPos = 0;

    m_ClipScaleFactor = 1.0;
    m_ClipRotateAngle = 0.0;

    m_isBold = false;
    m_isItalic = false;
    m_isUnderline = false;

    m_Text = "";
    m_acceptTextInput = false;
    m_textDocument = new QTextDocument();
    m_textCursor = QTextCursor(m_textDocument);
    m_textCursor.setPosition(QTextCursor::Start);
    m_fmt = QTextCharFormat(m_textCursor.charFormat());
    m_fmt.setFont(m_Font);
    m_fmt.setForeground(QBrush(Qt::black));

    m_keyEntry[0] = -1;
    m_keyEntry[1] = -1;

    m_useCustomCombo = false;
    m_tCursorBlinker = new QTimer(this);
    m_tCursorBlinker->setInterval(500);
    m_tCursorBlinker->start();
    m_tCursorBlink = false;

    connect(m_tCursorBlinker, SIGNAL(timeout()), SLOT(alternateTBlinker()));
}

void Editor::setHistoryLimit(int h){
    m_HistorySteps = h;
    qDebug() << "Changed the history limit. " << endl;
    emit historyLimitChanged(m_HistorySteps);
}

QPixmap Editor::getSelectionPixmap(){
    if(!m_Layers.empty()){
        if(m_SelectRect.width() > 0 && m_SelectRect.height() > 0){
            return m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->copy(m_SelectRect).getPixmap();
        }else{
            return QPixmap();
        }
    }else{
        return QPixmap();
    }
}

QPixmap Editor::getCurrentImage()
{
    QPixmap ret;
    QPainter p(&ret);
    if(!m_Layers.empty()){
        for(int i = 0; i < m_Layers.size(); i++){
            //p.setOpacity(m_Layers[i]->getFrame(m_CurrentFrame - 1)-);
            p.drawPixmap(0, 0, m_Layers[i]->getFrame(m_CurrentFrame - 1)->getPixmap());
        }
    }
    return ret;
}

void Editor::setBrushColor(const QColor &color)
{
    m_PrimaryColor = color;
}

QColor Editor::getCurrentBrushColor() const
{
    return m_PrimaryColor;
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
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(m_MousePath, m_CurrentTool);
            }
            backup();
            break;
        case ERASER_TOOL:
            m_DeviceDown = true;
            if(m_SelectActive) m_SelectActive = false;
            if(!m_MousePath.isEmpty()){
                m_MousePath.clear();
                m_MousePath.append(event->pos());
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(m_MousePath, m_CurrentTool);
            }
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
       default:
            break;
        }
    }

    //update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if(m_DeviceDown)
    {
        m_DeviceDown = false;
        m_MousePath.clear();
    }

    if(!m_Layers.empty())
    {
        if(m_SelectActive){
            m_SelectRect.setBottomRight(event->pos());
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
            //repaint();
            if(m_DeviceDown)
            {
                m_MousePath.append(event->pos());
                if(m_MousePath.size() > 2)
                {
                    m_MousePath.removeFirst();
                }
                emit curToolPressureChanged(m_CurrentTool.getPressureVal());
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->paintImage(&m_MousePath, m_CurrentTool);
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
        emit mousePositionChanged(event->pos());
    }
    update();
}

void Editor::deselect(){
    m_SelectActive = false;
    m_SelectRect.setTopLeft(QPoint(0, 0));
    m_SelectRect.setBottomRight(QPoint(0, 0));
}

void Editor::setBrush(Brush b){
    m_Brush.setSWidth(b.getSWidth());
    m_Brush.setSHeight(b.getSHeight());
    m_Brush.SetStencil(b.getStencil());

    m_Eraser.setSWidth(b.getSWidth());
    m_Eraser.setSHeight(b.getSHeight());
    m_Eraser.SetStencil(b.getStencil());
    if(m_ToolType == BRUSH_TOOL){
        m_CurrentTool = m_Brush;
    }else if(m_ToolType == ERASER_TOOL){
        m_CurrentTool = m_Eraser;
    }else{

    }
}

void Editor::tabletEvent(QTabletEvent *event)
{
    qDebug() << "Polling Tablet" << endl;
    if(!m_Layers.isEmpty())
    {
        if(!m_CurrentTool.isType(2)){
            switch(event->pointerType()){
            case QTabletEvent::PointerType::Pen:
                emit brushToolSelected();
                break;
            case QTabletEvent::PointerType::Eraser:
                emit eraserToolSelected();
                break;
            case QTabletEvent::PointerType::Cursor:
                emit cursorToolSelected();
                break;
            default:
                emit brushToolSelected();
                ;
            }
        }
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
                if(m_TabletInUse) m_TabletInUse = false;
                m_Pressure = 0.0;
            }
            break;
        }
        emit brushPressureChanged(event->pressure());
   }
    update();
}

/*Paint Image*/

void Editor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    /*-Primarily draw the canvas-*/
    int scaledWidth = m_realWidth * m_ScaleFactor;
    int scaledHeight = m_realHeight * m_ScaleFactor;

    if(!m_Layers.isEmpty())
    {
        QSize imageSize(m_Info.getWidth(), m_Info.getHeight());
        QPixmap drawnPixmap(imageSize);
        QPainter p(&drawnPixmap);
        for(int i = 0; i < m_Layers.size(); i++){
            if(m_Layers[i]->isVisible() && m_Layers[i]->getFrame(m_CurrentFrame - 1)->isVisible()){
                m_Layers[i]->getFrame(m_CurrentFrame-1)->paintImage(p);
                QImage drawnImage = m_Layers[i]->getFrame(m_CurrentFrame-1)->getPixmap().toImage();
                drawnImage.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
                if(i > 0){
                    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
                    p.setOpacity((qreal)m_Layers[i]->getOpacity() / 100.0f);
                }
                p.drawImage(0, 0, drawnImage);
            }
        }
        p.end();

        emit layerPreviewChanged(0, m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());

        resize(scaledWidth, scaledHeight);
        painter.drawImage(0,0, drawnPixmap.toImage().scaled(scaledWidth, scaledHeight));

    }


    if(m_SelectActive){
        if(m_AlternatePattern){ painter.setPen(Qt::DotLine); m_AlternatePattern = false; }else{  painter.setPen(Qt::DashDotLine); m_AlternatePattern = true; }
        painter.setBrush(Qt::transparent);
        painter.drawRect(m_SelectRect);
    }

    if(m_ClipboardPresent){
        if(m_ToolType == TEXT_TOOL){
            m_ClipboardPixmap = generateTextPixmap();
        }
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        if(m_AlternatePattern){ painter.setPen(Qt::DotLine); m_AlternatePattern = false; }else{  painter.setPen(Qt::DashDotLine); m_AlternatePattern = true; }
        painter.drawRect(m_ClipOffsetPoint.x(), m_ClipOffsetPoint.y(), m_ClipboardPixmap.rect().width(), m_ClipboardPixmap.rect().height());
        painter.drawPixmap(m_ClipOffsetPoint, m_ClipboardPixmap);
    }

    if(m_ToolType == BRUSH_TOOL){
        setCursor(QCursor(m_CurrentTool.getStencil().scaled(m_CurrentTool.getSize(), m_CurrentTool.getSize())));
    }else if(m_ToolType == ERASER_TOOL){
        setCursor(QCursor(Qt::CrossCursor));
        painter.setPen(Qt::darkGray);
        painter.setBrush(Qt::transparent);
        painter.drawPoint(this->mapFromGlobal(QCursor::pos()));
        painter.drawEllipse(this->mapFromGlobal(QCursor::pos()), m_CurrentTool.getSize(), m_CurrentTool.getSize()-3);
    }else if(m_ToolType == EYEDROPPER_TOOL){
        setCursor(QCursor(QPixmap(":/icon/resource/eyeDropper.png"), 0, 0));
    }else if(m_ToolType == CURSOR_TOOL){
        setCursor(QCursor(Qt::ArrowCursor));
    }else if(m_ToolType == PRIMITIVE_TOOL){
        painter.setPen(QPen(((Primitive)m_CurrentTool).getLineColor()));
        painter.setBrush(QBrush(((Primitive)m_CurrentTool).getFillColor()));
        painter.drawPath(((Primitive)m_CurrentTool).getShapePath());
    }
}

QString Editor::addText(int i, QChar c){

    if(i >= m_Text.length()){
        m_Text.append(c);
    }else{
        m_Text.insert(i, c);
    }
    return m_Text;
}

QString Editor::addText(int i, QString s){
    if(i >= m_Text.length()){
        m_Text.append(s);
    }else{
        m_Text.insert(i, s);
    }
    return m_Text;
}

void Editor::keyPressEvent(QKeyEvent *e){

    if(m_keyEntry[0] != -1 && m_keyEntry[1] != -1){
        if(m_keyEntry[0] == Qt::Key_O || m_keyEntry[1] == Qt::Key_BracketLeft){
            increaseOpacity();
        }else if(m_keyEntry[0] == Qt::Key_O || m_keyEntry[1] == Qt::Key_BracketRight){
            decreaseOpacity();
        }
    }else if(m_keyEntry[0] == -1){
        if(!m_useCustomCombo) m_useCustomCombo = true;
        m_keyEntry[0] = e->key();
    }else if(m_keyEntry[1] == -1){
        m_keyEntry[1] = e->key();
    }


    if(e->key() == Qt::Key_Escape){
        setBrush(CURSOR_TOOL);
    }else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Enter){
        commitChanges();
        if(m_acceptTextInput) m_acceptTextInput = false;
        emit commitAction();
    }else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_B){
        //toggle bold
        setBold(!m_isBold);
        emit boldToggled();
    }else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_I){
        //toggle italic
        setItalic(!m_isItalic);
        emit italicToggled();
    }else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_U){
        //toggle underline
        setUnderline(!m_isUnderline);
        emit underlineToggled();
    }else if(e->key() == Qt::Key_BracketLeft && !m_acceptTextInput && !m_useCustomCombo){
        decreaseBrushSize();
    }else if(e->key() == Qt::Key_BracketRight && !m_acceptTextInput && !m_useCustomCombo){
        increaseBrushSize();
    }


    if(m_acceptTextInput){
        if(e->key() == Qt::Key_Backspace){
            m_textCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
            m_textCursor.deleteChar();
        }else if(e->key() == Qt::Key_Left){
            m_textCursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
        }else if(e->key() == Qt::Key_Right){
            m_textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        }else if(e->modifiers() != Qt::ControlModifier){
            m_textCursor.insertText(e->text(), m_fmt);
            m_textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor);
        }
        qDebug() << "Adjusting size of document" << endl;
        m_textDocument->adjustSize();
    }
    update();
}

void Editor::keyReleaseEvent(QKeyEvent *e){
    if(m_keyEntry[1] == e->key()){
        m_keyEntry[1] = -1;
    }
    if(m_keyEntry[0] == e->key()){
        m_keyEntry[0] = -1;
        if(m_useCustomCombo) m_useCustomCombo = false;
    }
}

void Editor::newProject(ProjectInfo &info){
    m_Info = info;
    if(!m_Layers.isEmpty()){
        m_Layers.clear();
        m_CurrentIndex = 1;
        m_CurrentFrame = 1;
    }

    if(m_Layers.isEmpty()){
        switch(info.getType()){
            case 0:
                m_CurrentIndex = 1;
                m_CurrentFrame = 1;
                m_Layers.push_back(new Layer(Layer::Bitmap, info.getWidth(), info.getHeight(), info.getStartColor()));
                m_realWidth = info.getWidth();
                m_realHeight = info.getHeight();
                this->resize(m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size());
                break;
        default:
            break;
        }
    }
    m_ClipboardPixmap = QPixmap();
    m_ClipOffsetPoint = QPoint(0, 0);
    emit currentIndexChanged(m_CurrentIndex);
    emit currentFrameChanged(m_CurrentFrame);
    emit layerPreviewChanged(0, m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
    resize(info.getWidth(), info.getHeight());
    backup();
    update();
}

void Editor::addLayer()
{
    if(!m_Layers.isEmpty())
    {
        int width = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size().width();
        int height = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap().size().height();
        m_CurrentIndex++;
        m_Layers.push_back(new Layer(Layer::Bitmap_Blank, width, height));
        emit currentIndexChanged(m_CurrentIndex);
    }
}

void Editor::deleteLayer(int index)
{
    if(!m_Layers.isEmpty() && index > -1 && index < m_Layers.size())
    {
        m_Layers.removeAt(index);
        if( index == m_CurrentIndex && index > 0)
        {
            m_CurrentIndex--;
            emit currentIndexChanged(m_CurrentIndex);
        }
    }
}

void Editor::setLayerIndex(int i){
    m_LastIndex = m_CurrentIndex;
    if(i >= 1)
    {
        m_CurrentIndex = i+1;
    }
    else
    {
        m_CurrentIndex = 1;
    }
    emit layerPreviewChanged(0, m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->getPixmap());
    emit currentIndexChanged(m_CurrentIndex);
    update();
}

void Editor::setLayerOpacity(int o){
    if(!m_Layers.empty()){
        m_Layers.at(m_CurrentIndex-1)->setOpacity(o);
    }
    update();
}

void Editor::setLayerCompositionMode(int c){
    if(!m_Layers.empty()){ m_Layers.at(m_CurrentIndex)->setCompositionMode(c); }
}

void Editor::setLayerVisible(bool val){
    qDebug() << "Changing layer visibility" << endl;
    if(!m_Layers.empty()){
        m_Layers.at(m_CurrentIndex-1)->setVisible(val);
        qDebug() << "Visibility: " << val << endl;
    }
    update();
}

void Editor::setLayerVisible(int val){
    if(!m_Layers.empty()){
        if(val >= 1){
            m_Layers.at(val+1)->setVisible(!m_Layers.at(val+1)->isVisible());
        }else{
            m_Layers.at(1)->setVisible(!m_Layers.at(val+1)->isVisible());
        }
    }
}

void Editor::addFrame()
{
    for(int i = 0; i < m_Layers.size(); i++){
        m_Layers.at(i)->createFrame();
    }
}

void Editor::setBrush(ToolType type)
{
    m_ToolType = type;
    switch(m_ToolType)
    {
    case BRUSH_TOOL:
        m_CurrentTool = m_Brush;
        m_CurrentTool.setColor(m_PrimaryColor);
        m_CurrentTool.setToolType(0);
        m_acceptTextInput = false;
        emit brushSizeChanged(m_Brush.getSize());
        emit toolChanged(0);
        break;
    case ERASER_TOOL:
        m_CurrentTool = m_Eraser;
        m_CurrentTool.setToolType(1);
        m_acceptTextInput = false;
        emit brushSizeChanged(m_Eraser.getSize());
        emit toolChanged(1);
    case TEXT_TOOL:
        m_CurrentTool.setToolType(2);
        m_acceptTextInput = true;
        m_ClipboardPresent = true;
        emit toolChanged(2);
        break;
    case PRIMITIVE_TOOL:
        m_CurrentTool.setToolType(2);
        emit toolChanged(3);
        break;
    case EYEDROPPER_TOOL:
        m_CurrentTool.setToolType(2);
        m_acceptTextInput = false;
        break;
    case FILL_TOOL:
        m_CurrentTool.setToolType(2);
        m_acceptTextInput = false;
        break;
    case TRANSFORM_TRANSLATE:
        m_CurrentTool.setToolType(2);
        m_acceptTextInput = false;
        emit toolChanged(7);
        break;
    default:
        m_CurrentTool.setToolType(0);
        emit toolChanged(0);
        break;
    }
}

int Editor::getRealWidth() const
{
    return m_realWidth;
}

int Editor::getRealHeight() const
{
    return m_realHeight;
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

void Editor::increaseBrushSize(){
    if(m_CurrentTool.getSize() < 500){
        setBrushSize(m_CurrentTool.getSize() + 5);
    }
    emit brushSizeChanged(m_CurrentTool.getSize());
}

void Editor::decreaseBrushSize(){
    if(m_CurrentTool.getSize() > 0){
        setBrushSize(m_CurrentTool.getSize() - 5);
    }else{
        setBrushSize(0);
    }
    emit brushSizeChanged(m_CurrentTool.getSize());
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
    m_fmt.setForeground(QBrush(m_PrimaryColor));
    emit currentColorChanged(m_PrimaryColor);
}

void Editor::setGreenValue(int val)
{
    m_GreenVal = val;
    m_PrimaryColor.setGreen(m_GreenVal);
    m_CurrentTool.setColor(m_PrimaryColor);
    m_fmt.setForeground(QBrush(m_PrimaryColor));
    emit currentColorChanged(m_PrimaryColor);
}

void Editor::setBlueValue(int val)
{
    m_BlueVal = val;
    m_PrimaryColor.setBlue(m_BlueVal);
    m_CurrentTool.setColor(m_PrimaryColor);
    m_fmt.setForeground(QBrush(m_PrimaryColor));
    emit currentColorChanged(m_PrimaryColor);
}

void Editor::increaseOpacity(){
    if(m_OpacityVal < 100){
        setOpacity(m_OpacityVal+10);
    }
    emit brushOpacityChanged(m_OpacityVal);
}

void Editor::decreaseOpacity(){
    if(m_OpacityVal > 0){
        setOpacity(m_OpacityVal-10);
    }
    emit brushOpacityChanged(m_OpacityVal);
}

void Editor::setOpacity(int val)
{
    m_OpacityVal = val;
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
    m_fmt.setFont(m_Font);
    setFocus();
}

void Editor::setFontSize(int font){
    m_FontSize = font;
    m_fmt.setFontPointSize(m_FontSize);
    setFocus();
}

void Editor::backup()
{
    if(!m_Layers.isEmpty())
    {
        backup(m_CurrentIndex-1, m_CurrentFrame-1);
        emit historySizeChanged(m_HistoryStack.size());
    }
}

void Editor::setBold(bool v){
    m_isBold = v;
    if(m_isBold) m_fmt.setFontWeight(QFont::Bold); else m_fmt.setFontWeight(QFont::Normal);
    setFocus();
}

void Editor::setItalic(bool v){
    m_isItalic = v;
    m_fmt.setFontItalic(v);
    setFocus();
}

void Editor::setUnderline(bool v){
    m_isUnderline = v;
    m_fmt.setFontUnderline(v);
    setFocus();
}

void Editor::scale(double scaleVal)
{
    m_ScaleFactor = scaleVal;
    for(int i = 0; i < m_Layers.size(); i++){
        m_Layers.at(i)->getFrame(m_CurrentFrame-1)->scale(m_ScaleFactor);
    }
    resize(m_realWidth * scaleVal, m_realHeight * scaleVal);
    update();
}

void Editor::resetScale(){
    m_ScaleFactor = 1.0;
}

void Editor::backup(int backupLayer, int backupFrame)
{
    while(m_HistoryStack.size() > m_HistorySteps && m_HistoryStack.size() > 0)
    {
        m_HistoryStack.removeFirst();
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
    if(!m_Layers.isEmpty()){
        m_BackupIndex--;
        HistoryStack* lastElement = m_HistoryStack[m_BackupIndex];
        BitmapHistoryStack* lastBitmapHist = (BitmapHistoryStack*)lastElement;
        m_Layers.at(lastBitmapHist->m_Layer)->getFrame(lastBitmapHist->m_Frame)->setPixmap(lastBitmapHist->m_Bitmap.getPixmap());
    }
}

void Editor::redo()
{
    if(!m_Layers.isEmpty()){
        if(m_BackupIndex > -1 && m_BackupIndex < m_HistoryStack.size() -1)
        {
            m_BackupIndex++;
            HistoryStack* lastElement = m_HistoryStack.last();
            BitmapHistoryStack* lastBitmapHist = (BitmapHistoryStack*)lastElement;
            m_Layers.at(lastBitmapHist->m_Layer)->getFrame(lastBitmapHist->m_Frame)->setPixmap(lastBitmapHist->m_Bitmap.getPixmap());
        }
    }
}

void Editor::cut(){
    if(!m_Layers.isEmpty()){
        copy();
        if(!m_acceptTextInput){
            if(m_Layers.size() > 2){
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->cutImgOp(m_SelectRect, QColor(Qt::transparent));
            }else{
                //just fill the selection rect with white
                m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->cutImgOp(m_SelectRect, QColor(Qt::white));
            }
        }else{
            m_textCursor.removeSelectedText();
        }
    }
    backup();
}

void Editor::copy(){
    if(!m_Layers.isEmpty()){
        QClipboard* clip = QApplication::clipboard();
        if(m_acceptTextInput){
            clip->setText(m_textCursor.selection().toPlainText());
        }else{
            QPixmap copyPix = m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->copy(m_SelectRect).getPixmap();
            clip->setPixmap(copyPix);
        }
    }

    backup();
}

void Editor::paste(){
    if(!m_Layers.isEmpty()){
        const QClipboard* clip = QApplication::clipboard();
        const QMimeData* mimeData = clip->mimeData();
        if(!m_ClipboardPresent) m_ClipboardPresent = true;
        if(mimeData->hasImage()){
            m_ClipboardPixmap = QPixmap::fromImage(qvariant_cast<QImage>(mimeData->imageData()));
            m_ClipOffsetPoint = QPoint( (this->getCurrentImage().width()/2 - m_ClipboardPixmap.width()/2), (this->getCurrentImage().height()/2 - m_ClipboardPixmap.height()/2) );
            m_SelectRect = m_ClipboardPixmap.rect();
            setBrush(ToolType::TRANSFORM_TRANSLATE);
        }else if(mimeData->hasText()){
            setBrush(ToolType::TEXT_TOOL);
            m_textCursor.insertText(clip->text(), m_fmt);
        }else{
            qDebug() << "Invalid Paste Option!" << endl;
        }
        backup();
    }
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

void Editor::useWindowsPenAPI(bool val)
{
#ifdef Q_OS_WIN
    m_useWinInkAPI = val;
#endif
}

void Editor::commitChanges(){
    if(!m_Layers.isEmpty()){
        if(!m_ClipboardPixmap.isNull()){
            m_Layers.at(m_CurrentIndex-1)->getFrame(m_CurrentFrame-1)->commitChanges(m_ClipOffsetPoint, m_ClipboardPixmap);
        }
        if(m_acceptTextInput) m_acceptTextInput = false;
        if(m_ClipboardPresent) m_ClipboardPresent = false;
        m_textCursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
        m_textCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        m_textCursor.removeSelectedText();
        m_textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
        m_ClipboardPixmap = QPixmap();
        m_ClipOffsetPoint = QPoint(0, 0);
        backup();
    }
}

void Editor::alternateTBlinker(){
    m_tCursorBlink =! m_tCursorBlink;
}

QPixmap Editor::generateTextPixmap(){
    QTextEdit* tempEdit = new QTextEdit(this);
    tempEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tempEdit->setDocument(m_textDocument);
    QPixmap ret(m_textDocument->size().toSize());
    qDebug() << "Text Document size: " << m_textDocument->pageSize().width() << endl;
    ret.fill(Qt::transparent);
    QRect temp = tempEdit->cursorRect(m_textCursor);

    QPainter p(&ret);
    p.setPen(Qt::black);
    p.setBrush(Qt::black);
    tempEdit->document()->drawContents(&p, ret.rect());
    if(m_tCursorBlink){
        p.drawRect(temp);
    }

    p.end();
    delete tempEdit;
    tempEdit = 0;


    update();
    return ret;
}

QPixmap Editor::generateShapePixmap(Primitive prim){
    QPixmap ret(prim.getWidth(), prim.getHeight());
    QPainter p(&ret);
    p.setPen(prim.getPen());
    p.setBrush(prim.getBrush());
    p.drawPath(prim.getShapePath());
    return ret;
}
