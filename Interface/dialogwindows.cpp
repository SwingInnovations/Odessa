#include "dialogwindows.h"

OdessaNewDocDialog::OdessaNewDocDialog()
{
    //initialize a few things
    setWindowTitle("New Canvas");
    setModal(true);

    resize(176, 186);
    setFixedSize(this->size());

    optionsComboBox = new QComboBox(this);
    optionsComboBox->addItem("Standard Image");
    optionsComboBox->addItem("Animation");
    optionsComboBox->addItem("SpriteSheet");

    m_WidthLabel = new QLabel("Width: ", this);
    m_HeightLabel = new QLabel("Height: ", this);
    m_dpiLabel = new QLabel("DPI: ", this);

    m_widthLineEdit = new QLineEdit(this);
    m_heightLineEdit = new QLineEdit(this);
    m_dpiLineEdit = new QLineEdit(this);

    createButton = new QPushButton("&Create", this);
    cancelButton = new QPushButton("&Cancel", this);

    labelLayout = new QVBoxLayout();
    labelLayout->addWidget(m_WidthLabel);
    labelLayout->addWidget(m_HeightLabel);
    labelLayout->addWidget(m_dpiLabel);

    lineEditLayout = new QVBoxLayout();
    lineEditLayout->addWidget(m_widthLineEdit);
    lineEditLayout->addWidget(m_heightLineEdit);
    lineEditLayout->addWidget(m_dpiLineEdit);

    labelAndLineLayout = new QHBoxLayout();
    labelAndLineLayout->addLayout(labelLayout);
    labelAndLineLayout->addLayout(lineEditLayout);

    totalLayout = new QVBoxLayout();
    totalLayout->addWidget(optionsComboBox);
    totalLayout->addLayout(labelAndLineLayout);

    descripGroupBox = new QGroupBox(this);
    descripGroupBox->setTitle("Properties:");
    descripGroupBox->setLayout(totalLayout);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(cancelButton);

    finalLayout = new QVBoxLayout;
    finalLayout->addWidget(descripGroupBox);
    finalLayout->addLayout(buttonLayout);

    setLayout(finalLayout);

    connect(createButton, SIGNAL(clicked()), SLOT(newProjectSlot()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(close()));
}

OdessaNewDocDialog::~OdessaNewDocDialog()
{

}

void OdessaNewDocDialog::newProjectSlot()
{
    int type = optionsComboBox->currentIndex();
    int width = m_widthLineEdit->text().toInt();
    int height = m_heightLineEdit->text().toInt();
    int dpi = m_dpiLineEdit->text().toInt();
    emit newProject(type, width, height, dpi);

    close();
}

OdessaPrefDialog::OdessaPrefDialog()
{
    setWindowTitle("Preferences");
    setModal(true);

    contentWidget = new QListWidget(this);
    contentWidget->setMaximumWidth(128);

    pagesWidget = new QStackedWidget(this);
    pagesWidget->addWidget(new GeneralPrefPage);

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

}

OdessaPrefDialog::~OdessaPrefDialog()
{

}

GeneralPrefPage::GeneralPrefPage(QWidget *parent) : QWidget(parent)
{

}

GeneralPrefPage::~GeneralPrefPage()
{

}

