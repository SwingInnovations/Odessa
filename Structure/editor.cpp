#include "editor.h"

Editor::Editor(QWidget *parent): QWidget(parent), currentFrame(0), currentIndex(0), numOfFramesPerSecond(24)
{
    deviceDown = false;
    addLayer(this->size().width(), this->size().height());
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
   if(!mIndex.isEmpty())
   {
    for(int i = 0; i < mIndex.size(); i++)
    {
        QColor color(0, 255, 0, 255);
        mIndex.at(0)->getImage()->setColor(color);
    }
   }

    qDebug() << "Mouse Pressed" << endl;
    update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{

}

void Editor::tabletEvent(QTabletEvent *event)
{
    QColor color(0, 0, 100, 255);
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

void Editor::addLayer(int width, int height)
{
    mIndex.append(new Layer(Layer::Bitmap, currentIndex, width, height));
    currentIndex++;
    qDebug() << "Image Drawn!" << endl;
    qDebug() << "Image Layer count: " << currentIndex << endl;
}

void Editor::newProject(int type, int width, int height)
{
    switch(type)
    {
    case 0:
        //create Standard Image
        mIndex.append(new Layer(Layer::Bitmap, currentIndex, width, height));
        break;
    case 1:
        //create Animation
        break;
    case 2:
        //create SpriteSheet
        break;
    default:
        break;
    }
}
