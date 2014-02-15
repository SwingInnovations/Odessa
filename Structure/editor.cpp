#include "editor.h"

Editor::Editor(QWidget *parent): QWidget(parent), currentFrame(0), currentIndex(0), numOfFramesPerSecond(24)
{
    addLayer();
}

void Editor::paintEvent(QPaintEvent *event)
{
    qDebug() << "Painting" << endl;
    QPainter painter(this);
    if(!mIndex.isEmpty())
    {
        mIndex.at(0)->getImage()->paintImage(painter);
    }
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    QColor color(0, 255, 0, 255);
    mIndex.at(0)->getImage()->setColor(color);

    qDebug() << "Mouse Pressed" << endl;
    update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{

}

void Editor::tabletEvent(QTabletEvent *event)
{
    QColor color(0, 255, 0, 255);
    switch(event->type())
    {
    case QEvent::TabletPress:
        mIndex.at(0)->getImage()->setColor(color);
        qDebug() << "Tablet Pressed" << endl;
        break;
    case QEvent::TabletRelease:
        qDebug() << "Tablet Released" << endl;
        break;
    default:
        qDebug() << "Nothing Happening" << endl;
    }
    update();
}

void Editor::addLayer()
{
    mIndex.append(new Layer(Layer::Bitmap, currentIndex));
    currentIndex++;
    qDebug() << "Image Drawn!" << endl;
    qDebug() << "Image Layer count: " << currentIndex << endl;
}
