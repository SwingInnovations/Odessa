#ifndef PANELS_H
#define PANELS_H


#include <QWidget>
#include <QWidgetAction>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>

#include "slideedit.h"

/**
 * @brief The BrushConfigPanel class
 *
 */
class BrushConfigPanel : public QWidget
{
public:
    BrushConfigPanel(QWidget* parent = 0);
private:
    void initGUI();
    QPushButton* m_BrushModeBtn;
    QPushButton* m_StencilModeBtn;
};

class ColorConfigPanel : public QWidget{
public:
    ColorConfigPanel(QWidget* parent = 0);
};

#endif // PANELS_H
