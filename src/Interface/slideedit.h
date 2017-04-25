#ifndef SLIDEEDIT_H
#define SLIDEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QMenu>
#include <QAction>
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include <QWheelEvent>

class SlideEdit;

class SlideBoundsDialog : public QDialog{
  Q_OBJECT
public:
    SlideBoundsDialog();
    ~SlideBoundsDialog();
    void updateBounds(qreal, qreal);
signals:
    void boundsChanged(qreal, qreal);
private slots:
    void changeBounds();
private:
    QLineEdit* m_minBoundsLE;
    QLineEdit* m_maxBoundsLE;
};

class SlideEdit : public QLineEdit
{
    Q_OBJECT
public:
    SlideEdit(QWidget* parent = 0);
    void setLowerbound(const qreal value);
    void setUpperBound(const qreal value);
    void setCurrentValue(const qreal value);
    void setHighlightColor(QColor color){ m_foregroundColor = color; }
    void useIntegerStep(bool value){ m_intStep = value; }
    void lockBounds(bool value){ m_lockBounds = value; }                //TODO - Allow this to update the status of other menu.
    qreal getMin(){ return m_Min; }
    qreal getMax(){ return m_Max; }
    qreal getValue(){ return m_currentValue; }
signals:
    void valueChanged(qreal);
protected:
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* e);
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);
private slots:
    void updateValue(QString);
    void toggleLockBounds(bool);
    void updateBounds(qreal,qreal);
    void resetLowerBound();
    void resetUpperBound();
    void editBounds();
    void toggleIntStep(bool);
private:
    bool    m_isDown;
    bool    m_lockBounds;
    QRect   m_handle;
    QRect   m_progressed;
    qreal   m_Min;
    qreal   m_Max;
    qreal   m_currentValue;
    QColor  m_backgroundColor;
    QColor  m_foregroundColor;
    QMenu*  m_contextMenu;
    bool    m_intStep;

    QAction* m_revertLowerBoundAct;
    QAction* m_revertUpperBoundAct;
    QAction* m_editBoundsAct;
    QAction* m_lockBoundsAct;
    QAction* m_intStepAct;

    SlideBoundsDialog* m_boundsDialog;
};

#endif // SLIDEEDIT_H
