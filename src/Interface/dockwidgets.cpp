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
        mActualBrushList[0].SetStencil(mStencilWidget->GeneratePixmap());
        mTempBrushList = mActualBrushList;
        mGenBrushWidget->addBrush(mActualBrushList.at(0));
        mStencilWidget->updateStencilWidth(mTempBrushList.at(0).getSWidth());
        mStencilWidget->updateStencilHeight(mTempBrushList.at(0).getSHeight());
        qDebug() << "Generating new Library" << mBrushLib << endl;
    }else{
        //use loaded data
        mActualBrushList = loadBrushLib(mBrushLib);
        for(int i = 0; i < mActualBrushList.size(); i++){
            qDebug()<< mBrushLib <<"Loaded brush " << i << endl;
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
    qDebug() << "Stencil Width: " << mActualBrushList.at(mCurrentBrushIndex).getSWidth() << endl;
    qDebug() << "Stencil Height: " << mActualBrushList.at(mCurrentBrushIndex).getSHeight() << endl;
    qDebug() << "Hardness: " << mActualBrushList.at(mCurrentBrushIndex).getHardness() << endl;
    qDebug() << "Rotate: " << mActualBrushList.at(mCurrentBrushIndex).getRotate() << endl;
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

        qDebug() << "Wrote Brush to Disk" << endl;

        mActualBrushList.push_back(mTempBrushList.at(mCurrentBrushIndex));
        mGenBrushWidget->addBrush(mTempBrushList.at(mCurrentBrushIndex));
        mTempBrushList = mActualBrushList;
        break;
    }
    qDebug() << "Saving Brush" << endl;
}

void BrushDockWidget::saveBrushSetAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save brush library", mProjectPath, ".blib");
    saveBrushLib(filePath);
    qDebug() << "Saving Brush set" << endl;
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
    connect(mRSlider, SIGNAL(valueChanged(int)), SLOT(updateRed(int)));
    connect(mGSlider, SIGNAL(valueChanged(int)), SLOT(updateGreen(int)));
    connect(mBSlider, SIGNAL(valueChanged(int)), SLOT(updateBlue(int)));
    connect(mRSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateRed(QString)));
    connect(mGSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateGreen(QString)));
    connect(mBSpinBox, SIGNAL(valueChanged(QString)), SLOT(updateBlue(QString)));

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

}

void ColorDockWidget::updateHue(QString val){

}

void ColorDockWidget::updateSat(int val){

}

void ColorDockWidget::updateSat(QString val){

}

void ColorDockWidget::updateVal(int val){

}

void ColorDockWidget::updateVal(QString val){

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

/*

  BRUSH SHAPE WIDGET = Handles Adjusting the Brush Shape

*/

BrushShapeWidget::BrushShapeWidget(QWidget *parent) : QLabel(parent)
{
    brushPreviewPixmap = QPixmap(200, 200);
    brushPreviewPixmap.fill(Qt::transparent);
    this->setPixmap(brushPreviewPixmap);
    this->resize(brushPreviewPixmap.size());
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

LayerDockWidget::LayerDockWidget(QWidget *parent) : QDockWidget(parent)
{
    //initialize
    setWindowTitle("Layer");

    layerOptionsButton = new QToolButton(this);
    layerOptionsButton->setText("Options");

    compositionMode = new QComboBox(this);
    compositionMode->addItem("Normal");
    compositionMode->addItem("Multiply");

    layerManager = new QTreeWidget(this);

    QHBoxLayout* compLayout = new QHBoxLayout;
    compLayout->addWidget(compositionMode);
    compLayout->addWidget(layerOptionsButton);

    QVBoxLayout *layerLayout = new QVBoxLayout;
    layerLayout->addLayout(compLayout);
    layerLayout->addWidget(layerManager);

    QWidget *layerDisplay = new QWidget(this);
    layerDisplay->setLayout(layerLayout);
    setWidget(layerDisplay);
}

LayerDockWidget::~LayerDockWidget()
{

}

GeneralBrushWidget::GeneralBrushWidget(){
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
    mStrokePreview = QPixmap(175, 100);
    mStrokePreview.fill(Qt::gray);
    mStrokePreviewLabel = new QLabel(this);
    mStrokePreviewLabel->setPixmap(mStrokePreview);
    QVBoxLayout* vert1 = new QVBoxLayout;
    vert1->addWidget(mToolBtn);
    QHBoxLayout* horiz1 = new QHBoxLayout;
    horiz1->addWidget(mBrushIndex);
    horiz1->addLayout(vert1);
    QVBoxLayout* generalBrushLayout = new QVBoxLayout;
    generalBrushLayout->addLayout(horiz1);
    generalBrushLayout->addWidget(mStrokePreviewLabel);

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
}

void GeneralBrushWidget::updateName(QListWidgetItem *item){
    emit brushNameChanged(item->text());
}

void GeneralBrushWidget::addBrush(int iD, Brush brush){
    int temp = iD;
    Brush b = brush;
}

void GeneralBrushWidget::addBrush(Brush brush){
    QListWidgetItem* itm = new QListWidgetItem(brush.mName);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    mBrushIndex->addItem(itm);
}

void GeneralBrushWidget::updateStencil(QPixmap pixmap){
    int targetWidth = mStrokePreview.width();
    int targetHeight = mStrokePreview.height();
    int sourceWidth = pixmap.width();
    int sourceHeight = pixmap.height();
    if(sourceWidth > targetWidth, sourceHeight > targetHeight){
        pixmap = pixmap.scaled(mStrokePreview.size(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
        mStrokePreview = pixmap;
    }else{
        qDebug() << "Unable to load Pixmap" << endl;
    }
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

    QHBoxLayout* StencilPreviewLayout = new QHBoxLayout;
    StencilPreviewLayout->addWidget(mStencilLabel);
    StencilPreviewLayout->addWidget(mToolBtn);

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

QPixmap CustomBrushWidget::GeneratePixmap(){
    int stencilWidth = (mStencilPreview.width() * mWidthSlider->value()/10)/2;
    int stencilHeight = (mStencilPreview.height()* mHeightSlider->value()/10)/2;
    qreal hardness = 78 * ((qreal)mHardnessSlider->value()/100);
    QPoint midPoint(mStencilPreview.width()/2, mStencilPreview.height()/2);
    mStencilPreview.fill(Qt::transparent);
    QRadialGradient radGrad(midPoint, mStencilPreview.width()/2);
    radGrad.setColorAt(midPoint.x(), Qt::black);
    radGrad.setFocalRadius(hardness);
    QPainter p;
    p.begin(&mStencilPreview);
    p.setPen(Qt::NoPen);
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
        p.end();
        break;
    case SQUARE_SHAPE:
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
    qDebug() << "Generated pixmap "<< endl;
    return mStencilPreview;
}

void CustomBrushWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    int stencilWidth = (mStencilPreview.width() * mWidthSlider->value()/10)/2;
    int stencilHeight = (mStencilPreview.height()* mHeightSlider->value()/10)/2;
    qreal hardness = 78 * ((qreal)mHardnessSlider->value()/100);
    QPoint midPoint(mStencilPreview.width()/2, mStencilPreview.height()/2);
    mStencilPreview.fill(Qt::transparent);
    QRadialGradient radGrad(midPoint, mStencilPreview.width()/2);
    radGrad.setColorAt(midPoint.x(), Qt::black);
    radGrad.setFocalRadius(hardness);
    QPainter painter(&mStencilPreview);
    painter.setPen(Qt::NoPen);
    switch(mBrushShape){
        case CIRCLE_SHAPE:
            if(hasTexture){
                QBrush brush;
                brush.setTexture(mStencilTexture);
                painter.setBrush(brush);
            }else{
                painter.setBrush(radGrad);
            }
            painter.translate(midPoint);
            painter.rotate(mRotateSlider->value());
            painter.translate(-midPoint);
            painter.drawEllipse(midPoint, stencilWidth, stencilHeight);
            break;
        case SQUARE_SHAPE:
            int originX =  midPoint.x() - stencilWidth;
            int originY = midPoint.y() - stencilHeight;
            int dimX = stencilWidth*2;
            int dimY = stencilHeight*2;

            if(hasTexture){
                QBrush brush;
                brush.setTexture(mStencilTexture);
                painter.setBrush(brush);
            }else{
                painter.setBrush(Qt::black);
            }
            painter.translate(midPoint);
            painter.rotate(mRotateSlider->value());
            painter.translate(-midPoint);
            painter.drawRect(originX, originY, dimX, dimY);
            break;
    }
    mStencilLabel->setPixmap(mStencilPreview);
}

void CustomBrushWidget::updateBrushShape_Circle(){
    mBrushShape = CIRCLE_SHAPE;
    emit stencilChanged(this->GeneratePixmap());
}

void CustomBrushWidget::updateBrushShape_Square(){
    mBrushShape = SQUARE_SHAPE;
    emit stencilChanged(this->GeneratePixmap());
}

void CustomBrushWidget::updateBrushShape_Polygon(){
    mBrushShape = CUSTOM;
    emit stencilChanged(this->GeneratePixmap());
}

CustomBrushWidget::~CustomBrushWidget(){

}

ToolsPanel::ToolsPanel(QWidget* parent) : QDockWidget(parent){
    setWindowTitle("Tools");
    transTools = new TransformTools(this);
    defTools = new DefaultToolPanel(this);
    textPanel = new TextPanel(this);
    panelSpace = new QStackedWidget();
    panelSpace->addWidget(defTools);
    panelSpace->addWidget(transTools);
    panelSpace->addWidget(textPanel);
    panelSpace->setCurrentIndex(2);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(panelSpace);
    centralLayout->addSpacerItem(new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);
    setWidget(centralWidget);
    connect(transTools, SIGNAL(translateChanged(int,int)), SLOT(updateTranslate(int,int)));
    connect(transTools, SIGNAL(rotateChanged(int)), SLOT(updateRotate(int)));
    connect(transTools, SIGNAL(scaleChanged(int,int)), SLOT(updateScale(int,int)));
    connect(transTools, SIGNAL(transformModeChanged(int)), SLOT(updateTransformMode(int)));
    connect(transTools, SIGNAL(useWorldTransform(bool)), SLOT(updateWorldTransform(bool)));
}

ToolsPanel::~ToolsPanel(){

}

void ToolsPanel::setMode(int o){
    panelSpace->setCurrentIndex(o);
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
    m_TransXLbl = new QLabel("Translate X: ", this);
    m_TransXSB = new QSpinBox(this);
    QHBoxLayout* transXLayout = new QHBoxLayout;
    transXLayout->addWidget(m_TransXLbl);
    transXLayout->addWidget(m_TransXSB);

    m_TransYLbl = new QLabel("Translate Y: ", this);
    m_TransYSB = new QSpinBox(this);
    QHBoxLayout* transYLayout = new QHBoxLayout;
    transYLayout->addWidget(m_TransYLbl);
    transYLayout->addWidget(m_TransYSB);

    m_RotLbl = new QLabel("Rotate: ", this);
    m_RotSB = new QSpinBox(this);
    QHBoxLayout* rotXLayout = new QHBoxLayout;
    rotXLayout->addWidget(m_RotLbl);
    rotXLayout->addWidget(m_RotSB);

    //Hide Rotate
    m_RotLbl->hide();
    m_RotSB->hide();

    m_ScalXLbl = new QLabel("Scale X: ", this);
    m_ScalXSB = new QSpinBox(this);
    QHBoxLayout* scalXLayout = new QHBoxLayout;
    scalXLayout->addWidget(m_ScalXLbl);
    scalXLayout->addWidget(m_ScalXSB);

    m_ScalYLbl = new QLabel("Scale Y: ", this);
    m_ScalYSB = new QSpinBox(this);
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
}

void TransformTools::syncTransY(int v){
    if(m_Link4Trans){ m_TransYSB->setValue(v); }
}

void TransformTools::syncScalX(int v){
    if(m_Link4Scal){ m_ScalXSB->setValue(v); }
}

void TransformTools::syncScalY(int v){
    if(m_Link4Scal){ m_ScalYSB->setValue(v); }
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

    QHBoxLayout* centralLayout = new QHBoxLayout;
    centralLayout->addWidget(m_FontComboBox);
    centralLayout->addWidget(m_FontSizeSB);

    QGroupBox* grpBox = new QGroupBox(this);
    grpBox->setTitle("&Text");
    grpBox->setLayout(centralLayout);

    m_CommitButton = new QPushButton("&Commit", this);

    QVBoxLayout* finalLayout = new QVBoxLayout;
    finalLayout->addWidget(grpBox);
    finalLayout->addWidget(m_CommitButton);
    finalLayout->addSpacerItem(new QSpacerItem(25, 25, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    setLayout(finalLayout);

    connect(m_FontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(changeFont(QFont)));
    connect(m_FontSizeSB, SIGNAL(valueChanged(int)), SLOT(changeFontSize(int)));
    connect(m_CommitButton, SIGNAL(clicked()), SLOT(commitChanges()));
}

void TextPanel::changeFont(QFont font){
    m_Font = font;
    m_Font.setPointSize(m_FontSize);
    emit fontChanged(m_Font);
}

void TextPanel::changeFontSize(int s){
    m_FontSize = s;
    m_Font.setPointSize(m_FontSize);
    emit fontChanged(m_Font);
}

void TextPanel::commitChanges(){

}

TextPanel::~TextPanel(){

}
