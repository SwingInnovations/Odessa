#include "panels.h"
#include "panels.h"

BrushConfigPanel::BrushConfigPanel(QWidget *parent) : QWidget(parent)
{
    initGUI();
}

Brush BrushConfigPanel::getStartingBrush() const
{
    return m_ActualBrushList[0];
}

void BrushConfigPanel::updateBrushSize(int value)
{
    m_brushSizeSE->setCurrentValue((int)value);
}

void BrushConfigPanel::updateBrushSize(qreal size)
{
    emit brushWidthChanged((int)size);
}

void BrushConfigPanel::updateBrushOpacity(int value)
{
    m_opacitySE->setCurrentValue((int)value);
}

void BrushConfigPanel::updateBrushOpacity(qreal opacity)
{
    emit brushOpacityChanged((int)opacity);
}

void BrushConfigPanel::updateBrushSpacing(qreal spacing)
{
    emit brushSpacingChanged(spacing);
}

void BrushConfigPanel::updateTransferSize(qreal size)
{
    emit brushTransferSizeChanged((int)size);
}

void BrushConfigPanel::updateTransferOpacity(qreal opacity)
{
    emit brushTransferOpacityChanged((int)opacity);
}

void BrushConfigPanel::toggleTransferSize(bool value)
{
    m_transferSizeSE->setEnabled(value);
}

void BrushConfigPanel::toggleTransferOpacity(bool value)
{
    m_transferOpacitySE->setEnabled(value);
}

void BrushConfigPanel::updateCurrentBrushIndex(int newInd)
{
    m_currentBrushIndex = newInd;
    //TODO Update things in Stencil.
    m_currentStencil = m_ActualBrushList[m_currentBrushIndex].getStencil();
    auto newStencil = m_ActualBrushList[m_currentBrushIndex].getStencil().toImage();
    newStencil = newStencil.scaled(80, 89);
    newStencil.invertPixels();
    m_StencilPrvwLbl->setPixmap(QPixmap::fromImage(newStencil));
    m_nameLE->setText(m_ActualBrushList[m_currentBrushIndex].getName());
    generateStrokePreview();
}

void BrushConfigPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void BrushConfigPanel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void BrushConfigPanel::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void BrushConfigPanel::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void BrushConfigPanel::initGUI()
{
    readSettings();
    m_currentBrushShape = CIRCLE;
    if(m_BrushLib.isEmpty()) m_BrushLib = m_ProjectPath + "/Brush/default.blib";

    m_inCustom = false;
    /*-Header Stuff-*/
    m_openDockBtn = new QPushButton("Pop..", this);     //Opens Docked Window version of this panel

    auto headerLayout = new QHBoxLayout;
    headerLayout->setSpacing(0);
    headerLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    headerLayout->addWidget(m_openDockBtn);

    m_WorkSpaceWidget = new QTabWidget(this);

    /*-Add New Brush Widget-*/

    /*Brush List*/
    m_brushListWidget = new QListWidget(this);
    m_brushListWidget->setStyleSheet("background: rgb(15, 15, 15);");
    m_AddBrushBtn = new QPushButton("+", this);
    m_RemoveBrushBtn = new QPushButton("-", this);
    m_OtherOptBtn = new QToolButton(this);
    m_OtherOptBtn->setText("...");

    m_LoadBrushLibraryAct = new QAction("Load Library", this);
    m_SaveBrushLibraryAct = new QAction("Save Library", this);
    m_LoadBrushAct = new QAction("Load Brush", this);
    m_SaveBrushAct = new QAction("Save Brush", this);

    m_OptMenu = new QMenu(this);
    m_OptMenu->addAction(m_LoadBrushLibraryAct);
    m_OptMenu->addAction(m_SaveBrushLibraryAct);
    m_OptMenu->addSeparator();
    m_OptMenu->addAction(m_LoadBrushAct);
    m_OptMenu->addAction(m_SaveBrushAct);
    m_OtherOptBtn->setMenu(m_OptMenu);

    auto listBtnLayout = new QHBoxLayout;
    listBtnLayout->setSpacing(0);
    listBtnLayout->addWidget(m_AddBrushBtn);
    listBtnLayout->addWidget(m_RemoveBrushBtn);
    listBtnLayout->addWidget(m_OtherOptBtn);
    //TODO Populate Brush Menu

    auto brushListLayout = new QVBoxLayout;
    brushListLayout->addWidget(m_brushListWidget);
    brushListLayout->addLayout(listBtnLayout);

    m_StencilPrvwLbl = new QLabel("Stencil", this);
    m_StencilPrvwLbl->setMinimumSize(80, 80);
    m_StrokePrvwLbl = new QLabel("Stroke", this);
    m_StrokePrvwLbl->setMinimumSize(160, 80);

    auto sizeLbl = new QLabel("Size: ", this);
    m_brushSizeSE = new SlideEdit(this);
    m_brushSizeSE->setLowerbound(0);
    m_brushSizeSE->setUpperBound(200);

    auto opacityLbl = new QLabel("Opacity: ", this);
    m_opacitySE = new SlideEdit(this);
    m_opacitySE->setLowerbound(0);
    m_opacitySE->setUpperBound(100);
    m_opacitySE->setCurrentValue(100);
    m_opacitySE->useIntegerStep(true);
    m_opacitySE->lockBounds(true);

    auto drawModeLbl = new QLabel("DrawMode: ", this);
    m_drawModeCmbx = new QComboBox(this);
    m_drawModeCmbx->addItem("Normal");
    m_drawModeCmbx->insertSeparator(1);
    m_drawModeCmbx->addItem("Plus");
    m_drawModeCmbx->addItem("Multiply");
    m_drawModeCmbx->insertSeparator(4);
    m_drawModeCmbx->addItem("Screen");
    m_drawModeCmbx->addItem("Overlay");
    m_drawModeCmbx->insertSeparator(7);
    m_drawModeCmbx->addItem("Darken");
    m_drawModeCmbx->addItem("Lighten");
    m_drawModeCmbx->insertSeparator(10);
    m_drawModeCmbx->addItem("Color Dodge");
    m_drawModeCmbx->addItem("Color Burn");
    m_drawModeCmbx->insertSeparator(13);
    m_drawModeCmbx->addItem("Hard Light");
    m_drawModeCmbx->addItem("Soft Light");
    m_drawModeCmbx->insertSeparator(16);
    m_drawModeCmbx->addItem("Difference");
    m_drawModeCmbx->addItem("Exclusion");

    m_drawModeCmbx->setCurrentIndex(0);

    auto spacingLbl = new QLabel("Spacing: ", this);
    m_spacingSE = new SlideEdit(this);
    m_spacingSE->setLowerbound(0);
    m_spacingSE->setUpperBound(1);
    m_spacingSE->setCurrentValue(1);
    m_spacingSE->lockBounds(true);

    m_transferSizeCB = new QCheckBox("Size: ", this);
    m_transferSizeSE = new SlideEdit(this);
    m_transferSizeSE->setLowerbound(0);
    m_transferSizeSE->setUpperBound(100);
    m_transferSizeSE->useIntegerStep(true);
    m_transferSizeSE->setEnabled(false);

    m_transferOpacityCB = new QCheckBox("Opacity: ", this);
    m_transferOpacitySE = new SlideEdit(this);
    m_transferOpacitySE->setLowerbound(0);
    m_transferOpacitySE->setUpperBound(100);
    m_transferOpacitySE->useIntegerStep(true);
    m_transferOpacitySE->lockBounds(true);
    m_transferOpacitySE->setCurrentValue(100);
    m_transferOpacitySE->setEnabled(false);

    auto transferLayout = new QGridLayout;
    transferLayout->addWidget(m_transferSizeCB, 0, 0);
    transferLayout->addWidget(m_transferSizeSE, 0, 1);
    transferLayout->addWidget(m_transferOpacityCB, 1, 0);
    transferLayout->addWidget(m_transferOpacitySE, 1, 1);

    m_transferWidget = new QGroupBox(this);
    m_transferWidget->setTitle("Transfer");
    m_transferWidget->setLayout(transferLayout);

    auto brushGridLayout = new QGridLayout;
    brushGridLayout->addWidget(m_StencilPrvwLbl, 0, 0);
    brushGridLayout->addWidget(m_StrokePrvwLbl, 0, 1);
    brushGridLayout->addWidget(sizeLbl, 1, 0);
    brushGridLayout->addWidget(m_brushSizeSE, 1, 1);
    brushGridLayout->addWidget(opacityLbl, 2, 0);
    brushGridLayout->addWidget(m_opacitySE, 2, 1);
    brushGridLayout->addWidget(spacingLbl, 3, 0);
    brushGridLayout->addWidget(m_spacingSE, 3, 1);
    brushGridLayout->addWidget(drawModeLbl, 4, 0);
    brushGridLayout->addWidget(m_drawModeCmbx, 4, 1);
    brushGridLayout->addWidget(m_transferWidget, 6, 0, 1, 0);

    auto brushLayout = new QHBoxLayout;
    brushLayout->addLayout(brushListLayout);
    brushLayout->addLayout(brushGridLayout);

    /*-Begin Color Widget-*/
    m_StencilPreviewLbl = new QLabel("Stencil Preview", this);
    m_stencilPreview = QPixmap(160, 160);
    m_stencilPreview.fill(Qt::transparent);
    m_StencilPreviewLbl->setPixmap(m_stencilPreview);

    auto stencilWidthLbl = new QLabel("Width: ", this);
    m_StencilWidthSE = new SlideEdit(this);
    m_StencilWidthSE->setLowerbound(0);
    m_StencilWidthSE->setUpperBound(10);
    m_StencilWidthSE->setCurrentValue(10);
    m_StencilWidthSE->lockBounds(true);
    m_StencilWidthSE->useIntegerStep(true);

    auto stencilHeightLbl = new QLabel("Height", this);
    m_StencilHeightSE = new SlideEdit(this);
    m_StencilHeightSE->setLowerbound(0);
    m_StencilHeightSE->setUpperBound(10);
    m_StencilHeightSE->setCurrentValue(10);
    m_StencilHeightSE->useIntegerStep(true);
    m_StencilHeightSE->lockBounds(true);

    auto hardnessLbl = new QLabel("Hardness: ", this);
    m_HardnessSE = new SlideEdit(this);
    m_HardnessSE->setLowerbound(0);
    m_HardnessSE->setUpperBound(100);
    m_HardnessSE->setCurrentValue(100);
    m_HardnessSE->useIntegerStep(true);
    m_HardnessSE->lockBounds(true);

    auto rotateLbl = new QLabel("Rotate: ", this);
    m_RotateSE = new SlideEdit(this);
    m_RotateSE->setLowerbound(0);
    m_RotateSE->setUpperBound(360);
    m_RotateSE->setCurrentValue(0);
    m_RotateSE->useIntegerStep(true);
    m_RotateSE->lockBounds(true);

    auto shapeLbl = new QLabel("Shape: ", this);
    m_StencilShapeCmbx = new QComboBox(this);
    m_StencilShapeCmbx->addItem("Circle");
    m_StencilShapeCmbx->addItem("Square");
    m_StencilShapeCmbx->addItem("Custom");

    auto stencilGridLayout =  new QGridLayout;
    stencilGridLayout->addWidget(m_StencilPreviewLbl, 0, 1, Qt::AlignCenter);
    stencilGridLayout->addWidget(stencilWidthLbl, 1, 0);
    stencilGridLayout->addWidget(m_StencilWidthSE, 1, 1);
    stencilGridLayout->addWidget(stencilHeightLbl, 2, 0);
    stencilGridLayout->addWidget(m_StencilHeightSE, 2, 1);
    stencilGridLayout->addWidget(hardnessLbl, 3, 0);
    stencilGridLayout->addWidget(m_HardnessSE, 3, 1);
    stencilGridLayout->addWidget(rotateLbl, 4, 0);
    stencilGridLayout->addWidget(m_RotateSE, 4, 1);
    stencilGridLayout->addWidget(shapeLbl, 5, 0);
    stencilGridLayout->addWidget(m_StencilShapeCmbx, 5, 1);

    QWidget* brushWidget = new QWidget(this);
    brushWidget->setLayout(brushLayout);

    QWidget* stencilWidget = new QWidget(this);
    stencilWidget->setLayout(stencilGridLayout);

    m_WorkSpaceWidget->addTab(brushWidget, "Brush");
    m_WorkSpaceWidget->addTab(stencilWidget, "Stencil");

    auto brushNameLbl = new QLabel("Name: ", this);
    m_nameLE = new QLineEdit(this);
    m_nameLE->setStyleSheet("background: rgb(15, 15, 15);");

    auto nameLayout = new QHBoxLayout;
    nameLayout->addWidget(brushNameLbl);
    nameLayout->addWidget(m_nameLE);

    auto workspaceLayout = new QVBoxLayout;
    workspaceLayout->addLayout(nameLayout);
    workspaceLayout->addWidget(m_WorkSpaceWidget);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addLayout(headerLayout);
    centralLayout->addLayout(workspaceLayout);

    setLayout(centralLayout);

    if(!QFile(m_BrushLib).exists()){
        //generate default
        m_ActualBrushList.append(Brush());
        m_ActualBrushList[0].setSWidth(10);
        m_ActualBrushList[0].setSHeight(10);
        m_ActualBrushList[0].setSpacing(1);
        m_ActualBrushList[0].setHardness(100);
        m_ActualBrushList[0].SetName("Default");
        QPixmap sten1;
        sten1.load(":/icon/resource/default.png");
        m_ActualBrushList[0].SetStencil(sten1);
        m_ActualBrushList.append(Brush());
        m_ActualBrushList[1].setSWidth(10);
        m_ActualBrushList[1].setSHeight(10);
        m_ActualBrushList[1].setSpacing(1);
        m_ActualBrushList[1].setHardness(0);
        m_ActualBrushList[1].SetName("Airbrush");
        sten1.load(":/icon/resource/airStencil.png");
        m_ActualBrushList[1].SetStencil(sten1);
        m_TempBrushList = m_ActualBrushList;
        saveBrushLib(m_BrushLib);
    }else{
        //use loaded data
        m_ActualBrushList = loadBrushLib(m_BrushLib);
        for(int i = 0; i < m_ActualBrushList.size(); i++){
            list_addBrush(m_ActualBrushList[i]);
        }
        m_TempBrushList = m_ActualBrushList;
    }
    QPixmap firstStencil = m_ActualBrushList[0].getStencil();
    m_currentStencil = firstStencil;
    firstStencil = firstStencil.scaled(80, 80);
    m_StencilPrvwLbl->setMinimumSize(firstStencil.size().width(), firstStencil.size().height());
    auto img = firstStencil.toImage();
    img.invertPixels();
    m_StencilPrvwLbl->setPixmap(QPixmap::fromImage(img));
    m_nameLE->setText(m_ActualBrushList[0].getName());
    generateStrokePreview();

    m_currentBrushIndex = 0;

    connect(m_transferSizeCB, SIGNAL(clicked(bool)), SLOT(toggleTransferSize(bool)));
    connect(m_transferOpacityCB, SIGNAL(clicked(bool)), SLOT(toggleTransferOpacity(bool)));
    connect(m_brushSizeSE, SIGNAL(valueChanged(qreal)), SLOT(updateBrushSize(qreal)));
    connect(m_opacitySE, SIGNAL(valueChanged(qreal)), SLOT(updateBrushOpacity(qreal)));
    connect(m_spacingSE, SIGNAL(valueChanged(qreal)), SLOT(updateBrushSpacing(qreal)));
    connect(m_transferSizeSE, SIGNAL(valueChanged(qreal)), SLOT(updateTransferSize(qreal)));
    connect(m_transferOpacitySE,SIGNAL(valueChanged(qreal)), SLOT(updateTransferOpacity(qreal)));
    connect(m_brushListWidget, SIGNAL(currentRowChanged(int)), SLOT(updateCurrentBrushIndex(int)));
    connect(m_StencilWidthSE, SIGNAL(valueChanged(qreal)), SLOT(updateStencilWidth(qreal)));
    connect(m_StencilHeightSE, SIGNAL(valueChanged(qreal)), SLOT(updateStencilHeight(qreal)));
    connect(m_HardnessSE, SIGNAL(valueChanged(qreal)), SLOT(updateStencilHardness(qreal)));
    connect(m_RotateSE, SIGNAL(valueChanged(qreal)), SLOT(updateStencilRotate(qreal)));
    connect(m_StencilShapeCmbx, SIGNAL(currentIndexChanged(int)), SLOT(updateBrushShape(int)));
    connect(m_LoadBrushAct, SIGNAL(triggered()), SLOT(loadBrushAct()));
    connect(m_LoadBrushLibraryAct, SIGNAL(triggered()), SLOT(loadbrushLibAct()));
    connect(m_SaveBrushAct, SIGNAL(triggered()), SLOT(saveBrushAct()));
    connect(m_SaveBrushLibraryAct, SIGNAL(triggered()), SLOT(saveBrushLibAct()));
    GenerateStencilPreview();
}

void BrushConfigPanel::GenerateStencilPreview()
{
    int stencilWidth = (m_stencilPreview.width() * m_StencilWidthSE->getValue()/10) / 2;
    int stencilHeight = (m_stencilPreview.height() * m_StencilHeightSE->getValue()/10) / 2;
    qreal hardness =(qreal)m_HardnessSE->getValue() / 100.f;
    QPoint midPoint(m_stencilPreview.width()/2 , m_stencilPreview.height()/2);
    m_stencilPreview.fill(Qt::transparent);
    QRadialGradient radGrad(midPoint, m_stencilPreview.width() / 2);
    radGrad.setColorAt(midPoint.x() / m_stencilPreview.width(), Qt::black);
    radGrad.setColorAt(0.0, Qt::black);
    radGrad.setColorAt(hardness, Qt::black);
    if(hardness == 1.f) radGrad.setColorAt(1.0, Qt::black);
    else radGrad.setColorAt(1.0f, Qt::transparent);

    QPainter p(&m_stencilPreview);
    switch(m_currentBrushShape){
        case CIRCLE:
            //TODO Implement if texture is present;
            p.setBrush(radGrad);

            //END TODO

            p.translate(midPoint);
            p.rotate(m_RotateSE->getValue());
            p.translate(-midPoint);
            p.drawEllipse(midPoint, stencilWidth, stencilHeight);
            break;
        case SQUARE:
            int oX = midPoint.x() - stencilWidth;
            int oY = midPoint.y() - stencilHeight;
            int dimX = stencilWidth * 2;
            int dimY = stencilHeight * 2;

            //TODO Implement if texture is present
            p.setBrush(radGrad);
            //END TODO
            p.translate(midPoint);
            p.rotate(m_RotateSE->getValue());
            p.translate(-midPoint);
            p.drawRect(oX, oY, dimX, dimY);
            break;
    }
    m_StencilPreviewLbl->setPixmap(m_stencilPreview);
}

void BrushConfigPanel::readSettings()
{
    QSettings settings("SwingInnovations", "Odessa");
    m_ProjectPath = settings.value("projectPath").toString();
    m_BrushLib = settings.value("activeBrushLib").toString();
}

void BrushConfigPanel::writeSettings()
{
    QSettings settings("SwingInnovations", "Odessa");
    settings.setValue("activeBrushLib", m_BrushLib);
    saveBrushLib(m_BrushLib);
}

void BrushConfigPanel::loadBrushAct()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush", m_ProjectPath, ".brsh");
    Brush temp = loadBrush(filePath);
    m_TempBrushList.append(temp);
    m_ActualBrushList.append(temp);
    list_addBrush(temp);
}

void BrushConfigPanel::loadbrushLibAct()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush Library", m_ProjectPath, "*.blib");
    QMessageBox msgBox;
    msgBox.setText("Would you like to load a new brush set or add to existing?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, "Load new set");
    msgBox.setButtonText(QMessageBox::Cancel, "Add to existing set");
    auto newList = loadBrushLib(filePath);
    switch(msgBox.exec())
    {
        case QMessageBox::Ok:
            m_ActualBrushList = newList;
            m_BrushLib = filePath;
            break;
        case QMessageBox::Cancel:
            m_ActualBrushList = m_ActualBrushList + newList;
        break;
    }
}

void BrushConfigPanel::saveBrushAct()
{

}

void BrushConfigPanel::saveBrushLibAct()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Brush Library", m_ProjectPath, "*.blib");
    saveBrushLib(filePath);
}

void BrushConfigPanel::updateStencilWidth(qreal width)
{
    m_TempBrushList[m_currentBrushIndex].s_Width = (int)width;
    GenerateStencilPreview();
    emit stencilChanged(m_stencilPreview);
}

void BrushConfigPanel::updateStencilHeight(qreal height)
{
    m_TempBrushList[m_currentBrushIndex].s_Height = (int)height;
    GenerateStencilPreview();
    emit stencilChanged(m_stencilPreview);
}

void BrushConfigPanel::updateStencilHardness(qreal hardness)
{
    GenerateStencilPreview();
    emit stencilChanged(m_stencilPreview);
}

void BrushConfigPanel::updateStencilRotate(qreal rotate)
{

    GenerateStencilPreview();
    emit stencilChanged(m_stencilPreview);
}

void BrushConfigPanel::updateBrushShape(int index)
{
    switch(index){
    case 0:
        m_currentBrushShape = CIRCLE;
        break;
    case 1:
        m_currentBrushShape = SQUARE;
        break;
    case 3:
        m_currentBrushShape = CUSTOM;
        break;
    }
    GenerateStencilPreview();
}

Brush BrushConfigPanel::loadBrush(QString filePath)
{
    Brush ret;
    int encrypt = 5025;
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly)) qDebug() << "Error: Invalid file!" << endl;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    in >> encrypt >> ret;
    file.close();
    return ret;
}

void BrushConfigPanel::saveBrushLib(QString filePath)
{
    int encrypt = 5025;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)) qDebug() << "Error: Could not open file!" << endl;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);
    out << encrypt << m_ActualBrushList;
    file.flush();
    file.close();
}

QVector<Brush> BrushConfigPanel::loadBrushLib(QString filePath)
{
    int encrypt = 5025;
    QVector<Brush> ret;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) qDebug() <<  "Error: Could not open file!" << endl;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    in >> encrypt >> ret;
    file.close();
    return ret;
}

void BrushConfigPanel::list_addBrush(Brush brush)
{
    QListWidgetItem* itm = new QListWidgetItem(brush.m_Name);
    QImage stencilIcon = brush.getStencil().toImage();
    stencilIcon.invertPixels();
    itm->setIcon(QPixmap::fromImage(stencilIcon));
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    m_brushListWidget->addItem(itm);
}

void BrushConfigPanel::generateStrokePreview()
{
    m_StrokePreview = QPixmap(160, 80);
    m_StrokePreview.fill(Qt::transparent);
    QPainterPath path;
    path.moveTo(20, 20);
    path.cubicTo(QPointF(1.0/3.0 * (double)m_StrokePreview.width(), m_StrokePreview.height()), QPointF(1.0/3.0 * (double)m_StrokePreview.width(), m_StrokePreview.height()), QPointF(m_StrokePreview.width()/2, m_StrokePreview.height()/2));
    path.cubicTo(QPointF(2.0/3.0 * (double)m_StrokePreview.width(), 0), QPointF(2.0/3.0 * (double)m_StrokePreview.width(), 0), QPointF(m_StrokePreview.width()-20, m_StrokePreview.height() - 20));

    qreal minWidth = 5.0;
    qreal maxWidth = 10.0;

    QImage stenBase = m_currentStencil.toImage();
    stenBase.invertPixels(QImage::InvertRgb);
    stenBase.createAlphaMask();
    stenBase.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    QImage stencil(stenBase);
    stencil.fill(Qt::white);
    stencil.setAlphaChannel(stenBase);
    QPixmap fSten = QPixmap::fromImage(stencil.scaled(minWidth, minWidth));

    QPainter p(&m_StrokePreview);
    p.setPen(Qt::black);
    p.setBrush(Qt::transparent);
    qreal bigger = 0.0;
    for(double i = 0.0; i < 1.0; i+= 0.0001){
        QPoint drawPoint = path.pointAtPercent(i).toPoint();
//        if(m_usePressureWidth){
//            if(i <= 0.5){
//                bigger = i;
//            }else{
//                bigger = -i;
//            }
//            fSten = fSten.scaled(minWidth + bigger, minWidth + bigger);
//             p.drawPixmap(QPoint(drawPoint.x() - fSten.width()/2.0, drawPoint.y() - fSten.height()/2), fSten);
//        }else{
//             p.drawPixmap(QPoint(drawPoint.x() - fSten.width()/2.0, drawPoint.y() - fSten.height()/2), fSten);
//        }

        p.drawPixmap(QPoint(drawPoint.x() - fSten.width()/2.0, drawPoint.y() - fSten.height()/2), fSten);

    }
    p.end();
    m_StrokePrvwLbl->setPixmap(m_StrokePreview);
}

ColorCell::ColorCell(QColor color, QWidget *parent, Editor *editor) : QWidget(parent)
{
    m_color = color;
    m_editor = editor;
    setFixedSize(32, 32);
    setMouseTracking(true);
}

void ColorCell::SetColor(QColor color)
{
    m_color = color;
    update();
}

void ColorCell::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Widget Pressed" << endl;
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "Left Button Pressed" << endl;
        //Assign color to editor
        m_editor->setBrushColor(m_color);
        return;
    }

    if(event->button() == Qt::RightButton)
    {
        //Assign color from editor
        qDebug() << "Right Button Pressed" << endl;
        m_color = m_editor->getCurrentBrushColor();
        repaint();
    }
}

void ColorCell::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(m_color);
    p.drawRect(QRect(0, 0, 32, 32));
}


ColorConfigPanel::ColorConfigPanel(QWidget *parent, Editor *editor, ColorConfigOrientation orientation) : QWidget(parent), m_colorPalleteLoaded(false)
{
    m_editor = editor;
    initGui(orientation);
}

ColorConfigPanel::~ColorConfigPanel()
{

}

void ColorConfigPanel::updateColorFromEditor(QColor color)
{
    m_colorWheel->setActualColor(color);
    m_RSlider->setCurrentValue(color.red(), false);
    m_GSlider->setCurrentValue(color.green(), false);
    m_BSlider->setCurrentValue(color.blue(), false);
    updateHSV(color);
}

void ColorConfigPanel::updateRed(qreal newRed)
{
    m_colorWheel->setRed((int)newRed);
    emit redChanged((int)newRed);
    updateHSV(m_colorWheel->getColor());
}

void ColorConfigPanel::updateGreen(qreal newGreen)
{
    m_colorWheel->setGreen((int)newGreen);
    emit greenChanged((int)newGreen);
    updateHSV(m_colorWheel->getColor());
}

void ColorConfigPanel::updateBlue(qreal newBlue)
{
    m_colorWheel->setBlue((int)newBlue);
    emit blueChanged((int)newBlue);
    updateHSV(m_colorWheel->getColor());
}

//Updating from color wheel
void ColorConfigPanel::updateColor(QColor incomingColor)
{
    m_RSlider->setCurrentValue(incomingColor.red(), false);
    m_GSlider->setCurrentValue(incomingColor.green(), false);
    m_BSlider->setCurrentValue(incomingColor.blue(), false);
    updateHSV(incomingColor);
}

void ColorConfigPanel::loadColorPalleteAct()
{
    QString colorPalletePath = QFileDialog::getOpenFileName(this, "Open Color Pallete", QDir::currentPath(), ".stpal");
    if(colorPalletePath.size() > 0)
    {
        m_currentPalletString = colorPalletePath;
        loadPallete(m_currentPalletString);
    }
    //TODO Save this to QSetting
}

void ColorConfigPanel::saveColorPalleteAct()
{
    //TODO Implement
    QString colorPalletePath = QFileDialog::getSaveFileName(this, "Save Color Pallete", QDir::currentPath(), ".stpal");
    if(colorPalletePath.size() > 0)
    {
        savePallete(colorPalletePath);
    }
}

void ColorConfigPanel::toggleColorPicker()
{
    //TODO Implement - Changes color picker shape from triangle to square.

}

void ColorConfigPanel::updateHSV(QColor incomingColor)
{
    int h, s, v;
    incomingColor.getHsv(&h, &s, &v);
    m_HSlider->setCurrentValue(h, false);
    m_SSlider->setCurrentValue(s, false);
    m_VSlider->setCurrentValue(v, false);
}

void ColorConfigPanel::initGui(ColorConfigPanel::ColorConfigOrientation orientation)
{
    readFromLastPallette();     //Load from the system settings
    bool isVerticalLayout = (orientation == ColorConfigOrientation::Vertical);
    QBoxLayout* centralLayout;

    if(isVerticalLayout)
    {
        centralLayout = new QVBoxLayout;
    }
    else
    {
        centralLayout = new QHBoxLayout;
    }


    QVBoxLayout* colorWheelLayout = new QVBoxLayout;
    m_colorWheel = new ColorWheel(this);
    auto pix = m_colorWheel->pixmap();
    pix->scaled(320, 320);
    m_colorWheel->setPixmap(*pix);

    //Create Menu for options
    QAction* loadPalleteAct = new QAction("Load Pallete", this);
    QAction* savePalleteAct = new QAction("Save Pallete", this);

    QMenu* colorMenu = new QMenu(this);
    colorMenu->addAction(loadPalleteAct);
    colorMenu->addAction(savePalleteAct);

    QPushButton* triangleBtn = new QPushButton("Triangle", this);   //TODO Implement this.. Switch to triangle color picker
    QPushButton* squareBtn = new QPushButton("Square", this);       //TODO Implement this.. Switch to Rectangular color picker
    QToolButton* optionsBtn = new QToolButton(this);
    optionsBtn->setText("..");
    optionsBtn->setFixedWidth(32);
    optionsBtn->setMenu(colorMenu);

    QHBoxLayout* shapeBtnLayout = new QHBoxLayout;
    shapeBtnLayout->setSpacing(0);
    shapeBtnLayout->addWidget(triangleBtn);
    shapeBtnLayout->addWidget(squareBtn);
    shapeBtnLayout->addWidget(optionsBtn);

    colorWheelLayout->addWidget(m_colorWheel);
    if(isVerticalLayout)
    {
        colorWheelLayout->setAlignment(m_colorWheel, Qt::AlignCenter);
    }
    colorWheelLayout->addLayout(shapeBtnLayout);

    centralLayout->addLayout(colorWheelLayout);

    auto colorTabs = new QTabWidget(this);

    QGridLayout* colorPalletLayout = new QGridLayout;
    colorPalletLayout->setHorizontalSpacing(1);
    colorPalletLayout->setVerticalSpacing(1);

    if(m_colorPalleteLoaded)
    {
        //Load with known values
        //TODO Implement
    }
    else
    {
        int posX = 1, posY = 0, r = 10, g = 10, b = 10;
        bool rPassed, gPassed;
        rPassed = gPassed = false;
        for(uint i = 0; i < 60; i++)
        {
            colorPalletLayout->addWidget(new ColorCell(QColor(r, g, b), this, m_editor), posY, posX);
            if(posX == 12)
            {
                posX = 0;
                posY++;
            }

            if(!rPassed)
            {
                if(r <= 255)
                {
                    r += 15;
                    g = 0;
                    b = 0;
                }
                else
                {
                    rPassed = true;
                }
            }
            else if(!gPassed)
            {
                if(g <= 255)
                {
                    r = 0;
                    g += 15;
                    b = 0;
                }
                else
                {
                    gPassed = true;
                }
            }
            else
            {
                r = 0;
                b+=15;
                g = 0;
            }
            posX += 1;
            m_currentPallete.colors[i] = QColor(r, g, b);
        }
        m_rows = posY;
        m_cols = posX;
    }

    QWidget* PalleteTabWidget = new QWidget(this);
    PalleteTabWidget->setLayout(colorPalletLayout);

    //START RGB Widget
    QWidget* RGBTabWidget = new QWidget(this);
    m_RSlider = new SlideEdit(this);
    m_RSlider->setLowerbound(0);
    m_RSlider->setUpperBound(255);
    m_RSlider->setCurrentValue(0);
    m_RSlider->lockBounds(true);
    m_RSlider->useIntegerStep(true);

    m_GSlider = new SlideEdit(this);
    m_GSlider->setLowerbound(0);
    m_GSlider->setUpperBound(255);
    m_GSlider->setCurrentValue(0);
    m_GSlider->lockBounds(true);
    m_GSlider->useIntegerStep(true);

    m_BSlider = new SlideEdit(this);
    m_BSlider->setLowerbound(0);
    m_BSlider->setUpperBound(255);
    m_BSlider->setCurrentValue(0);
    m_BSlider->lockBounds(true);
    m_BSlider->useIntegerStep(true);

    QGridLayout* RGBGrid = new QGridLayout;
    RGBGrid->addWidget(new QLabel("R:", this), 0, 0);
    RGBGrid->addWidget(m_RSlider, 0, 1);
    RGBGrid->addWidget(new QLabel("G:", this), 1, 0);
    RGBGrid->addWidget(m_GSlider, 1, 1);
    RGBGrid->addWidget(new QLabel("B:", this), 2, 0);
    RGBGrid->addWidget(m_BSlider, 2, 1);

    RGBTabWidget->setLayout(RGBGrid);
    //END RGB Widget

    //START HSV Tab
    QWidget* HSVTabWidget = new QWidget(this);
    m_HSlider = new SlideEdit(this);
    m_HSlider->setLowerbound(0);
    m_HSlider->setUpperBound(255);
    m_HSlider->setCurrentValue(0);
    m_HSlider->lockBounds(true);
    m_HSlider->useIntegerStep(true);

    m_SSlider = new SlideEdit(this);
    m_SSlider->setLowerbound(0);
    m_SSlider->setUpperBound(255);
    m_SSlider->setCurrentValue(0);
    m_SSlider->lockBounds(true);
    m_SSlider->useIntegerStep(true);

    m_VSlider = new SlideEdit(this);
    m_VSlider->setLowerbound(0);
    m_VSlider->setUpperBound(255);
    m_VSlider->setCurrentValue(0);
    m_VSlider->lockBounds(true);
    m_VSlider->useIntegerStep(true);

    QGridLayout* HSVGrid = new QGridLayout;
    HSVGrid->addWidget(new QLabel("H: ", this), 0, 0);
    HSVGrid->addWidget(m_HSlider, 0, 1);
    HSVGrid->addWidget(new QLabel("S: ", this), 1, 0);
    HSVGrid->addWidget(m_SSlider, 1, 1);
    HSVGrid->addWidget(new QLabel("V: ", this), 2, 0);
    HSVGrid->addWidget(m_VSlider, 2, 1);
    HSVTabWidget->setLayout(HSVGrid);
    //END HSVTab

    colorTabs->addTab(PalleteTabWidget, "Pallete");
    colorTabs->addTab(RGBTabWidget, "RGB");
    colorTabs->addTab(HSVTabWidget, "HSV");
	colorTabs->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );

    if(!isVerticalLayout)
    {
        colorTabs->setFixedWidth(316);
    }

    centralLayout->addWidget(colorTabs);

    if(isVerticalLayout){
        centralLayout->addSpacerItem(new QSpacerItem(0 ,0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }

    setLayout(centralLayout);

    connect(m_colorWheel, SIGNAL(colorChanged(QColor)), SLOT(updateColor(QColor)));
    connect(m_RSlider, SIGNAL(valueChanged(qreal)), SLOT(updateRed(qreal)));
    connect(m_GSlider, SIGNAL(valueChanged(qreal)), SLOT(updateGreen(qreal)));
    connect(m_BSlider, SIGNAL(valueChanged(qreal)), SLOT(updateBlue(qreal)));
    connect(m_editor, SIGNAL(currentColorChanged(QColor)), SLOT(updateColorFromEditor(QColor)));
    connect(loadPalleteAct, SIGNAL(triggered()), SLOT(loadColorPalleteAct()));
    connect(savePalleteAct, SIGNAL(triggered()), SLOT(saveColorPalleteAct()));
}

void ColorConfigPanel::readFromLastPallette()
{
    QSettings settings("SwingInnovations", "Odessa");
    m_currentPalletString = settings.value("currentPalletePath").toString();
    if(m_currentPalletString.size() > 0)
    {
        loadPallete(m_currentPalletString);
    }
    else
    {
        qDebug() << "No Color Pallete Found" << endl;
    }
}

void ColorConfigPanel::loadPallete(QString filePath)
{
    int encrypt = 5025;
    ColorPalleteInfo colorPalletInfo;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error, could not open file!" << endl;
        return;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    in >> encrypt >> colorPalletInfo;
    file.close();
    m_currentPallete = colorPalletInfo;
}

void ColorConfigPanel::savePallete(QString filePath)
{
    int encrypt = 5025;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open file" << endl;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);
    out << encrypt << m_currentPallete;

    file.flush();
    file.close();
}

