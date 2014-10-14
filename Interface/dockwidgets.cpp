#include "dockwidgets.h"

BrushDockWidget::BrushDockWidget(QWidget *parent) : QDockWidget(parent)
{
    /*-Constructor-*/
    mTabWidget = new QTabWidget(this);
    mGenBrushWidget = new GeneralBrushWidget;
    mTransBrushWidget = new GeneralBrushWidget;
    mStencilWidget = new CustomBrushWidget;

    mActualBrushList = QVector<Brush>();
    mTempBrushList = QVector<Brush>();

    mCurrentBrushIndex = 0;

    ReadSettings();

    if(!QFile(mBrushLib).exists()){
        //generate default
        mActualBrushList.append(Brush());
        mActualBrushList[0].SetSWidth(10);
        mActualBrushList[0].SetSHeight(10);
        mActualBrushList[0].SetName("Default");
        mTempBrushList = mActualBrushList;
        mGenBrushWidget->AddBrush(mActualBrushList.at(0));
        mTransBrushWidget->AddBrush(mActualBrushList.at(0));
        mStencilWidget->UpdateStencilWidth(mTempBrushList.at(0).GetSWidth());
        mStencilWidget->UpdateStencilHeight(mTempBrushList.at(0).GetSHeight());
        qDebug() << "Generating new Library" << endl;
    }else{
        //use loaded data
        mActualBrushList = LoadBrushLib(mBrushLib);
        mTempBrushList = mActualBrushList;
    }

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
    mTransferSizeLE = new QLineEdit(this);
    mTransferSizeLE->setFixedWidth(32);
    mTransferSizeLE->setText(QString::number(0));
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
    mTransferOpacityLE = new QLineEdit(this);
    mTransferOpacityLE->setFixedWidth(32);
    mTransferOpacityLE->setText(QString::number(0));
    mTransferOpacityLE->setEnabled(false);
    QHBoxLayout* transferOpacityLayout = new QHBoxLayout;
    transferOpacityLayout->addWidget(mTransferOpacityToggle);
    transferOpacityLayout->addWidget(mTransferOpacitySlider);
    transferOpacityLayout->addWidget(mTransferOpacityLE);

    QVBoxLayout* transferParam = new QVBoxLayout;
    transferParam->addLayout(transferSizeLayout);
    transferParam->addLayout(transferOpacityLayout);

    /*-Brush_General-*/

    QVBoxLayout* GeneralBrushLayout = new QVBoxLayout;
    //GeneralBrushLayout->addLayout(GeneralBrushWidget);
    GeneralBrushLayout->addWidget(mGenBrushWidget);
    GeneralBrushLayout->addLayout(generalParam);

    QVBoxLayout* TransferBrushLayout = new QVBoxLayout;
    TransferBrushLayout->addWidget(mTransBrushWidget);
    TransferBrushLayout->addLayout(transferParam);

    QWidget* GeneralBrushTab = new QWidget(this);
    GeneralBrushTab->setLayout(GeneralBrushLayout);

    QWidget* TransferBrushTab = new QWidget(this);
    TransferBrushTab->setLayout(TransferBrushLayout);

    /*-Brush_Advanced-*/

    QVBoxLayout* AdvancedBrushLayout = new QVBoxLayout;
    AdvancedBrushLayout->addWidget(mStencilWidget);

    QWidget* AdvancedBrushTab = new QWidget(this);
    AdvancedBrushTab->setLayout(AdvancedBrushLayout);

    mTabWidget->addTab(GeneralBrushTab, "General");
    mTabWidget->addTab(TransferBrushTab, "Transfer");
    mTabWidget->addTab(AdvancedBrushTab, "Custom");

    mTabWidget->setTabPosition(QTabWidget::South);
    mTabWidget->setTabShape(QTabWidget::Rounded);

    setWidget(mTabWidget);
    this->setMinimumWidth(292);

    connect(mSizeSlider, SIGNAL(valueChanged(int)), SLOT(UpdateSize(int)));
    connect(mSizeLE, SIGNAL(valueChanged(QString)), SLOT(UpdateSize(QString)));
    connect(mOpacitySlider, SIGNAL(valueChanged(int)), SLOT(UpdateOpacity(int)));
    connect(mOpacityLE, SIGNAL(valueChanged(QString)), SLOT(UpdateOpacity(QString)));
    connect(mSpacingSlider, SIGNAL(valueChanged(int)), SLOT(UpdateSpacing(int)));
    connect(mSpacingLE, SIGNAL(valueChanged(QString)), SLOT(UpdateSpacing(QString)));
    connect(mTransferSizeToggle, SIGNAL(toggled(bool)), SLOT(ToggleTransferSize(bool)));
    connect(mTransferSizeSlider, SIGNAL(valueChanged(int)), SLOT(UpdateTransferSize(int)));
    connect(mTransferSizeLE, SIGNAL(textChanged(QString)), SLOT(UpdateTransferSize(QString)));
    connect(mTransferOpacityToggle, SIGNAL(toggled(bool)), SLOT(ToggleTransferOpacity(bool)));
    connect(mTransferOpacitySlider, SIGNAL(valueChanged(int)), SLOT(UpdateTransferOpacity(int)));
    connect(mTransferOpacityLE, SIGNAL(textChanged(QString)), SLOT(UpdateTransferOpacity(QString)));
    connect(mStencilWidget, SIGNAL(StencilChanged(QPixmap)), SLOT(UpdateStencil(QPixmap)));
    connect(mStencilWidget, SIGNAL(StencilChanged(QPixmap)), mGenBrushWidget, SLOT(UpdateStencil(QPixmap)));
    connect(mStencilWidget, SIGNAL(StencilChanged(QPixmap)), mTransBrushWidget, SLOT(UpdateStencil(QPixmap)));
    connect(mStencilWidget, SIGNAL(StencilPathChanged(QString)), SLOT(UpdateStencilPath(QString)));
    connect(mGenBrushWidget, SIGNAL(LoadStencilTriggered()), SLOT(LoadStencilAct()));
    connect(mGenBrushWidget, SIGNAL(LoadBrushTriggered()), SLOT(LoadBrushAct()));
    connect(mGenBrushWidget, SIGNAL(LoadBrushSetTriggered()), SLOT(LoadBrushSetAct()));
    connect(mGenBrushWidget, SIGNAL(SaveStencilTriggered()), SLOT(SaveStencilAct()));
    connect(mGenBrushWidget, SIGNAL(SaveBrushTriggered()), SLOT(SaveBrushAct()));
    connect(mGenBrushWidget, SIGNAL(SaveBrushSetTriggered()), SLOT(SaveBrushSetAct()));
    connect(mTransBrushWidget, SIGNAL(LoadStencilTriggered()), SLOT(LoadStencilAct()));
    connect(mTransBrushWidget, SIGNAL(LoadBrushTriggered()), SLOT(LoadBrushAct()));
    connect(mTransBrushWidget, SIGNAL(LoadBrushSetTriggered()), SLOT(LoadBrushSetAct()));
    connect(mTransBrushWidget, SIGNAL(SaveStencilTriggered()), SLOT(SaveStencilAct()));
    connect(mTransBrushWidget, SIGNAL(SaveBrushTriggered()), SLOT(SaveBrushAct()));
    connect(mTransBrushWidget, SIGNAL(SaveBrushSetTriggered()), SLOT(SaveBrushSetAct()));
    connect(mStencilWidget, SIGNAL(LoadStencilTriggered()), SLOT(LoadStencilAct()));
    connect(mStencilWidget, SIGNAL(LoadBrushTriggered()), SLOT(LoadBrushAct()));
    connect(mStencilWidget, SIGNAL(LoadBrushSetTriggered()), SLOT(LoadBrushSetAct()));
    connect(mStencilWidget, SIGNAL(SaveStencilTriggered()), SLOT(SaveStencilAct()));
    connect(mStencilWidget, SIGNAL(SaveBrushTriggered()), SLOT(SaveBrushAct()));
    connect(mStencilWidget, SIGNAL(SaveBrushSetTriggered()), SLOT(SaveBrushSetAct()));
    connect(mGenBrushWidget, SIGNAL(BrushLibIndexChanged(int)), SLOT(SetCurrentIndex(int)));
    connect(mGenBrushWidget, SIGNAL(BrushLibIndexChanged(int)), SLOT(SetCurrentIndex(int)));
}

void BrushDockWidget::SetDirectory(QString dir){
    mProjectPath = dir;
    mGenBrushWidget->SetDir(dir);
    mTransBrushWidget->SetDir(dir);
    mStencilWidget->SetDir(dir);
}

void BrushDockWidget::UpdateSize(int val)
{
    mSizeLE->setValue(val);
    emit BrushSizeChanged(val);
}

void BrushDockWidget::UpdateSize(QString val)
{
    mSizeSlider->setValue(val.toInt());
    emit BrushSizeChanged(val.toInt());
}

void BrushDockWidget::UpdateOpacity(int val)
{
    mOpacityLE->setValue(val);
    emit BrushOpacityChanged(val);
}

void BrushDockWidget::UpdateOpacity(QString val)
{
    mOpacitySlider->setValue(val.toInt());
    emit BrushOpacityChanged(val.toInt());
}

void BrushDockWidget::UpdateSpacing(int val){
    mSpacingLE->setValue(val);
    emit BrushSpacingChanged(val);
}

void BrushDockWidget::UpdateSpacing(QString val){
    mSpacingSlider->setValue(val.toInt());
    emit BrushSpacingChanged(val.toInt());
}

void BrushDockWidget::UpdateTransferSize(int val)
{
    mTransferSizeLE->setText(QString::number(val));
    emit BrushTransferSizeChanged(val);
}

void BrushDockWidget::UpdateTransferSize(QString val)
{
    mTransferSizeSlider->setValue(val.toInt());
    emit BrushTransferSizeChanged(val.toInt());
}

void BrushDockWidget::UpdateTransferOpacity(int val)
{
    mTransferOpacityLE->setText(QString::number(val));
    emit BrushTransferOpacityChanged(val);
}

void BrushDockWidget::UpdateTransferOpacity(QString val)
{
    mTransferOpacitySlider->setValue(val.toInt());
    emit BrushTransferOpacityChanged(val.toInt());
}

void BrushDockWidget::ToggleTransferSize(bool val)
{
    mTransferSizeSlider->setEnabled(val);
    mTransferSizeLE->setEnabled(val);
    if(val == false){
        emit BrushTransferSizeChanged(0);
    }
}

void BrushDockWidget::ToggleTransferOpacity(bool val)
{
    mTransferOpacitySlider->setEnabled(val);
    mTransferOpacityLE->setEnabled(val);
    if(val == false){
        emit BrushTransferOpacityChanged(0);
    }
}

void BrushDockWidget::UpdateStencil(QPixmap pixmap){
    emit BrushStencilChanged(pixmap);
}

void BrushDockWidget::UpdateStencilPath(QString filePath){
    emit BrushStencilPathChanged(filePath);
}

void BrushDockWidget::SetCurrentIndex(int val){
    mCurrentBrushIndex = val;
    mStencilWidget->UpdateStencilWidth(mActualBrushList.at(mCurrentBrushIndex).GetSWidth());
    mStencilWidget->UpdateStencilHeight(mActualBrushList.at(mCurrentBrushIndex).GetSHeight());
    mStencilWidget->UpdateBrushHardness(mActualBrushList.at(mCurrentBrushIndex).getHardness());
    mStencilWidget->UpdateStencilRotate(mActualBrushList.at(mCurrentBrushIndex).getRotate());
}

void BrushDockWidget::LoadStencilAct(){
    qDebug()<<"Loading Stencil" << endl;
    QString filePath = QFileDialog::getOpenFileName(this, "Open Stencil", QDir::currentPath());
    QPixmap pixmap;
    pixmap.load(filePath);
    mStencilWidget->UpdateStencil(pixmap);
}

void BrushDockWidget::LoadBrushAct(){
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush", mProjectPath, ".brsh");
    Brush temp = LoadBrush(filePath);
    mTempBrushList.append(temp);
    mActualBrushList.append(temp);
    mGenBrushWidget->AddBrush(temp);
    mTransBrushWidget->AddBrush(temp);
    qDebug()<<"Loading Brush" << endl;
}

void BrushDockWidget::LoadBrushSetAct(){
    QString filePath = QFileDialog::getOpenFileName(this, "Open Brush Library", mProjectPath, "*.blib");

    QMessageBox msgBox;
    msgBox.setText("Would you like to Load a new brush set or add to existing?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, "Load new set");
    msgBox.setButtonText(QMessageBox::Cancel, "Add to existing set");
    switch(msgBox.exec()){
    case QMessageBox::Ok:                       //Replaces Existing
       mActualBrushList = LoadBrushLib(filePath);
       mBrushLib = filePath;
        break;
    case QMessageBox::Cancel:                   //Appends to brush set
        QVector<Brush> temp = LoadBrushLib(filePath);
        mActualBrushList = mActualBrushList + temp;
        break;
    defualt:
        break;
    }

    qDebug()<<"Loading Brush Set" << endl;
}

void BrushDockWidget::SaveStencilAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save Stencil",QDir::currentPath());
    QPixmap pixmap = mStencilWidget->GetPixmap();
    pixmap.save(filePath);

    qDebug() << "Saving Stencil" << endl;
}

void BrushDockWidget::SaveBrushAct(){
    QMessageBox msgBox;
    msgBox.setText("Save just to library or to External Location?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok, "Save to library");
    msgBox.setButtonText(QMessageBox::Cancel, "Save to library and external");
    switch(msgBox.exec()){
    case QMessageBox::Ok:
        mActualBrushList.append(mTempBrushList.at(mCurrentBrushIndex));
        mGenBrushWidget->AddBrush(mTempBrushList.at(mCurrentBrushIndex));
        mTransBrushWidget->AddBrush(mTempBrushList.at(mCurrentBrushIndex));
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
        out << encrypt << ret;

        file.flush();
        file.close();

        qDebug() << "Wrote Brush to Disk" << endl;

        mActualBrushList.append(mTempBrushList.at(mCurrentBrushIndex));
        mGenBrushWidget->AddBrush(mTempBrushList.at(mCurrentBrushIndex));
        mTransBrushWidget->AddBrush(mTempBrushList.at(mCurrentBrushIndex));
        break;
    }
    qDebug() << "Saving Brush" << endl;
}

void BrushDockWidget::SaveBrushSetAct(){
    QString filePath = QFileDialog::getSaveFileName(this, "Save brush library", mProjectPath, ".blib");
    SaveBrushLib(filePath);
    qDebug() << "Saving Brush set" << endl;
}

QVector<Brush> BrushDockWidget::LoadBrushLib(QString filePath){
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

void BrushDockWidget::SaveBrushLib(QString filePath){
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

Brush BrushDockWidget::LoadBrush(QString filePath){
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

void BrushDockWidget::DeleteBrushAct(){

}

void BrushDockWidget::resizeEvent(QResizeEvent *e){

}

void BrushDockWidget::ReadSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    mProjectPath = settings.value("projectPath").toString();
    mBrushLib = settings.value("activeBrushLib").toString();
}

void BrushDockWidget::WriteSettings(){
    QSettings settings("SwingInnovations", "Odessa");
    settings.setValue("activeBrushLib", mBrushLib);
    qDebug() << mProjectPath <<"default.blib" << endl;
    SaveBrushLib(mProjectPath+"default.blib");
}

BrushDockWidget::~BrushDockWidget()
{
    WriteSettings();
}

ColorDockWidget::ColorDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Color");

    colorModeTab = new QTabWidget(this);

    //RGB
    m_RLabel = new QLabel(this);
    m_RLabel->setText("R");
    m_RSlider = new QSlider(this);
    m_RSlider->setOrientation(Qt::Horizontal);
    m_RSlider->setRange(0, 255);
    m_RLineEdit = new QLineEdit(this);
    m_RLineEdit->setFixedWidth(32);
    RLayout = new QHBoxLayout;
    RLayout->addWidget(m_RLabel);
    RLayout->addWidget(m_RSlider);
    RLayout->addWidget(m_RLineEdit);

    m_GLabel = new QLabel(this);
    m_GLabel->setText("G");
    m_GSlider = new QSlider(this);
    m_GSlider->setOrientation(Qt::Horizontal);
    m_GSlider->setRange(0, 255);
    m_GLineEdit = new QLineEdit(this);
    m_GLineEdit->setFixedWidth(32);
    GLayout = new QHBoxLayout;
    GLayout->addWidget(m_GLabel);
    GLayout->addWidget(m_GSlider);
    GLayout->addWidget(m_GLineEdit);

    m_BLabel = new QLabel(this);
    m_BLabel->setText("B");
    m_BSlider = new QSlider(this);
    m_BSlider->setOrientation(Qt::Horizontal);
    m_BSlider->setRange(0, 255);
    m_BLineEdit = new QLineEdit(this);
    m_BLineEdit->setFixedWidth(32);
    BLayout = new QHBoxLayout;
    BLayout->addWidget(m_BLabel);
    BLayout->addWidget(m_BSlider);
    BLayout->addWidget(m_BLineEdit);

    masterRGBLayout = new QVBoxLayout;
    masterRGBLayout->addLayout(RLayout);
    masterRGBLayout->addLayout(GLayout);
    masterRGBLayout->addLayout(BLayout);

    QWidget* RGBPanel = new QWidget(this);
    RGBPanel->setLayout(masterRGBLayout);

    colorModeTab->addTab(RGBPanel, "RGB");

    m_HLabel = new QLabel(this);
    m_HLabel->setText("Hue:");
    m_HSlider = new QSlider(this);
    m_HSlider->setOrientation(Qt::Horizontal);
    m_HSlider->setRange(0, 255);
    m_HLineEdit = new QLineEdit(this);
    m_HLineEdit->setFixedWidth(32);
    HLayout = new QHBoxLayout;
    HLayout->addWidget(m_HLabel);
    HLayout->addWidget(m_HSlider);
    HLayout->addWidget(m_HLineEdit);

    m_SLabel = new QLabel(this);
    m_SLabel->setText("Sat:");
    m_SSLider = new QSlider(this);
    m_SSLider->setOrientation(Qt::Horizontal);
    m_SSLider->setRange(0, 255);
    m_SLineEdit = new QLineEdit(this);
    m_SLineEdit->setFixedWidth(32);
    SLayout = new QHBoxLayout;
    SLayout->addWidget(m_SLabel);
    SLayout->addWidget(m_SSLider);
    SLayout->addWidget(m_SLineEdit);

    m_VLabel = new QLabel(this);
    m_VLabel->setText("Val.");
    m_VSlider = new QSlider(this);
    m_VSlider->setOrientation(Qt::Horizontal);
    m_VSlider->setRange(0, 255);
    m_VLineEdit = new QLineEdit;
    m_VLineEdit->setFixedWidth(32);
    VLayout = new QHBoxLayout;
    VLayout->addWidget(m_VLabel);
    VLayout->addWidget(m_VSlider);
    VLayout->addWidget(m_VLineEdit);

    masterHSVLayout = new QVBoxLayout;
    masterHSVLayout->addLayout(HLayout);
    masterHSVLayout->addLayout(SLayout);
    masterHSVLayout->addLayout(VLayout);

    QWidget* HSVPanel = new QWidget(this);
    HSVPanel->setLayout(masterHSVLayout);
    colorModeTab->addTab(HSVPanel, "HSV");

    colorWheelPixmap = QPixmap(200, 200);
    colorWheelPixmap.fill(QColor(Qt::gray));

    colorWheel = new ColorWheelWidget(this);
    colorWheel->setPixmap(colorWheelPixmap);

    QHBoxLayout* colorDisplayLt = new QHBoxLayout;
    colorDisplayLt->setAlignment(Qt::AlignCenter);
    colorDisplayLt->addWidget(colorWheel);

    m_ColorWheelContainer = new QGroupBox(this);
    m_ColorWheelContainer->setTitle("Color Wheel");
    m_ColorWheelContainer->setLayout(colorDisplayLt);

    QVBoxLayout* masterColorLayout = new QVBoxLayout;
    masterColorLayout->addWidget(m_ColorWheelContainer);
    masterColorLayout->addWidget(colorModeTab);

    QWidget* masterColorWidget = new QWidget(this);
    masterColorWidget->setLayout(masterColorLayout);

    connect(colorWheel, SIGNAL(redChanged(int)), SLOT(setRed(int)));
    connect(colorWheel, SIGNAL(greenChanged(int)), SLOT(setGreen(int)));
    connect(colorWheel, SIGNAL(blueChanged(int)), SLOT(setBlue(int)));
    connect(colorWheel, SIGNAL(actualRedChanged(int)), SLOT(set_RLE(int)));
    connect(colorWheel, SIGNAL(actualGreenChanged(int)), SLOT(set_GLE(int)));
    connect(colorWheel, SIGNAL(actualBlueChanged(int)), SLOT(set_BLE(int)));
    connect(colorWheel, SIGNAL(actualColorPoint(QPoint)), SLOT(setActualColorPos(QPoint)));
    connect(colorWheel, SIGNAL(colorChanged(QColor)), SLOT(setActualColor(QColor)));
    connect(m_RSlider, SIGNAL(valueChanged(int)), SLOT(set_RLE(int)));
    connect(m_RLineEdit, SIGNAL(textChanged(QString)), SLOT(set_RSlider(QString)));
    connect(m_GSlider, SIGNAL(valueChanged(int)), SLOT(set_GLE(int)));
    connect(m_GLineEdit, SIGNAL(textChanged(QString)), SLOT(set_GSlider(QString)));
    connect(m_BSlider, SIGNAL(valueChanged(int)), SLOT(set_BLE(int)));
    connect(m_BLineEdit, SIGNAL(textChanged(QString)), SLOT(set_BSlider(QString)));
    connect(m_HSlider, SIGNAL(valueChanged(int)), SLOT(set_HLE(int)));
    connect(m_HLineEdit, SIGNAL(textChanged(QString)), SLOT(set_HSlider(QString)));
    connect(m_SSLider, SIGNAL(valueChanged(int)), SLOT(set_SLE(int)));
    connect(m_SLineEdit, SIGNAL(textChanged(QString)), SLOT(set_SSlider(QString)));
    connect(m_VSlider, SIGNAL(valueChanged(int)), SLOT(set_VLE(int)));
    connect(m_VLineEdit, SIGNAL(textChanged(QString)), SLOT(set_VSlider(QString)));  

    setWidget(masterColorWidget);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void ColorDockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(&colorWheelPixmap);
    //Start Color wheel
    QConicalGradient grad;
    grad.setCenter(100, 100);
    grad.setColorAt(0, Qt::green);
    grad.setColorAt(0.175, QColor(Qt::yellow));
    grad.setColorAt(0.35, QColor(Qt::red));
    grad.setColorAt(0.525, QColor(Qt::magenta));
    grad.setColorAt(0.65, QColor(Qt::blue));
    grad.setColorAt(0.8253, QColor(Qt::cyan));
    grad.setColorAt(1, QColor(Qt::green));
    painter.setBrush(grad);
    painter.drawEllipse(0, 0, 200, 200);

    painter.setBrush(Qt::gray);
    painter.drawEllipse(50, 50, 100, 100);

    //handle drawing
    primaryColorPos = QPoint(175, 100);
    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(QColor(Qt::black));
    painter.drawEllipse(primaryColorPos, 10, 10);

    complementColorPos = QPoint(25, 100);
    painter.setBrush(QBrush(Qt::transparent));
    painter.setPen(QColor(Qt::gray));
    painter.drawEllipse(complementColorPos, 10, 10);

    QColor primaryColor(red, green, blue, 255);

    //central painting wheel
    QConicalGradient colorGrad;
    colorGrad.setCenter(100, 100);
    colorGrad.setColorAt(0, primaryColor);
    colorGrad.setColorAt(0.25, Qt::white);
    colorGrad.setColorAt(0.75, Qt::black);
    colorGrad.setColorAt(1, primaryColor);
    colorGrad.setAngle(45);

    painter.setBrush(colorGrad);
    painter.setPen(QColor(Qt::black));

    refineColorRect = QRect(65, 65, 70, 70);
    painter.translate(100, -40);
    painter.rotate(45);
    painter.drawRect(refineColorRect);

    colorWheel->setRefineRect(refineColorRect);

    painter.resetTransform();

    painter.setBrush(Qt::transparent);
    painter.setPen(Qt::black);
    painter.drawPoint(actualColorPos);
    painter.drawEllipse(actualColorPos, 5, 5);

    //primary Color preview
    painter.setBrush(QColor(actualRed, actualGreen, actualBlue, 255));
    painter.drawRect(0, 175, 25, 25);

    colorWheel->setPixmap(colorWheelPixmap);

}

ColorDockWidget::~ColorDockWidget()
{

}

void ColorDockWidget::setActualColor(QColor color)
{
    actualRed = color.red();
    actualGreen = color.green();
    actualBlue = color.blue();
}

void ColorDockWidget::setActualColorPos(QPoint point)
{
    actualColorPos = point;
}


void ColorDockWidget::set_RLE(int val)
{
    m_RLineEdit->setText(QString::number(val));
    emit redChanged(val);
}

void ColorDockWidget::set_RSlider(QString val)
{
    m_RSlider->setValue(val.toInt());
    emit redChanged(val.toInt());
}

void ColorDockWidget::set_GLE(int val)
{
    m_GLineEdit->setText(QString::number(val));
    emit greenChanged(val);
}

void ColorDockWidget::set_GSlider(QString val)
{
    m_GSlider->setValue(val.toInt());
    emit greenChanged(val.toInt());
}

void ColorDockWidget::set_BLE(int val)
{
    m_BLineEdit->setText(QString::number(val));
    emit blueChanged(val);

}

void ColorDockWidget::set_BSlider(QString val)
{
    m_BSlider->setValue(val.toInt());
    emit blueChanged(val.toInt());
}

void ColorDockWidget::set_HLE(int val)
{
    m_HLineEdit->setText(QString::number(val));
    emit hueChanged(val);
}

void ColorDockWidget::set_HSlider(QString val)
{
    m_HSlider->setValue(val.toInt());
    emit hueChanged(val.toInt());
}

void ColorDockWidget::set_SLE(int val)
{
    m_SLineEdit->setText(QString::number(val));
    emit saturationChanged(val);
}

void ColorDockWidget::set_SSlider(QString val)
{
    m_SSLider->setValue(val.toInt());
    emit saturationChanged(val.toInt());
}

void ColorDockWidget::set_VLE(int val)
{
    m_VLineEdit->setText(QString::number(val));
    emit valueChanged(val);
}

void ColorDockWidget::set_VSlider(QString val)
{
    m_VSlider->setValue(val.toInt());
    emit valueChanged(val.toInt());
}

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
    QPainter painter(&brushPreviewPixmap);
    painter.drawEllipse(0, 0, 20, 20);
}

void BrushShapeWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void BrushShapeWidget::mousePressEvent(QMouseEvent *event)
{

}

/*

  COLOR WHEEL WIDGET = Handles additional input

*/
ColorWheelWidget::ColorWheelWidget(QWidget *parent) : QLabel(parent)
{

}

ColorWheelWidget::~ColorWheelWidget()
{

}

void ColorWheelWidget::mousePressEvent(QMouseEvent *event)
{
        QPixmap pix = QWidget::grab();
        QImage img = pix.toImage();
        QColor color(img.pixel(event->pos()));
        if(!refineColorRect.contains(event->pos()))
        {
            emit redChanged(color.red());
            emit greenChanged(color.green());
            emit blueChanged(color.blue());
        }

        if(refineColorRect.contains(event->pos()))
        {
            //draw the circle
            emit colorChanged(color);
            emit actualColorPoint(event->pos());
            emit actualRedChanged(color.red());
            emit actualGreenChanged(color.green());
            emit actualBlueChanged(color.blue());
        }
        qDebug() << "Color Should Change" << endl;
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

    layerManager = new QListWidget(this);

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
    connect(mLoadStencilAct, SIGNAL(triggered()), SLOT(UpdateLoadStencil()));
    connect(mLoadBrushAct, SIGNAL(triggered()), SLOT(UpdateLoadBrush()));
    connect(mLoadBrushSetAct, SIGNAL(triggered()), SLOT(UpdateLoadBrushSet()));
    connect(mSaveStencilAct, SIGNAL(triggered()), SLOT(UpdateSaveStencil()));
    connect(mSaveBrushAct, SIGNAL(triggered()), SLOT(UpdateSaveBrush()));
    connect(mSaveBrushSetAct, SIGNAL(triggered()), SLOT(UpdateSaveBrushSet()));
    connect(mDeleteBrushAct, SIGNAL(triggered()), SLOT(UpdateDeleteBrush()));
    connect(mBrushIndex, SIGNAL(currentRowChanged(int)), SLOT(UpdateBrushLibIndex(int)));
}

void GeneralBrushWidget::AddBrush(int iD, Brush brush){

}

void GeneralBrushWidget::AddBrush(Brush brush){
    mBrushIndex->addItem(brush.mName);
}

void GeneralBrushWidget::UpdateStencil(QPixmap pixmap){
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

    connect(mLoadStencilAct, SIGNAL(triggered()), SLOT(UpdateLoadStencil()));
    connect(mLoadBrushAct, SIGNAL(triggered()), SLOT(UpdateLoadBrush()));
    connect(mLoadBrushSetAct, SIGNAL(triggered()), SLOT(UpdateLoadBrushSet()));
    connect(mSaveStencilAct, SIGNAL(triggered()), SLOT(UpdateSaveStencil()));
    connect(mSaveBrushAct, SIGNAL(triggered()), SLOT(UpdateSaveBrush()));
    connect(mSaveBrushSetAct, SIGNAL(triggered()), SLOT(UpdateSaveBrushSet()));
    connect(mDeleteBrushAct, SIGNAL(triggered()), SLOT(UpdateDeleteBrush()));
    connect(mWidthLE, SIGNAL(textChanged(QString)), SLOT(UpdateStencilWidth(QString)));
    connect(mWidthSlider, SIGNAL(valueChanged(int)), SLOT(UpdateStencilWidth(int)));
    connect(mHeightLE, SIGNAL(textChanged(QString)), SLOT(UpdateStencilHeight(QString)));
    connect(mHeightSlider, SIGNAL(valueChanged(int)), SLOT(UpdateStencilHeight(int)));
    connect(mHeightLE, SIGNAL(textChanged(QString)), SLOT(UpdateStencilHeight(QString)));
    connect(mHardnessSlider, SIGNAL(valueChanged(int)), SLOT(UpdateBrushHardness(int)));
    connect(mHardnessLE, SIGNAL(textChanged(QString)), SLOT(UpdateBrushHardness(QString)));
    connect(mRotateSlider, SIGNAL(valueChanged(int)), SLOT(UpdateStencilRotate(int)));
    connect(mRotateLE, SIGNAL(textChanged(QString)), SLOT(UpdateStencilRotate(QString)));
    connect(this, SIGNAL(StencilChanged(QPixmap)), SLOT(UpdateStencil(QPixmap)));
    connect(mCircleButton, SIGNAL(clicked()), SLOT(UpdateBrushShape_Circle()));
    connect(mSquareButton, SIGNAL(clicked()), SLOT(UpdateBrushShape_Square()));
    connect(mCustomButton, SIGNAL(clicked()), SLOT(UpdateBrushShape_Polygon()));
    connect(mTextureBtn, SIGNAL(clicked()), SLOT(UpdateStencilTexture()));
    connect(mTextureFileLE, SIGNAL(textChanged(QString)), SLOT(UpdateStencilTextureLE(QString)));
}

void CustomBrushWidget::TempSave(QPixmap pixmap){
    QImage image = pixmap.toImage();
    image.convertToFormat(QImage::Format_RGB888, Qt::AutoColor);
    if(tempFile.open()){
        image.save(tempFile.fileName());
    }
    tempFile.close();
    emit StencilPathChanged(tempFile.fileName());
}

void CustomBrushWidget::UpdateStencil(QPixmap pixmap){
    TempSave(pixmap);
}

void CustomBrushWidget::UpdateStencilTexture(){
    hasTexture = true;
    QString fileName = QFileDialog::getOpenFileName(this, "Load Texture", QDir::currentPath());
    mStencilTexture.load(fileName);
    QImage image = mStencilTexture.toImage();
    QRgb col;
    int gray;
    int width = mStencilTexture.width();
    int height = mStencilTexture.height();
    for(unsigned int i = 0; i < width; i++){
        for(unsigned int j = 0; j < height; j++){
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    mStencilTexture = mStencilTexture.fromImage(image);
    mStencilTexture = mStencilTexture.scaled(mStencilPreview.width(), mStencilPreview.height(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
    mTextureFileLE->setText(fileName);
}

void CustomBrushWidget::UpdateStencilWidth(int val){
   mWidthLE->setText(QString::number(val));
   emit StencilWidthChanged(val);
   emit StencilChanged(mStencilPreview);
}

void CustomBrushWidget::UpdateStencilWidth(QString val){
    mWidthSlider->setValue(val.toInt());
    emit StencilWidthChanged(val.toInt());
}

void CustomBrushWidget::UpdateStencilHeight(int val){
    mHeightLE->setText(QString::number(val));
    emit StencilHeightChanged(val);
    emit StencilChanged(mStencilPreview);
}

void CustomBrushWidget::UpdateStencilHeight(QString val){
    mHeightSlider->setValue(val.toInt());
    emit StencilHeightChanged(val.toInt());
}

void CustomBrushWidget::UpdateBrushHardness(int val){
    mHardnessLE->setText(QString::number(val));
    emit BrushHardnessChanged(val);
    emit StencilChanged(mStencilPreview);
}

void CustomBrushWidget::UpdateBrushHardness(QString val){
    mHardnessSlider->setValue(val.toInt());
    emit BrushHardnessChanged(val.toInt());
}

void CustomBrushWidget::UpdateStencilRotate(int val){
    if(val > 360){
        val = 0;
        mRotateSlider->setValue(0);
    }
    mRotateLE->setText(QString::number(val));
    emit RotateChanged(val);
    emit StencilChanged(mStencilPreview);
}

void CustomBrushWidget::UpdateStencilRotate(QString val){
    if(val.toInt() > 360){
        mRotateSlider->setValue(0);
        emit RotateChanged(0);
    }else{
        mRotateSlider->setValue(val.toInt());
        emit RotateChanged(val.toInt());
    }
}

void CustomBrushWidget::UpdateStencilTextureLE(QString val){
    if(val.isEmpty()){
        hasTexture = false;
    }else{
        hasTexture = true;
    }
}

void CustomBrushWidget::paintEvent(QPaintEvent *event){

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

        painter.drawRect(originX, originY, dimX, dimY);
        break;
    }
    mStencilLabel->setPixmap(mStencilPreview);
}

void CustomBrushWidget::UpdateBrushShape_Circle(){
    mBrushShape = CIRCLE_SHAPE;
}

void CustomBrushWidget::UpdateBrushShape_Square(){
    mBrushShape = SQUARE_SHAPE;
}

void CustomBrushWidget::UpdateBrushShape_Polygon(){
    mBrushShape = CUSTOM;
}

CustomBrushWidget::~CustomBrushWidget(){

}
