#include "dialogwindows.h"

OdessaNewDocDialog::OdessaNewDocDialog()
{
    //initialize a few things
    setWindowTitle("New Canvas");
    setModal(true);

    parameterInfo = "nil<br>null";

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
    QHBoxLayout* widthLayout = new QHBoxLayout;
    widthLayout->addWidget(m_WidthLabel);
    widthLayout->addWidget(m_WidthLE);

    m_HeightLabel = new QLabel("Height: ", this);
    m_HeightLE = new QLineEdit(this);
    m_HeightLE->setFixedWidth(48);
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
    QVBoxLayout* infoLayout = new QVBoxLayout;
    infoLayout->addWidget(m_InformationGrpLbl);
    m_InformationGrpBox->setLayout(infoLayout);

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
    finalLayout->addLayout(buttonLayout);

    setLayout(finalLayout);

    connect(m_OkBtn, SIGNAL(clicked()), SLOT(newProjectSlot()));
    connect(m_CloseBtn, SIGNAL(clicked()), SLOT(close()));
    connect(m_TypeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(setDocType(int)));

    m_FpsLabel->hide();
    m_FpsLE->hide();
    m_FrameCountLabel->hide();
    m_FrameCountLE->hide();

    m_SpriteCount_ColLabel->hide();
    m_SpriteCount_ColLE->hide();
    m_SpriteCount_RowLabel->hide();
    m_SpriteCount_RowLE->hide();
    setFixedSize(188, 183);
}

OdessaNewDocDialog::~OdessaNewDocDialog()
{

}

void OdessaNewDocDialog::setDocType(int val){
    info.setType(val);
    switch(val){
        case 0: //default
            m_FpsLabel->hide();
            m_FpsLE->hide();
            m_FrameCountLabel->hide();
            m_FrameCountLE->hide();

            m_SpriteCount_ColLabel->hide();
            m_SpriteCount_ColLE->hide();
            m_SpriteCount_RowLabel->hide();
            m_SpriteCount_RowLE->hide();
            setFixedSize(188, 183);
            break;
        case 1:
            m_FpsLabel->hide();
            m_FpsLE->hide();
            m_FrameCountLabel->hide();
            m_FrameCountLE->hide();

            m_SpriteCount_ColLabel->show();
            m_SpriteCount_ColLE->show();
            m_SpriteCount_RowLabel->show();
            m_SpriteCount_RowLE->show();
            setFixedSize(188, 239);
            break;
        case 2:
            m_FpsLabel->show();
            m_FpsLE->show();
            m_FrameCountLabel->show();
            m_FrameCountLE->show();

            m_SpriteCount_ColLabel->hide();
            m_SpriteCount_ColLE->hide();
            m_SpriteCount_RowLabel->hide();
            m_SpriteCount_RowLE->hide();
            setFixedSize(188, 239);
            break;
        default:
            break;
    }
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

    emit newProject(info);
    close();
}

OdessaPrefDialog::OdessaPrefDialog()
{
    setWindowTitle("Preferences");
    setModal(true);

    contentWidget = new QListWidget(this);
    contentWidget->setMaximumWidth(128);

    genPref = new GeneralPrefPage(this);

    pagesWidget = new QStackedWidget(this);
    pagesWidget->addWidget(genPref);

    m_OkButton = new QPushButton("Ok", this);
    m_ApplyButton = new QPushButton("Apply", this);
    m_CancelButton = new QPushButton("Cancel", this);

    QListWidgetItem* generalItem = new QListWidgetItem(contentWidget);
    generalItem->setText("General");
    generalItem->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem* animationItem = new QListWidgetItem(contentWidget);
    animationItem->setText("Animation");
    animationItem->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem* spriteItem = new QListWidgetItem(contentWidget);
    spriteItem->setText("Sprite Sheet");
    spriteItem->setTextAlignment(Qt::AlignHCenter);

    QHBoxLayout* contentLayout = new QHBoxLayout;
    contentLayout->addWidget(contentWidget);
    contentLayout->addWidget(pagesWidget);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacing(this->width()/3);
    buttonLayout->addWidget(m_OkButton);
    buttonLayout->addWidget(m_ApplyButton);
    buttonLayout->addWidget(m_CancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(contentLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(genPref, SIGNAL(projectPathChanged(QString)), SLOT(updateProjectPath(QString)));
}

void OdessaPrefDialog::updateProjectPath(QString val){
    emit projectPathChanged(val);
}

OdessaPrefDialog::~OdessaPrefDialog()
{

}

GeneralPrefPage::GeneralPrefPage(QWidget *parent) : QWidget(parent)
{
    QSettings settings("SwingInnovations", "Odessa");
    QString filePath = settings.value("projectPath").toString();

    mProjectPathLbl = new QLabel("Project path:", this);
    mProjectPathLE = new QLineEdit(this);
    mProjectPathLE->setText(filePath);
    mChangeProjectPathBtn = new QPushButton("...", this);
    QHBoxLayout* projectPathGrp = new QHBoxLayout;
    projectPathGrp->addWidget(mProjectPathLbl);
    projectPathGrp->addWidget(mProjectPathLE);
    projectPathGrp->addWidget(mChangeProjectPathBtn);

    mHistoryLbl = new QLabel("History Steps: ", this);
    mStepsBox = new QSpinBox(this);
    mStepsBox->setValue(24);
    QHBoxLayout* historyGrp = new QHBoxLayout;
    historyGrp->addWidget(mHistoryLbl);
    historyGrp->addWidget(mStepsBox);

    QVBoxLayout* masterLayout = new QVBoxLayout;
    masterLayout->addLayout(projectPathGrp);
    masterLayout->addLayout(historyGrp);

    setLayout(masterLayout);

    connect(mChangeProjectPathBtn, SIGNAL(clicked()), SLOT(changeProjectPath()));
    connect(mStepsBox, SIGNAL(valueChanged(int)), SLOT(changeHistorySteps(int)));
}

void GeneralPrefPage::changeProjectPath(){
    QString filePath = QFileDialog::getExistingDirectory(this, "Set Project Path: ", QDir::currentPath());
    mProjectPathLE->setText(filePath);
    emit projectPathChanged(filePath);
}

void GeneralPrefPage::changeHistorySteps(int val){
    mStepsBox->setValue(val);
}

GeneralPrefPage::~GeneralPrefPage()
{

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
