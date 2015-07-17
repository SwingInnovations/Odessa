#include "dockwidgets.h"

BrushDockWidget::BrushDockWidget(QWidget *parent) : QDockWidget(parent)
{
    /*-Constructor-*/
    mTabWidget = new QTabWidget(this);
    mGenBrushWidget = new GeneralBrushWidget;
    mStencilWidget = new CustomBrushWidget;

    mActualBrushList = QVector<Brush>();
    mTempBrushList = QVector<Brush>();

    mCurrentBrushIndex = 0;
    m_firstTimeRun = false;

    readSettings();
    mBrushLib = mProjectPath + "/Brush/default.blib";

    if(!QFile(mBrushLib).exists()){
        //generate default
        mActualBrushList.append(Brush());
        mActualBrushList[0].setSWidth(10);
        mActualBrushList[0].setSHeight(10);
        mActualBrushList[0].setSpacing(1);
        mActualBrushList[0].setHardness(100);
        mActualBrushList[0].SetName("Default");
        mStencilWidget->setBrushSettings(mActualBrushList.first());
        QPixmap sten1;
        sten1.load(":/icon/resource/default.png");
        mActualBrushList[0].SetStencil(sten1);
        mTempBrushList = mActualBrushList;
        mGenBrushWidget->addBrush(mActualBrushList.at(0));
        mGenBrushWidget->setStencilPixmap(mActualBrushList.first().getStencil());
        mStencilWidget->updateStencilWidth(mTempBrushList.at(0).getSWidth());
        mStencilWidget->updateStencilHeight(mTempBrushList.at(0).getSHeight());
        saveBrushLib(mBrushLib);
    }else{
        //use loaded data
        mActualBrushList = loadBrushLib(mBrushLib);
        for(int i = 0; i < mActualBrushList.size(); i++){
            mGenBrushWidget->addBrush(mActualBrushList.at(i));
        }
        mTempBrushList = mActualBrushList;
    }

    mDrawModeComboBox = new QComboBox(this);
    mDrawModeComboBox->addItem("Normal");
    mDrawModeComboBox->addItem("Multiply");
    mDrawModeComboBox->addItem("Color");
    mSizeLabel = new QLabel("Size:", this);
    mSizeSlider = new QSlider(Qt::Horizontal, this);
    mSizeSlider->setRange(0, 500);
    mSizeSlider->setValue(5);
    mSizeSlider->setMinimumWidth(150);
    mSizeLE = new QSpinBox(this);
    mSizeLE->setRange(0, 500);
    mSizeLE->setFixedWidth(48);
    mSizeLE->setValue(5);
    QHBoxLayout* sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(mSizeLabel);
    sizeLayout->addWidget(mSizeSlider);
    sizeLayout->addWidget(mSizeLE);

    mOpacityLabel = new QLabel("Opacity:", this);
    mOpacitySlider = new QSlider(Qt::Horizontal, this);
    mOpacitySlider->setRange(0, 100);
    mOpacitySlider->setValue(100);
    mOpacityLE = new QSpinBox(this);
    mOpacityLE->setRange(0, 100);
    mOpacityLE->setFixedWidth(48);
    mOpacityLE->setValue(100);
    QHBoxLayout* opacityLayout = new QHBoxLayout;
    opacityLayout->addWidget(mOpacityLabel);
    opacityLayout->addWidget(mOpacitySlider);
    opacityLayout->addWidget(mOpacityLE);

    mSpacingLabel = new QLabel("Spacing:", this);
    mSpacingSlider = new QSlider(Qt::Horizontal, this);
    mSpacingSlider->setRange(0, 3);
    mSpacingSlider->setPageStep(0.1);
    mSpacingSlider->setValue(1);
    mSpacingSlider->setMinimumWidth(150);
    mSpacingLE = new QSpinBox(this);
    mSpacingLE->setFixedWidth(48);
    mSpacingLE->setValue(1);
    QHBoxLayout* spacingLayout = new QHBoxLayout;
    spacingLayout->addWidget(mSpacingLabel);
    spacingLayout->addWidget(mSpacingSlider);
    spacingLayout->addWidget(mSpacingLE);

    QVBoxLayout* generalParam = new QVBoxLayout;
    generalParam->addWidget(mDrawModeComboBox);
    generalParam->addLayout(sizeLayout);
    generalParam->addLayout(opacityLayout);
    generalParam->addLayout(spacingLayout);

    /*-Transfer-*/
    mTransferSizeToggle = new QCheckBox("Size:", this);
    mTransferSizeToggle->setChecked(false);
    mTransferSizeSlider = new QSlider(Qt::Horizontal, this);
    mTransferSizeSlider->setRange(0, 500);
    mTransferSizeSlider->setValue(0);
    mTransferSizeSlider->setEnabled(false);
    mTransferSizeLE = new QSpinBox(this);
    mTransferSizeLE->setFixedWidth(48);
    mTransferSizeLE->setRange(0, 500);
    mTransferSizeLE->setValue(0);
    mTransferSizeLE->setEnabled(false);
    QHBoxLayout* transferSizeLayout = new QHBoxLayout;
    transferSizeLayout->addWidget(mTransferSizeToggle);
    transferSizeLayout->addWidget(mTransferSizeSlider);
    transferSizeLayout->addWidget(mTransferSizeLE);

    mTransferOpacityToggle = new QCheckBox("Opacity:", this);
    mTransferOpacityToggle->setChecked(false);
    mTransferOpacitySlider = new QSlider(Qt::Horizontal, this);
    mTransferOpacitySlider->setRange(0, 255);
    mTransferOpacitySlider->setValue(0);
    mTransferOpacitySlider->setEnabled(false);
    mTransferOpacityLE = new QSpinBox(this);
    mTransferOpacityLE->setRange(0, 100);
    mTransferOpacityLE->setFixedWidth(48);
    mTransferOpacityLE->setValue(0);
    mTransferOpacityLE->setEnabled(false);
    QHBoxLayout* transferOpacityLayout = new QHBoxLayout;
    transferOpacityLayout->addWidget(mTransferOpacityToggle);
    transferOpacityLayout->addWidget(mTransferOpacitySlider);
    transferOpacityLayout->addWidget(mTransferOpacityLE);

    mTransferOpacityLE->setVisible(false);
    mTransferOpacitySlider->setVisible(false);
    mTransferOpacityToggle->setVisible(false);
    mTransferSizeLE->setVisible(false);
    mTransferSizeSlider->setVisible(false);
    mTransferSizeToggle->setVisible(false);

    QVBoxLayout* transferParam = new QVBoxLayout;
    transferParam->addLayout(transferSizeLayout);
    transferParam->addLayout(transferOpacityLayout);
    transGrpBox = new QGroupBox("Transfer" ,this);
    transGrpBox->setCheckable(true);
    transGrpBox->setChecked(false);
    transGrpBox->setLayout(transferParam);

    generalParam->addWidget(transGrpBox);

    /*-Brush_General-*/

    QVBoxLayout* GeneralBrushLayout = new QVBoxLayout;
    GeneralBrushLayout->addWidget(mGenBrushWidget);
    GeneralBrushLayout->addLayout(generalParam);

    QWidget* GeneralBrushTab = new QWidget(this);
    GeneralBrushTab->setLayout(GeneralBrushLayout);

    /*-Brush_Advanced-*/

    QVBoxLayout* AdvancedBrushLayout = new QVBoxLayout;
    AdvancedBrushLayout->addWidget(mStencilWidget);

    QWidget* AdvancedBrushTab = new QWidget(this);
    AdvancedBrushTab->setLayout(AdvancedBrushLayout);

    mTabWidget->addTab(GeneralBrushTab, "General");
    mTabWidget->addTab(AdvancedBrushTab, "Custom");

    mTabWidget->setTabPosition(QTabWidget::North);
    mTabWidget->setTabShape(QTabWidget::Rounded);

    QVBoxLayout* displayLayout = new QVBoxLayout;
    displayLayout->addWidget(mTabWidget);
    displayLayout->addSpacerItem(new QSpacerItem(292, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QWidget* displayWidget = new QWidget(this);
    displayWidget->setLayout(displayLayout);

    setWidget(displayWidget);

    connect(mSizeSlider, SIGNAL(valueChanged(int)), SLOT(updateSize(int)));
    connect(mSizeLE, SIGNAL(valueChanged(QString)), SLOT(updateSize(QString)));
    connect(mOpacitySlider, SIGNAL(valueChanged(int)), SLOT(updateOpacity(int)));
    connect(mOpacityLE, SIGNAL(valueChanged(QString)), SLOT(updateOpacity(QString)));
    connect(mSpacingSlider, SIGNAL(valueChanged(int)), SLOT(updateSpacing(int)));
    connect(mSpacingLE, SIGNAL(valueChanged(QString)), SLOT(updateSpacing(QString)));
    connect(mTransferSizeToggle, SIGNAL(toggled(bool)), SLOT(toggleTransferSize(bool)));
    connect(mTransferSizeSlider, SIGNAL(valueChanged(int)), SLOT(updateTransferSize(int)));
    connect(mTransferSizeLE, SIGNAL(valueChanged(QString)), SLOT(updateTransferSize(QString)));
    connect(mTransferOpacityToggle, SIGNAL(toggled(bool)), SLOT(toggleTransferOpacity(bool)));
    connect(mTransferOpacitySlider, SIGNAL(valueChanged(int)), SLOT(updateTransferOpacity(int)));
    connect(mTransferOpacityLE, SIGNAL(valueChanged(QString)), SLOT(updateTransferOpacity(QString)));
    connect(mStencilWidget, SIGNAL(stencilChanged(QPixmap)), SLOT(updateStencil(QPixmap)));
    connect(mStencilWidget, SIGNAL(stencilChanged(QPixmap)), mGenBrushWidget, SLOT(updateStencil(QPixmap)));
    connect(mStencilWidget, SIGNAL(stencilPathChanged(QString)), SLOT(updateStencilPath(QString)));
    connect(transGrpBox, SIGNAL(toggled(bool)), SLOT(toggleTransferVisibility(bool)));
    connect(mGenBrushWidget, SIGNAL(loadStencilTriggered()), SLOT(loadStencilAct()));
    connect(mGenBrushWidget, SIGNAL(loadBrushTriggered()), SLOT(loadBrushAct()));
    connect(mGenBrushWidget, SIGNAL(loadBrushSetTriggered()), SLOT(loadBrushSetAct()));
    connect(mGenBrushWidget, SIGNAL(saveStencilTriggered()), SLOT(saveStencilAct()));
    connect(mGenBrushWidget, SIGNAL(saveBrushTriggered()), SLOT(saveBrushAct()));
    connect(mGenBrushWidget, SIGNAL(saveBrushSetTriggered()), SLOT(saveBrushSetAct()));
    connect(mStencilWidget, SIGNAL(loadStencilTriggered()), SLOT(loadStencilAct()));
    connect(mStencilWidget, SIGNAL(loadBrushTriggered()), SLOT(loadBrushAct()));
    connect(mStencilWidget, SIGNAL(loadBrushSetTriggered()), SLOT(loadBrushSetAct()));
    connect(mStencilWidget, SIGNAL(saveStencilTriggered()), SLOT(saveStencilAct()));
    connect(mStencilWidget, SIGNAL(saveBrushTriggered()), SLOT(saveBrushAct()));
    connect(mStencilWidget, SIGNAL(saveBrushSetTriggered()), SLOT(saveBrushSetAct()));
    connect(mStencilWidget, SIGNAL(StencilWidthChanged(int)), SLOT(updateStencilWidth(int)));
    connect(mStencilWidget, SIGNAL(stencilHeightChanged(int)), SLOT(updateStencilHeight(int)));
    connect(mStencilWidget, SIGNAL(brushHardnessChanged(int)), SLOT(updateStencilHardness(int)));
    connect(mStencilWidget, SIGNAL(rotateChanged(int)), SLOT(updateStencilRotate(int)));
    connect(mGenBrushWidget, SIGNAL(brushLibIndexChanged(int)), SLOT(setCurrentIndex(int)));
    connect(mGenBrushWidget, SIGNAL(brushNameChanged(QString)), SLOT(updateBrushName(QString)));
    update();
}

void BrushDockWidget::setDirectory(QString dir){
    mProjectPath = dir;
    mGenBrushWidget->setDir(dir);
}

void BrushDockWidget::updateSize(int val)
{
    mSizeLE->setValue(val);
    emit brushSizeChanged(val);
}

void BrushDockWidget::updateSize(QString val)
{
    mSizeSlider->setValue(val.toInt());
    emit brushSizeChanged(val.toInt());
}

void BrushDockWidget::updateOpacity(int val)
{
    mOpacityLE->setValue(val);
    emit brushOpacityChanged(val);
}

void BrushDockWidget::updateOpacity(QString val)
{
    mOpacitySlider->setValue(val.toInt());
    emit brushOpacityChanged(val.toInt());
}

void BrushDockWidget::updateSpacing(int val){
    mSpacingLE->setValue(val);
    emit brushSpacingChanged(val);
}

void BrushDockWidget::updateSpacing(QString val){
    mSpacingSlider->setValue(val.toInt());
    emit brushSpacingChanged(val.toInt());
}

void BrushDockWidget::updateTransferSize(int val)
{
    mTransferSizeLE->setValue(val);
    mGenBrushWidget->generateStrokePreview();
    emit brushTransferSizeChanged(val);
}

void BrushDockWidget::updateTransferSize(QString val)
{
    mTransferSizeSlider->setValue(val.toInt());
    emit brushTransferSizeChanged(val.toInt());
}

void BrushDockWidget::updateTransferOpacity(int val)
{
    mTransferOpacityLE->setValue(val);
    emit brushTransferOpacityChanged(val);
}

void BrushDockWidget::updateTransferOpacity(QString val)
{
    mTransferOpacitySlider->setValue(val.toInt());
    emit brushTransferOpacityChanged(val.toInt());
}

void BrushDockWidget::toggleTransferSize(bool val)
{
    mTransferSizeSlider->setEnabled(val);
    mTransferSizeLE->setEnabled(val);
    mGenBrushWidget->activateUsePressureWidth(val);
    if(!val){
        emit brushTransferSizeChanged(0);
    }else{
        emit brushTransferSizeChanged(mTransferSizeLE->value());
    }
}

void BrushDockWidget::toggleTransferOpacity(bool val)
{
    mTransferOpacitySlider->setEnabled(val);
    mTransferOpacityLE->setEnabled(val);
    if(val == false){
        emit brushTransferOpacityChanged(0);
    }else{
        emit brushTransferOpacityChanged(mTransferSizeSlider->value());
    }
}

void BrushDockWidget::toggleTransferVisibility(bool val){
    if(val){
        mTransferOpacityLE->setVisible(true);
        mTransferOpacitySlider->setVisible(true);
        mTransferOpacityToggle->setVisible(true);
        mTransferSizeLE->setVisible(true);
        mTransferSizeSlider->setVisible(true);
        mTransferSizeToggle->setVisible(true);
    }else{
        mTransferOpacityLE->setVisible(false);
        mTransferOpacitySlider->setVisible(false);
        mTransferOpacityToggle->setVisible(false);
        mTransferSizeLE->setVisible(false);
        mTransferSizeSlider->setVisible(false);
        mTransferSizeToggle->setVisible(false);
    }
}

void BrushDockWidget::updateStencilWidth(int val){
    mTempBrushList[mCurrentBrushIndex].setSWidth(val);
}

void BrushDockWidget::updateStencilHeight(int val){
    mTempBrushList[mCurrentBrushIndex].setSHeight(val);
}

void BrushDockWidget::updateStencilHardness(int val){
    mTempBrushList[mCurrentBrushIndex].setHardness(val);
}

void BrushDockWidget::updateStencilRotate(int val){
    mTempBrushList[mCurrentBrushIndex].SetRotate(val);
}

void BrushDockWidget::updateStencil(QPixmap pixmap){
    mTempBrushList[mCurrentBrushIndex].SetStencil(pixmap);
    mGenBrushWidget->setStencilPixmap(pixmap);
    emit brushStencilChanged(pixmap);
}

void BrushDockWidget::updateStencilPath(QString filePath){
    emit brushStencilPathChanged(filePath);
}

void BrushDockWidget::updateBrushName(QString name){
    mActualBrushList[mCurrentBrushIndex].SetName(name);
    mTempBrushList[mCurrentBrushIndex].SetName(name);
}

void BrushDockWidget::setCurrentIndex(int val){
    mCurrentBrushIndex = val;
    mStencilWidget->updateStencilWidth(mActualBrushList.at(mCurrentBrushIndex).getSWidth());
    mStencilWidget->updateStencilHeight(mActualBrushList.at(mCurrentBrushIndex).getSHeight());
    mStencilWidget->updateBrushHardness(mActualBrushList.at(mCurrentBrushIndex).getHardness());
    mStencilWidget->updateStencilRotate(mActualBrushList.at(mCurrentBrushIndex).getRotate());
    mStencilWidget->updateStencil(mActualBrushList.at(mCurrentBrushIndex).getStencil());
    mGenBrushWidget->setStencilPixmap(mActualBrushList.at(mCurrentBrushIndex).getStencil());
    emit stencilWidthChanged(mActualBrushList.at(mCurrentBrushIndex).getSWidth());
    emit stencilHeightChanged(mActualBrushList.at(mCurrentBrushIndex).getSHeight());
    emit brushHardnessChanged(mActualBrushList.at(mCurrentBrushIndex).getHardness());
    emit stencilRotateChanged(mActualBrushList.at(mCurrentBrushIndex).getRotate());
    emit brushStencilChanged(mActualBrushList.at(mCurrentBrushIndex).getStencil());
}

void BrushDockWidget::loadStencilAct(){
    qDebug()<<"Loading Stencil" << endl;
    QString filePath = QFileDialog::getOpenFileName(this, "Open Stencil", QDir::currentPath());
    QPixmap pixmap;
    pixmap.load(filePath);
    mStencilWidget->updateStencil(pixmap);
}

void BrushDockWidget::loadBrushAct(){
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush", mProjectPath, ".brsh");
    Brush temp = loadBrush(filePath);
    mTempBrushList.append(temp);
    mActualBrushList.append(temp);
    mGenBrushWidget->addBrush(temp);
    qDebug()<<"Loading Brush" << endl;
}

void BrushDockWidget::loadBrushSetAct(){
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush Library", mProjectPath, "*.blib");

    QMessageBox msgBox;
    msgBox.setText("Would you like to Load a new brush set or add to existing?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, "Load new set");
    msgBox.setButtonText(QMessageBox::Cancel, "Add to existing set");
    switch(msgBox.exec()){
    case QMessageBox::Ok:                       //Replaces Existing
       mActualBrushList = loadBrushLib(filePath);
       mBrushLib = filePath;
        break;
    case QMessageBox::Cancel:                   //Appends to brush set
        QVector<Brush> temp = loadBrushLib(filePath);
        mActualBrushList = mActualBrushList + temp;
        break;
    }

    qDebug()<<"Loading Brush Set" << endl;
}

void BrushDockWidget::saveStencilAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save Stencil",QDir::currentPath());
    QPixmap pixmap = mStencilWidget->GetPixmap();
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
        mActualBrushList.push_back(mTempBrushList.at(mCurrentBrushIndex));
        mGenBrushWidget->addBrush(mTempBrushList.at(mCurrentBrushIndex));
        mTempBrushList = mActualBrushList;
        break;
    case QMessageBox::Cancel:
        QString filePath = QFileDialog::getSaveFileName(this, "Save Brush", mProjectPath, ".brsh");
        int encrypt = 5025;
        Brush ret = mTempBrushList[mCurrentBrushIndex];
        QFile file(filePath);
        if(!file.open(QIODevice::WriteOnly)){
            qDebug() << "Error, cannot open file";
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);
        out << encrypt <<ret;

        file.flush();
        file.close();

        mActualBrushList.push_back(mTempBrushList.at(mCurrentBrushIndex));
        mGenBrushWidget->addBrush(mTempBrushList.at(mCurrentBrushIndex));
        mTempBrushList = mActualBrushList;
        break;
    }
}

void BrushDockWidget::saveBrushSetAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save brush library", mProjectPath, ".blib");
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
    out << encrypt << mActualBrushList;

    file.flush();
    file.close();
    qDebug() << "Saved brush set";
}

Brush BrushDockWidget::getStartBrush(){
    qDebug() << "Stencil stats: \t Width: " << mActualBrushList.first().getStencil().width() << " Height: " << mActualBrushList.first().getStencil().height() << endl;
    return mActualBrushList[0];
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
    mProjectPath = settings.value("projectPath").toString();
    mBrushLib = settings.value("activeBrushLib").toString();
}

void BrushDockWidget::writeSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    settings.setValue("activeBrushLib", mBrushLib);
    qDebug() << mBrushLib << endl;
    saveBrushLib(mBrushLib);
}

BrushDockWidget::~BrushDockWidget()
{
    saveBrushLib(mBrushLib);
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
    mToolBtn = new QToolButton(this);
    mToolBtn->setText("Tool");
    mToolBtn->setFixedWidth(48);
    mToolBtn->setFixedHeight(48);
    mToolMenu = new QMenu(this);
    mLoadStencilAct = new QAction("&Load Stencil", this);
    mLoadBrushAct = new QAction("&Load Brush", this);
    mLoadBrushSetAct = new QAction("&Load Brush Set", this);
    mSaveStencilAct = new QAction("&Save Stencil", this);
    mSaveBrushAct = new QAction("&Save Brush", this);
    mSaveBrushSetAct = new QAction("&Save Brush Set", this);
    mDeleteBrushAct = new QAction("Delete Brush", this);
    mToolMenu->addAction(mLoadStencilAct);
    mToolMenu->addAction(mLoadBrushAct);
    mToolMenu->addAction(mLoadBrushSetAct);
    mToolMenu->addSeparator();
    mToolMenu->addAction(mSaveStencilAct);
    mToolMenu->addAction(mSaveBrushAct);
    mToolMenu->addAction(mSaveBrushSetAct);
    mToolMenu->addSeparator();
    mToolMenu->addAction(mDeleteBrushAct);
    mToolBtn->setMenu(mToolMenu);

    mBrushIndex = new QListWidget(this);
    mBrushIndex->setMinimumWidth(130);
    mBrushIndex->setBaseSize(130, 130);
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
    vert1->addWidget(mToolBtn);
    vert1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    QHBoxLayout* horiz1 = new QHBoxLayout;
    horiz1->addWidget(mBrushIndex);
    horiz1->addLayout(vert1);
    QVBoxLayout* generalBrushLayout = new QVBoxLayout;
    generalBrushLayout->addLayout(horiz1);
    generalBrushLayout->addWidget(m_PreviewLabel);
    generalBrushLayout->setAlignment(m_PreviewLabel, Qt::AlignCenter);
    generalBrushLayout->addLayout(toggleStrokeLayout);

    setLayout(generalBrushLayout);
    connect(mLoadStencilAct, SIGNAL(triggered()), SLOT(updateLoadStencil()));
    connect(mLoadBrushAct, SIGNAL(triggered()), SLOT(updateLoadBrush()));
    connect(mLoadBrushSetAct, SIGNAL(triggered()), SLOT(updateLoadBrushSet()));
    connect(mSaveStencilAct, SIGNAL(triggered()), SLOT(updateSaveStencil()));
    connect(mSaveBrushAct, SIGNAL(triggered()), SLOT(updateSaveBrush()));
    connect(mSaveBrushSetAct, SIGNAL(triggered()), SLOT(updateSaveBrushSet()));
    connect(mDeleteBrushAct, SIGNAL(triggered()), SLOT(updateDeleteBrush()));
    connect(mBrushIndex, SIGNAL(currentRowChanged(int)), SLOT(updateBrushLibIndex(int)));
    connect(mBrushIndex, SIGNAL(itemChanged(QListWidgetItem*)), SLOT(updateName(QListWidgetItem*)));
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
    mBrushIndex->addItem(itm);
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

    mBrushShape = CIRCLE_SHAPE;
    hasTexture = false;

    mStencilPreview = QPixmap(160, 160);
    mStencilPreview.fill(Qt::transparent);
    mStencilLabel = new QLabel(this);
    mStencilLabel->setPixmap(mStencilPreview);

    mToolBtn = new QToolButton(this);
    mToolBtn->setText("Tool");
    mToolBtn->setFixedWidth(48);
    mToolBtn->setFixedHeight(48);
    mToolMenu = new QMenu(this);
    mLoadStencilAct = new QAction("&Load Stencil", this);
    mLoadBrushAct = new QAction("&Load Brush", this);
    mLoadBrushSetAct = new QAction("&Load Brush Set", this);
    mSaveStencilAct = new QAction("&Save Stencil", this);
    mSaveBrushAct = new QAction("&Save Brush", this);
    mSaveBrushSetAct = new QAction("&Save Brush Set", this);
    mDeleteBrushAct = new QAction("Delete Brush", this);
    mToolMenu->addAction(mLoadStencilAct);
    mToolMenu->addAction(mLoadBrushAct);
    mToolMenu->addAction(mLoadBrushSetAct);
    mToolMenu->addSeparator();
    mToolMenu->addAction(mSaveStencilAct);
    mToolMenu->addAction(mSaveBrushAct);
    mToolMenu->addAction(mSaveBrushSetAct);
    mToolMenu->addSeparator();
    mToolMenu->addAction(mDeleteBrushAct);
    mToolBtn->setMenu(mToolMenu);

    QVBoxLayout* v1Layout = new QVBoxLayout;
    v1Layout->addWidget(mToolBtn);
    v1Layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));

    QHBoxLayout* StencilPreviewLayout = new QHBoxLayout;
    StencilPreviewLayout->addWidget(mStencilLabel);
    StencilPreviewLayout->setAlignment(mStencilLabel, Qt::AlignCenter);
    StencilPreviewLayout->addLayout(v1Layout);

    mWidthLabel = new QLabel("Width:", this);
    mWidthSlider = new QSlider(Qt::Horizontal, this);
    mWidthSlider->setRange(0, 10);
    mWidthSlider->setValue(10);
    mWidthLE = new QLineEdit(this);
    mWidthLE->setFixedWidth(32);
    mWidthLE->setText(QString::number(10));
    QHBoxLayout* widthLayout = new QHBoxLayout;
    widthLayout->addWidget(mWidthLabel);
    widthLayout->addWidget(mWidthSlider);
    widthLayout->addWidget(mWidthLE);

    mHeightLabel = new QLabel("Height:", this);
    mHeightSlider = new QSlider(Qt::Horizontal, this);
    mHeightSlider->setRange(0, 10);
    mHeightSlider->setValue(10);
    mHeightLE = new QLineEdit(this);
    mHeightLE->setFixedWidth(32);
    mHeightLE->setText(QString::number(10));
    QHBoxLayout* heightLayout = new QHBoxLayout;
    heightLayout->addWidget(mHeightLabel);
    heightLayout->addWidget(mHeightSlider);
    heightLayout->addWidget(mHeightLE);

    mHardnessLabel = new QLabel("Hardness:", this);
    mHardnessSlider = new QSlider(Qt::Horizontal, this);
    mHardnessSlider->setRange(0, 100);
    mHardnessSlider->setValue(100);
    mHardnessLE = new QLineEdit(this);
    mHardnessLE->setFixedWidth(32);
    mHardnessLE->setText(QString::number(100));
    QHBoxLayout* hardnessLayout = new QHBoxLayout;
    hardnessLayout->addWidget(mHardnessLabel);
    hardnessLayout->addWidget(mHardnessSlider);
    hardnessLayout->addWidget(mHardnessLE);

    mRotateLabel = new QLabel("Rotate:", this);
    mRotateSlider = new QSlider(Qt::Horizontal, this);
    mRotateSlider->setRange(0, 361);
    mRotateSlider->setValue(0);
    mRotateLE = new QLineEdit(this);
    mRotateLE->setFixedWidth(32);
    mRotateLE->setText(QString::number(0));
    QHBoxLayout* rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(mRotateLabel);
    rotateLayout->addWidget(mRotateSlider);
    rotateLayout->addWidget(mRotateLE);

    mCircleButton = new QPushButton("Circle", this);
    mSquareButton = new QPushButton("Square", this);
    mCustomButton = new QPushButton("Custom", this);
    QHBoxLayout* stencilShapeLayout = new QHBoxLayout;
    stencilShapeLayout->addWidget(mCircleButton);
    stencilShapeLayout->addWidget(mSquareButton);
    stencilShapeLayout->addWidget(mCustomButton);

    mTextureLabel = new QLabel("Texture: ", this);
    mTextureFileLE = new QLineEdit(this);
    mTextureBtn = new QPushButton("...",this);
    QHBoxLayout* textureLayout = new QHBoxLayout;
    textureLayout->addWidget(mTextureLabel);
    textureLayout->addWidget(mTextureFileLE);
    textureLayout->addWidget(mTextureBtn);

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

    connect(mLoadStencilAct, SIGNAL(triggered()), SLOT(updateLoadStencil()));
    connect(mLoadBrushAct, SIGNAL(triggered()), SLOT(updateLoadBrush()));
    connect(mLoadBrushSetAct, SIGNAL(triggered()), SLOT(updateLoadBrushSet()));
    connect(mSaveStencilAct, SIGNAL(triggered()), SLOT(updateSaveStencil()));
    connect(mSaveBrushAct, SIGNAL(triggered()), SLOT(updateSaveBrush()));
    connect(mSaveBrushSetAct, SIGNAL(triggered()), SLOT(updateSaveBrushSet()));
    connect(mDeleteBrushAct, SIGNAL(triggered()), SLOT(updateDeleteBrush()));
    connect(mWidthLE, SIGNAL(textChanged(QString)), SLOT(updateStencilWidth(QString)));
    connect(mWidthSlider, SIGNAL(valueChanged(int)), SLOT(updateStencilWidth(int)));
    connect(mHeightLE, SIGNAL(textChanged(QString)), SLOT(updateStencilHeight(QString)));
    connect(mHeightSlider, SIGNAL(valueChanged(int)), SLOT(updateStencilHeight(int)));
    connect(mHeightLE, SIGNAL(textChanged(QString)), SLOT(updateStencilHeight(QString)));
    connect(mHardnessSlider, SIGNAL(valueChanged(int)), SLOT(updateBrushHardness(int)));
    connect(mHardnessLE, SIGNAL(textChanged(QString)), SLOT(updateBrushHardness(QString)));
    connect(mRotateSlider, SIGNAL(valueChanged(int)), SLOT(updateStencilRotate(int)));
    connect(mRotateLE, SIGNAL(textChanged(QString)), SLOT(updateStencilRotate(QString)));
    connect(this, SIGNAL(stencilChanged(QPixmap)), SLOT(updateStencil(QPixmap)));
    connect(mCircleButton, SIGNAL(clicked()), SLOT(updateBrushShape_Circle()));
    connect(mSquareButton, SIGNAL(clicked()), SLOT(updateBrushShape_Square()));
    connect(mCustomButton, SIGNAL(clicked()), SLOT(updateBrushShape_Polygon()));
    connect(mTextureBtn, SIGNAL(clicked()), SLOT(updateStencilTexture()));
    connect(mTextureFileLE, SIGNAL(textChanged(QString)), SLOT(updateStencilTextureLE(QString)));
}

void CustomBrushWidget::TempSave(QPixmap pixmap){
    QImage image = pixmap.toImage();
    image.convertToFormat(QImage::Format_RGB888, Qt::AutoColor);
    if(tempFile.open()){
        image.save(tempFile.fileName());
    }
    tempFile.close();
    emit stencilPathChanged(tempFile.fileName());
}

void CustomBrushWidget::updateStencil(QPixmap pixmap){
    TempSave(pixmap);
}

void CustomBrushWidget::updateStencilTexture(){
    hasTexture = true;
    QString fileName = QFileDialog::getOpenFileName(this, "Load Texture", QDir::currentPath());
    mStencilTexture.load(fileName);
    QImage image = mStencilTexture.toImage();
    QRgb col;
    int gray;
    int width = mStencilTexture.width();
    int height = mStencilTexture.height();
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    mStencilTexture = mStencilTexture.fromImage(image);
    mStencilTexture = mStencilTexture.scaled(mStencilPreview.width(), mStencilPreview.height(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
    mTextureFileLE->setText(fileName);
}

void CustomBrushWidget::updateStencilWidth(int val){
   mWidthLE->setText(QString::number(val));
   emit StencilWidthChanged(val);
   emit stencilChanged(mStencilPreview);
}

void CustomBrushWidget::updateStencilWidth(QString val){
    mWidthSlider->setValue(val.toInt());
    emit StencilWidthChanged(val.toInt());
}

void CustomBrushWidget::updateStencilHeight(int val){
    mHeightLE->setText(QString::number(val));
    emit stencilHeightChanged(val);
    emit stencilChanged(mStencilPreview);
}

void CustomBrushWidget::updateStencilHeight(QString val){
    mHeightSlider->setValue(val.toInt());
    emit stencilHeightChanged(val.toInt());
}

void CustomBrushWidget::updateBrushHardness(int val){
    mHardnessLE->setText(QString::number(val));
    emit brushHardnessChanged(val);
    emit stencilChanged(mStencilPreview);
}

void CustomBrushWidget::updateBrushHardness(QString val){
    mHardnessSlider->setValue(val.toInt());
    emit brushHardnessChanged(val.toInt());
}

void CustomBrushWidget::updateStencilRotate(int val){
    if(val > 360){
        val = 0;
        mRotateSlider->setValue(0);
    }
    mRotateLE->setText(QString::number(val));
    emit rotateChanged(val);
    emit stencilChanged(mStencilPreview);
}

void CustomBrushWidget::updateStencilRotate(QString val){
    if(val.toInt() > 360){
        mRotateSlider->setValue(0);
        emit rotateChanged(0);
    }else{
        mRotateSlider->setValue(val.toInt());
        emit rotateChanged(val.toInt());
    }
}

void CustomBrushWidget::updateStencilTextureLE(QString val){
    if(val.isEmpty()){
        hasTexture = false;
    }else{
        hasTexture = true;
    }
}

void CustomBrushWidget::setBrushSettings(Brush b){
    mWidthSlider->setValue(b.sWidth);
    mHeightSlider->setValue(b.sHeight);
    mHardnessSlider->setValue(b.getHardness());
    mRotateSlider->setValue(b.getRotate());
    update();
}

QPixmap CustomBrushWidget::GeneratePixmap(){
    mStencilPreview.fill(Qt::transparent);
    int stencilWidth = (mStencilPreview.width() * mWidthSlider->value()/10)/2;
    int stencilHeight = (mStencilPreview.height()* mHeightSlider->value()/10)/2;
    qreal fRadius = ((qreal)mHardnessSlider->value()/100.0);
    QPoint midPoint(mStencilPreview.width()/2, mStencilPreview.height()/2);

    qDebug() << "fRadius: " << fRadius << endl;

    QRadialGradient radGrad(midPoint, midPoint.x());
    radGrad.setColorAt(0.0, Qt::black);
    radGrad.setColorAt(fRadius, Qt::black);
    if(fRadius == 1.0){
        radGrad.setColorAt(1.0, Qt::black);
    }else{
        radGrad.setColorAt(1.0, Qt::transparent);
    }

    QPixmap img = mStencilPreview;

    QPainter p;
    p.begin(&img);
    p.setRenderHint(QPainter::Antialiasing);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.setPen(Qt::NoPen);
    p.setBrush(radGrad);
    switch(mBrushShape){
    case CIRCLE_SHAPE:
        if(hasTexture){
            QBrush brush;
            brush.setTexture(mStencilTexture);
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

        if(hasTexture){
            QBrush brush;
            brush.setTexture(mStencilTexture);
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
    mStencilPreview = img;
    return mStencilPreview;
}

void CustomBrushWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
//    int stencilWidth = (mStencilPreview.width() * mWidthSlider->value()/10)/2;
//    int stencilHeight = (mStencilPreview.height()* mHeightSlider->value()/10)/2;
//    qreal hardness = 78 * ((qreal)mHardnessSlider->value()/100);
//    QPoint midPoint(mStencilPreview.width()/2, mStencilPreview.height()/2);
//    mStencilPreview.fill(Qt::transparent);
//    QRadialGradient radGrad(midPoint, mStencilPreview.width()/2);
//    radGrad.setColorAt(midPoint.x()/mStencilPreview.width(), Qt::black);
//    radGrad.setFocalRadius(hardness);

//    QPainter painter(&mStencilPreview);
//    painter.setPen(Qt::NoPen);
//    switch(mBrushShape){
//        case CIRCLE_SHAPE:
//            if(hasTexture){
//                QBrush brush;
//                brush.setTexture(mStencilTexture);
//                painter.setBrush(brush);
//            }else{
//                painter.setBrush(radGrad);
//            }
//            painter.translate(midPoint);
//            painter.rotate(mRotateSlider->value());
//            painter.translate(-midPoint);
//            painter.drawEllipse(midPoint, stencilWidth, stencilHeight);
//            break;
//        case SQUARE_SHAPE:
//            int originX =  midPoint.x() - stencilWidth;
//            int originY = midPoint.y() - stencilHeight;
//            int dimX = stencilWidth*2;
//            int dimY = stencilHeight*2;

//            if(hasTexture){
//                QBrush brush;
//                brush.setTexture(mStencilTexture);
//                painter.setBrush(brush);
//            }else{
//                painter.setBrush(Qt::black);
//            }
//            painter.translate(midPoint);
//            painter.rotate(mRotateSlider->value());
//            painter.translate(-midPoint);
//            painter.drawRect(originX, originY, dimX, dimY);
//            break;
//    }
//    mStencilLabel->setPixmap(mStencilPreview);
   QImage ret = GeneratePixmap().toImage();
   ret.invertPixels(QImage::InvertRgba);
   mStencilPreview = QPixmap::fromImage(ret);
   mStencilLabel->setPixmap(mStencilPreview);
}

void CustomBrushWidget::updateBrushShape_Circle(){
    mBrushShape = CIRCLE_SHAPE;
    update();
    emit stencilChanged(GeneratePixmap());
}

void CustomBrushWidget::updateBrushShape_Square(){
    mBrushShape = SQUARE_SHAPE;
    update();
    emit stencilChanged(GeneratePixmap());
}

void CustomBrushWidget::updateBrushShape_Polygon(){
    mBrushShape = CUSTOM;
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
    mColorWheel = new ColorWheel(this);
    mColorTabs = new QTabWidget(this);

    //Red Parameters
    mRLabel = new QLabel("R:", this);
    mRSlider = new QSlider(this);
    mRSlider->setOrientation(Qt::Horizontal);
    mRSlider->setRange(0, 255);
    mRSlider->setValue(0);
    mRSpinBox = new QSpinBox(this);
    mRSpinBox->setRange(0, 255);
    mRSpinBox->setValue(0);

    QHBoxLayout* rBoxLayout = new QHBoxLayout;
    rBoxLayout->addWidget(mRLabel);
    rBoxLayout->addWidget(mRSlider);
    rBoxLayout->addWidget(mRSpinBox);

    //Green Parameters
    mGLabel = new QLabel("G:", this);
    mGSlider = new QSlider(this);
    mGSlider->setOrientation(Qt::Horizontal);
    mGSlider->setRange(0, 255);
    mGSlider->setValue(0);
    mGSpinBox = new QSpinBox(this);
    mGSpinBox->setRange(0, 255);
    mGSpinBox->setValue(0);

    QHBoxLayout* gBoxLayout = new QHBoxLayout;
    gBoxLayout->addWidget(mGLabel);
    gBoxLayout->addWidget(mGSlider);
    gBoxLayout->addWidget(mGSpinBox);

    //Blue Parameters
    mBLabel = new QLabel("B:", this);
    mBSlider = new QSlider(this);
    mBSlider->setOrientation(Qt::Horizontal);
    mBSlider->setRange(0, 255);
    mBSlider->setValue(0);
    mBSpinBox = new QSpinBox(this);
    mBSpinBox->setRange(0, 255);
    mBSpinBox->setValue(0);

    QHBoxLayout* bBoxLayout = new QHBoxLayout;
    bBoxLayout->addWidget(mBLabel);
    bBoxLayout->addWidget(mBSlider);
    bBoxLayout->addWidget(mBSpinBox);

    //Hue Parameters
    mHLabel = new QLabel("H:", this);
    mHSlider = new QSlider(this);
    mHSlider->setOrientation(Qt::Horizontal);
    mHSlider->setRange(0, 255);
    mHSlider->setValue(0);
    mHSpinBox = new QSpinBox(this);
    mHSpinBox->setRange(0, 255);
    mHSpinBox->setValue(0);

    QHBoxLayout* hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(mHLabel);
    hBoxLayout->addWidget(mHSlider);
    hBoxLayout->addWidget(mHSpinBox);

    //Saturation Parameters
    mSLabel = new QLabel("S:", this);
    mSSlider = new QSlider(this);
    mSSlider->setOrientation(Qt::Horizontal);
    mSSlider->setRange(0, 255);
    mSSlider->setValue(0);
    mSSpinBox = new QSpinBox(this);
    mSSpinBox->setRange(0, 255);
    mSSpinBox->setValue(0);

    QHBoxLayout* sBoxLayout = new QHBoxLayout;
    sBoxLayout->addWidget(mSLabel);
    sBoxLayout->addWidget(mSSlider);
    sBoxLayout->addWidget(mSSpinBox);

    //Value Parameters
    mVLabel = new QLabel("V:", this);
    mVSlider = new QSlider(this);
    mVSlider->setOrientation(Qt::Horizontal);
    mVSlider->setRange(0, 255);
    mVSlider->setValue(0);
    mVSpinBox = new QSpinBox(this);
    mVSpinBox->setRange(0, 255);
    mVSpinBox->setValue(0);

    QHBoxLayout* vBoxLayout = new QHBoxLayout;
    vBoxLayout->addWidget(mVLabel);
    vBoxLayout->addWidget(mVSlider);
    vBoxLayout->addWidget(mVSpinBox);

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

    mColorTabs->addTab(RGBPanel, "RGB");
    mColorTabs->addTab(HSVPanel, "HSV");

    QVBoxLayout* masterLayout = new QVBoxLayout;
    masterLayout->addWidget(mColorWheel);
    masterLayout->setAlignment(mColorWheel, Qt::AlignCenter);
    masterLayout->addWidget(mColorTabs);
    masterLayout->addSpacerItem(new QSpacerItem(292, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QWidget* masterWidget = new QWidget(this);
    masterWidget->setLayout(masterLayout);
    setWidget(masterWidget);

    connect(mColorWheel, SIGNAL(redChanged(int)), SLOT(updateRed(int)));
    connect(mColorWheel, SIGNAL(blueChanged(int)), SLOT(updateBlue(int)));
    connect(mColorWheel, SIGNAL(greenChanged(int)), SLOT(updateGreen(int)));
    connect(mColorWheel, SIGNAL(colorChanged(QColor)), SLOT(updateColor(QColor)));
    connect(mRSlider, SIGNAL(valueChanged(int)), SLOT(updateRed(int)));
    connect(mGSlider, SIGNAL(valueChanged(int)), SLOT(updateGreen(int)));
    connect(mBSlider, SIGNAL(valueChanged(int)), SLOT(updateBlue(int)));
    connect(mRSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateRed(QString)));
    connect(mGSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateGreen(QString)));
    connect(mBSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateBlue(QString)));
    connect(mHSlider, SIGNAL(valueChanged(int)), SLOT(updateHue(int)));
    connect(mSSlider, SIGNAL(valueChanged(int)), SLOT(updateSat(int)));
    connect(mVSlider, SIGNAL(valueChanged(int)), SLOT(updateVal(int)));
    connect(mHSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateHue(QString)));
    connect(mSSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateSat(QString)));
    connect(mVSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateVal(QString)));
}

void ColorDockWidget::updateRed(int val){
    mRSpinBox->setValue(val);
    mColorWheel->setRed(val);
    emit redChanged(val);
}

void ColorDockWidget::updateRed(QString val){
    mRSlider->setValue(val.toInt());
    emit redChanged(val.toInt());
}

void ColorDockWidget::updateGreen(int val){
    mGSpinBox->setValue(val);
    mColorWheel->setGreen(val);
    emit greenChanged(val);
}

void ColorDockWidget::updateGreen(QString val){
    mGSlider->setValue(val.toInt());
    emit greenChanged(val.toInt());
}

void ColorDockWidget::updateBlue(int val){
    mBSpinBox->setValue(val);
    mColorWheel->setBlue(val);
    emit blueChanged(val);
}

void ColorDockWidget::updateBlue(QString val){
    mBSlider->setValue(val.toInt());
    emit blueChanged(val.toInt());
}

void ColorDockWidget::updateHue(int val){
    QColor col = mColorWheel->getColor();
    mHSpinBox->setValue(val);
    int h = val;
    int s = col.saturation();
    int v = col.value();
    col.setHsv(h, s, v);
    mColorWheel->setActualColor(col);
    emit redChanged(col.red());
    emit greenChanged(col.green());
    emit blueChanged(col.blue());
}

void ColorDockWidget::updateHue(QString val){
    QColor col = mColorWheel->getColor();
    mHSlider->setValue(val.toInt());
    int h = val.toInt();
    int s = col.saturation();
    int v = col.value();
    col.setHsv(h, s, v);
    mColorWheel->setActualColor(col);
}

void ColorDockWidget::updateSat(int val){
    QColor col = mColorWheel->getColor();
    mSSpinBox->setValue(val);
    int h = col.hue();
    int s = val;
    int v = col.value();
    col.setHsv(h, s, v);
    mColorWheel->setActualColor(col);
    emit redChanged(col.red());
    emit greenChanged(col.green());
    emit blueChanged(col.blue());
}

void ColorDockWidget::updateSat(QString val){
    QColor col = mColorWheel->getColor();
    mSSlider->setValue(val.toInt());
    int h = col.hue();
    int s = val.toInt();
    int v = col.value();
    col.setHsv(h, s, v);
    mColorWheel->setActualColor(col);
}

void ColorDockWidget::updateVal(int val){
    QColor col = mColorWheel->getColor();
    mVSpinBox->setValue(val);
    int h = col.hue();
    int s = col.saturation();
    int v = val;
    col.setHsv(h, s, v);
    mColorWheel->setActualColor(col);
    emit redChanged(col.red());
    emit greenChanged(col.green());
    emit blueChanged(col.blue());
}

void ColorDockWidget::updateVal(QString val){
    QColor col = mColorWheel->getColor();
    mVSlider->setValue(val.toInt());
    int h = col.hue();
    int s = col.saturation();
    int v = val.toInt();
    col.setHsv(h, s, v);
    mColorWheel->setActualColor(col);
}

void ColorDockWidget::updateColor(QColor col){
    int r = col.red();
    int g = col.green();
    int b = col.blue();

    int h = col.hue();
    int s = col.saturation();
    int v = col.value();

    mRSlider->setValue(r);
    mRSpinBox->setValue(r);
    mGSlider->setValue(g);
    mGSpinBox->setValue(g);
    mBSlider->setValue(b);
    mBSlider->setValue(b);

    mHSlider->setValue(h);
    mHSpinBox->setValue(h);
    mSSlider->setValue(s);
    mSSpinBox->setValue(s);
    mVSlider->setValue(v);
    mVSpinBox->setValue(v);
}

/*- Color wheel -*/
ColorWheel::ColorWheel(QWidget *parent) : QLabel(parent)
{
    mPixmap = QPixmap(250, 200);
    mPixmap.fill(QColor(53, 53, 53));
    setPixmap(mPixmap);

    primaryRed = 0;
    primaryGreen = 0;
    primaryBlue = 0;
    altRed = 255;
    altGreen = 255;
    altBlue = 255;

    rotationAngle = 0.0;

    primaryColorRect = QRect(210, 160, 20, 20);
    altColorRect = QRect(220, 170, 20, 20);
    QRect referenceRect(72, 47,105, 105);

    points.reserve(3);
    points.push_back(QPoint(referenceRect.topLeft().x() + referenceRect.width()/2, referenceRect.top() - 20));
    points.push_back(referenceRect.bottomLeft());
    points.push_back(referenceRect.bottomRight());

    centerRectPoint = QPoint(points.at(0).x(), 100);

    colorRangeTri.moveTo(points.at(0));
    colorRangeTri.lineTo(points.at(1));
    colorRangeTri.lineTo(points.at(2));
    colorRangeTri.lineTo(points.at(0));

    primaryBasePoint = QPoint(125, 15);
    altBasePoint = QPoint(125, 185);
    toggleAlt = false;
    QColor col(primaryRed, primaryGreen, primaryBlue);
    mHue = col.hue();
    mSaturation = col.saturation();
    mValue = col.value();
}

QColor ColorWheel::getColorFromPoint(QPoint point){
    QPixmap pic = QWidget::grab();
    QImage img = pic.toImage();
    return QColor(img.pixel(point));
}

void ColorWheel::setActualColor(QColor col){
    actualRed = col.red();
    actualGreen = col.green();
    actualBlue = col.blue();
    update();
}

QColor ColorWheel::getColor(){
    QColor ret(actualRed, actualGreen, actualBlue);
    return ret;
}

void ColorWheel::setRed(int r){
    actualRed = r;
    repaint();
}

void ColorWheel::setGreen(int g){
    actualGreen = g;
    repaint();
}

void ColorWheel::setBlue(int b){
    actualBlue = b;
    repaint();
}

void ColorWheel::processHSV(QColor col){
    mHue = col.hslHue();
    mSaturation = col.saturation();
    mValue = col.value();
}

void ColorWheel::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
        if(primaryColorRect.contains(ev->pos())){
            QColor color = QColorDialog::getColor(QColor(actualRed, actualGreen, actualBlue));
            if(color.isValid()){
                actualRed = color.red();
                actualGreen = color.green();
                actualBlue = color.blue();
            }
            emit redChanged(actualRed);
            emit greenChanged(actualGreen);
            emit blueChanged(actualBlue);
            emit colorChanged(QColor(actualRed, actualGreen, actualBlue));
        }
        if(altColorRect.contains(ev->pos())){
            emit redChanged(altRed);
            emit greenChanged(altGreen);
            emit blueChanged(altBlue);
        }
        if(colorRangeTri.contains(ev->pos())){
            //set the color
            preciseColor = ev->pos();
            QColor newColor = getColorFromPoint(ev->pos());
            actualRed = newColor.red();
            actualGreen = newColor.green();
            actualBlue = newColor.blue();
            emit redChanged(actualRed);
            emit greenChanged(actualGreen);
            emit blueChanged(actualBlue);
            emit colorChanged(QColor(actualRed, actualGreen, actualBlue));
        }
        if(!mouseDown && !colorRangeTri.contains(ev->pos())) mouseDown = true;
        if(mouseDown){
            QPoint centerPoint(175, 100);
            QPoint dPoint = centerPoint - ev->pos();
            rotationAngle = atan2(dPoint.x(), dPoint.y());
            rotationAngle = rotationAngle * (180.0 / M_PI);
            processBaseMovePoint();
        }
    }
    if(ev->button() == Qt::RightButton){
        int swapRed = 0, swapGreen = 0, swapBlue = 0;
        swapRed = actualRed;
        swapGreen = actualGreen;
        swapBlue = actualBlue;
        actualRed = altRed;
        actualGreen = altGreen;
        actualBlue = altBlue;
        altRed = swapRed;
        altGreen = swapGreen;
        altBlue = swapBlue;
        emit redChanged(actualRed);
        emit greenChanged(actualGreen);
        emit blueChanged(actualBlue);
        emit colorChanged(QColor(actualRed, actualGreen, actualBlue));
    }
    if(ev->button() == Qt::MidButton){
        toggleAlt =! toggleAlt;
        if(toggleAlt){
            QColor newColor = getColorFromPoint(altBasePoint);
            primaryRed = newColor.red();
            primaryGreen = newColor.green();
            primaryBlue = newColor.blue();
            rotationAngle+= 180.0f;
        }else{
            QColor newColor = getColorFromPoint(primaryBasePoint);
            primaryRed = newColor.red();
            primaryGreen = newColor.green();
            primaryBlue = newColor.blue();
            rotationAngle+= 180.0f;
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
    QPoint pbp = QPoint(primaryBasePoint.x(), primaryBasePoint.y());
    QPoint abp = QPoint(altBasePoint.x(), altBasePoint.y());

    QLine line;
    line.setP1(QPoint(125,23));
    line.setP2(QPoint(125, 177));
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.translate(ctrPoint);
    painter.rotate(-rotationAngle);
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
    QColor primaryColor(primaryRed, primaryGreen, primaryBlue);
    QColor altColor(altRed, altGreen, altBlue);
    painter.setPen(Qt::black);
    painter.setBrush(altColor);
    painter.drawRect(altColorRect);
    QColor actualColor(actualRed, actualGreen, actualBlue);
    painter.setBrush(actualColor);
    painter.drawRect(primaryColorRect);

    QConicalGradient colorGrad;
    colorGrad.setCenter(centerRectPoint);
    colorGrad.setAngle(90);
    //colorGrad.setColorAt(0, Qt::white);
    colorGrad.setColorAt(0.0, primaryColor);
    colorGrad.setColorAt(0.40, Qt::black);
    colorGrad.setColorAt(0.60, Qt::white);
    colorGrad.setColorAt(1.0, primaryColor);

    painter.setBrush(colorGrad);
    painter.translate(centerRectPoint);
    painter.rotate(-rotationAngle);
    painter.translate(-centerRectPoint);
    painter.drawPath(colorRangeTri);
    painter.resetTransform();
    painter.end();
}

void ColorWheel::mouseMoveEvent(QMouseEvent *e){
    if(mouseDown){
        QPoint centerPoint(175, 100);
        QPoint dPoint = centerPoint - e->pos();
        rotationAngle = atan2(dPoint.x(), dPoint.y());
        rotationAngle = rotationAngle * (180.0 / M_PI);
        qDebug() << "Rotation Angle: " << rotationAngle << endl;
        processBaseMovePoint();

        //Adjust the primary color
        if(!toggleAlt){
            QColor color = getColorFromPoint(primaryBasePoint);
            primaryRed = color.red();
            primaryGreen = color.green();
            primaryBlue = color.blue();
        }else{
            QColor color = getColorFromPoint(altBasePoint);
            primaryRed = color.red();
            primaryGreen = color.green();
            primaryBlue = color.blue();
            rotationAngle += 180.0f;
        }
    }
    repaint();
}

void ColorWheel::mouseReleaseEvent(QMouseEvent *ev){
    Q_UNUSED(ev)
    if(mouseDown){
        mouseDown = false;
    }
}

void ColorWheel::processBaseMovePoint(){
    QTransform transform;
    QPoint ctrPoint(125, 100);
    primaryBasePoint = QPoint(125, 15);
    altBasePoint = QPoint(125, 185);
    transform.translate(ctrPoint.x(), ctrPoint.y());
    transform.rotate(-rotationAngle);
    transform.translate(-ctrPoint.x(), -ctrPoint.y());
    primaryBasePoint = transform.map(primaryBasePoint);
    altBasePoint = transform.map(altBasePoint);
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
    m_compositionMode->addItem("Multiply");

    m_layerManager = new QTreeWidget(this);
    m_layerManager->setSelectionMode(QTreeWidget::ExtendedSelection);
    m_layerManager->sortItems(0, Qt::DescendingOrder);
    m_layerManager->setDragEnabled(true);
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, "Background");
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    itm->setSelected(false);
    itm->setData(0, Qt::UserRole + 1, QVariant(m_layerCount));
    itm->setData(0, Qt::UserRole + 2, QVariant(0));
    itm->setData(0, Qt::UserRole + 3, QVariant(100));
    itm->setData(0, Qt::UserRole + 4, QVariant(0));
    itm->setSelected(true);
    itm->setCheckState(0, Qt::Checked);
    m_layerManager->addTopLevelItem(itm);

    QHBoxLayout* compLayout = new QHBoxLayout;
    compLayout->addWidget(m_compositionMode);
    compLayout->addWidget(m_layerOptionsBtn);

    QHBoxLayout* opacityLayout = new QHBoxLayout;
    opacityLayout->addWidget(m_opacityLbl);
    opacityLayout->addWidget(m_opacitySlider);
    opacityLayout->addWidget(m_opacitySpinbox);

    QVBoxLayout *layerLayout = new QVBoxLayout;
    layerLayout->addLayout(compLayout);
    layerLayout->addLayout(opacityLayout);
    layerLayout->addWidget(m_layerManager);

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
    m_layerManager->addTopLevelItem(itm);
}

void LayerDockWidget::addLayer(){
    m_layerCount++;
    QVariant layerCount(m_layerCount);
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, "Layer" + QString::number(m_layerCount));
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
    itm->setCheckState(0, Qt::Checked);
    itm->setData(0, Qt::UserRole + 1, QVariant(m_layerCount));
    itm->setData(0, Qt::UserRole + 2, QVariant(0));
    itm->setData(0, Qt::UserRole + 3, QVariant(100));
    itm->setData(0, Qt::UserRole + 4, QVariant(0));
    m_layerManager->addTopLevelItem(itm);
    m_layerManager->sortItems(0, Qt::DescendingOrder);
    emit layerAdded();
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

void LayerDockWidget::groupLayers(){
    QTreeWidgetItem* grpFolder = new QTreeWidgetItem(m_layerManager);
    for(int i = 0; i < m_layerManager->topLevelItemCount(); i++){
        QTreeWidgetItem* itm = m_layerManager->topLevelItem(i);
        if(itm->isSelected()){
            grpFolder->addChild(itm);
            m_layerManager->removeItemWidget(itm, 0);
        }
    }
    grpFolder->setText(0, "Group");
    grpFolder->setFlags(grpFolder->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    grpFolder->setExpanded(true);
    m_layerManager->addTopLevelItem(grpFolder);
    m_layerManager->sortItems(0, Qt::DescendingOrder);
}

void LayerDockWidget::ungroupLayers(){

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

void LayerDockWidget::setCompositionMode(int i){
    m_compositionMode->setCurrentIndex(i);
}

void LayerDockWidget::updateLayer(QTreeWidgetItem *itm, int i){
    Q_UNUSED(i);
    m_compositionMode->setCurrentIndex(itm->data(0, Qt::UserRole + 4).toInt());
    m_opacitySlider->setValue(itm->data(0, Qt::UserRole + 3).toInt());
    m_opacitySpinbox->setValue(itm->data(0, Qt::UserRole + 3).toInt());

    emit compositionModeChanged(itm->data(0, Qt::UserRole + 4).toInt());
    emit opacityChanged(itm->data(0, Qt::UserRole + 3).toInt());
    emit layerChanged(itm->data(i, Qt::UserRole + 1).toInt());
}

void LayerDockWidget::updateLayerInfo(QTreeWidgetItem *itm, int i){
    if(itm->checkState(i) == Qt::Unchecked || itm->checkState(i) == Qt::Checked){
        emit toggleLayerVisible(itm->data(i, Qt::UserRole +1).toInt());
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
    m_PointSB->setRange(0, 100);

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


