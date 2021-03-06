#include "dialogwindows.h"

OdessaNewDocDialog::OdessaNewDocDialog()
{
    //initialize a few things
    setWindowTitle("New Canvas");
    setModal(true);

    parameterInfo = "Create a standard image. <br> Width - Image's width in pixels.<br> Height - Image's height in pixels. <br> DPI - The Images DPI";

    m_TypeComboBox = new QComboBox(this);
    m_TypeComboBox->addItem("Image");
    m_TypeComboBox->addItem("SpriteSheet");
    m_TypeComboBox->addItem("Animation");

    m_CanvasSizeComboBox = new QComboBox(this);
    m_CanvasSizeComboBox->addItem("800 x 600");
    m_CanvasSizeComboBox->addItem("1280 x 720");
    m_CanvasSizeComboBox->addItem("1920 x 1080");

    m_WidthLabel = new QLabel("Width: ",this);
    m_WidthLE = new QLineEdit(this);
    m_WidthLE->setFixedWidth(48);
    m_WidthLE->setText("800");
    QHBoxLayout* widthLayout = new QHBoxLayout;
    widthLayout->addWidget(m_WidthLabel);
    widthLayout->addWidget(m_WidthLE);

    m_HeightLabel = new QLabel("Height: ", this);
    m_HeightLE = new QLineEdit(this);
    m_HeightLE->setFixedWidth(48);
    m_HeightLE->setText("600");
    QHBoxLayout* heightLayout = new QHBoxLayout;
    heightLayout->addWidget(m_HeightLabel);
    heightLayout->addWidget(m_HeightLE);

    m_DPILabel = new QLabel("DPI: ", this);
    m_DPILE = new QLineEdit(this);
    m_DPILE->setFixedWidth(48);
    QHBoxLayout* dpiLayout = new QHBoxLayout;
    dpiLayout->addWidget(m_DPILabel);
    dpiLayout->addWidget(m_DPILE);

    QVBoxLayout* essentialLayout = new QVBoxLayout;
    essentialLayout->addWidget(m_CanvasSizeComboBox);
    essentialLayout->addLayout(widthLayout);
    essentialLayout->addLayout(heightLayout);
    essentialLayout->addLayout(dpiLayout);

    /*-Sprite Sheet specific things-*/
    m_SpriteCount_RowLabel = new QLabel("Rows: ", this);
    m_SpriteCount_RowLE = new QLineEdit(this);
    m_SpriteCount_RowLE->setFixedWidth(48);
    QHBoxLayout* spriteRowLayout = new QHBoxLayout;
    spriteRowLayout->addWidget(m_SpriteCount_RowLabel);
    spriteRowLayout->addWidget(m_SpriteCount_RowLE);

    m_SpriteCount_ColLabel = new QLabel("Cols: ", this);
    m_SpriteCount_ColLE = new QLineEdit(this);
    m_SpriteCount_ColLE->setFixedWidth(48);
    QHBoxLayout* spriteColLayout = new QHBoxLayout;
    spriteColLayout->addWidget(m_SpriteCount_ColLabel);
    spriteColLayout->addWidget(m_SpriteCount_ColLE);

    m_SpriteLayout = new QVBoxLayout;
    m_SpriteLayout->addLayout(spriteRowLayout);
    m_SpriteLayout->addLayout(spriteColLayout);

    /*-Animation Specific Things-*/
    m_FrameCountLabel = new QLabel("Frames: ", this);
    m_FrameCountLE = new QLineEdit(this);
    m_FrameCountLE->setFixedWidth(48);
    QHBoxLayout* frameCount_Layout = new QHBoxLayout;
    frameCount_Layout->addWidget(m_FrameCountLabel);
    frameCount_Layout->addWidget(m_FrameCountLE);

    m_FpsLabel = new QLabel("FPS: ", this);
    m_FpsLE = new QLineEdit(this);
    m_FpsLE->setFixedWidth(48);
    QHBoxLayout* fpsLayout = new QHBoxLayout;
    fpsLayout->addWidget(m_FpsLabel);
    fpsLayout->addWidget(m_FpsLE);

    m_AnimLayout = new QVBoxLayout;
    m_AnimLayout->addLayout(frameCount_Layout);
    m_AnimLayout->addLayout(fpsLayout);

    m_InformationGrpBox = new QGroupBox("Info: ", this);
    m_InformationGrpLbl = new QLabel(this);
    m_InformationGrpLbl->setText(parameterInfo);
    m_InformationGrpLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout* infoLayout = new QVBoxLayout;
    infoLayout->addWidget(m_InformationGrpLbl);
    m_InformationGrpBox->setLayout(infoLayout);


    m_ColorLabel = new QLabel("Background Color", this);
    m_ColorBtn = new QPushButton(this);
    QPixmap pixmap(10, 10);
    m_backgroundColor = QColor(Qt::white);
    pixmap.fill(m_backgroundColor);
    m_ColorBtn->setIcon(QIcon(pixmap.scaled(m_ColorBtn->size())));
    QHBoxLayout* colorLayout = new QHBoxLayout;
    colorLayout->addWidget(m_ColorLabel);
    colorLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    colorLayout->addWidget(m_ColorBtn);

    QVBoxLayout* parameterLayout = new QVBoxLayout;
    parameterLayout->addLayout(essentialLayout);
    parameterLayout->addLayout(m_SpriteLayout);
    parameterLayout->addLayout(m_AnimLayout);

    QHBoxLayout* centralLayout = new QHBoxLayout;
    centralLayout->addLayout(parameterLayout);
    centralLayout->addWidget(m_InformationGrpBox);

    /*-action Buttons-*/
    m_OkBtn = new QPushButton("&Create", this);
    m_CloseBtn = new QPushButton("&Close", this);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_OkBtn);
    buttonLayout->addWidget(m_CloseBtn);
    buttonLayout->setAlignment(Qt::AlignRight);

    QVBoxLayout* finalLayout = new QVBoxLayout;
    finalLayout->addWidget(m_TypeComboBox);
    finalLayout->addLayout(centralLayout);
    finalLayout->addLayout(colorLayout);
    finalLayout->addLayout(buttonLayout);

    setLayout(finalLayout);

    connect(m_OkBtn, SIGNAL(clicked()), SLOT(newProjectSlot()));
    connect(m_CloseBtn, SIGNAL(clicked()), SLOT(close()));
    connect(m_TypeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(setDocType(int)));
    connect(m_CanvasSizeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(setPresetSize(int)));
    connect(m_ColorBtn, SIGNAL(clicked()), SLOT(setNewColor()));

    m_FpsLabel->hide();
    m_FpsLE->hide();
    m_FrameCountLabel->hide();
    m_FrameCountLE->hide();

    m_SpriteCount_ColLabel->hide();
    m_SpriteCount_ColLE->hide();
    m_SpriteCount_RowLabel->hide();
    m_SpriteCount_RowLE->hide();
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

OdessaNewDocDialog::~OdessaNewDocDialog()
{

}

void OdessaNewDocDialog::setPresetSize(int val){
    switch(val){
    case 0:
        m_WidthLE->setText("800");
        m_HeightLE->setText("600");
        break;
    case 1:
        m_WidthLE->setText("1280");
        m_HeightLE->setText("720");
        break;
    case 2:
        m_WidthLE->setText("1920");
        m_HeightLE->setText("1080");
        break;
    default:
        break;
    }
}

void OdessaNewDocDialog::setNewColor(){
    m_backgroundColor = QColorDialog::getColor(m_backgroundColor, this, "Background Color");
    QPixmap pixmap(10, 10);
    pixmap.fill(m_backgroundColor);
    m_ColorBtn->setIcon(QIcon(pixmap.scaled(m_ColorBtn->size())));
    m_ColorBtn->setIconSize(QSize(m_ColorBtn->size().width()-10, m_ColorBtn->size().height()-10));
}

void OdessaNewDocDialog::setDocType(int val){
    info.setType(val);
    switch(val){
        case 0: //default
            parameterInfo = "Creates a standard image. <br> Width - Image's width in pixels.<br> Height - Image's height in pixels. <br> DPI - The image's DPI";
            m_FpsLabel->hide();
            m_FpsLE->hide();
            m_FrameCountLabel->hide();
            m_FrameCountLE->hide();

            m_SpriteCount_ColLabel->hide();
            m_SpriteCount_ColLE->hide();
            m_SpriteCount_RowLabel->hide();
            m_SpriteCount_RowLE->hide();
            break;
        case 1:
            parameterInfo = "Creates a Sprite Sheet. <br> Width - Image's width in pixels.<br> Height - Image's height in pixels. <br> DPI - The image's DPI <br> Rows: Number of rows. <br> Col: Number of columns.";
            m_FpsLabel->hide();
            m_FpsLE->hide();
            m_FrameCountLabel->hide();
            m_FrameCountLE->hide();

            m_SpriteCount_ColLabel->show();
            m_SpriteCount_ColLE->show();
            m_SpriteCount_RowLabel->show();
            m_SpriteCount_RowLE->show();
            break;
        case 2:
            parameterInfo = "Creates a Animation Project. <br> Width - Image's width in pixels.<br> Height - Image's height in pixels. <br> DPI - The image's DPI <br> Frame Count: Number of frames. <br> FPS: Frames per second.";
            m_FpsLabel->show();
            m_FpsLE->show();
            m_FrameCountLabel->show();
            m_FrameCountLE->show();

            m_SpriteCount_ColLabel->hide();
            m_SpriteCount_ColLE->hide();
            m_SpriteCount_RowLabel->hide();
            m_SpriteCount_RowLE->hide();
            break;
        default:
            break;
    }
    m_InformationGrpLbl->setText(parameterInfo);
}

void OdessaNewDocDialog::newProjectSlot()
{
    if(m_WidthLE->text() != NULL){ info.setWidth(m_WidthLE->text().toInt()); }else{ info.setWidth(0); }
    if(m_HeightLE->text() != NULL){ info.setHeight(m_HeightLE->text().toInt()); }else{ info.setHeight(0); }
    if(m_DPILE->text() != NULL){ info.setDPI(m_DPILE->text().toInt()); }else{ info.setDPI(0); }
    if(m_SpriteCount_RowLE->text() != NULL){ info.setSpriteCount_Row(m_SpriteCount_RowLE->text().toInt()); }else{ info.setSpriteCount_Row(0); }
    if(m_SpriteCount_ColLE->text() != NULL){ info.setSpriteCount_Col(m_SpriteCount_ColLE->text().toInt()); }else{ info.setSpriteCount_Col(0); }
    if(m_FrameCountLE->text() != NULL){ info.setFrameCount(m_FrameCountLE->text().toInt()); }else{ info.setFrameCount(0); }
    if(m_FpsLE->text() != NULL){ info.setFPS(m_FpsLE->text().toInt()); }else{ info.setFPS(0); }
    info.setStartColor(m_backgroundColor);
    emit newProject(info);
    close();
}

OdessaPrefDialog::OdessaPrefDialog()
{
    setWindowTitle("Preferences");
    setModal(true);

    m_ContentWidget = new QListWidget(this);
    m_ContentWidget->setMaximumWidth(128);

    genPref = new GeneralPrefPage(this);
    animPref = new AnimationPrefPage(this);
    spritePref = new SpriteSheetPrefPage(this);

    pagesWidget = new QStackedWidget(this);
    pagesWidget->addWidget(genPref);
    pagesWidget->addWidget(animPref);
    pagesWidget->addWidget(spritePref);

    splitView = new QSplitter(this);
    splitView->addWidget(m_ContentWidget);
    splitView->addWidget(pagesWidget);

    m_OkButton = new QPushButton("Ok", this);
    m_ApplyButton = new QPushButton("Apply", this);
    m_CancelButton = new QPushButton("Cancel", this);

    QListWidgetItem* generalItem = new QListWidgetItem(m_ContentWidget);
    generalItem->setText("General");
    generalItem->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem* animationItem = new QListWidgetItem(m_ContentWidget);
    animationItem->setText("Animation");
    animationItem->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem* spriteItem = new QListWidgetItem(m_ContentWidget);
    spriteItem->setText("Sprite Sheet");
    spriteItem->setTextAlignment(Qt::AlignHCenter);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    buttonLayout->addSpacing(this->width()/3);
    buttonLayout->addWidget(m_OkButton);
    buttonLayout->addWidget(m_ApplyButton);
    buttonLayout->addWidget(m_CancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitView);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(genPref, SIGNAL(projectPathChanged(QString)), SLOT(updateProjectPath(QString)));
    connect(genPref, SIGNAL(historyStepsChanged(int)), SLOT(updateHistoryLimit(int)));
    connect(m_ContentWidget, SIGNAL(currentRowChanged(int)), pagesWidget, SLOT(setCurrentIndex(int)));
    connect(m_OkButton, SIGNAL(clicked()), SLOT(okChanges()));
    connect(m_ApplyButton, SIGNAL(clicked()), SLOT(applyChanges()));
    connect(m_CancelButton, SIGNAL(clicked()), SLOT(close()));
}

void OdessaPrefDialog::setProjectPath(QString path){
    genPref->setProjectPath(path);
}

void OdessaPrefDialog::updateHistoryLimit(int limit){
    emit historyStepsChanged(limit);
}

void OdessaPrefDialog::updateProjectPath(QString val){
    emit projectPathChanged(val);
}

void OdessaPrefDialog::applyChanges(){
    genPref->applyChanges();
}

void OdessaPrefDialog::okChanges(){
    applyChanges();
    this->close();
}

OdessaPrefDialog::~OdessaPrefDialog()
{

}

GeneralPrefPage::GeneralPrefPage(QWidget *parent) : QWidget(parent)
{
    QSettings settings("SwingInnovations", "Odessa");
    QString filePath = settings.value("projectPath").toString();

    m_ThemeLbl = new QLabel("Theme: ", this);
    m_ThemeCombobox = new QComboBox(this);
    m_ThemeCombobox->addItem("Dark");
    m_ThemeCombobox->addItem("Light");

    QString styleChoice = settings.value("theme").toString();
    if(styleChoice == "Dark"){
        m_ThemeCombobox->setCurrentIndex(0);
    }else{
        m_ThemeCombobox->setCurrentIndex(1);
    }

    QHBoxLayout* themeGrp = new QHBoxLayout;
    themeGrp->addWidget(m_ThemeLbl);
    themeGrp->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    themeGrp->addWidget(m_ThemeCombobox);

    mProjectPathLbl = new QLabel("Project path:", this);
    mProjectPathLE = new QLineEdit(this);
    mProjectPathLE->setText(filePath);
    mProjectPathLE->setAlignment(Qt::AlignRight);
    mProjectPathLE->home(false);
    mChangeProjectPathBtn = new QPushButton("...", this);

    mHistoryLbl = new QLabel("History Steps: ", this);
    mStepsBox = new QSpinBox(this);
    mStepsBox->setValue(24);

    m_HardwareAccLbl = new QLabel("Enable Hardware Acceleration: ", this);
    m_HardwareAccChk = new QCheckBox(this);

#if defined(_WIN32)
    m_useWindowsAPI = new QCheckBox("Use Windows Pen API", this);
#endif

    auto gridLayout = new QGridLayout;
    // Theme
    gridLayout->addWidget(m_ThemeLbl, 0, 0);
    gridLayout->addWidget(m_ThemeCombobox, 0, 3);
    gridLayout->addWidget(mProjectPathLbl, 1, 0);
    gridLayout->addWidget(mProjectPathLE, 1, 1);
    gridLayout->addWidget(mChangeProjectPathBtn, 1, 3);
    gridLayout->addWidget(mHistoryLbl, 2, 0);
    gridLayout->addWidget(mStepsBox, 2, 3);
    gridLayout->addWidget(m_HardwareAccLbl, 3, 0);
    gridLayout->addWidget(m_HardwareAccChk, 3, 3);
#if defined(_WIN32)
    gridLayout->addWidget(m_useWindowsAPI, 4, 0);
#endif

    auto masterLayout = new QVBoxLayout;
    masterLayout->addLayout(gridLayout);
    masterLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(masterLayout);

    connect(mChangeProjectPathBtn, SIGNAL(clicked()), SLOT(changeProjectPath()));
}

void GeneralPrefPage::setProjectPath(QString path){
    mProjectPathLE->setText(path);
    mProjectPathLE->setAlignment(Qt::AlignLeft);
}

void GeneralPrefPage::changeProjectPath(){
    QString oldPath = mProjectPathLE->text();
    QString filePath = QFileDialog::getExistingDirectory(this, "Set Project Path: ", QDir::currentPath());
    if(filePath.length() < 1){
        mProjectPathLE->setText(oldPath);
    }else{
        mProjectPathLE->setText(filePath);
        mProjectPathLE->home(false);
    }

    emit projectPathChanged(mProjectPathLE->text());
}

void GeneralPrefPage::changeHistorySteps(int val){
    mStepsBox->setValue(val);
}

void GeneralPrefPage::applyChanges(){
    emit historyStepsChanged(mStepsBox->value());
    QSettings settings("SwingInnovations", "Odessa");
    settings.setValue("theme", m_ThemeCombobox->currentText());
    settings.setValue("HWAcceleration", m_HardwareAccChk->isChecked());
}

GeneralPrefPage::~GeneralPrefPage()
{

}

AnimationPrefPage::AnimationPrefPage(QWidget *parent) : QWidget(parent){
    initGui();
}

void AnimationPrefPage::initGui(){
    m_totalFramesLbl = new QLabel("Total FPS: ", this);
    m_totalFramesSB = new QSpinBox(this);
    m_totalFramesSB->setMaximum(1000000);
    m_totalFramesSB->setMinimum(1);
    m_totalFramesSB->setValue(240);

    m_fpsLbl = new QLabel("Frames Per Second (FPS): ", this);
    m_fpsSB = new QSpinBox(this);
    m_fpsSB->setMinimum(1);
    m_fpsSB->setMaximum(120);
    m_fpsSB->setValue(24);

    QHBoxLayout* totalFramesLayout = new QHBoxLayout;
    totalFramesLayout->addWidget(m_totalFramesLbl);
    totalFramesLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    totalFramesLayout->addWidget(m_totalFramesSB);

    QHBoxLayout* fpsLayout = new QHBoxLayout;
    fpsLayout->addWidget(m_fpsLbl);
    fpsLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    fpsLayout->addWidget(m_fpsSB);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addLayout(totalFramesLayout);
    centralLayout->addLayout(fpsLayout);
    centralLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(centralLayout);
}

SpriteSheetPrefPage::SpriteSheetPrefPage(QWidget *parent) : QWidget(parent){
    initGui();
}

void SpriteSheetPrefPage::initGui(){
    m_rowCntLbl = new QLabel("Row Cell Count: ", this);
    m_rowCntSB = new QSpinBox(this);
    m_rowCntSB->setValue(0);
    m_rowCntSB->setMinimum(1);

    m_colCntLbl = new QLabel("Column Cell Count: ", this);
    m_colCntSB = new QSpinBox(this);
    m_colCntSB->setValue(0);
    m_colCntSB->setMinimum(1);

    QHBoxLayout* rowLayout = new QHBoxLayout;
    rowLayout->addWidget(m_rowCntLbl);
    rowLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    rowLayout->addWidget(m_rowCntSB);

    QHBoxLayout* colLayout = new QHBoxLayout;
    colLayout->addWidget(m_colCntLbl);
    colLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    colLayout->addWidget(m_colCntSB);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addLayout(rowLayout);
    centralLayout->addLayout(colLayout);
    centralLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(centralLayout);
}

ProjectInfo::ProjectInfo()
{
    width = 0;
    height = 0;
    type = 0;
    dpi = 0;
    frameCount = 0;
    fps = 0;
}

ProjectInfo::ProjectInfo(const ProjectInfo &other){
    width = other.width;
    height = other.height;
    type = other.type;
    dpi = other.dpi;
    frameCount = other.frameCount;
    fps = other.fps;
}

ProjectInfo::~ProjectInfo()
{

}

void ProjectInfo::setWidth(int w){
    width = w;
}

void ProjectInfo::setHeight(int h){
    height = h;
}

void ProjectInfo::setDPI(int d){
    dpi = d;
}

void ProjectInfo::setType(int t){
    type = t;
}

void ProjectInfo::setFrameCount(int fc){
    frameCount = fc;
}

void ProjectInfo::setFPS(int fps){
    this->fps = fps;
}

void ProjectInfo::setSpriteCount_Row(int row){
    spriteCount_Row = row;
}

void ProjectInfo::setSpriteCount_Col(int col){
    spriteCount_Col = col;
}

void ProjectInfo::setStartColor(QColor col){
    startColor = col;
}

DebugWindow::DebugWindow(){
    m_dataView = new QTableWidget(this);
    m_dataView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_dataView->setColumnCount(2);
    m_dataView->setRowCount(9);
    m_dataView->setHorizontalHeaderLabels(QString("Item;Value").split(';'));
    m_dataView->setItem(0, 0, new QTableWidgetItem("Mouse X: "));
    m_dataView->setItem(0, 1, new QTableWidgetItem("0"));
    m_dataView->setItem(1, 0, new QTableWidgetItem("Mouse Y: "));
    m_dataView->setItem(1, 1, new QTableWidgetItem("0"));
    m_dataView->setItem(2, 0, new QTableWidgetItem("Current Tool: "));
    m_dataView->setItem(2, 1, new QTableWidgetItem("Cursor"));
    m_dataView->setItem(3, 0, new QTableWidgetItem("Actual Pressure: "));
    m_dataView->setItem(3, 1, new QTableWidgetItem("0"));
    m_dataView->setItem(4, 0, new QTableWidgetItem("Current Index: "));
    m_dataView->setItem(4, 1, new QTableWidgetItem("0"));
    m_dataView->setItem(5, 0, new QTableWidgetItem("Current Frame: "));
    m_dataView->setItem(5, 1, new QTableWidgetItem("0"));
    m_dataView->setItem(6, 0, new QTableWidgetItem("Brush Reported Pressure: "));
    m_dataView->setItem(6, 1, new QTableWidgetItem("0"));
    m_dataView->setItem(7, 0, new QTableWidgetItem("History Limit: "));
    m_dataView->setItem(7, 1, new QTableWidgetItem("24"));
    m_dataView->setItem(8, 0, new QTableWidgetItem("Size of history stack: "));
    m_dataView->setItem(8, 1, new QTableWidgetItem("0"));
    m_dataView->resizeColumnsToContents();

    m_dataView->item(0, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(1, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(2, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(3, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(4, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(5, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(6, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(7, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(8, 1)->setTextAlignment(Qt::AlignRight);

    m_closeBtn = new QPushButton("&Close", this);

    QVBoxLayout* overallLayout = new QVBoxLayout;
    overallLayout->addWidget(m_dataView);
    overallLayout->addWidget(m_closeBtn);
    setLayout(overallLayout);

    connect(m_closeBtn, SIGNAL(clicked()), SLOT(close()));
}

void DebugWindow::updateMousePosition(QPoint pos){
    m_dataView->item(0, 1)->setText(QString::number(pos.x()));
    m_dataView->item(0, 1)->setTextAlignment(Qt::AlignRight);
    m_dataView->item(1, 1)->setText(QString::number(pos.y()));
    m_dataView->item(1, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateCurrentTool(QString str){
    m_dataView->item(2, 1)->setText(str);
    m_dataView->item(2, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateActualPressure(qreal pressure){
    m_dataView->item(3, 1)->setText(QString::number(pressure));
    m_dataView->item(3, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateToolPressure(qreal pressure){
    m_dataView->item(6, 1)->setText(QString::number(pressure));
    m_dataView->item(6, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateCurrentIndex(int index){
    m_dataView->item(4, 1)->setText(QString::number(index));
    m_dataView->item(4, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateCurrentFrame(int frame){
    m_dataView->item(5, 1)->setText(QString::number(frame));
    m_dataView->item(5, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateHistoryLimit(int limit){
    m_dataView->item(7, 1)->setText(QString::number(limit));
    m_dataView->item(7, 1)->setTextAlignment(Qt::AlignRight);
}

void DebugWindow::updateHistoryStack(int stackSize){
    m_dataView->item(8, 1)->setText(QString::number(stackSize));
    m_dataView->item(8, 1)->setTextAlignment(Qt::AlignRight);
}

DebugWindow::~DebugWindow(){

}
