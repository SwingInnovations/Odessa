#include "dockwidgets.h"

BrushDockWidget::BrushDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Brush");

    //Size
    mSizeLabel = new QLabel(this);
    mSizeLabel->setText("Size: ");
    mSizeSlider = new QSlider(this);
    mSizeSlider->setOrientation(Qt::Horizontal);
    mSizeLE = new QLineEdit(this);
    mSizeLE->setFixedWidth(32);
    mSizeLayout = new QHBoxLayout;
    mSizeLayout->addWidget(mSizeLabel);
    mSizeLayout->addWidget(mSizeSlider);
    mSizeLayout->addWidget(mSizeLE);

    //Feather
    mFeatherLabel = new QLabel(this);
    mFeatherLabel->setText("Feather:");
    mFeatherSlider = new QSlider(this);
    mFeatherSlider->setRange(0, 100);
    mFeatherSlider->setOrientation(Qt::Horizontal);
    mFeatherLE = new QLineEdit(this);
    mFeatherLE->setFixedWidth(32);
    mFeatherLayout = new QHBoxLayout;
    mFeatherLayout->addWidget(mFeatherLabel);
    mFeatherLayout->addWidget(mFeatherSlider);
    mFeatherLayout->addWidget(mFeatherLE);

    //Spacing
    mSpacingLabel = new QLabel(this);
    mSpacingLabel->setText("Spacing:");
    mSpacingSlider = new QSlider(this);
    mSpacingSlider->setOrientation(Qt::Horizontal);
    mSpacingLE = new QLineEdit(this);
    mSpacingLE->setFixedWidth(32);
    mSpacingLayout = new QHBoxLayout;
    mSpacingLayout->addWidget(mSpacingLabel);
    mSpacingLayout->addWidget(mSpacingSlider);
    mSpacingLayout->addWidget(mSpacingLE);

    primaryBrushControlLayout = new QVBoxLayout;
    primaryBrushControlLayout->addLayout(mSizeLayout);
    primaryBrushControlLayout->addStretch(1);
    primaryBrushControlLayout->addLayout(mFeatherLayout);
    primaryBrushControlLayout->addStretch(1);
    primaryBrushControlLayout->addLayout(mSpacingLayout);
    primaryBrushControlLayout->setSpacing(0);

    connect(mSizeSlider, SIGNAL(valueChanged(int)), SLOT(set_mSizeLE(int)));
    connect(mSizeLE, SIGNAL(textChanged(QString)), SLOT(set_mSizeSlider(QString)));
    connect(mFeatherSlider, SIGNAL(valueChanged(int)), SLOT(set_mFeatherLE(int)));
    connect(mFeatherLE, SIGNAL(textChanged(QString)), SLOT(set_mFeatherSlider(QString)));
    connect(mSpacingSlider, SIGNAL(valueChanged(int)), SLOT(set_mSpacingLE(int)));
    connect(mSpacingLE, SIGNAL(textChanged(QString)), SLOT(set_mSpacingSlider(QString)));

    QWidget *layoutView = new QWidget(this);
    layoutView->setLayout(primaryBrushControlLayout);
    this->setWidget(layoutView);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

}

void BrushDockWidget::set_mSizeLE(int val)
{
    this->mSizeLE->setText(QString::number(val));
    emit mSizeChanged(val);
}

void BrushDockWidget::set_mFeatherLE(int val)
{
    this->mFeatherLE->setText(QString::number(val));
    emit mFeatherChanged(val);
}

void BrushDockWidget::set_mSpacingLE(int val)
{
    this->mSpacingLE->setText(QString::number(val));
    emit mSpacingChanged(val);
}

void BrushDockWidget::set_mSizeSlider(QString val)
{
    mSizeSlider->setValue(val.toInt());
    emit mSizeChanged(val.toInt());
}

void BrushDockWidget::set_mFeatherSlider(QString val)
{
    mFeatherSlider->setValue(val.toInt());
    emit mFeatherChanged(val.toInt());
}

void BrushDockWidget::set_mSpacingSlider(QString val)
{
    mSpacingSlider->setValue(val.toInt());
    emit mSpacingChanged(val.toInt());
}

BrushDockWidget::~BrushDockWidget()
{

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

    setWidget(colorModeTab);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

ColorDockWidget::~ColorDockWidget()
{

}

TimelineDockWidget::TimelineDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Timeline");
}

TimelineDockWidget::~TimelineDockWidget()
{

}

ColorWheelWidget::ColorWheelWidget(QWidget *parent) : QWidget(parent)
{

}

ColorWheelWidget::~ColorWheelWidget()
{

}
