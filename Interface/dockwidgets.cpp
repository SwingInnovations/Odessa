#include "dockwidgets.h"

BrushDockWidget::BrushDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Brush");

    //Size
    mSizeLabel = new QLabel(this);
    mSizeLabel->setText("Size: ");
    mSizeSlider = new QSlider(this);
    mSizeSlider->setOrientation(Qt::Horizontal);
    mSizeSlider->setValue(5);
    mSizeLE = new QLineEdit(this);
    mSizeLE->setFixedWidth(32);
    mSizeLE->setText(QString::number(5));
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
    mFeatherLE->setText(QString::number(0));
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
    mSpacingLE->setText(QString::number(0));
    mSpacingLayout = new QHBoxLayout;
    mSpacingLayout->addWidget(mSpacingLabel);
    mSpacingLayout->addWidget(mSpacingSlider);
    mSpacingLayout->addWidget(mSpacingLE);

    mOpacityLabel = new QLabel(this);
    mOpacityLabel->setText("Opacity:");
    mOpacitySlider = new QSlider(this);
    mOpacitySlider->setRange(0, 255);
    mOpacitySlider->setOrientation(Qt::Horizontal);
    mOpacitySlider->setValue(255);
    mOpacityLE = new QLineEdit(this);
    mOpacityLE->setFixedWidth(32);
    mOpacityLE->setText(QString::number(255));
    mOpacityLayout = new QHBoxLayout;
    mOpacityLayout->addWidget(mOpacityLabel);
    mOpacityLayout->addWidget(mOpacitySlider);
    mOpacityLayout->addWidget(mOpacityLE);

    mTransferOpacity = new QCheckBox(this);
    mTransferOpacity->setText("Opacity");
    mTransferOpacity->setChecked(false);
    mTransferOpacityAmt = new QSlider(this);
    mTransferOpacityAmt->setRange(0, 255);
    mTransferOpacityAmt->setOrientation(Qt::Horizontal);
    mTransferOpacityAmt->setEnabled(false);
    mTransferOpacityLE = new QLineEdit(this);
    mTransferOpacityLE->setFixedWidth(32);
    mTransferOpacityLE->setEnabled(false);
    mTransferOpacityLayout = new QHBoxLayout;
    mTransferOpacityLayout->addWidget(mTransferOpacity);
    mTransferOpacityLayout->addWidget(mTransferOpacityAmt);
    mTransferOpacityLayout->addWidget(mTransferOpacityLE);

    mTransferWidth = new QCheckBox(this);
    mTransferWidth->setText("Size:");
    mTransferWidth->setChecked(false);
    mTransferWidthSlider = new QSlider(this);
    mTransferWidthSlider->setRange(0, 255);
    mTransferWidthSlider->setOrientation(Qt::Horizontal);
    mTransferWidthSlider->setEnabled(false);
    mTransferWidthLE = new QLineEdit(this);
    mTransferWidthLE->setFixedWidth(32);
    mTransferWidthLE->setEnabled(false);
    mTransferWidthLayout = new QHBoxLayout;
    mTransferWidthLayout->addWidget(mTransferWidth);
    mTransferWidthLayout->addWidget(mTransferWidthSlider);
    mTransferWidthLayout->addWidget(mTransferWidthLE);

    secondaryBrushControlLayout = new QVBoxLayout;
    secondaryBrushControlLayout->addLayout(mTransferOpacityLayout);
    secondaryBrushControlLayout->addLayout(mTransferWidthLayout);

    mPressureContainer = new QGroupBox(this);
    mPressureContainer->setTitle("Pressure");
    mPressureContainer->setLayout(secondaryBrushControlLayout);

    primaryBrushControlLayout = new QVBoxLayout;

    primaryBrushControlLayout->addLayout(mSizeLayout);
    primaryBrushControlLayout->addSpacing(0);
    primaryBrushControlLayout->addLayout(mFeatherLayout);
    primaryBrushControlLayout->addSpacing(0);
    primaryBrushControlLayout->addLayout(mSpacingLayout);
    primaryBrushControlLayout->setSpacing(0);
    primaryBrushControlLayout->addLayout(mOpacityLayout);
    primaryBrushControlLayout->addWidget(mPressureContainer);

    connect(mSizeSlider, SIGNAL(valueChanged(int)), SLOT(set_mSizeLE(int)));
    connect(mSizeLE, SIGNAL(textChanged(QString)), SLOT(set_mSizeSlider(QString)));
    connect(mFeatherSlider, SIGNAL(valueChanged(int)), SLOT(set_mFeatherLE(int)));
    connect(mFeatherLE, SIGNAL(textChanged(QString)), SLOT(set_mFeatherSlider(QString)));
    connect(mSpacingSlider, SIGNAL(valueChanged(int)), SLOT(set_mSpacingLE(int)));
    connect(mSpacingLE, SIGNAL(textChanged(QString)), SLOT(set_mSpacingSlider(QString)));
    connect(mOpacityLE, SIGNAL(textChanged(QString)), SLOT(set_mOpacitySlider(QString)));
    connect(mOpacitySlider, SIGNAL(valueChanged(int)), SLOT(set_mOpacityLE(int)));
    connect(mTransferOpacity, SIGNAL(toggled(bool)), SLOT(toggleTransferOpacity(bool)));
    connect(mTransferWidth, SIGNAL(toggled(bool)), SLOT(toggleTransferSize(bool)));
    connect(mTransferOpacityAmt, SIGNAL(valueChanged(int)), SLOT(set_mTransferOpacity(int)));
    connect(mTransferOpacityLE, SIGNAL(textChanged(QString)), SLOT(set_mTransferOpacitySlider(QString)));
    connect(mTransferWidthSlider, SIGNAL(valueChanged(int)), SLOT(set_mTransferSize(int)));
    connect(mTransferWidthLE, SIGNAL(textChanged(QString)), SLOT(set_mTransferSizeSlider(QString)));

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

void BrushDockWidget::set_mOpacityLE(int val)
{
    mOpacityLE->setText(QString::number(val));
    emit mOpacityChanged(val);
}

void BrushDockWidget::set_mOpacitySlider(QString val)
{
    mOpacitySlider->setValue(val.toInt());
    emit mOpacityChanged(val.toInt());
}

void BrushDockWidget::set_mTransferOpacity(int val)
{
    mTransferOpacityLE->setText(QString::number(val));
    emit mTransferOpacityChanged(val);
}

void BrushDockWidget::set_mTransferOpacitySlider(QString val)
{
    mTransferOpacityAmt->setValue(val.toInt());
    emit mTransferOpacityChanged(val.toInt());
}

void BrushDockWidget::set_mTransferSize(int val)
{
    mTransferWidthLE->setText(QString::number(val));
    if(mTransferWidth->isEnabled())
    {
        emit mTransferSizeChanged(val);
    }else{
        emit mTransferSizeChanged(0);
    }
}

void BrushDockWidget::set_mTransferSizeSlider(QString val)
{
    mTransferWidthSlider->setValue(val.toInt());
    if(mTransferWidth->isEnabled())
    {
        emit mTransferSizeChanged(val.toInt());
    }else{
        emit mTransferSizeChanged(0);
    }
}

void BrushDockWidget::toggleTransferOpacity(bool val)
{
    if(val)
    {
        mTransferOpacityAmt->setEnabled(true);
        mTransferOpacityLE->setEnabled(true);
    }else{
        mTransferOpacityAmt->setEnabled(false);
        mTransferOpacityLE->setEnabled(false);
    }
}

void BrushDockWidget::toggleTransferSize(bool val)
{
    if(val)
    {
        mTransferWidthSlider->setEnabled(true);
        mTransferWidthLE->setEnabled(true);
        emit mTransferSizeChanged(val);
    }else{
        mTransferWidthSlider->setEnabled(false);
        mTransferWidthLE->setEnabled(false);
        emit mTransferSizeChanged(0);
    }
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

//    connect(colorWheel, SIGNAL(redChanged(int)), SLOT(set_RLE(int)));
//    connect(colorWheel, SIGNAL(blueChanged(int)), SLOT(set_BLE(int)));
//    connect(colorWheel, SIGNAL(greenChanged(int)), SLOT(set_GLE(int)));
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

    compositionMode = new QComboBox(this);
    compositionMode->addItem("Normal");
    compositionMode->addItem("Multiply");

    layerManager = new QListWidget(this);

    QVBoxLayout *layerLayout = new QVBoxLayout;
    layerLayout->addWidget(compositionMode);
    layerLayout->addWidget(layerManager);

    QWidget *layerDisplay = new QWidget(this);
    layerDisplay->setLayout(layerLayout);
    setWidget(layerDisplay);
}

LayerDockWidget::~LayerDockWidget()
{

}

