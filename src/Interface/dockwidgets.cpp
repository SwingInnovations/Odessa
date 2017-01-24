#include "dockwidgets.h"

BrushDockWidget::BrushDockWidget(QWidget *parent) : QDockWidget(parent)
{
    /*-Constructor-*/
    m_TabWidget = new QTabWidget(this);
    m_GenBrushWidget = new GeneralBrushWidget;
    m_StencilWidget = new CustomBrushWidget;

    m_ActualBrushList = QVector<Brush>();
    m_TempBrushList = QVector<Brush>();

    m_CurrentBrushIndex = 0;
    m_firstTimeRun = false;

    readSettings();
    m_BrushLib = m_ProjectPath + "/Brush/default.blib";

    if(!QFile(m_BrushLib).exists()){
        //generate default
        m_ActualBrushList.append(Brush());
        m_ActualBrushList[0].setSWidth(10);
        m_ActualBrushList[0].setSHeight(10);
        m_ActualBrushList[0].setSpacing(1);
        m_ActualBrushList[0].setHardness(100);
        m_ActualBrushList[0].SetName("Default");
        m_StencilWidget->setBrushSettings(m_ActualBrushList.first());
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
        m_GenBrushWidget->addBrush(m_ActualBrushList.at(0));
        m_GenBrushWidget->addBrush(m_ActualBrushList.at(1));
        m_GenBrushWidget->setStencilPixmap(m_ActualBrushList.first().getStencil());
        m_StencilWidget->updateStencilWidth(m_TempBrushList.at(0).getSWidth());
        m_StencilWidget->updateStencilHeight(m_TempBrushList.at(0).getSHeight());
        saveBrushLib(m_BrushLib);
    }else{
        //use loaded data
        m_ActualBrushList = loadBrushLib(m_BrushLib);
        for(int i = 0; i < m_ActualBrushList.size(); i++){
            m_GenBrushWidget->addBrush(m_ActualBrushList.at(i));
        }
        m_TempBrushList = m_ActualBrushList;
    }

    m_DrawModeCmbx = new QComboBox(this);
    m_DrawModeCmbx->addItem("Normal");
    m_DrawModeCmbx->insertSeparator(1);
    m_DrawModeCmbx->addItem("Plus");
    m_DrawModeCmbx->addItem("Multiply");
    m_DrawModeCmbx->insertSeparator(4);
    m_DrawModeCmbx->addItem("Screen");
    m_DrawModeCmbx->addItem("Overlay");
    m_DrawModeCmbx->insertSeparator(7);
    m_DrawModeCmbx->addItem("Darken");
    m_DrawModeCmbx->addItem("Lighten");
    m_DrawModeCmbx->addItem("Color Dodge");
    m_DrawModeCmbx->addItem("Color Burn");
    m_DrawModeCmbx->addItem("Hard Light");
    m_DrawModeCmbx->addItem("Soft Light");
    m_DrawModeCmbx->insertSeparator(14);
    m_DrawModeCmbx->addItem("Difference");
    m_DrawModeCmbx->addItem("Exclusion");

    m_SizeLabel = new QLabel("Size:", this);
    m_SizeSlider = new QSlider(Qt::Horizontal, this);
    m_SizeSlider->setRange(0, 500);
    m_SizeSlider->setValue(5);
    m_SizeSlider->setMinimumWidth(150);
    m_SizeLE = new QSpinBox(this);
    m_SizeLE->setRange(0, 500);
    m_SizeLE->setFixedWidth(48);
    m_SizeLE->setValue(5);
    QHBoxLayout* sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(m_SizeLabel);
    sizeLayout->addWidget(m_SizeSlider);
    sizeLayout->addWidget(m_SizeLE);

    m_OpacityLabel = new QLabel("Opacity:", this);
    m_OpacitySlider = new QSlider(Qt::Horizontal, this);
    m_OpacitySlider->setRange(0, 100);
    m_OpacitySlider->setValue(100);
    m_OpacityLE = new QSpinBox(this);
    m_OpacityLE->setRange(0, 100);
    m_OpacityLE->setFixedWidth(48);
    m_OpacityLE->setValue(100);
    QHBoxLayout* opacityLayout = new QHBoxLayout;
    opacityLayout->addWidget(m_OpacityLabel);
    opacityLayout->addWidget(m_OpacitySlider);
    opacityLayout->addWidget(m_OpacityLE);

    m_SpacingLabel = new QLabel("Spacing:", this);
    m_SpacingSlider = new QSlider(Qt::Horizontal, this);
    m_SpacingSlider->setRange(0, 3);
    m_SpacingSlider->setPageStep(0.1);
    m_SpacingSlider->setValue(1);
    m_SpacingSlider->setMinimumWidth(150);
    m_SpacingLE = new QSpinBox(this);
    m_SpacingLE->setFixedWidth(48);
    m_SpacingLE->setValue(1);
    QHBoxLayout* spacingLayout = new QHBoxLayout;
    spacingLayout->addWidget(m_SpacingLabel);
    spacingLayout->addWidget(m_SpacingSlider);
    spacingLayout->addWidget(m_SpacingLE);

    QVBoxLayout* generalParam = new QVBoxLayout;
    generalParam->addWidget(m_DrawModeCmbx);
    generalParam->addLayout(sizeLayout);
    generalParam->addLayout(opacityLayout);
    generalParam->addLayout(spacingLayout);

    /*-Transfer-*/
    m_TransferSizeToggle = new QCheckBox("Size:", this);
    m_TransferSizeToggle->setChecked(false);
    m_TransferSizeSlider = new QSlider(Qt::Horizontal, this);
    m_TransferSizeSlider->setRange(0, 500);
    m_TransferSizeSlider->setValue(0);
    m_TransferSizeSlider->setEnabled(false);
    m_TransferSizeLE = new QSpinBox(this);
    m_TransferSizeLE->setFixedWidth(48);
    m_TransferSizeLE->setRange(0, 500);
    m_TransferSizeLE->setValue(0);
    m_TransferSizeLE->setEnabled(false);
    QHBoxLayout* transferSizeLayout = new QHBoxLayout;
    transferSizeLayout->addWidget(m_TransferSizeToggle);
    transferSizeLayout->addWidget(m_TransferSizeSlider);
    transferSizeLayout->addWidget(m_TransferSizeLE);

    m_TransferOpacityToggle = new QCheckBox("Opacity:", this);
    m_TransferOpacityToggle->setChecked(false);
    m_TransferOpacitySlider = new QSlider(Qt::Horizontal, this);
    m_TransferOpacitySlider->setRange(0, 255);
    m_TransferOpacitySlider->setValue(0);
    m_TransferOpacitySlider->setEnabled(false);
    m_TransferOpacityLE = new QSpinBox(this);
    m_TransferOpacityLE->setRange(0, 100);
    m_TransferOpacityLE->setFixedWidth(48);
    m_TransferOpacityLE->setValue(0);
    m_TransferOpacityLE->setEnabled(false);
    QHBoxLayout* transferOpacityLayout = new QHBoxLayout;
    transferOpacityLayout->addWidget(m_TransferOpacityToggle);
    transferOpacityLayout->addWidget(m_TransferOpacitySlider);
    transferOpacityLayout->addWidget(m_TransferOpacityLE);

    m_TransferOpacityLE->setVisible(false);
    m_TransferOpacitySlider->setVisible(false);
    m_TransferOpacityToggle->setVisible(false);
    m_TransferSizeLE->setVisible(false);
    m_TransferSizeSlider->setVisible(false);
    m_TransferSizeToggle->setVisible(false);

    QVBoxLayout* transferParam = new QVBoxLayout;
    transferParam->addLayout(transferSizeLayout);
    transferParam->addLayout(transferOpacityLayout);
    m_transGrpBox = new QGroupBox("Transfer" ,this);
    m_transGrpBox->setCheckable(true);
    m_transGrpBox->setChecked(false);
    m_transGrpBox->setLayout(transferParam);

    generalParam->addWidget(m_transGrpBox);

    /*-Brush_General-*/

    QVBoxLayout* GeneralBrushLayout = new QVBoxLayout;
    GeneralBrushLayout->addWidget(m_GenBrushWidget);
    GeneralBrushLayout->addLayout(generalParam);

    QWidget* GeneralBrushTab = new QWidget(this);
    GeneralBrushTab->setLayout(GeneralBrushLayout);

    /*-Brush_Advanced-*/

    QVBoxLayout* AdvancedBrushLayout = new QVBoxLayout;
    AdvancedBrushLayout->addWidget(m_StencilWidget);

    QWidget* AdvancedBrushTab = new QWidget(this);
    AdvancedBrushTab->setLayout(AdvancedBrushLayout);

    m_TabWidget->addTab(GeneralBrushTab, "General");
    m_TabWidget->addTab(AdvancedBrushTab, "Custom");

    m_TabWidget->setTabPosition(QTabWidget::North);
    m_TabWidget->setTabShape(QTabWidget::Rounded);

    QVBoxLayout* displayLayout = new QVBoxLayout;
    displayLayout->addWidget(m_TabWidget);
    displayLayout->addSpacerItem(new QSpacerItem(292, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QWidget* displayWidget = new QWidget(this);
    displayWidget->setLayout(displayLayout);

    setWidget(displayWidget);

    connect(m_SizeSlider, SIGNAL(valueChanged(int)), SLOT(updateSize(int)));
    connect(m_SizeLE, SIGNAL(valueChanged(QString)), SLOT(updateSize(QString)));
    connect(m_OpacitySlider, SIGNAL(valueChanged(int)), SLOT(updateOpacity(int)));
    connect(m_OpacityLE, SIGNAL(valueChanged(QString)), SLOT(updateOpacity(QString)));
    connect(m_SpacingSlider, SIGNAL(valueChanged(int)), SLOT(updateSpacing(int)));
    connect(m_SpacingLE, SIGNAL(valueChanged(QString)), SLOT(updateSpacing(QString)));
    connect(m_TransferSizeToggle, SIGNAL(toggled(bool)), SLOT(toggleTransferSize(bool)));
    connect(m_TransferSizeSlider, SIGNAL(valueChanged(int)), SLOT(updateTransferSize(int)));
    connect(m_TransferSizeLE, SIGNAL(valueChanged(QString)), SLOT(updateTransferSize(QString)));
    connect(m_TransferOpacityToggle, SIGNAL(toggled(bool)), SLOT(toggleTransferOpacity(bool)));
    connect(m_TransferOpacitySlider, SIGNAL(valueChanged(int)), SLOT(updateTransferOpacity(int)));
    connect(m_TransferOpacityLE, SIGNAL(valueChanged(QString)), SLOT(updateTransferOpacity(QString)));
    connect(m_StencilWidget, SIGNAL(stencilChanged(QPixmap)), SLOT(updateStencil(QPixmap)));
    connect(m_StencilWidget, SIGNAL(stencilChanged(QPixmap)), m_GenBrushWidget, SLOT(updateStencil(QPixmap)));
    connect(m_StencilWidget, SIGNAL(stencilPathChanged(QString)), SLOT(updateStencilPath(QString)));
    connect(m_transGrpBox, SIGNAL(toggled(bool)), SLOT(toggleTransferVisibility(bool)));
    connect(m_GenBrushWidget, SIGNAL(loadStencilTriggered()), SLOT(loadStencilAct()));
    connect(m_GenBrushWidget, SIGNAL(loadBrushTriggered()), SLOT(loadBrushAct()));
    connect(m_GenBrushWidget, SIGNAL(loadBrushSetTriggered()), SLOT(loadBrushSetAct()));
    connect(m_GenBrushWidget, SIGNAL(saveStencilTriggered()), SLOT(saveStencilAct()));
    connect(m_GenBrushWidget, SIGNAL(saveBrushTriggered()), SLOT(saveBrushAct()));
    connect(m_GenBrushWidget, SIGNAL(saveBrushSetTriggered()), SLOT(saveBrushSetAct()));
    connect(m_StencilWidget, SIGNAL(loadStencilTriggered()), SLOT(loadStencilAct()));
    connect(m_StencilWidget, SIGNAL(loadBrushTriggered()), SLOT(loadBrushAct()));
    connect(m_StencilWidget, SIGNAL(loadBrushSetTriggered()), SLOT(loadBrushSetAct()));
    connect(m_StencilWidget, SIGNAL(saveStencilTriggered()), SLOT(saveStencilAct()));
    connect(m_StencilWidget, SIGNAL(saveBrushTriggered()), SLOT(saveBrushAct()));
    connect(m_StencilWidget, SIGNAL(saveBrushSetTriggered()), SLOT(saveBrushSetAct()));
    connect(m_StencilWidget, SIGNAL(StencilWidthChanged(int)), SLOT(updateStencilWidth(int)));
    connect(m_StencilWidget, SIGNAL(stencilHeightChanged(int)), SLOT(updateStencilHeight(int)));
    connect(m_StencilWidget, SIGNAL(brushHardnessChanged(int)), SLOT(updateStencilHardness(int)));
    connect(m_StencilWidget, SIGNAL(rotateChanged(int)), SLOT(updateStencilRotate(int)));
    connect(m_GenBrushWidget, SIGNAL(brushLibIndexChanged(int)), SLOT(setCurrentIndex(int)));
    connect(m_GenBrushWidget, SIGNAL(brushNameChanged(QString)), SLOT(updateBrushName(QString)));
    update();
}

void BrushDockWidget::setDirectory(QString dir){
    m_ProjectPath = dir;
    m_GenBrushWidget->setDir(dir);
}

void BrushDockWidget::updateSize(int val)
{
    m_SizeLE->setValue(val);
    emit brushSizeChanged(val);
}

void BrushDockWidget::updateSize(QString val)
{
    m_SizeSlider->setValue(val.toInt());
    emit brushSizeChanged(val.toInt());
}

void BrushDockWidget::updateOpacity(int val)
{
    m_OpacityLE->setValue(val);
    emit brushOpacityChanged(val);
}

void BrushDockWidget::updateOpacity(QString val)
{
    m_OpacitySlider->setValue(val.toInt());
    emit brushOpacityChanged(val.toInt());
}

void BrushDockWidget::updateSpacing(int val){
    m_SpacingLE->setValue(val);
    emit brushSpacingChanged(val);
}

void BrushDockWidget::updateSpacing(QString val){
    m_SpacingSlider->setValue(val.toInt());
    emit brushSpacingChanged(val.toInt());
}

void BrushDockWidget::updateTransferSize(int val)
{
    m_TransferSizeLE->setValue(val);
    m_GenBrushWidget->generateStrokePreview();
    emit brushTransferSizeChanged(val);
}

void BrushDockWidget::updateTransferSize(QString val)
{
    m_TransferSizeSlider->setValue(val.toInt());
    emit brushTransferSizeChanged(val.toInt());
}

void BrushDockWidget::updateTransferOpacity(int val)
{
    m_TransferOpacityLE->setValue(val);
    emit brushTransferOpacityChanged(val);
}

void BrushDockWidget::updateTransferOpacity(QString val)
{
    m_TransferOpacitySlider->setValue(val.toInt());
    emit brushTransferOpacityChanged(val.toInt());
}

void BrushDockWidget::toggleTransferSize(bool val)
{
    m_TransferSizeSlider->setEnabled(val);
    m_TransferSizeLE->setEnabled(val);
    m_GenBrushWidget->activateUsePressureWidth(val);
    if(!val){
        emit brushTransferSizeChanged(0);
    }else{
        emit brushTransferSizeChanged(m_TransferSizeLE->value());
    }
}

void BrushDockWidget::toggleTransferOpacity(bool val)
{
    m_TransferOpacitySlider->setEnabled(val);
    m_TransferOpacityLE->setEnabled(val);
    if(val == false){
        emit brushTransferOpacityChanged(0);
    }else{
        emit brushTransferOpacityChanged(m_TransferSizeSlider->value());
    }
}

void BrushDockWidget::toggleTransferVisibility(bool val){
    if(val){
        m_TransferOpacityLE->setVisible(true);
        m_TransferOpacitySlider->setVisible(true);
        m_TransferOpacityToggle->setVisible(true);
        m_TransferSizeLE->setVisible(true);
        m_TransferSizeSlider->setVisible(true);
        m_TransferSizeToggle->setVisible(true);
    }else{
        m_TransferOpacityLE->setVisible(false);
        m_TransferOpacitySlider->setVisible(false);
        m_TransferOpacityToggle->setVisible(false);
        m_TransferSizeLE->setVisible(false);
        m_TransferSizeSlider->setVisible(false);
        m_TransferSizeToggle->setVisible(false);
    }
}

void BrushDockWidget::updateStencilWidth(int val){
    m_TempBrushList[m_CurrentBrushIndex].setSWidth(val);
}

void BrushDockWidget::updateStencilHeight(int val){
    m_TempBrushList[m_CurrentBrushIndex].setSHeight(val);
}

void BrushDockWidget::updateStencilHardness(int val){
    m_TempBrushList[m_CurrentBrushIndex].setHardness(val);
}

void BrushDockWidget::updateStencilRotate(int val){
    m_TempBrushList[m_CurrentBrushIndex].SetRotate(val);
}

void BrushDockWidget::updateStencil(QPixmap pixmap){
    m_TempBrushList[m_CurrentBrushIndex].SetStencil(pixmap);
    m_GenBrushWidget->setStencilPixmap(pixmap);
    emit brushStencilChanged(pixmap);
}

void BrushDockWidget::updateStencilPath(QString filePath){
    emit brushStencilPathChanged(filePath);
}

void BrushDockWidget::updateBrushName(QString name){
    m_ActualBrushList[m_CurrentBrushIndex].SetName(name);
    m_TempBrushList[m_CurrentBrushIndex].SetName(name);
}

void BrushDockWidget::setCurrentIndex(int val){
    m_CurrentBrushIndex = val;
    m_StencilWidget->updateStencilWidth(m_ActualBrushList.at(m_CurrentBrushIndex).getSWidth());
    m_StencilWidget->updateStencilHeight(m_ActualBrushList.at(m_CurrentBrushIndex).getSHeight());
    m_StencilWidget->updateBrushHardness(m_ActualBrushList.at(m_CurrentBrushIndex).getHardness());
    m_StencilWidget->updateStencilRotate(m_ActualBrushList.at(m_CurrentBrushIndex).getRotate());
    m_StencilWidget->updateStencil(m_ActualBrushList.at(m_CurrentBrushIndex).getStencil());
    m_GenBrushWidget->setStencilPixmap(m_ActualBrushList.at(m_CurrentBrushIndex).getStencil());
    emit stencilWidthChanged(m_ActualBrushList.at(m_CurrentBrushIndex).getSWidth());
    emit stencilHeightChanged(m_ActualBrushList.at(m_CurrentBrushIndex).getSHeight());
    emit brushHardnessChanged(m_ActualBrushList.at(m_CurrentBrushIndex).getHardness());
    emit stencilRotateChanged(m_ActualBrushList.at(m_CurrentBrushIndex).getRotate());
    emit brushStencilChanged(m_ActualBrushList.at(m_CurrentBrushIndex).getStencil());
}

void BrushDockWidget::setStencil(QPixmap pix){
    m_StencilWidget->setStencil(pix);
}

void BrushDockWidget::loadStencilAct(){
    qDebug()<<"Loading Stencil" << endl;
    QString filePath = QFileDialog::getOpenFileName(this, "Open Stencil", QDir::currentPath());
    QPixmap pixmap;
    pixmap.load(filePath);
    m_StencilWidget->updateStencil(pixmap);
}

void BrushDockWidget::loadBrushAct(){
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush", m_ProjectPath, ".brsh");
    Brush temp = loadBrush(filePath);
    m_TempBrushList.append(temp);
    m_ActualBrushList.append(temp);
    m_GenBrushWidget->addBrush(temp);
    qDebug()<<"Loading Brush" << endl;
}

void BrushDockWidget::loadBrushSetAct(){
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush Library", m_ProjectPath, "*.blib");

    QMessageBox msgBox;
    msgBox.setText("Would you like to Load a new brush set or add to existing?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, "Load new set");
    msgBox.setButtonText(QMessageBox::Cancel, "Add to existing set");
    switch(msgBox.exec()){
    case QMessageBox::Ok:                       //Replaces Existing
       m_ActualBrushList = loadBrushLib(filePath);
       m_BrushLib = filePath;
        break;
    case QMessageBox::Cancel:                   //Appends to brush set
        QVector<Brush> temp = loadBrushLib(filePath);
        m_ActualBrushList = m_ActualBrushList + temp;
        break;
    }

    qDebug()<<"Loading Brush Set" << endl;
}

void BrushDockWidget::saveStencilAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save Stencil",QDir::currentPath());
    QPixmap pixmap = m_StencilWidget->GetPixmap();
    pixmap.save(filePath);

    qDebug() << "Saving Stencil" << endl;
}

void BrushDockWidget::saveBrushAct(){
    QMessageBox msgBox;
    msgBox.setText("Save just to library or to External Location?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, "Save to library");
    msgBox.setButtonText(QMessageBox::Cancel, "Save to library and external");
    switch(msgBox.exec()){
    case QMessageBox::Ok:
        m_ActualBrushList.push_back(m_TempBrushList.at(m_CurrentBrushIndex));
        m_GenBrushWidget->addBrush(m_TempBrushList.at(m_CurrentBrushIndex));
        m_TempBrushList = m_ActualBrushList;
        break;
    case QMessageBox::Cancel:
        QString filePath = QFileDialog::getSaveFileName(this, "Save Brush", m_ProjectPath, ".brsh");
        int encrypt = 5025;
        Brush ret = m_TempBrushList[m_CurrentBrushIndex];
        QFile file(filePath);
        if(!file.open(QIODevice::WriteOnly)){
            qDebug() << "Error, cannot open file";
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);
        out << encrypt <<ret;

        file.flush();
        file.close();

        m_ActualBrushList.push_back(m_TempBrushList.at(m_CurrentBrushIndex));
        m_GenBrushWidget->addBrush(m_TempBrushList.at(m_CurrentBrushIndex));
        m_TempBrushList = m_ActualBrushList;
        break;
    }
}

void BrushDockWidget::saveBrushSetAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save brush library", m_ProjectPath, ".blib");
    saveBrushLib(filePath);
}

QVector<Brush> BrushDockWidget::loadBrushLib(QString filePath){
    int encrypt = 5025;
    QVector<Brush> ret;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<< "Error, Could not open file" << endl;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    in >> encrypt >> ret;
    file.close();

    return ret;
}

void BrushDockWidget::saveBrushLib(QString filePath){
    int encrypt = 5025;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<< "Error, could not open file" << endl;
    }
    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_5_0);
    out << encrypt << m_ActualBrushList;

    file.flush();
    file.close();
    qDebug() << "Saved brush set";
}

Brush BrushDockWidget::getStartBrush(){
    qDebug() << "Stencil stats: \t Width: " << m_ActualBrushList.first().getStencil().width() << " Height: " << m_ActualBrushList.first().getStencil().height() << endl;
    return m_ActualBrushList[0];
}

Brush BrushDockWidget::loadBrush(QString filePath){
    Brush ret;
    int encrypt = 5025;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<< "Error, invalid file" << endl;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    in >> encrypt >> ret;

    file.close();

    return ret;
}

void BrushDockWidget::deleteBrushAct(){

}

void BrushDockWidget::resizeEvent(QResizeEvent *e){
    Q_UNUSED(e)
}

void BrushDockWidget::readSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    m_ProjectPath = settings.value("projectPath").toString();
    m_BrushLib = settings.value("activeBrushLib").toString();
}

void BrushDockWidget::writeSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    settings.setValue("activeBrushLib", m_BrushLib);
    qDebug() << m_BrushLib << endl;
    saveBrushLib(m_BrushLib);
}

BrushDockWidget::~BrushDockWidget()
{
    saveBrushLib(m_BrushLib);
    writeSettings();
}


/*

  BRUSH SHAPE WIDGET = Handles Adjusting the Brush Shape

*/

BrushShapeWidget::BrushShapeWidget(QWidget *parent) : QLabel(parent)
{
    brushPreviewPixmap = QPixmap(200, 200);
    brushPreviewPixmap.fill(Qt::transparent);
    this->setPixmap(brushPreviewPixmap);
    this->resize(brushPreviewPixmap.size());
    m_ShowStroke = false;
}

void BrushShapeWidget::toggleStroke(bool v)
{
    m_ShowStroke = v;
}

void BrushShapeWidget::setMaxSize(qreal v)
{
    m_MaxPressure = v;
}

void BrushShapeWidget::setMinSize(qreal v){
    m_MinSize = v;
}

void BrushShapeWidget::setBrush(Brush b){
    m_brush = b;
}

BrushShapeWidget::~BrushShapeWidget()
{

}

void BrushShapeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(&brushPreviewPixmap);
    painter.drawEllipse(0, 0, 20, 20);
}

void BrushShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void BrushShapeWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}


GeneralBrushWidget::GeneralBrushWidget(){
    m_usePressureWidth = false;
    m_ToolBtn = new QToolButton(this);
    m_ToolBtn->setText("Tool");
    m_ToolBtn->setFixedWidth(48);
    m_ToolBtn->setFixedHeight(48);
    m_ToolMenu = new QMenu(this);
    m_LoadStencilAct = new QAction("&Load Stencil", this);
    m_LoadBrushAct = new QAction("&Load Brush", this);
    m_LoadBrushSetAct = new QAction("&Load Brush Set", this);
    m_SaveStencilAct = new QAction("&Save Stencil", this);
    m_SaveBrushAct = new QAction("&Save Brush", this);
    m_SaveBrushSetAct = new QAction("&Save Brush Set", this);
    m_DeleteBrushAct = new QAction("Delete Brush", this);
    m_ToolMenu->addAction(m_LoadStencilAct);
    m_ToolMenu->addAction(m_LoadBrushAct);
    m_ToolMenu->addAction(m_LoadBrushSetAct);
    m_ToolMenu->addSeparator();
    m_ToolMenu->addAction(m_SaveStencilAct);
    m_ToolMenu->addAction(m_SaveBrushAct);
    m_ToolMenu->addAction(m_SaveBrushSetAct);
    m_ToolMenu->addSeparator();
    m_ToolMenu->addAction(m_DeleteBrushAct);
    m_ToolBtn->setMenu(m_ToolMenu);

    m_BrushIndex = new QListWidget(this);
    m_BrushIndex->setMinimumWidth(130);
    m_BrushIndex->setBaseSize(130, 130);
    m_StencilPreview = QPixmap(175, 100);
    m_StencilPreview.fill(Qt::gray);
    m_PreviewLabel = new QLabel(this);
    m_PreviewLabel->setPixmap(m_StencilPreview);

    m_showStencilBtn = new QPushButton("[Stencil]", this);
    m_showStencilBtn->setCheckable(true);
    m_showStencilBtn->setChecked(true);
    m_showStrokeBtn = new QPushButton("[Stroke]", this);
    m_showStrokeBtn->setCheckable(true);

    QHBoxLayout* toggleStrokeLayout = new QHBoxLayout;
    toggleStrokeLayout->addWidget(m_showStencilBtn);
    toggleStrokeLayout->addWidget(m_showStrokeBtn);

    QVBoxLayout* vert1 = new QVBoxLayout;
    vert1->addWidget(m_ToolBtn);
    vert1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    QHBoxLayout* horiz1 = new QHBoxLayout;
    horiz1->addWidget(m_BrushIndex);
    horiz1->addLayout(vert1);
    QVBoxLayout* generalBrushLayout = new QVBoxLayout;
    generalBrushLayout->addLayout(horiz1);
    generalBrushLayout->addWidget(m_PreviewLabel);
    generalBrushLayout->setAlignment(m_PreviewLabel, Qt::AlignCenter);
    generalBrushLayout->addLayout(toggleStrokeLayout);

    setLayout(generalBrushLayout);
    connect(m_LoadStencilAct, SIGNAL(triggered()), SLOT(updateLoadStencil()));
    connect(m_LoadBrushAct, SIGNAL(triggered()), SLOT(updateLoadBrush()));
    connect(m_LoadBrushSetAct, SIGNAL(triggered()), SLOT(updateLoadBrushSet()));
    connect(m_SaveStencilAct, SIGNAL(triggered()), SLOT(updateSaveStencil()));
    connect(m_SaveBrushAct, SIGNAL(triggered()), SLOT(updateSaveBrush()));
    connect(m_SaveBrushSetAct, SIGNAL(triggered()), SLOT(updateSaveBrushSet()));
    connect(m_DeleteBrushAct, SIGNAL(triggered()), SLOT(updateDeleteBrush()));
    connect(m_BrushIndex, SIGNAL(currentRowChanged(int)), SLOT(updateBrushLibIndex(int)));
    connect(m_BrushIndex, SIGNAL(itemChanged(QListWidgetItem*)), SLOT(updateName(QListWidgetItem*)));
    connect(m_showStencilBtn, SIGNAL(toggled(bool)), SLOT(showStencil(bool)));
    connect(m_showStrokeBtn, SIGNAL(toggled(bool)), SLOT(showStroke(bool)));
}

void GeneralBrushWidget::updateName(QListWidgetItem *item){
    emit brushNameChanged(item->text());
}

void GeneralBrushWidget::addBrush(int iD, Brush brush){
    int temp = iD;
    Brush b = brush;
}

void GeneralBrushWidget::addBrush(Brush brush){
    QListWidgetItem* itm = new QListWidgetItem(brush.m_Name);
    QImage stencilIcon = brush.getStencil().toImage();
    stencilIcon.invertPixels();
    itm->setIcon(QPixmap::fromImage(stencilIcon));
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    m_BrushIndex->addItem(itm);
}

int GeneralBrushWidget::getSelectedIndex(){
   for(int i = 0; i < m_BrushIndex->count(); i++){
       if(m_BrushIndex->item(i)->isSelected()){
           return i;
       }
   }
   return 0;
}

void GeneralBrushWidget::deleteSelected(int index){
    QListWidgetItem* itm = m_BrushIndex->item(index);
    m_BrushIndex->removeItemWidget(itm);
    itm = nullptr;
}

void GeneralBrushWidget::updateStencil(QPixmap pixmap){
    int targetWidth = m_StencilPreview.width();
    int targetHeight = m_StencilPreview.height();
    int sourceWidth = pixmap.width();
    int sourceHeight = pixmap.height();
    if(sourceWidth >= targetWidth, sourceHeight >= targetHeight){
        pixmap = pixmap.scaled(m_StencilPreview.size(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
        m_StencilPreview = pixmap;
    }else{
        qDebug() << "Unable to load Pixmap" << endl;
        qDebug() << "Target Width/height: " << m_StencilPreview.size() << endl;
        qDebug() << "Source Width/Height: " << pixmap.size() << endl;
    }
}

void GeneralBrushWidget::setStencilPixmap(QPixmap pix){
    m_StencilPreview = pix;
    if(m_showStencilBtn->isChecked()){
        m_PreviewLabel->setPixmap(m_StencilPreview);
    }
    update();
}

void GeneralBrushWidget::showStencil(bool v){
    m_showStrokeBtn->setChecked(!v);
    m_PreviewLabel->setPixmap(m_StencilPreview);
    update();
}

void GeneralBrushWidget::showStroke(bool v){
    m_showStencilBtn->setChecked(!v);
    generateStrokePreview();
    m_PreviewLabel->setPixmap(m_StrokePreview);
    /*-TODO - Show Stroke-*/
    update();
}

void GeneralBrushWidget::activateUsePressureWidth(bool v){
    m_usePressureWidth = v;
    update();
}

void GeneralBrushWidget::generateStrokePreview(){
    m_StrokePreview = QPixmap(this->width() - 40, m_StencilPreview.height() * 0.5);
    m_StrokePreview.fill(Qt::gray);
    QPainterPath path;
    path.moveTo(20, 20);
    path.cubicTo(QPointF(1.0/3.0 * (double)m_StrokePreview.width(), m_StrokePreview.height()), QPointF(1.0/3.0 * (double)m_StrokePreview.width(), m_StrokePreview.height()), QPointF(m_StrokePreview.width()/2, m_StrokePreview.height()/2));
    path.cubicTo(QPointF(2.0/3.0 * (double)m_StrokePreview.width(), 0), QPointF(2.0/3.0 * (double)m_StrokePreview.width(), 0), QPointF(m_StrokePreview.width()-20, m_StrokePreview.height() - 20));

    qreal minWidth = 5.0;
    qreal maxWidth = 10.0;

    QImage stenBase = m_StencilPreview.toImage();
    stenBase.invertPixels(QImage::InvertRgb);
    stenBase.createAlphaMask();
    stenBase.convertToFormat(QImage::Format_ARGB32, Qt::AutoColor);
    QImage stencil(stenBase);
    stencil.fill(Qt::black);
    stencil.setAlphaChannel(stenBase);
    QPixmap fSten = QPixmap::fromImage(stencil.scaled(minWidth, minWidth));

    QPainter p(&m_StrokePreview);
    p.setPen(Qt::black);
    p.setBrush(Qt::transparent);
    qreal bigger = 0.0;
    for(double i = 0.0; i < 1.0; i+= 0.0001){
        QPoint drawPoint = path.pointAtPercent(i).toPoint();
        if(m_usePressureWidth){
            if(i <= 0.5){
                bigger = i;
            }else{
                bigger = -i;
            }
            fSten = fSten.scaled(minWidth + bigger, minWidth + bigger);
             p.drawPixmap(QPoint(drawPoint.x() - fSten.width()/2.0, drawPoint.y() - fSten.height()/2), fSten);
        }else{
             p.drawPixmap(QPoint(drawPoint.x() - fSten.width()/2.0, drawPoint.y() - fSten.height()/2), fSten);
        }
    }
}

void GeneralBrushWidget::resizeEvent(QResizeEvent *e){
    Q_UNUSED(e);
    if(m_showStrokeBtn->isChecked()){
        generateStrokePreview();
        m_PreviewLabel->setPixmap(m_StrokePreview);
    }
    update();
}

GeneralBrushWidget::~GeneralBrushWidget(){

}

CustomBrushWidget::CustomBrushWidget(){

    m_BrushShape = CIRCLE_SHAPE;
    m_HasTexture = false;

    m_StencilPreview = QPixmap(160, 160);
    m_StencilPreview.fill(Qt::transparent);
    m_StencilLbl = new QLabel(this);
    m_StencilLbl->setPixmap(m_StencilPreview);

    m_ToolBtn = new QToolButton(this);
    m_ToolBtn->setText("Tool");
    m_ToolBtn->setFixedWidth(48);
    m_ToolBtn->setFixedHeight(48);
    m_ToolMenu = new QMenu(this);
    m_LoadStencilAct = new QAction("&Load Stencil", this);
    m_LoadBrushAct = new QAction("&Load Brush", this);
    m_LoadBrushSetAct = new QAction("&Load Brush Set", this);
    m_SaveStencilAct = new QAction("&Save Stencil", this);
    m_SaveBrushAct = new QAction("&Save Brush", this);
    m_SaveBrushSetAct = new QAction("&Save Brush Set", this);
    m_DeleteBrushAct = new QAction("Delete Brush", this);
    m_ToolMenu->addAction(m_LoadStencilAct);
    m_ToolMenu->addAction(m_LoadBrushAct);
    m_ToolMenu->addAction(m_LoadBrushSetAct);
    m_ToolMenu->addSeparator();
    m_ToolMenu->addAction(m_SaveStencilAct);
    m_ToolMenu->addAction(m_SaveBrushAct);
    m_ToolMenu->addAction(m_SaveBrushSetAct);
    m_ToolMenu->addSeparator();
    m_ToolMenu->addAction(m_DeleteBrushAct);
    m_ToolBtn->setMenu(m_ToolMenu);

    QVBoxLayout* v1Layout = new QVBoxLayout;
    v1Layout->addWidget(m_ToolBtn);
    v1Layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

    QHBoxLayout* StencilPreviewLayout = new QHBoxLayout;
    StencilPreviewLayout->addWidget(m_StencilLbl);
    StencilPreviewLayout->setAlignment(m_StencilLbl, Qt::AlignCenter);
    StencilPreviewLayout->addLayout(v1Layout);

    m_WidthLbl = new QLabel("Width:", this);
    m_WidthSlider = new QSlider(Qt::Horizontal, this);
    m_WidthSlider->setRange(0, 10);
    m_WidthSlider->setValue(10);
    m_WidthLE = new QLineEdit(this);
    m_WidthLE->setFixedWidth(32);
    m_WidthLE->setText(QString::number(10));
    QHBoxLayout* widthLayout = new QHBoxLayout;
    widthLayout->addWidget(m_WidthLbl);
    widthLayout->addWidget(m_WidthSlider);
    widthLayout->addWidget(m_WidthLE);

    m_HeightLbl = new QLabel("Height:", this);
    m_HeightSlider = new QSlider(Qt::Horizontal, this);
    m_HeightSlider->setRange(0, 10);
    m_HeightSlider->setValue(10);
    m_HeightLE = new QLineEdit(this);
    m_HeightLE->setFixedWidth(32);
    m_HeightLE->setText(QString::number(10));
    QHBoxLayout* heightLayout = new QHBoxLayout;
    heightLayout->addWidget(m_HeightLbl);
    heightLayout->addWidget(m_HeightSlider);
    heightLayout->addWidget(m_HeightLE);

    m_HardnessLbl = new QLabel("Hardness:", this);
    m_HardnessSlider = new QSlider(Qt::Horizontal, this);
    m_HardnessSlider->setRange(0, 100);
    m_HardnessSlider->setValue(100);
    m_HardnessLE = new QLineEdit(this);
    m_HardnessLE->setFixedWidth(32);
    m_HardnessLE->setText(QString::number(100));
    QHBoxLayout* hardnessLayout = new QHBoxLayout;
    hardnessLayout->addWidget(m_HardnessLbl);
    hardnessLayout->addWidget(m_HardnessSlider);
    hardnessLayout->addWidget(m_HardnessLE);

    m_RotateLbl = new QLabel("Rotate:", this);
    m_RotateSlider = new QSlider(Qt::Horizontal, this);
    m_RotateSlider->setRange(0, 361);
    m_RotateSlider->setValue(0);
    m_RotateLE = new QLineEdit(this);
    m_RotateLE->setFixedWidth(32);
    m_RotateLE->setText(QString::number(0));
    QHBoxLayout* rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(m_RotateLbl);
    rotateLayout->addWidget(m_RotateSlider);
    rotateLayout->addWidget(m_RotateLE);

    m_CircleButton = new QPushButton("Circle", this);
    m_SquareButton = new QPushButton("Square", this);
    m_CustomButton = new QPushButton("Custom", this);
    QHBoxLayout* stencilShapeLayout = new QHBoxLayout;
    stencilShapeLayout->addWidget(m_CircleButton);
    stencilShapeLayout->addWidget(m_SquareButton);
    stencilShapeLayout->addWidget(m_CustomButton);

    m_TextureLbl = new QLabel("Texture: ", this);
    m_TextureFileLE = new QLineEdit(this);
    m_TextureBtn = new QPushButton("...",this);
    QHBoxLayout* textureLayout = new QHBoxLayout;
    textureLayout->addWidget(m_TextureLbl);
    textureLayout->addWidget(m_TextureFileLE);
    textureLayout->addWidget(m_TextureBtn);

    QVBoxLayout* advancedLayout = new QVBoxLayout;
    advancedLayout->addLayout(widthLayout);
    advancedLayout->addLayout(heightLayout);
    advancedLayout->addLayout(hardnessLayout);
    advancedLayout->addLayout(rotateLayout);
    advancedLayout->addLayout(stencilShapeLayout);
    advancedLayout->addLayout(textureLayout);

    QVBoxLayout* AdvancedPanel = new QVBoxLayout;
    AdvancedPanel->addLayout(StencilPreviewLayout);
    AdvancedPanel->addLayout(advancedLayout);
    setLayout(AdvancedPanel);

    connect(m_LoadStencilAct, SIGNAL(triggered()), SLOT(updateLoadStencil()));
    connect(m_LoadBrushAct, SIGNAL(triggered()), SLOT(updateLoadBrush()));
    connect(m_LoadBrushSetAct, SIGNAL(triggered()), SLOT(updateLoadBrushSet()));
    connect(m_SaveStencilAct, SIGNAL(triggered()), SLOT(updateSaveStencil()));
    connect(m_SaveBrushAct, SIGNAL(triggered()), SLOT(updateSaveBrush()));
    connect(m_SaveBrushSetAct, SIGNAL(triggered()), SLOT(updateSaveBrushSet()));
    connect(m_DeleteBrushAct, SIGNAL(triggered()), SLOT(updateDeleteBrush()));
    connect(m_WidthLE, SIGNAL(textChanged(QString)), SLOT(updateStencilWidth(QString)));
    connect(m_WidthSlider, SIGNAL(valueChanged(int)), SLOT(updateStencilWidth(int)));
    connect(m_HeightLE, SIGNAL(textChanged(QString)), SLOT(updateStencilHeight(QString)));
    connect(m_HeightSlider, SIGNAL(valueChanged(int)), SLOT(updateStencilHeight(int)));
    connect(m_HeightLE, SIGNAL(textChanged(QString)), SLOT(updateStencilHeight(QString)));
    connect(m_HardnessSlider, SIGNAL(valueChanged(int)), SLOT(updateBrushHardness(int)));
    connect(m_HardnessLE, SIGNAL(textChanged(QString)), SLOT(updateBrushHardness(QString)));
    connect(m_RotateSlider, SIGNAL(valueChanged(int)), SLOT(updateStencilRotate(int)));
    connect(m_RotateLE, SIGNAL(textChanged(QString)), SLOT(updateStencilRotate(QString)));
    connect(this, SIGNAL(stencilChanged(QPixmap)), SLOT(updateStencil(QPixmap)));
    connect(m_CircleButton, SIGNAL(clicked()), SLOT(updateBrushShape_Circle()));
    connect(m_SquareButton, SIGNAL(clicked()), SLOT(updateBrushShape_Square()));
    connect(m_CustomButton, SIGNAL(clicked()), SLOT(updateBrushShape_Polygon()));
    connect(m_TextureBtn, SIGNAL(clicked()), SLOT(updateStencilTexture()));
    connect(m_TextureFileLE, SIGNAL(textChanged(QString)), SLOT(updateStencilTextureLE(QString)));
}

void CustomBrushWidget::TempSave(QPixmap pixmap){
    QImage image = pixmap.toImage();
    image.convertToFormat(QImage::Format_RGB888, Qt::AutoColor);
    if(m_TempFile.open()){
        image.save(m_TempFile.fileName());
    }
    m_TempFile.close();
    emit stencilPathChanged(m_TempFile.fileName());
}

void CustomBrushWidget::updateStencil(QPixmap pixmap){
    TempSave(pixmap);
}

void CustomBrushWidget::updateStencilTexture(){
    m_HasTexture = true;
    QString fileName = QFileDialog::getOpenFileName(this, "Load Texture", QDir::currentPath());
    m_StencilTexture.load(fileName);
    QImage image = m_StencilTexture.toImage();
    QRgb col;
    int gray;
    int width = m_StencilTexture.width();
    int height = m_StencilTexture.height();
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    m_StencilTexture = m_StencilTexture.fromImage(image);
    m_StencilTexture = m_StencilTexture.scaled(m_StencilPreview.width(), m_StencilPreview.height(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
    m_TextureFileLE->setText(fileName);
}

void CustomBrushWidget::setStencil(QPixmap pix){
    pix = pix.scaled(160, 160);

}

void CustomBrushWidget::updateStencilWidth(int val){
   m_WidthLE->setText(QString::number(val));
   emit StencilWidthChanged(val);
   emit stencilChanged(m_StencilPreview);
}

void CustomBrushWidget::updateStencilWidth(QString val){
    m_WidthSlider->setValue(val.toInt());
    emit StencilWidthChanged(val.toInt());
}

void CustomBrushWidget::updateStencilHeight(int val){
    m_HeightLE->setText(QString::number(val));
    emit stencilHeightChanged(val);
    emit stencilChanged(m_StencilPreview);
}

void CustomBrushWidget::updateStencilHeight(QString val){
    m_HeightSlider->setValue(val.toInt());
    emit stencilHeightChanged(val.toInt());
}

void CustomBrushWidget::updateBrushHardness(int val){
    m_HardnessLE->setText(QString::number(val));
    emit brushHardnessChanged(val);
    emit stencilChanged(m_StencilPreview);
}

void CustomBrushWidget::updateBrushHardness(QString val){
    m_HardnessSlider->setValue(val.toInt());
    emit brushHardnessChanged(val.toInt());
}

void CustomBrushWidget::updateStencilRotate(int val){
    if(val > 360){
        val = 0;
        m_RotateSlider->setValue(0);
    }
    m_RotateLE->setText(QString::number(val));
    emit rotateChanged(val);
    emit stencilChanged(m_StencilPreview);
}

void CustomBrushWidget::updateStencilRotate(QString val){
    if(val.toInt() > 360){
        m_RotateSlider->setValue(0);
        emit rotateChanged(0);
    }else{
        m_RotateSlider->setValue(val.toInt());
        emit rotateChanged(val.toInt());
    }
}

void CustomBrushWidget::updateStencilTextureLE(QString val){
    if(val.isEmpty()){
        m_HasTexture = false;
    }else{
        m_HasTexture = true;
    }
}

void CustomBrushWidget::setBrushSettings(Brush b){
    m_WidthSlider->setValue(b.s_Width);
    m_HeightSlider->setValue(b.s_Height);
    m_HardnessSlider->setValue(b.getHardness());
    m_RotateSlider->setValue(b.getRotate());
    update();
}

QPixmap CustomBrushWidget::GeneratePixmap(){
    m_StencilPreview.fill(Qt::transparent);
    int stencilWidth = (m_StencilPreview.width() * m_WidthSlider->value()/10)/2;
    int stencilHeight = (m_StencilPreview.height()* m_HeightSlider->value()/10)/2;
    qreal fRadius = ((qreal)m_HardnessSlider->value()/100.0);
    QPoint midPoint(m_StencilPreview.width()/2, m_StencilPreview.height()/2);

    qDebug() << "fRadius: " << fRadius << endl;

    QRadialGradient radGrad(midPoint, midPoint.x());
    radGrad.setColorAt(0.0, Qt::black);
    radGrad.setColorAt(fRadius, Qt::black);
    if(fRadius == 1.0){
        radGrad.setColorAt(1.0, Qt::black);
    }else{
        radGrad.setColorAt(1.0, Qt::transparent);
    }

    QPixmap img = m_StencilPreview;

    QPainter p;
    p.begin(&img);
    p.setRenderHint(QPainter::Antialiasing);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.setPen(Qt::NoPen);
    p.setBrush(radGrad);
    switch(m_BrushShape){
    case CIRCLE_SHAPE:
        if(m_HasTexture){
            QBrush brush;
            brush.setTexture(m_StencilTexture);
            p.setBrush(brush);
        }else{
            p.setBrush(radGrad);
        }
        p.drawEllipse(midPoint, stencilWidth, stencilHeight);
        break;
    case SQUARE_SHAPE:
    {
        int originX =  midPoint.x() - stencilWidth;
        int originY = midPoint.y() - stencilHeight;
        int dimX = stencilWidth*2;
        int dimY = stencilHeight*2;

        if(m_HasTexture){
            QBrush brush;
            brush.setTexture(m_StencilTexture);
            p.setBrush(brush);
        }else{
            p.setBrush(Qt::black);
        }

        p.drawRect(originX, originY, dimX, dimY);
        break;
    }
    default:
        break;
    }
    p.end();
    m_StencilPreview = img;
    return m_StencilPreview;
}

void CustomBrushWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    int stencilWidth = (m_StencilPreview.width() * m_WidthSlider->value()/10)/2;
    int stencilHeight = (m_StencilPreview.height()* m_HeightSlider->value()/10)/2;
    qreal hardness = ((qreal)m_HardnessSlider->value()/100);
    QPoint midPoint(m_StencilPreview.width()/2, m_StencilPreview.height()/2);
    m_StencilPreview.fill(Qt::transparent);
    QRadialGradient radGrad(midPoint, m_StencilPreview.width()/2);
    radGrad.setColorAt(midPoint.x()/m_StencilPreview.width(), Qt::black);
    radGrad.setColorAt(0.0, Qt::black);
    radGrad.setColorAt(hardness, Qt::black);
    if(hardness == 1.0){
        radGrad.setColorAt(1.0, Qt::black);
    }else{
        radGrad.setColorAt(1.0, Qt::transparent);
    }

    QPainter painter(&m_StencilPreview);
    painter.setPen(Qt::NoPen);
    switch(m_BrushShape){
        case CIRCLE_SHAPE:
            if(m_HasTexture){
                QBrush brush;
                brush.setTexture(m_StencilTexture);
                painter.setBrush(brush);
            }else{
                painter.setBrush(radGrad);
            }
            painter.translate(midPoint);
            painter.rotate(m_RotateSlider->value());
            painter.translate(-midPoint);
            painter.drawEllipse(midPoint, stencilWidth, stencilHeight);
            break;
        case SQUARE_SHAPE:
            int originX =  midPoint.x() - stencilWidth;
            int originY = midPoint.y() - stencilHeight;
            int dimX = stencilWidth*2;
            int dimY = stencilHeight*2;

            if(m_HasTexture){
                QBrush brush;
                brush.setTexture(m_StencilTexture);
                painter.setBrush(brush);
            }else{
                painter.setBrush(Qt::black);
            }
            painter.translate(midPoint);
            painter.rotate(m_RotateSlider->value());
            painter.translate(-midPoint);
            painter.drawRect(originX, originY, dimX, dimY);
            break;
    }
    m_StencilLbl->setPixmap(m_StencilPreview);

//   QImage ret = GeneratePixmap().toImage();
//   ret.invertPixels(QImage::InvertRgba);
//   mStencilPreview = QPixmap::fromImage(ret);
//   mStencilLabel->setPixmap(mStencilPreview);
}

void CustomBrushWidget::updateBrushShape_Circle(){
    m_BrushShape = CIRCLE_SHAPE;
    update();
    emit stencilChanged(GeneratePixmap());
}

void CustomBrushWidget::updateBrushShape_Square(){
    m_BrushShape = SQUARE_SHAPE;
    update();
    emit stencilChanged(GeneratePixmap());
}

void CustomBrushWidget::updateBrushShape_Polygon(){
    m_BrushShape = CUSTOM;
    update();
    emit stencilChanged(GeneratePixmap());
}

CustomBrushWidget::~CustomBrushWidget(){

}

/*- Color Widget -*/
ColorDockWidget::ColorDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Color");
    //initialize everything
    m_ColorWheel = new ColorWheel(this);
    m_ColorTabs = new QTabWidget(this);

    //Red Parameters
    m_RLabel = new QLabel("R:", this);
    m_RSlider = new QSlider(this);
    m_RSlider->setOrientation(Qt::Horizontal);
    m_RSlider->setRange(0, 255);
    m_RSlider->setValue(0);
    m_RSpinBox = new QSpinBox(this);
    m_RSpinBox->setRange(0, 255);
    m_RSpinBox->setValue(0);

    QHBoxLayout* rBoxLayout = new QHBoxLayout;
    rBoxLayout->addWidget(m_RLabel);
    rBoxLayout->addWidget(m_RSlider);
    rBoxLayout->addWidget(m_RSpinBox);

    //Green Parameters
    m_GLabel = new QLabel("G:", this);
    m_GSlider = new QSlider(this);
    m_GSlider->setOrientation(Qt::Horizontal);
    m_GSlider->setRange(0, 255);
    m_GSlider->setValue(0);
    m_GSpinBox = new QSpinBox(this);
    m_GSpinBox->setRange(0, 255);
    m_GSpinBox->setValue(0);

    QHBoxLayout* gBoxLayout = new QHBoxLayout;
    gBoxLayout->addWidget(m_GLabel);
    gBoxLayout->addWidget(m_GSlider);
    gBoxLayout->addWidget(m_GSpinBox);

    //Blue Parameters
    m_BLabel = new QLabel("B:", this);
    m_BSlider = new QSlider(this);
    m_BSlider->setOrientation(Qt::Horizontal);
    m_BSlider->setRange(0, 255);
    m_BSlider->setValue(0);
    m_BSpinBox = new QSpinBox(this);
    m_BSpinBox->setRange(0, 255);
    m_BSpinBox->setValue(0);

    QHBoxLayout* bBoxLayout = new QHBoxLayout;
    bBoxLayout->addWidget(m_BLabel);
    bBoxLayout->addWidget(m_BSlider);
    bBoxLayout->addWidget(m_BSpinBox);

    //Hue Parameters
    m_HLabel = new QLabel("H:", this);
    m_HSlider = new QSlider(this);
    m_HSlider->setOrientation(Qt::Horizontal);
    m_HSlider->setRange(0, 255);
    m_HSlider->setValue(0);
    m_HSpinBox = new QSpinBox(this);
    m_HSpinBox->setRange(0, 255);
    m_HSpinBox->setValue(0);

    QHBoxLayout* hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(m_HLabel);
    hBoxLayout->addWidget(m_HSlider);
    hBoxLayout->addWidget(m_HSpinBox);

    //Saturation Parameters
    m_SLabel = new QLabel("S:", this);
    m_SSlider = new QSlider(this);
    m_SSlider->setOrientation(Qt::Horizontal);
    m_SSlider->setRange(0, 255);
    m_SSlider->setValue(0);
    m_SSpinBox = new QSpinBox(this);
    m_SSpinBox->setRange(0, 255);
    m_SSpinBox->setValue(0);

    QHBoxLayout* sBoxLayout = new QHBoxLayout;
    sBoxLayout->addWidget(m_SLabel);
    sBoxLayout->addWidget(m_SSlider);
    sBoxLayout->addWidget(m_SSpinBox);

    //Value Parameters
    m_VLabel = new QLabel("V:", this);
    m_VSlider = new QSlider(this);
    m_VSlider->setOrientation(Qt::Horizontal);
    m_VSlider->setRange(0, 255);
    m_VSlider->setValue(0);
    m_VSpinBox = new QSpinBox(this);
    m_VSpinBox->setRange(0, 255);
    m_VSpinBox->setValue(0);

    QHBoxLayout* vBoxLayout = new QHBoxLayout;
    vBoxLayout->addWidget(m_VLabel);
    vBoxLayout->addWidget(m_VSlider);
    vBoxLayout->addWidget(m_VSpinBox);

    QVBoxLayout* RGBLayout = new QVBoxLayout;
    RGBLayout->addLayout(rBoxLayout);
    RGBLayout->addLayout(gBoxLayout);
    RGBLayout->addLayout(bBoxLayout);
    QWidget* RGBPanel = new QWidget(this);
    RGBPanel->setLayout(RGBLayout);

    QVBoxLayout* HSVLayout = new QVBoxLayout;
    HSVLayout->addLayout(hBoxLayout);
    HSVLayout->addLayout(sBoxLayout);
    HSVLayout->addLayout(vBoxLayout);
    QWidget* HSVPanel = new QWidget(this);
    HSVPanel->setLayout(HSVLayout);

    m_ColorTabs->addTab(RGBPanel, "RGB");
    m_ColorTabs->addTab(HSVPanel, "HSV");

    QVBoxLayout* masterLayout = new QVBoxLayout;
    masterLayout->addWidget(m_ColorWheel);
    masterLayout->setAlignment(m_ColorWheel, Qt::AlignCenter);
    masterLayout->addWidget(m_ColorTabs);
    masterLayout->addSpacerItem(new QSpacerItem(292, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QWidget* masterWidget = new QWidget(this);
    masterWidget->setLayout(masterLayout);
    setWidget(masterWidget);

    connect(m_ColorWheel, SIGNAL(redChanged(int)), SLOT(updateRed(int)));
    connect(m_ColorWheel, SIGNAL(blueChanged(int)), SLOT(updateBlue(int)));
    connect(m_ColorWheel, SIGNAL(greenChanged(int)), SLOT(updateGreen(int)));
    connect(m_ColorWheel, SIGNAL(colorChanged(QColor)), SLOT(updateColor(QColor)));
    connect(m_RSlider, SIGNAL(valueChanged(int)), SLOT(updateRed(int)));
    connect(m_GSlider, SIGNAL(valueChanged(int)), SLOT(updateGreen(int)));
    connect(m_BSlider, SIGNAL(valueChanged(int)), SLOT(updateBlue(int)));
    connect(m_RSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateRed(QString)));
    connect(m_GSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateGreen(QString)));
    connect(m_BSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateBlue(QString)));
    connect(m_HSlider, SIGNAL(valueChanged(int)), SLOT(updateHue(int)));
    connect(m_SSlider, SIGNAL(valueChanged(int)), SLOT(updateSat(int)));
    connect(m_VSlider, SIGNAL(valueChanged(int)), SLOT(updateVal(int)));
    connect(m_HSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateHue(QString)));
    connect(m_SSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateSat(QString)));
    connect(m_VSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateVal(QString)));
}

void ColorDockWidget::updateRed(int val){
    m_RSpinBox->setValue(val);
    m_ColorWheel->setRed(val);
    emit redChanged(val);
}

void ColorDockWidget::updateRed(QString val){
    m_RSlider->setValue(val.toInt());
    emit redChanged(val.toInt());
}

void ColorDockWidget::updateGreen(int val){
    m_GSpinBox->setValue(val);
    m_ColorWheel->setGreen(val);
    emit greenChanged(val);
}

void ColorDockWidget::updateGreen(QString val){
    m_GSlider->setValue(val.toInt());
    emit greenChanged(val.toInt());
}

void ColorDockWidget::updateBlue(int val){
    m_BSpinBox->setValue(val);
    m_ColorWheel->setBlue(val);
    emit blueChanged(val);
}

void ColorDockWidget::updateBlue(QString val){
    m_BSlider->setValue(val.toInt());
    emit blueChanged(val.toInt());
}

void ColorDockWidget::updateHue(int val){
    QColor col = m_ColorWheel->getColor();
    m_HSpinBox->setValue(val);
    int h = val;
    int s = col.saturation();
    int v = col.value();
    col.setHsv(h, s, v);
    m_ColorWheel->setActualColor(col);
    emit redChanged(col.red());
    emit greenChanged(col.green());
    emit blueChanged(col.blue());
}

void ColorDockWidget::updateHue(QString val){
    QColor col = m_ColorWheel->getColor();
    m_HSlider->setValue(val.toInt());
    int h = val.toInt();
    int s = col.saturation();
    int v = col.value();
    col.setHsv(h, s, v);
    m_ColorWheel->setActualColor(col);
}

void ColorDockWidget::updateSat(int val){
    QColor col = m_ColorWheel->getColor();
    m_SSpinBox->setValue(val);
    int h = col.hue();
    int s = val;
    int v = col.value();
    col.setHsv(h, s, v);
    m_ColorWheel->setActualColor(col);
    emit redChanged(col.red());
    emit greenChanged(col.green());
    emit blueChanged(col.blue());
}

void ColorDockWidget::updateSat(QString val){
    QColor col = m_ColorWheel->getColor();
    m_SSlider->setValue(val.toInt());
    int h = col.hue();
    int s = val.toInt();
    int v = col.value();
    col.setHsv(h, s, v);
    m_ColorWheel->setActualColor(col);
}

void ColorDockWidget::updateVal(int val){
    QColor col = m_ColorWheel->getColor();
    m_VSpinBox->setValue(val);
    int h = col.hue();
    int s = col.saturation();
    int v = val;
    col.setHsv(h, s, v);
    m_ColorWheel->setActualColor(col);
    emit redChanged(col.red());
    emit greenChanged(col.green());
    emit blueChanged(col.blue());
}

void ColorDockWidget::updateVal(QString val){
    QColor col = m_ColorWheel->getColor();
    m_VSlider->setValue(val.toInt());
    int h = col.hue();
    int s = col.saturation();
    int v = val.toInt();
    col.setHsv(h, s, v);
    m_ColorWheel->setActualColor(col);
}

void ColorDockWidget::updateColor(QColor col){
    int r = col.red();
    int g = col.green();
    int b = col.blue();

    int h = col.hue();
    int s = col.saturation();
    int v = col.value();

    m_RSlider->setValue(r);
    m_RSpinBox->setValue(r);
    m_GSlider->setValue(g);
    m_GSpinBox->setValue(g);
    m_BSlider->setValue(b);
    m_BSlider->setValue(b);

    m_HSlider->setValue(h);
    m_HSpinBox->setValue(h);
    m_SSlider->setValue(s);
    m_SSpinBox->setValue(s);
    m_VSlider->setValue(v);
    m_VSpinBox->setValue(v);
}

/*- Color wheel -*/
ColorWheel::ColorWheel(QWidget *parent) : QLabel(parent)
{
    m_Pixmap = QPixmap(250, 200);
    m_Pixmap.fill(QColor(53, 53, 53));
    setPixmap(m_Pixmap);

    m_PrimaryRed = 0;
    m_PrimaryGreen = 0;
    m_PrimaryBlue = 0;
    m_AltRed = 255;
    m_AltGreen = 255;
    m_AltBlue = 255;

    m_RotationAngle = 0.0;

    m_PrimaryColorRect = QRect(210, 160, 20, 20);
    m_AltColorRect = QRect(220, 170, 20, 20);
    QRect referenceRect(72, 47,105, 105);

    m_Points.reserve(3);
    m_Points.push_back(QPoint(referenceRect.topLeft().x() + referenceRect.width()/2, referenceRect.top() - 20));
    m_Points.push_back(referenceRect.bottomLeft());
    m_Points.push_back(referenceRect.bottomRight());

    m_CenterRectPoint = QPoint(m_Points.at(0).x(), 100);

    m_ColorRangeTri.moveTo(m_Points.at(0));
    m_ColorRangeTri.lineTo(m_Points.at(1));
    m_ColorRangeTri.lineTo(m_Points.at(2));
    m_ColorRangeTri.lineTo(m_Points.at(0));

    m_PrimaryBasePoint = QPoint(125, 15);
    m_AltBasePoint = QPoint(125, 185);
    m_toggleAlt = false;
    QColor col(m_PrimaryRed, m_PrimaryGreen, m_PrimaryBlue);
    m_Hue = col.hue();
    m_Saturation = col.saturation();
    m_Value = col.value();
}

QColor ColorWheel::getColorFromPoint(QPoint point){
    QPixmap pic = QWidget::grab();
    QImage img = pic.toImage();
    return QColor(img.pixel(point));
}

void ColorWheel::setActualColor(QColor col){
    m_ActualRed = col.red();
    m_ActualGreen = col.green();
    m_ActualBlue = col.blue();
    update();
}

QColor ColorWheel::getColor(){
    QColor ret(m_ActualRed, m_ActualGreen, m_ActualBlue);
    return ret;
}

void ColorWheel::setRed(int r){
    m_ActualRed = r;
    repaint();
}

void ColorWheel::setGreen(int g){
    m_ActualGreen = g;
    repaint();
}

void ColorWheel::setBlue(int b){
    m_ActualBlue = b;
    repaint();
}

void ColorWheel::processHSV(QColor col){
    m_Hue = col.hslHue();
    m_Saturation = col.saturation();
    m_Value = col.value();
}

void ColorWheel::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
        if(m_PrimaryColorRect.contains(ev->pos())){
            QColor color = QColorDialog::getColor(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
            if(color.isValid()){
                m_ActualRed = color.red();
                m_ActualGreen = color.green();
                m_ActualBlue = color.blue();
            }
            emit redChanged(m_ActualRed);
            emit greenChanged(m_ActualGreen);
            emit blueChanged(m_ActualBlue);
            emit colorChanged(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
        }
        if(m_AltColorRect.contains(ev->pos())){
            emit redChanged(m_AltRed);
            emit greenChanged(m_AltGreen);
            emit blueChanged(m_AltBlue);
        }
        if(m_ColorRangeTri.contains(ev->pos())){
            //set the color
            m_PreciseColor = ev->pos();
            QColor newColor = getColorFromPoint(ev->pos());
            m_ActualRed = newColor.red();
            m_ActualGreen = newColor.green();
            m_ActualBlue = newColor.blue();
            emit redChanged(m_ActualRed);
            emit greenChanged(m_ActualGreen);
            emit blueChanged(m_ActualBlue);
            emit colorChanged(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
        }
        if(!m_MouseDown && !m_ColorRangeTri.contains(ev->pos())) m_MouseDown = true;
        if(m_MouseDown){
            QPoint centerPoint(175, 100);
            QPoint dPoint = centerPoint - ev->pos();
            m_RotationAngle = atan2(dPoint.x(), dPoint.y());
            m_RotationAngle = m_RotationAngle * (180.0 / M_PI);
            processBaseMovePoint();
        }
    }
    if(ev->button() == Qt::RightButton){
        int swapRed = 0, swapGreen = 0, swapBlue = 0;
        swapRed = m_ActualRed;
        swapGreen = m_ActualGreen;
        swapBlue = m_ActualBlue;
        m_ActualRed = m_AltRed;
        m_ActualGreen = m_AltGreen;
        m_ActualBlue = m_AltBlue;
        m_AltRed = swapRed;
        m_AltGreen = swapGreen;
        m_AltBlue = swapBlue;
        emit redChanged(m_ActualRed);
        emit greenChanged(m_ActualGreen);
        emit blueChanged(m_ActualBlue);
        emit colorChanged(QColor(m_ActualRed, m_ActualGreen, m_ActualBlue));
    }
    if(ev->button() == Qt::MidButton){
        m_toggleAlt =! m_toggleAlt;
        if(m_toggleAlt){
            QColor newColor = getColorFromPoint(m_AltBasePoint);
            m_PrimaryRed = newColor.red();
            m_PrimaryGreen = newColor.green();
            m_PrimaryBlue = newColor.blue();
            m_RotationAngle+= 180.0f;
        }else{
            QColor newColor = getColorFromPoint(m_PrimaryBasePoint);
            m_PrimaryRed = newColor.red();
            m_PrimaryGreen = newColor.green();
            m_PrimaryBlue = newColor.blue();
            m_RotationAngle+= 180.0f;
        }
    }
    repaint();
}

void ColorWheel::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(53, 53, 53));
    painter.drawRect(0, 0, 250, 200);
    QConicalGradient externalColor;
    externalColor.setCenter(100, 100);
    externalColor.setColorAt(0, Qt::green);
    externalColor.setColorAt(0.175, Qt::yellow);
    externalColor.setColorAt(0.35, Qt::red);
    externalColor.setColorAt(0.525, Qt::magenta);
    externalColor.setColorAt(0.65, Qt::blue);
    externalColor.setColorAt(0.8253, Qt::cyan);
    externalColor.setColorAt(1.0, Qt::green);
    painter.setBrush(externalColor);
    painter.drawEllipse(25, 0, 200, 200);

    QPoint ctrPoint(125, 100);
    QPoint pbp = QPoint(m_PrimaryBasePoint.x(), m_PrimaryBasePoint.y());
    QPoint abp = QPoint(m_AltBasePoint.x(), m_AltBasePoint.y());

    QLine line;
    line.setP1(QPoint(125,23));
    line.setP2(QPoint(125, 177));
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.translate(ctrPoint);
    painter.rotate(-m_RotationAngle);
    painter.translate(-ctrPoint);
    painter.drawLine(line);
    painter.resetTransform();

    painter.setBrush(Qt::transparent);
    painter.drawEllipse(pbp, 8, 8);
    painter.drawEllipse(abp, 8, 8);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(53, 53, 53));
    painter.drawEllipse(ctrPoint, 75, 75);

    //Color Rect
    QColor primaryColor(m_PrimaryRed, m_PrimaryGreen, m_PrimaryBlue);
    QColor altColor(m_AltRed, m_AltGreen, m_AltBlue);
    painter.setPen(Qt::black);
    painter.setBrush(altColor);
    painter.drawRect(m_AltColorRect);
    QColor actualColor(m_ActualRed, m_ActualGreen, m_ActualBlue);
    painter.setBrush(actualColor);
    painter.drawRect(m_PrimaryColorRect);

    QConicalGradient colorGrad;
    colorGrad.setCenter(m_CenterRectPoint);
    colorGrad.setAngle(90);
    //colorGrad.setColorAt(0, Qt::white);
    colorGrad.setColorAt(0.0, primaryColor);
    colorGrad.setColorAt(0.40, Qt::black);
    colorGrad.setColorAt(0.60, Qt::white);
    colorGrad.setColorAt(1.0, primaryColor);

    painter.setBrush(colorGrad);
    painter.translate(m_CenterRectPoint);
    painter.rotate(-m_RotationAngle);
    painter.translate(-m_CenterRectPoint);
    painter.drawPath(m_ColorRangeTri);
    painter.resetTransform();
    painter.end();
}

void ColorWheel::mouseMoveEvent(QMouseEvent *e){
    if(m_MouseDown){
        QPoint centerPoint(175, 100);
        QPoint dPoint = centerPoint - e->pos();
        m_RotationAngle = atan2(dPoint.x(), dPoint.y());
        m_RotationAngle = m_RotationAngle * (180.0 / M_PI);
        qDebug() << "Rotation Angle: " << m_RotationAngle << endl;
        processBaseMovePoint();

        //Adjust the primary color
        if(!m_toggleAlt){
            QColor color = getColorFromPoint(m_PrimaryBasePoint);
            m_PrimaryRed = color.red();
            m_PrimaryGreen = color.green();
            m_PrimaryBlue = color.blue();
        }else{
            QColor color = getColorFromPoint(m_AltBasePoint);
            m_PrimaryRed = color.red();
            m_PrimaryGreen = color.green();
            m_PrimaryBlue = color.blue();
            m_RotationAngle += 180.0f;
        }
    }
    repaint();
}

void ColorWheel::mouseReleaseEvent(QMouseEvent *ev){
    Q_UNUSED(ev)
    if(m_MouseDown){
        m_MouseDown = false;
    }
}

void ColorWheel::processBaseMovePoint(){
    QTransform transform;
    QPoint ctrPoint(125, 100);
    m_PrimaryBasePoint = QPoint(125, 15);
    m_AltBasePoint = QPoint(125, 185);
    transform.translate(ctrPoint.x(), ctrPoint.y());
    transform.rotate(-m_RotationAngle);
    transform.translate(-ctrPoint.x(), -ctrPoint.y());
    m_PrimaryBasePoint = transform.map(m_PrimaryBasePoint);
    m_AltBasePoint = transform.map(m_AltBasePoint);
}


/*- TimeLine Widget -*/

TimelineDockWidget::TimelineDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Timeline");
}

TimelineDockWidget::~TimelineDockWidget()
{

}

/*-Layer Widget-*/

LayerDockWidget::LayerDockWidget(QWidget *parent) : QDockWidget(parent)
{
    //initialize
    setWindowTitle("Layer");

    m_layerCount = 0;

    m_layerOptionsBtn = new QToolButton(this);
    m_layerOptionsBtn->setText("Menu");
    m_addLayerAct = new QAction("&Add Layer", this);
    m_duplicateLayerAct = new QAction("&Duplicate Layer", this);
    m_deleteLayerAct = new QAction("&Delete Layer", this);
    m_groupAct = new QAction("&Group", this);
    m_ungroupAct = new QAction("&Ungroup", this);
    m_layerOptionsMenu = new QMenu(this);

    m_layerOptionsMenu->addAction(m_addLayerAct);
    m_layerOptionsMenu->addAction(m_duplicateLayerAct);
    m_layerOptionsMenu->addAction(m_deleteLayerAct);
    m_layerOptionsMenu->addSeparator();
    m_layerOptionsMenu->addAction(m_groupAct);
    m_layerOptionsMenu->addAction(m_ungroupAct);

    m_layerOptionsBtn->setMenu(m_layerOptionsMenu);

    m_opacityLbl = new QLabel("Opacity", this);
    m_opacitySlider = new QSlider(this);
    m_opacitySlider->setOrientation(Qt::Horizontal);
    m_opacitySlider->setRange(0, 100);
    m_opacitySlider->setValue(100);
    m_opacitySpinbox = new QSpinBox(this);
    m_opacitySpinbox->setRange(0, 100);
    m_opacitySpinbox->setValue(100);

    m_compositionMode = new QComboBox(this);
    m_compositionMode->addItem("Normal");
    m_compositionMode->insertSeparator(1);
    m_compositionMode->addItem("Plus");
    m_compositionMode->addItem("Multiply");
    m_compositionMode->insertSeparator(4);
    m_compositionMode->addItem("Screen");
    m_compositionMode->addItem("Overlay");
    m_compositionMode->insertSeparator(7);
    m_compositionMode->addItem("Darken");
    m_compositionMode->addItem("Lighten");
    m_compositionMode->addItem("Color Dodge");
    m_compositionMode->addItem("Color Burn");
    m_compositionMode->addItem("Hard Light");
    m_compositionMode->addItem("Soft Light");
    m_compositionMode->insertSeparator(14);
    m_compositionMode->addItem("Difference");
    m_compositionMode->addItem("Exclusion");

    m_layerManager = new LayerPanel(this);
//    m_layerManager->setSelectionMode(QTreeWidget::ExtendedSelection);
//    m_layerManager->sortItems(0, Qt::DescendingOrder);
//    m_layerManager->setDragEnabled(true);
//    m_layerManager->setIconSize(QSize(72, 40));

    m_addLayerBtn = new QPushButton(this);
    m_addLayerBtn->setIcon(QPixmap(":/icon/resource/plus_lite.png"));
    m_deleteLayerBtn = new QPushButton(this);
    m_deleteLayerBtn->setIcon(QPixmap(":/icon/resource/minus_lite.png"));
    m_groupBtn = new QPushButton("[G]", this);
    m_ungroupBtn = new QPushButton("[xG]", this);

    QHBoxLayout* compLayout = new QHBoxLayout;
    compLayout->addWidget(m_compositionMode);
    compLayout->addWidget(m_layerOptionsBtn);

    QHBoxLayout* opacityLayout = new QHBoxLayout;
    opacityLayout->addWidget(m_opacityLbl);
    opacityLayout->addWidget(m_opacitySlider);
    opacityLayout->addWidget(m_opacitySpinbox);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(0);
    btnLayout->addWidget(m_addLayerBtn);
    btnLayout->addWidget(m_deleteLayerBtn);
    btnLayout->addWidget(m_groupBtn);
    btnLayout->addWidget(m_ungroupBtn);

    QVBoxLayout *layerLayout = new QVBoxLayout;
    layerLayout->addLayout(compLayout);
    layerLayout->addLayout(opacityLayout);
    layerLayout->addWidget(m_layerManager);
    layerLayout->addLayout(btnLayout);

    QWidget *layerDisplay = new QWidget(this);
    layerDisplay->setLayout(layerLayout);
    setWidget(layerDisplay);

    connect(m_layerManager, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(updateLayer(QTreeWidgetItem*,int)));
    connect(m_compositionMode, SIGNAL(currentIndexChanged(int)), SLOT(updateCompositonMode(int)));
    connect(m_addLayerAct, SIGNAL(triggered()), SLOT(addLayer()));
    connect(m_groupAct, SIGNAL(triggered()), SLOT(groupLayers()));
    connect(m_duplicateLayerAct, SIGNAL(triggered()), SLOT(duplicateLayer()));
    connect(m_opacitySlider, SIGNAL(valueChanged(int)), SLOT(updateOpacity(int)));
    connect(m_opacitySpinbox, SIGNAL(valueChanged(QString)), SLOT(updateOpacity(QString)));
    connect(m_addLayerBtn, SIGNAL(clicked()), SLOT(addLayer()));
    connect(m_groupBtn, SIGNAL(clicked(bool)), SLOT(groupLayers()));
}

void LayerDockWidget::duplicateLayer(){
    m_layerCount++;
    QTreeWidgetItem* item = m_layerManager->currentItem()->clone();
    item->setText(0, item->text(0) + "Copy" );
    emit layerAdded();
}

void LayerDockWidget::reset(){
    m_layerManager->clear();
    m_layerCount = 0;
    QTreeWidgetItem* itm = new QTreeWidgetItem(m_layerManager);
    itm->setText(0, "Background");
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    itm->setCheckState(0, Qt::Checked);
    itm->setData(0, Qt::UserRole + 1, QVariant(m_layerCount));
    itm->setData(0, Qt::UserRole + 2, QVariant(0));
    itm->setData(0, Qt::UserRole + 3, QVariant(100));
    itm->setData(0, Qt::UserRole + 4, QVariant(0));
    itm->setData(0, Qt::UserRole + 5, QVariant(false));
    m_layerManager->addTopLevelItem(itm);
    m_layerManager->setCurrentItem(itm);
}

void LayerDockWidget::addLayer(){
    m_layerCount++;
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, "Layer" + QString::number(m_layerCount));
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
    itm->setCheckState(0, Qt::Checked);
    itm->setData(0, Qt::UserRole + 1, QVariant(m_layerCount)); // Corresponding layer assignment
    itm->setData(0, Qt::UserRole + 2, QVariant(0)); //visibility
    itm->setData(0, Qt::UserRole + 3, QVariant(100)); // Opacity
    itm->setData(0, Qt::UserRole + 4, QVariant(0)); //Composition mode
    itm->setData(0, Qt::UserRole + 5, QVariant(false)); //Determine if a layer or not
    m_opacitySlider->blockSignals(true);
    m_opacitySpinbox->blockSignals(true);
    m_opacitySlider->setValue(100);
    m_opacitySpinbox->setValue(100);
    m_opacitySlider->blockSignals(false);
    m_opacitySlider->blockSignals(false);

    m_layerManager->addTopLevelItem(itm);
    m_layerManager->sortItems(0, Qt::DescendingOrder);
    m_layerManager->setCurrentItem(itm);
    emit layerAdded();
}

void LayerDockWidget::removeLayer(){
    foreach(QTreeWidgetItem* itm , m_layerManager->selectedItems()){
        if(itm->isSelected()){
            int index = itm->data(0, Qt::UserRole + 1).toInt();
            if(index > 0){
                delete itm;
                emit layerRemoved(index);
            }
        }
    }
}

void LayerDockWidget::addChildLayer(QTreeWidgetItem *parent){
    m_layerCount++;
    QTreeWidgetItem* itm = new QTreeWidgetItem;
    itm->setText(0, "childLayer");
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
    itm->setCheckState(0, Qt::Checked);
    itm->setData(0, Qt::UserRole + 1, QVariant(m_layerCount));
    itm->setData(0, Qt::UserRole + 2, QVariant(0));
    itm->setData(0, Qt::UserRole + 3, QVariant(100));
    itm->setData(0, Qt::UserRole + 4, QVariant(0));
    parent->addChild(itm);
    parent->sortChildren(0, Qt::DescendingOrder);
}

void LayerDockWidget::addChildLayer(QTreeWidgetItem *parent, QString childName){
    m_layerCount++;
    QTreeWidgetItem* itm = new QTreeWidgetItem;
    itm->setText(0, childName);
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
    itm->setCheckState(0, Qt::Checked);
    itm->setData(0, Qt::UserRole + 1, QVariant(m_layerCount));
    itm->setData(0, Qt::UserRole + 2, QVariant(0));
    itm->setData(0, Qt::UserRole + 3, QVariant(100));
    parent->addChild(itm);
    parent->sortChildren(0, Qt::DescendingOrder);
}

void LayerDockWidget::groupLayers(){
    QTreeWidgetItem* grpFolder = new QTreeWidgetItem(m_layerManager);
    grpFolder->setText(0, "Group");
    grpFolder->setFlags(grpFolder->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsUserTristate);
//    for(int i = 0; i < m_layerManager->topLevelItemCount(); i++){
//        QTreeWidgetItem* itm = m_layerManager->topLevelItem(i);
//        if(itm->isSelected()){
//            grpFolder->addChild(itm);
//            m_layerManager->removeItemWidget(itm, 0);
//        }
//    }

    QList<QPixmap> icons;
    QPixmap mainIcon;

    for(int i = 0; i < m_layerManager->selectedItems().size(); i++){
        grpFolder->addChild(m_layerManager->selectedItems().at(i));
        icons.push_back(m_layerManager->selectedItems().at(i)->icon(0).pixmap(QSize(72, 40)));
    }

    QPainter p(&mainIcon);
    for(int i = 0; i < icons.size(); i++){
        p.drawPixmap(0, 0, icons.at(i));
    }

    grpFolder->setIcon(0, QIcon(mainIcon));

    foreach (QTreeWidgetItem* itm, m_layerManager->selectedItems()) {
       delete itm;
    }

    grpFolder->setExpanded(true);
    m_layerManager->sortItems(0, Qt::DescendingOrder);
    m_layerManager->expandItem(grpFolder);
}

void LayerDockWidget::ungroupLayers(){
    QTreeWidgetItem* grp = nullptr;
    grp = m_layerManager->selectedItems().at(0);
    if(grp->data(0, Qt::UserRole + 5).toBool()){

    }
}

void LayerDockWidget::updateOpacity(int o){
    m_opacitySpinbox->setValue(o);
    QTreeWidgetItem* item = m_layerManager->currentItem();
    if(!item){
        item = m_layerManager->topLevelItem(0);
    }

    item->setData(0, Qt::UserRole + 3, QVariant(o));
    emit opacityChanged(o);
}

void LayerDockWidget::updateOpacity(QString o){
    m_opacitySlider->setValue(o.toInt());
    emit opacityChanged(o.toInt());
}

void LayerDockWidget::updateLayerPreview(int i, QPixmap pix){
    QTreeWidgetItem* itm = m_layerManager->currentItem();
    if(itm != NULL){
        itm->setIcon(i, QIcon(pix));
    }
}

void LayerDockWidget::setCompositionMode(int i){
    m_compositionMode->setCurrentIndex(i);
}

void LayerDockWidget::updateLayer(QTreeWidgetItem *itm, int i){
    Q_UNUSED(i);

    int opacity = itm->data(0, Qt::UserRole + 3).toInt();

    m_compositionMode->setCurrentIndex(itm->data(0, Qt::UserRole + 4).toInt());
    m_opacitySlider->blockSignals(true);
    m_opacitySlider->setValue(opacity);
    m_opacitySlider->blockSignals(false);
    m_opacitySpinbox->blockSignals(true);
    m_opacitySpinbox->setValue(itm->data(0, Qt::UserRole + 3).toInt());
    m_opacitySpinbox->blockSignals(false);

    if(itm->checkState(i) == Qt::Unchecked){
        emit toggleLayerVisible(false);
    }else if(itm->checkState(i) == Qt::Checked){
        emit toggleLayerVisible(true);
    }else{
        qDebug() << "Cannot uncheck the noncheckable." << endl;
    }

    qDebug() << "Opacity: " << opacity << endl;

    emit compositionModeChanged(itm->data(0, Qt::UserRole + 4).toInt());
    emit layerChanged(itm->data(i, Qt::UserRole + 1).toInt());
}

void LayerDockWidget::updateLayerInfo(QTreeWidgetItem *itm, int i){
    if(itm->checkState(i) == Qt::Unchecked || itm->checkState(i) == Qt::Checked){
        //emit toggleLayerVisible(itm->data(i, Qt::UserRole +1).toInt());
    }
}

void LayerDockWidget::updateCompositonMode(int i){
    QTreeWidgetItem* item = m_layerManager->currentItem();
    item->setData(0, Qt::UserRole + 4, QVariant(i));
    emit compositionModeChanged(i);
}

LayerDockWidget::~LayerDockWidget()
{

}

ToolsPanel::ToolsPanel(QWidget* parent) : QDockWidget(parent){
    setWindowTitle("Tools");
    transTools = new TransformTools(this);
    defTools = new DefaultToolPanel(this);
    textPanel = new TextPanel(this);
    primPanel = new PrimitivePanel(this);
    panelSpace = new QStackedWidget();
    panelSpace->addWidget(defTools);
    panelSpace->addWidget(transTools);
    panelSpace->addWidget(textPanel);
    panelSpace->addWidget(primPanel);
    panelSpace->setCurrentIndex(0);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(panelSpace);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(scrollArea);
    centralLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);
    setWidget(centralWidget);
    connect(transTools, SIGNAL(translateChanged(int,int)), SLOT(updateTranslate(int,int)));
    connect(transTools, SIGNAL(rotateChanged(int)), SLOT(updateRotate(int)));
    connect(transTools, SIGNAL(scaleChanged(int,int)), SLOT(updateScale(int,int)));
    connect(transTools, SIGNAL(transformModeChanged(int)), SLOT(updateTransformMode(int)));
    connect(transTools, SIGNAL(useWorldTransform(bool)), SLOT(updateWorldTransform(bool)));
    connect(textPanel, SIGNAL(fontChanged(QFont)), SLOT(updateFont(QFont)));
    connect(textPanel, SIGNAL(fontSizeChanged(int)), SLOT(updateFontSize(int)));
    connect(textPanel, SIGNAL(fontBoldChanged(bool)), SLOT(updateFontBold(bool)));
    connect(textPanel, SIGNAL(fontItalicChanged(bool)), SLOT(updateFontItalic(bool)));
    connect(textPanel, SIGNAL(fontUnderlineChanged(bool)), SLOT(updateFontUnderline(bool)));
    connect(textPanel, SIGNAL(actionCommited()), SLOT(updateActionCommit()));
}

ToolsPanel::~ToolsPanel(){

}

void ToolsPanel::setMode(int o){
    switch(o){
    case 0:
    case 1:
        panelSpace->setCurrentIndex(0);
        break;
    case 2:
        panelSpace->setCurrentIndex(2);
        break;
    case 3:
        panelSpace->setCurrentIndex(3);
        break;
    case 4:
    case 5:
    case 6:
        panelSpace->setCurrentIndex(2);
        break;
    case 7:
    case 8:
    case 9:
        panelSpace->setCurrentIndex(1);
        break;
    default:
        panelSpace->setCurrentIndex(0);
    }
}

void ToolsPanel::updateTranslate(int x, int y){
    emit translateChanged(x, y);
}

void ToolsPanel::updateRotate(int x){
    emit rotateChanged(x);
}

void ToolsPanel::updateScale(int x, int y){
    emit scaleChanged(x, y);
}

void ToolsPanel::updateTransformMode(int v){
    emit transformModeChanged(v);
}

void ToolsPanel::updateWorldTransform(bool v){
    emit useWorldTransform(v);
}

void ToolsPanel::updateFont(QFont font){
    emit fontChanged(font);
}

void ToolsPanel::updateFontSize(int fontSize){
    emit fontSizeChanged(fontSize);
}

void ToolsPanel::toggleBold(){
    textPanel->toggleBold();
}

void ToolsPanel::toggleItalic(){
    textPanel->toggleItalic();
}

void ToolsPanel::toggleUnderline(){
    textPanel->toggleUnderline();
}

void ToolsPanel::updateFontBold(bool v){
    emit fontBoldChanged(v);
}

void ToolsPanel::updateFontItalic(bool v){
    emit fontItalicChanged(v);
}

void ToolsPanel::updateFontUnderline(bool v){
    emit fontUnderlineChanged(v);
}

void ToolsPanel::updateActionCommit(){
    emit actionCommitted();
}

DefaultToolPanel::DefaultToolPanel(QWidget *parent) : QWidget(parent){
    QGroupBox* grpBox = new QGroupBox(this);
    grpBox->setTitle("Info");
    infoString = "This is the tool panel, this will automatically change once special tools are active.";
    QLabel* lbl = new QLabel(infoString, this);
    lbl->setWordWrap(true);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(lbl);
    grpBox->setLayout(layout);
    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(grpBox);
    setLayout(centralLayout);
}

DefaultToolPanel::~DefaultToolPanel(){

}

TransformTools::TransformTools(QWidget *parent) : QWidget(parent){

    QButtonGroup* modeGrp;
    transformMode = 0;

    m_Link4Trans = false;
    m_Link4Rot = false;
    m_Link4Scal = false;

    m_TranslateBtn = new QRadioButton("&Translate", this);
    m_TranslateBtn->setChecked(true);
    m_RotateBtn = new QRadioButton("&Rotate", this);
    m_ScaleBtn = new QRadioButton("&Scale", this);
    modeGrp = new QButtonGroup(this);
    modeGrp->addButton(m_TranslateBtn);
    modeGrp->addButton(m_RotateBtn);
    modeGrp->addButton(m_ScaleBtn);

    QHBoxLayout* optionLayout = new QHBoxLayout;
    optionLayout->addWidget(m_TranslateBtn);
    optionLayout->addWidget(m_RotateBtn);
    optionLayout->addWidget(m_ScaleBtn);

    //Translate
    m_TransXLbl = new QLabel("Translate X:", this);
    m_TransXSB = new QSpinBox(this);
    m_TransXSB->setRange(-100, 10000);
    m_TransXSB->setMinimumWidth(48);
    QHBoxLayout* transXLayout = new QHBoxLayout;
    transXLayout->addWidget(m_TransXLbl);
    transXLayout->addWidget(m_TransXSB);

    m_TransYLbl = new QLabel("Translate Y:", this);
    m_TransYSB = new QSpinBox(this);
    m_TransYSB->setRange(-100, 10000);
    m_TransYSB->setMinimumWidth(48);
    QHBoxLayout* transYLayout = new QHBoxLayout;
    transYLayout->addWidget(m_TransYLbl);
    transYLayout->addWidget(m_TransYSB);

    m_RotLbl = new QLabel("Rotate:", this);
    m_RotSB = new QSpinBox(this);
    m_RotSB->setRange(0, 359);
    m_RotSB->setMinimumWidth(48);
    QHBoxLayout* rotXLayout = new QHBoxLayout;
    rotXLayout->addWidget(m_RotLbl);
    rotXLayout->addWidget(m_RotSB);

    //Hide Rotate
    m_RotLbl->hide();
    m_RotSB->hide();

    m_ScalXLbl = new QLabel("Scale X:", this);
    m_ScalXSB = new QSpinBox(this);
    m_ScalXSB->setRange(-100, 10000);
    m_ScalXSB->setMinimumWidth(48);
    QHBoxLayout* scalXLayout = new QHBoxLayout;
    scalXLayout->addWidget(m_ScalXLbl);
    scalXLayout->addWidget(m_ScalXSB);

    m_ScalYLbl = new QLabel("Scale Y:", this);
    m_ScalYSB = new QSpinBox(this);
    m_ScalYSB->setRange(-100, 100000);
    m_ScalYSB->setMinimumWidth(48);
    QHBoxLayout* scalYLayout = new QHBoxLayout;
    scalYLayout->addWidget(m_ScalYLbl);
    scalYLayout->addWidget(m_ScalYSB);
    m_CommitButton = new QPushButton("&Commit", this);

    //Hide other things
    m_ScalXLbl->hide();
    m_ScalXSB->hide();
    m_ScalYLbl->hide();
    m_ScalYSB->hide();

    m_LinkTransformBtn = new QPushButton("[&L]", this);
    m_LinkTransformBtn->setMinimumWidth(18);
    m_LinkTransformBtn->setCheckable(true);
    m_LinkTransformBtn->setChecked(false);

    QHBoxLayout* transformManualCtlLayout = new QHBoxLayout;
    transformManualCtlLayout->addLayout(transXLayout);
    transformManualCtlLayout->addLayout(rotXLayout);
    transformManualCtlLayout->addLayout(scalXLayout);
    transformManualCtlLayout->addWidget(m_LinkTransformBtn);
    transformManualCtlLayout->addLayout(transYLayout);
    transformManualCtlLayout->addLayout(scalYLayout);

    m_WorldTransformBtn = new QRadioButton("&World", this);
    m_WorldTransformBtn->setChecked(true);
    m_LocalTransformBtn = new QRadioButton("&Local", this);

    QHBoxLayout* transTypeLayout = new QHBoxLayout;
    transTypeLayout->addWidget(m_WorldTransformBtn);
    transTypeLayout->addWidget(m_LocalTransformBtn);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addLayout(optionLayout);
    centralLayout->addLayout(transformManualCtlLayout);
    centralLayout->addLayout(transTypeLayout);

    QGroupBox* grpBox = new QGroupBox(this);
    grpBox->setTitle("Transform");
    grpBox->setLayout(centralLayout);
    QVBoxLayout* finalLayout = new QVBoxLayout;
    finalLayout->addWidget(grpBox);
    finalLayout->addWidget(m_CommitButton);
    finalLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(finalLayout);

    connect(m_TranslateBtn, SIGNAL(toggled(bool)), SLOT(changeToTrans(bool)));
    connect(m_RotateBtn, SIGNAL(toggled(bool)), SLOT(changeToRot(bool)));
    connect(m_ScaleBtn, SIGNAL(toggled(bool)), SLOT(changeToScal(bool)));
    connect(m_LinkTransformBtn, SIGNAL(toggled(bool)), SLOT(activateLink(bool)));
    connect(m_TransXSB, SIGNAL(valueChanged(int)), SLOT(syncTransY(int)));
    connect(m_TransYSB, SIGNAL(valueChanged(int)), SLOT(syncTransX(int)));
    connect(m_ScalXSB, SIGNAL(valueChanged(int)), SLOT(syncScalY(int)));
    connect(m_ScalYSB, SIGNAL(valueChanged(int)), SLOT(syncScalX(int)));
    connect(m_WorldTransformBtn, SIGNAL(toggled(bool)), SLOT(updateWorldTransformUse(bool)));
}

void TransformTools::activateLink(bool s){
    switch(transformMode){
    case 0:
        m_Link4Trans = s;
        break;
    case 1:
        m_Link4Rot = s;
        break;
    case 2:
        m_Link4Scal = s;
        break;
    default:
        break;
    }
}

void TransformTools::setTransformMode(int t){
    transformMode = t;
}

void TransformTools::changeToTrans(bool s){
    m_RotLbl->setVisible(!s);
    m_RotSB->setVisible(!s);

    m_LinkTransformBtn->show();

    m_ScalXLbl->setVisible(!s);
    m_ScalXSB->setVisible(!s);
    m_ScalYLbl->setVisible(!s);
    m_ScalYSB->setVisible(!s);

    m_TransXLbl->setVisible(s);
    m_TransXSB->setVisible(s);
    m_TransYLbl->setVisible(s);
    m_TransYSB->setVisible(s);

    transformMode = 0;
    emit transformModeChanged(transformMode);
}

void TransformTools::changeToRot(bool s){
    m_TransXLbl->setVisible(!s);
    m_TransXSB->setVisible(!s);
    m_TransYLbl->setVisible(!s);
    m_TransYSB->setVisible(!s);
    m_LinkTransformBtn->hide();

    m_ScalXLbl->setVisible(!s);
    m_ScalXSB->setVisible(!s);
    m_ScalYLbl->setVisible(!s);
    m_ScalYSB->setVisible(!s);

    m_RotLbl->setVisible(s);
    m_RotSB->setVisible(s);

    transformMode = 1;
    emit transformModeChanged(transformMode);
}

void TransformTools::changeToScal(bool s){

    m_TransXLbl->setVisible(!s);
    m_TransXSB->setVisible(!s);
    m_TransYLbl->setVisible(!s);
    m_TransYSB->setVisible(!s);

    m_RotLbl->setVisible(!s);
    m_RotSB->setVisible(!s);

    m_ScalXLbl->setVisible(s);
    m_ScalXSB->setVisible(s);
    m_ScalYLbl->setVisible(s);
    m_ScalYSB->setVisible(s);
    m_LinkTransformBtn->show();

    transformMode = 2;
    emit transformModeChanged(transformMode);
}

void TransformTools::updateTranslate(){
    emit translateChanged(m_TransXSB->text().toInt(), m_TransYSB->text().toInt());
}

void TransformTools::updateRotate(){
    emit rotateChanged(m_RotSB->text().toInt());
}

void TransformTools::updateScale(){
    emit scaleChanged(m_ScalXSB->text().toInt(), m_ScalYSB->text().toInt());
}

void TransformTools::syncTransX(int v){
    if(m_Link4Trans){ m_TransXSB->setValue(v); }
    updateTranslate();
}

void TransformTools::syncTransY(int v){
    if(m_Link4Trans){ m_TransYSB->setValue(v); }
    updateTranslate();
}

void TransformTools::syncScalX(int v){
    if(m_Link4Scal){ m_ScalXSB->setValue(v); }
    updateScale();
}

void TransformTools::syncScalY(int v){
    if(m_Link4Scal){ m_ScalYSB->setValue(v); }
    updateScale();
}

void TransformTools::updateWorldTransformUse(bool v){
    emit useWorldTransform(v);
}

TransformTools::~TransformTools(){

}

TextPanel::TextPanel(QWidget *parent) : QWidget(parent){
    m_FontComboBox = new QFontComboBox(this);
    m_FontSizeSB = new QSpinBox(this);
    m_FontSizeSB->setValue(7);

    m_FontSize = 7;

    m_Font = QFont("MS Shell DLG 2", 7);

    m_BoldBtn = new QPushButton("B",this);
    m_BoldBtn->setCheckable(true);
    m_ItalicBtn = new QPushButton("I", this);
    m_ItalicBtn->setCheckable(true);
    m_UnderlineBtn = new QPushButton("U", this);
    m_UnderlineBtn->setCheckable(true);

    QHBoxLayout* centralLayout = new QHBoxLayout;
    centralLayout->addWidget(m_FontComboBox);
    centralLayout->addWidget(m_FontSizeSB);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_BoldBtn);
    btnLayout->addWidget(m_ItalicBtn);
    btnLayout->addWidget(m_UnderlineBtn);

    QVBoxLayout* textLayout = new QVBoxLayout;
    textLayout->addLayout(centralLayout);
    textLayout->addLayout(btnLayout);

    QGroupBox* grpBox = new QGroupBox(this);
    grpBox->setTitle("&Text");
    grpBox->setLayout(textLayout);

    m_CommitButton = new QPushButton("&Commit", this);

    QVBoxLayout* finalLayout = new QVBoxLayout;
    finalLayout->addWidget(grpBox);
    finalLayout->addWidget(m_CommitButton);
    finalLayout->addSpacerItem(new QSpacerItem(25, 25, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(finalLayout);

    connect(m_FontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(changeFont(QFont)));
    connect(m_FontSizeSB, SIGNAL(valueChanged(int)), SLOT(changeFontSize(int)));
    connect(m_BoldBtn, SIGNAL(clicked(bool)), SLOT(updateFontBold(bool)));
    connect(m_ItalicBtn, SIGNAL(clicked(bool)), SLOT(updateFontItalic(bool)));
    connect(m_UnderlineBtn, SIGNAL(clicked(bool)), SLOT(updateFontUnderline(bool)));
    connect(m_CommitButton, SIGNAL(clicked()), SLOT(commitChanges()));
}

void TextPanel::toggleBold(){
    m_BoldBtn->setChecked(!m_BoldBtn->isChecked());
}

void TextPanel::toggleItalic(){
    m_ItalicBtn->setChecked(!m_ItalicBtn->isChecked());
}

void TextPanel::toggleUnderline(){
    m_UnderlineBtn->setChecked(!m_UnderlineBtn->isChecked());
}

void TextPanel::changeFont(QFont font){
    m_Font = font;
    m_Font.setPointSize(m_FontSize);
    emit fontChanged(m_Font);
}

void TextPanel::changeFontSize(int s){
    m_FontSize = s;
    emit fontSizeChanged(m_FontSize);
}

void TextPanel::updateFontBold(bool v){
    emit fontBoldChanged(v);
}

void TextPanel::updateFontItalic(bool v){
    emit fontItalicChanged(v);
}

void TextPanel::updateFontUnderline(bool v){
    emit fontUnderlineChanged(v);
}

void TextPanel::commitChanges(){
    emit actionCommited();
}

TextPanel::~TextPanel(){

}

PrimitivePanel::PrimitivePanel(QWidget *parent) : QWidget(parent){

    m_lineColor = QColor(Qt::black);
    m_fillColor = QColor(Qt::transparent);

    m_isLineBtn = new QRadioButton("&Line", this);
    m_isLineBtn->setChecked(true);
    m_isConcaveBtn = new QRadioButton("&Concave", this);
    m_isConvexBtn = new QRadioButton("&Convex", this);
    m_concaveGrp = new QButtonGroup(this);
    m_concaveGrp->addButton(m_isLineBtn);
    m_concaveGrp->addButton(m_isConcaveBtn);
    m_concaveGrp->addButton(m_isConvexBtn);

    QHBoxLayout* radioBtnLayout = new QHBoxLayout;
    radioBtnLayout->addWidget(m_isLineBtn);
    radioBtnLayout->addWidget(m_isConcaveBtn);
    radioBtnLayout->addWidget(m_isConvexBtn);

    m_PointCountLbl = new QLabel("Vertices: ", this);
    m_PointSB = new QSpinBox(this);
    m_PointSB->setValue(3);
    m_PointSB->setRange(3, 100);

    QHBoxLayout* pointLayout = new QHBoxLayout;
    pointLayout->addWidget(m_PointCountLbl);
    pointLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    pointLayout->addWidget(m_PointSB);

    m_PenWidthLbl = new QLabel("Pen Width: ", this);
    m_PenWidthSB = new QSpinBox(this);
    m_PenWidthSB->setRange(0, 100);

    QHBoxLayout* penLayout = new QHBoxLayout;
    penLayout->addWidget(m_PenWidthLbl);
    penLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    penLayout->addWidget(m_PenWidthSB);

    m_WidthLbl = new QLabel("Width: ", this);
    m_WidthSlider = new QSlider(this);
    m_WidthSlider->setRange(0, 100);
    m_WidthSlider->setOrientation(Qt::Horizontal);
    m_WidthSB = new QSpinBox(this);
    m_WidthSB->setRange(0, 100);

    QHBoxLayout* widthLayout = new QHBoxLayout;
    widthLayout->addWidget(m_WidthLbl);
    widthLayout->addWidget(m_WidthSlider);
    widthLayout->addWidget(m_WidthSB);

    m_HeightLbl = new QLabel("Height: ", this);
    m_HeightSlider = new QSlider(this);
    m_HeightSlider->setRange(0, 100);
    m_HeightSlider->setOrientation(Qt::Horizontal);
    m_HeightSB = new QSpinBox(this);
    m_HeightSB->setRange(0, 100);

    QHBoxLayout* heightLayout = new QHBoxLayout;
    heightLayout->addWidget(m_HeightLbl);
    heightLayout->addWidget(m_HeightSlider);
    heightLayout->addWidget(m_HeightSB);
    m_CommitBtn = new QPushButton("Commit", this);

    m_lineColorLbl = new QLabel("Line Color: ", this);
    m_lineColorBtn = new QPushButton(this);
    QPixmap lineColorImg(m_lineColorBtn->size());
    lineColorImg.fill(m_lineColor);
    m_lineColorBtn->setIcon(QIcon(lineColorImg));
    QHBoxLayout* lineColorLayout = new QHBoxLayout;
    lineColorLayout->addWidget(m_lineColorLbl);
    lineColorLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    lineColorLayout->addWidget(m_lineColorBtn);

    m_fillColorLbl = new QLabel("Fill Color: ", this);
    m_fillColorBtn = new QPushButton(this);
    QPixmap fillColorImg(m_fillColorBtn->size());
    fillColorImg.fill(m_fillColor);
    m_fillColorBtn->setIcon(QIcon(fillColorImg));
    QHBoxLayout* fillColorLayout = new QHBoxLayout;
    fillColorLayout->addWidget(m_fillColorLbl);
    fillColorLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    fillColorLayout->addWidget(m_fillColorBtn);

    QVBoxLayout* overallLayout = new QVBoxLayout;
    overallLayout->addLayout(radioBtnLayout);
    overallLayout->addLayout(pointLayout);
    overallLayout->addLayout(penLayout);
    overallLayout->addLayout(widthLayout);
    overallLayout->addLayout(heightLayout);
    overallLayout->addLayout(lineColorLayout);
    overallLayout->addLayout(fillColorLayout);
    overallLayout->addWidget(m_CommitBtn);

    QGroupBox* grpBox = new QGroupBox(this);
    grpBox->setTitle("Primitives");
    grpBox->setLayout(overallLayout);

    QVBoxLayout* displayLayout = new QVBoxLayout;
    displayLayout->addWidget(grpBox);
    setLayout(displayLayout);

    m_PointSB->setEnabled(false);
    m_WidthSlider->setEnabled(false);
    m_WidthSB->setEnabled(false);
    m_HeightSB->setEnabled(false);
    m_HeightSlider->setEnabled(false);

    connect(m_isLineBtn, SIGNAL(clicked(bool)), SLOT(setLineMode(bool)));
    connect(m_isConcaveBtn, SIGNAL(clicked(bool)), SLOT(setConcaveMode(bool)));
    connect(m_isConvexBtn, SIGNAL(clicked(bool)), SLOT(setConvexMode(bool)));
    connect(m_PointSB, SIGNAL(valueChanged(int)), SLOT(updatePointCount(int)));
    connect(m_PenWidthSB, SIGNAL(valueChanged(int)), SLOT(updatePenWidth(int)));
    connect(m_WidthSlider, SIGNAL(valueChanged(int)), SLOT(updateWidth(int)));
    connect(m_HeightSlider, SIGNAL(valueChanged(int)), SLOT(updateHeight(int)));
    connect(m_WidthSB, SIGNAL(valueChanged(QString)), SLOT(updateWidth(QString)));
    connect(m_HeightSB, SIGNAL(valueChanged(QString)), SLOT(updateHeight(QString)));
    connect(m_lineColorBtn, SIGNAL(clicked()), SLOT(updateLineColor()));
    connect(m_fillColorBtn, SIGNAL(clicked()), SLOT(updateFillColor()));
    connect(m_CommitBtn, SIGNAL(clicked()), SLOT(commitChanges()));
}

void PrimitivePanel::updateWidth(int width){
    m_WidthSB->setValue(width);
    emit widthChanged(width);
}

void PrimitivePanel::updateWidth(QString width){
    m_WidthSlider->setValue(width.toInt());
}

void PrimitivePanel::updateHeight(int height){
    m_HeightSB->setValue(height);
    emit heightChanged(height);
}

void PrimitivePanel::updateHeight(QString height){
    m_HeightSlider->setValue(height.toInt());
}

void PrimitivePanel::updatePenWidth(int penWidth){
    emit penWidthChanged(penWidth);
}

void PrimitivePanel::updatePointCount(int sideCount){
    emit pointCountChanged(sideCount);
}

void PrimitivePanel::commitChanges(){
    emit actionCommited();
}

void PrimitivePanel::setLineMode(bool v){
    if(v){
        m_PointSB->setEnabled(false);
        m_WidthSlider->setEnabled(false);
        m_WidthSB->setEnabled(false);
        m_HeightSB->setEnabled(false);
        m_HeightSlider->setEnabled(false);
        emit shapeModeChanged(0);
    }
}

void PrimitivePanel::setConcaveMode(bool v){
    if(v){
        m_PointSB->setEnabled(true);
        m_WidthSlider->setEnabled(true);
        m_WidthSB->setEnabled(true);
        m_HeightSB->setEnabled(true);
        m_HeightSlider->setEnabled(true);
        emit shapeModeChanged(1);
    }
}

void PrimitivePanel::setConvexMode(bool v){
    if(v){
        m_PointSB->setEnabled(true);
        m_WidthSlider->setEnabled(true);
        m_WidthSB->setEnabled(true);
        m_HeightSB->setEnabled(true);
        m_HeightSlider->setEnabled(true);
        emit shapeModeChanged(2);
    }
}

void PrimitivePanel::updateLineColor(){
    m_lineColor = QColorDialog::getColor(m_lineColor, this, "Line Color");
    QPixmap lineColorImg(m_lineColorBtn->size());
    lineColorImg.fill(m_lineColor);
    m_lineColorBtn->setIcon(QIcon(lineColorImg));

    emit lineColorChanged(m_lineColor);
    update();
}

void PrimitivePanel::updateFillColor(){
    m_fillColor = QColorDialog::getColor(m_fillColor, this, "Fill Color");
    QPixmap fillColorImg(m_fillColorBtn->size());
    fillColorImg.fill(m_fillColor);
    m_fillColorBtn->setIcon(QIcon(fillColorImg));

    emit fillColorChanged(m_fillColor);
    update();
}

void PrimitivePanel::changeWidth(int width){
    m_WidthSB->setValue(width);
    m_WidthSlider->setValue(width);
}

void PrimitivePanel::changeHeight(int height){
    m_HeightSB->setValue(height);
    m_HeightSlider->setValue(height);
}

PrimitivePanel::~PrimitivePanel(){

}



BrushPanel::~BrushPanel()
{

}
