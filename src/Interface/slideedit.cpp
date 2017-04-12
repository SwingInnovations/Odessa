#include "slideedit.h"

SlideBoundsDialog::SlideBoundsDialog(){
    setWindowTitle("Bounds Properties");
    m_minBoundsLE = new QLineEdit(this);
    m_minBoundsLE->setText(QString::number(0));
    m_maxBoundsLE = new QLineEdit(this);
    m_maxBoundsLE->setText(QString::number(10));

    auto minLayout = new QHBoxLayout;
    minLayout->addWidget(new QLabel("Min: ", this));
    minLayout->addWidget(m_minBoundsLE);

    auto maxLayout = new QHBoxLayout;
    maxLayout->addWidget(new QLabel("Max: ", this));
    maxLayout->addWidget(m_maxBoundsLE);

    auto okBtn = new QPushButton("Ok", this);
    auto cancelBtn = new QPushButton("Cancel",this);

    auto propLayout = new QVBoxLayout;
    propLayout->addLayout(minLayout);
    propLayout->addLayout(maxLayout);

    auto propBox = new QGroupBox("Properties:", this);
    propBox->setLayout(propLayout);

    auto btnLayout = new QHBoxLayout;
    btnLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);

    auto centralLayout = new QVBoxLayout;
    centralLayout->addWidget(propBox);
    centralLayout->addLayout(btnLayout);

    setLayout(centralLayout);

    connect(okBtn, SIGNAL(clicked()), SLOT(changeBounds()));
    connect(cancelBtn, SIGNAL(clicked()), SLOT(close()));
}

SlideBoundsDialog::~SlideBoundsDialog()
{

}

void SlideBoundsDialog::updateBounds(qreal min, qreal max)
{
    m_minBoundsLE->setText(QString::number(min));
    m_maxBoundsLE->setText(QString::number(max));
}

void SlideBoundsDialog::changeBounds(){
    emit boundsChanged((qreal)m_minBoundsLE->text().toFloat(),
                       (qreal)m_maxBoundsLE->text().toFloat());
    close();
}


SlideEdit::SlideEdit(QWidget *parent) : QLineEdit(parent)
{
    m_Min = 0.0;
    m_Max = 10.0;
    setCurrentValue(10);
    m_foregroundColor = QColor(83, 125, 148).lighter(120);
    m_foregroundColor.setAlphaF(0.7);
    m_lockBounds = false;
    m_intStep = false;

    this->setAlignment(Qt::AlignCenter);

    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    m_isDown = false;

    m_boundsDialog = new SlideBoundsDialog();
    m_boundsDialog->hide();

    m_revertLowerBoundAct = new QAction("Resert Lower Bounds", this);
    m_revertUpperBoundAct = new QAction("Revert Upper Bound", this);
    m_editBoundsAct = new QAction("Edit Bounds", this);
    m_lockBoundsAct = new QAction("Lock Bounds", this);
    m_intStepAct = new QAction("Integer Step", this);

    m_intStepAct->setCheckable(true);
    m_intStepAct->setChecked(m_intStep);

    m_lockBoundsAct->setCheckable(true);
    m_lockBoundsAct->setChecked(m_lockBounds);

    connect(m_revertLowerBoundAct, SIGNAL(triggered()), SLOT(resetLowerBound()));
    connect(m_revertUpperBoundAct, SIGNAL(triggered()), SLOT(resetUpperBound()));
    connect(m_lockBoundsAct, SIGNAL(triggered(bool)), SLOT(toggleLockBounds(bool)));
    connect(m_editBoundsAct, SIGNAL(triggered()), SLOT(editBounds()));
    connect(m_intStepAct, SIGNAL(triggered(bool)), SLOT(toggleIntStep(bool)));

    connect(this, SIGNAL(textChanged(QString)), SLOT(updateValue(QString)));
    connect(m_boundsDialog, SIGNAL(boundsChanged(qreal,qreal)), SLOT(updateBounds(qreal,qreal)));
}

void SlideEdit::setLowerbound(const qreal value)
{
    if(!m_lockBounds){
        if(value <= 0.0) m_Min = 0.0;
        else m_Min = value;
    }
}

void SlideEdit::setUpperBound(const qreal value)
{
    if(!m_lockBounds){
        m_Max = value;
        if(m_Max < m_currentValue) m_currentValue = m_Max;
    }

}

void SlideEdit::setCurrentValue(const qreal value)
{
    if(!m_intStep) m_currentValue = value;
    else{
        if(value < 0.5f) m_currentValue = 0;
        else m_currentValue = ceil(value);
    }
    if(m_currentValue > m_Max && !m_lockBounds){
        m_Max = value;
    }
    setText(QString::number(m_currentValue));
    emit valueChanged(m_currentValue);
}

void SlideEdit::mouseMoveEvent(QMouseEvent *event)
{
    if(m_handle.contains(event->pos())){
        setCursor(QCursor(Qt::ArrowCursor));
    }else{
        setCursor(QCursor(Qt::IBeamCursor));
    }
    if(m_isDown){
        auto px = event->pos().x();
        if(px >= 0 && px <= width()){
            m_handle.setX(px);
            m_lockBounds = true;
            setCurrentValue(((qreal)px / (qreal)width()) * m_Max);
            m_lockBounds = false;
        }
    }
}

void SlideEdit::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && m_handle.contains(event->pos()))m_isDown = true;
}

void SlideEdit::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_isDown) m_isDown = false;
}

void SlideEdit::wheelEvent(QWheelEvent *e)
{
    qreal numSteps = e->delta() / 15.0f;
    qreal currentValue = m_currentValue - numSteps;
    if(m_lockBounds){
        if(currentValue > m_Max) setCurrentValue(m_Max);
        else if(currentValue < m_Min) setCurrentValue(m_Min);
        else setCurrentValue(currentValue);
        e->accept();
        return;
    }
    setCurrentValue(currentValue);
    e->accept();
}

void SlideEdit::paintEvent(QPaintEvent *paintEvent)
{
    QLineEdit::paintEvent(paintEvent);
    auto ratio = m_currentValue / m_Max;
    auto pX = ratio * this->geometry().width();

    if(pX <= 12) {
        m_handle.setX(m_Min);
        setCurrentValue(m_Min);
    }else        m_handle.setX(pX - 12);

    m_handle.setY(0);
    m_handle.setWidth(12);
    m_handle.setHeight(this->height());

    m_progressed.setX(0);
    m_progressed.setY(0);
    m_progressed.setWidth(m_handle.x());
    m_progressed.setHeight(this->height());

    QPainter p(this);
    p.setBrush(QBrush(Qt::white));
    p.drawRect(m_handle);
    p.fillRect(m_handle, QBrush(Qt::white));
    if(this->isEnabled()) p.setBrush(QBrush(m_foregroundColor));
    else p.setBrush(QColor(128, 128, 128));
    p.drawRect(m_progressed);
}

void SlideEdit::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu menu(this);
    menu.addAction(m_revertLowerBoundAct);
    menu.addAction(m_revertUpperBoundAct);
    menu.addSeparator();
    menu.addAction(m_lockBoundsAct);
    menu.addAction(m_editBoundsAct);
    menu.addAction(m_intStepAct);
    menu.exec(e->globalPos());
}

void SlideEdit::updateValue(QString value)
{
    qreal val = (qreal)value.toDouble();
    setCurrentValue(val);
}

void SlideEdit::toggleLockBounds(bool flag)
{
    m_lockBounds = flag;
}

void SlideEdit::updateBounds(qreal min, qreal max)
{
    setLowerbound(min);
    setUpperBound(max);
    if(m_currentValue > max) setCurrentValue(max);
    update();
}

void SlideEdit::resetLowerBound(){
    m_Min = 0;
}

void SlideEdit::resetUpperBound(){
    m_Max = 10;
}

void SlideEdit::editBounds()
{
    m_boundsDialog->updateBounds(m_Min, m_Max);
    m_boundsDialog->exec();
}

void SlideEdit::toggleIntStep(bool value)
{
    useIntegerStep(value);
}
