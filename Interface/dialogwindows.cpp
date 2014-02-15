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

    connect(cancelButton, SIGNAL(clicked()), SLOT(close()));
}

OdessaNewDocDialog::~OdessaNewDocDialog()
{

}

