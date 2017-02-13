#include "panels.h"

BrushConfigPanel::BrushConfigPanel(QWidget *parent) : QWidget(parent)
{
    initGUI();
    //TODO Hookup signals and slots.
}

void BrushConfigPanel::updateBrushSize(qreal size)
{
    emit brushWidthChanged((int)size);
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

void BrushConfigPanel::initGUI()
{
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
    m_LoadStencilAct = new QAction("Load Stencil", this);
    m_SaveStencilAct = new QAction("Save Stencil", this);

    m_OptMenu = new QMenu(this);
    m_OptMenu->addAction(m_LoadBrushLibraryAct);
    m_OptMenu->addAction(m_SaveBrushLibraryAct);
    m_OptMenu->addSeparator();
    m_OptMenu->addAction(m_LoadStencilAct);
    m_OptMenu->addAction(m_SaveStencilAct);

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
    m_StrokePrvwLbl = new QLabel("Stroke", this);

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
    brushGridLayout->addWidget(m_transferWidget, 4, 0, 1, 0);

    auto brushLayout = new QHBoxLayout;
    brushLayout->addLayout(brushListLayout);
    brushLayout->addLayout(brushGridLayout);

    /*-Begin Color Widget-*/
    m_StencilPreviewLbl = new QLabel("Stencil Preview", this);

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

    auto stencilGridLayout =  new QGridLayout;
    stencilGridLayout->addWidget(m_StencilPreviewLbl, 0, 1, 0, 1, Qt::AlignCenter);
    stencilGridLayout->addWidget(stencilWidthLbl, 1, 0);
    stencilGridLayout->addWidget(m_StencilWidthSE, 1, 1);
    stencilGridLayout->addWidget(stencilHeightLbl, 2, 0);
    stencilGridLayout->addWidget(m_StencilHeightSE, 2, 1);
    stencilGridLayout->addWidget(hardnessLbl, 3, 0);
    stencilGridLayout->addWidget(m_HardnessSE, 3, 1);

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

    connect(m_transferSizeCB, SIGNAL(clicked(bool)), SLOT(toggleTransferSize(bool)));
    connect(m_transferOpacityCB, SIGNAL(clicked(bool)), SLOT(toggleTransferOpacity(bool)));
    connect(m_brushSizeSE, SIGNAL(valueChanged(qreal)), SLOT(updateBrushSize(qreal)));
    connect(m_opacitySE, SIGNAL(valueChanged(qreal)), SLOT(updateBrushOpacity(qreal)));
    connect(m_spacingSE, SIGNAL(valueChanged(qreal)), SLOT(updateBrushSpacing(qreal)));
    connect(m_transferSizeSE, SIGNAL(valueChanged(qreal)), SLOT(updateTransferSize(qreal)));
    connect(m_transferOpacitySE,SIGNAL(valueChanged(qreal)), SLOT(updateTransferOpacity(qreal)));
}



ColorConfigPanel::ColorConfigPanel(QWidget *parent) : QWidget(parent)
{

}

ColorConfigPanel::~ColorConfigPanel()
{

}
