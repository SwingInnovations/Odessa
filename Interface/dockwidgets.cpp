#include "dockwidgets.h"

BrushDockWidget::BrushDockWidget(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("Brush");

    m_OpenBrushAct = new QAction("&Open Brush..", this);
    m_OpenBrushLibAct = new QAction("&Open Brush set..", this);
    m_ExportBrushAct = new QAction("&Export Brush", this);
    m_ExportBrushLibAct = new QAction("&Export Brush Set", this);

    m_BrushMenu = new QMenu(this);
    m_BrushMenu->addAction(m_OpenBrushAct);
    m_BrushMenu->addAction(m_OpenBrushLibAct);
    m_BrushMenu->addSeparator();
    m_BrushMenu->addAction(m_ExportBrushAct);
    m_BrushMenu->addAction(m_ExportBrushLibAct);

    /* Setup top widget */
    /* This will appear under the general and advanced tabs */
    m_BrushToolButton = new QToolButton(this);
    m_BrushToolButton->setText("Brush");
    m_BrushToolButton->setFixedWidth(48);
    m_BrushToolButton->setMenu(m_BrushMenu);
    m_BrushPreviewLbl = new QLabel(this);
    m_BrushPreviewLbl->setText("Test");
    QVBoxLayout* vBGLayout = new QVBoxLayout;
    vBGLayout->addWidget(m_BrushToolButton);
    vBGLayout->addWidget(m_BrushPreviewLbl);

    m_BrushLibView = new QListView(this);
    QHBoxLayout* hBGLayout = new QHBoxLayout;
    hBGLayout->addWidget(m_BrushLibView);
    hBGLayout->addLayout(vBGLayout);

    QWidget* MainBrushWork = new QWidget(this);
    MainBrushWork->setLayout(hBGLayout);

    /* This will appear under the Advanced Brush Tab */
    m_BrushWorkArea = new QLabel(this);
    m_brushPreview = QPixmap(100, 100);

    /* General Brush Properties */
    m_SizeLabel = new QLabel(this);
    m_SizeLabel->setText("Size:");
    m_SizeSlider = new QSlider(this);
    m_SizeSlider->setRange(0, 500);
    m_SizeSlider->setOrientation(Qt::Horizontal);
    m_SizeSlider->setValue(5);
    m_SizeLE = new QLineEdit(this);
    m_SizeLE->setFixedWidth(32);
    m_SizeLE->setText(QString::number(m_SizeSlider->value()));
    QHBoxLayout* hGSLayout = new QHBoxLayout;
    hGSLayout->addWidget(m_SizeLabel);
    hGSLayout->addWidget(m_SizeSlider);
    hGSLayout->addWidget(m_SizeLE);

    m_OpacityLabel = new QLabel(this);
    m_OpacityLabel->setText("Opacity:");
    m_OpacitySlider = new QSlider(this);
    m_OpacitySlider->setRange(0, 255);
    m_OpacitySlider->setOrientation(Qt::Horizontal);
    m_OpacitySlider->setValue(100);
    m_OpacityLE = new QLineEdit(this);
    m_OpacityLE->setFixedWidth(32);
    m_OpacityLE->setText(QString::number(m_OpacitySlider->value()));
    QHBoxLayout* hGOLayout = new QHBoxLayout;
    hGOLayout->addWidget(m_OpacityLabel);
    hGOLayout->addWidget(m_OpacitySlider);
    hGOLayout->addWidget(m_OpacityLE);

    QVBoxLayout* genBrushLayout = new QVBoxLayout;
    genBrushLayout->addLayout(hGSLayout);
    genBrushLayout->addLayout(hGOLayout);

    QWidget* GeneralBrushTab = new QWidget(this);
    GeneralBrushTab->setLayout(genBrushLayout);

    /* Transfer Brush Properties */
    m_TransferSizeCheck = new QCheckBox(this);
    m_TransferSizeCheck->setText("Size:");
    m_TransferSizeCheck->setCheckable(true);
    m_TransferSizeCheck->setChecked(false);
    m_TransferSizeSlider = new QSlider(this);
    m_TransferSizeSlider->setRange(0, 500);
    m_TransferSizeSlider->setOrientation(Qt::Horizontal);
    m_TransferSizeSlider->setValue(0);
    m_TransferSizeSlider->setEnabled(false);
    m_TransferSizeLE = new QLineEdit(this);
    m_TransferSizeLE->setFixedWidth(32);
    m_TransferSizeLE->setText(QString::number(m_TransferSizeSlider->value()));
    m_TransferSizeLE->setEnabled(false);
    QHBoxLayout* hTSLayout = new QHBoxLayout;
    hTSLayout->addWidget(m_TransferSizeCheck);
    hTSLayout->addWidget(m_TransferSizeSlider);
    hTSLayout->addWidget(m_TransferSizeLE);

    m_TransferOpacityCheck = new QCheckBox(this);
    m_TransferOpacityCheck->setText("Opacity:");
    m_TransferOpacityCheck->setCheckable(true);
    m_TransferOpacityCheck->setChecked(false);
    m_TransferOpacitySlider = new QSlider(this);
    m_TransferOpacitySlider->setRange(0, 100);
    m_TransferOpacitySlider->setValue(0);
    m_TransferOpacitySlider->setEnabled(false);
    m_TransferOpacitySlider->setOrientation(Qt::Horizontal);
    m_TransferOpacityLE = new QLineEdit(this);
    m_TransferOpacityLE->setFixedWidth(32);
    m_TransferOpacityLE->setEnabled(false);
    m_TransferOpacityLE->setText(QString::number(m_TransferOpacitySlider->value()));
    QHBoxLayout* hTOLayout = new QHBoxLayout;
    hTOLayout->addWidget(m_TransferOpacityCheck);
    hTOLayout->addWidget(m_TransferOpacitySlider);
    hTOLayout->addWidget(m_TransferOpacityLE);

    QVBoxLayout* tranBrushLayout = new QVBoxLayout;
    tranBrushLayout->addLayout(hTSLayout);
    tranBrushLayout->addLayout(hTOLayout);

    QWidget* TransferBrushTab = new QWidget(this);
    TransferBrushTab->setLayout(tranBrushLayout);

    m_BrushStack = new QStackedLayout;
    m_BrushStack->addWidget(MainBrushWork);

    m_BrushAttrib = new QTabWidget(this);
    m_BrushAttrib->addTab(GeneralBrushTab, "General");
    m_BrushAttrib->addTab(TransferBrushTab, "Transfer");

    QVBoxLayout* Layout = new QVBoxLayout;
    Layout->addLayout(m_BrushStack);
    Layout->addWidget(m_BrushAttrib);


    QWidget* DisplayWidget = new QWidget(this);
    DisplayWidget->setLayout(Layout);

    this->setWidget(DisplayWidget);

    connect(m_SizeLE, SIGNAL(textChanged(QString)), SLOT(UpdateSize(QString)));
    connect(m_SizeSlider, SIGNAL(valueChanged(int)), SLOT(UpdateSize(int)));
    connect(m_OpacityLE, SIGNAL(textChanged(QString)), SLOT(UpdateOpacity(QString)));
    connect(m_OpacitySlider, SIGNAL(valueChanged(int)), SLOT(UpdateOpacity(int)));
    connect(m_TransferSizeLE, SIGNAL(textChanged(QString)), SLOT(UpdateTransferSize(QString)));
    connect(m_TransferSizeSlider, SIGNAL(valueChanged(int)), SLOT(UpdateTransferSize(int)));
    connect(m_TransferOpacityLE, SIGNAL(textChanged(QString)), SLOT(UpdateTransferOpacity(QString)));
    connect(m_TransferOpacitySlider, SIGNAL(valueChanged(int)), SLOT(UpdateTransferOpacity(int)));
    connect(m_TransferSizeCheck, SIGNAL(toggled(bool)), SLOT(ToggleTransferSize(bool)));
    connect(m_TransferOpacityCheck, SIGNAL(toggled(bool)), SLOT(ToggleTransferOpacity(bool)));
}

void BrushDockWidget::UpdateSize(int val)
{
    m_SizeLE->setText(QString::number(val));
    emit BrushSizeChanged(val);
}

void BrushDockWidget::UpdateSize(QString val)
{
    m_SizeSlider->setValue(val.toInt());
    emit BrushSizeChanged(val.toInt());
}

void BrushDockWidget::UpdateOpacity(int val)
{
    m_OpacityLE->setText(QString::number(val));
    emit BrushOpacityChanged(val);
}

void BrushDockWidget::UpdateOpacity(QString val)
{
    m_OpacitySlider->setValue(val.toInt());
    emit BrushOpacityChanged(val.toInt());
}

void BrushDockWidget::UpdateTransferSize(int val)
{
    m_TransferSizeLE->setText(QString::number(val));
    emit BrushTransferSizeChanged(val);
}

void BrushDockWidget::UpdateTransferSize(QString val)
{
    m_TransferSizeSlider->setValue(val.toInt());
    emit BrushTransferSizeChanged(val.toInt());
}

void BrushDockWidget::UpdateTransferOpacity(int val)
{
    m_TransferOpacityLE->setText(QString::number(val));
    emit BrushTransferOpacityChanged(val);
}

void BrushDockWidget::UpdateTransferOpacity(QString val)
{
    m_TransferOpacitySlider->setValue(val.toInt());
    emit BrushTransferOpacityChanged(val.toInt());
}

void BrushDockWidget::ToggleTransferSize(bool val)
{
    if(val)
    {
        m_TransferSizeSlider->setEnabled(true);
        m_TransferSizeLE->setEnabled(true);
        emit BrushTransferSizeChanged(m_TransferSizeSlider->value());
    }else{
        m_TransferSizeSlider->setEnabled(false);
        m_TransferSizeLE->setEnabled(false);
        emit BrushTransferSizeChanged(0);
    }
}

void BrushDockWidget::ToggleTransferOpacity(bool val)
{
    if(val)
    {
        m_TransferOpacitySlider->setEnabled(true);
        m_TransferOpacityLE->setEnabled(true);
        emit BrushTransferOpacityChanged(m_TransferOpacitySlider->value());
    }else{
        m_TransferOpacitySlider->setEnabled(false);
        m_TransferOpacityLE->setEnabled(false);
        emit BrushTransferOpacityChanged(0);
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

