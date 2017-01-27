#include "panels.h"

BrushConfigPanel::BrushConfigPanel(QWidget *parent) : QWidget(parent)
{
    initGUI();
    //TODO Hookup signals and slots.
}

void BrushConfigPanel::initGUI()
{
    m_BrushModeBtn = new QPushButton("Brush", this);
    m_StencilModeBtn = new QPushButton("Stencil", this);

    auto modeLayout = new QHBoxLayout;
    modeLayout->addWidget(m_BrushModeBtn);
    modeLayout->addWidget(m_StencilModeBtn);

    auto centralLayout = new QVBoxLayout;
    centralLayout->addLayout(modeLayout);
    setLayout(centralLayout);
}
