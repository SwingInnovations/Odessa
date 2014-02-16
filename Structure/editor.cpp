#include "editor.h"

Editor::Editor(QWidget *parent): QWidget(parent), currentFrame(0), currentIndex(0), numOfFramesPerSecond(24)
{
    deviceDown = false;
    setAutoFillBackground(true);
    //addLayer(this->size().width(), this->size().height());
    brush.setBrush(QBrush(Qt::SolidLine));
    brush.setColor(QColor(0, 0, 0, 255));
    brush.getPen().setWidth(5);
    brush.getPen().setColor(brush.getColor());

    qDebug() << "KnownPos" << knownPos << endl;
}

void Editor::paintEvent(QPaintEvent *event)
{
    qDebug() << "Painting" << endl;
    QPainter painter(this);
    if(!mIndex.isEmpty())
    {
        if(deviceDown)
        {
            mIndex.at(0)->getImage()->paintImage(painter, knownPos, brush, drawPath);
            qDebug() << "Is Painting" << endl;
        }
        mIndex.at(0)->getImage()->paintImage(painter);
    }
}

void Editor::mousePressEvent(QMouseEvent *event)
{
   if(!mIndex.isEmpty())
   {
    for(int i = 0; i < mIndex.size(); i++)
    {
        //QColor color(0, 255, 0, 255);
        //mIndex.at(0)->getImage()->setColor(color);
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
    switch(event->type())
    {
    case QEvent::TabletPress:
        if(!deviceDown)
        {
            deviceDown = true;
            drawPath[0] = drawPath[1] = drawPath[2] = event->pos();
            knownPos = event->pos();
            qDebug() << "KnownPos" << knownPos << endl;
        }
        break;
    case QEvent::TabletRelease:
        if(deviceDown)
        {
            deviceDown = false;
        }
        qDebug() << "Tablet Released" << endl;
        qDebug() << "KnownPos" << knownPos << endl;
        break;
    case QEvent::TabletMove:
        drawPath[2] = drawPath[1];
        drawPath[1] = drawPath[0];
        drawPath[0] = event->pos();
        knownPos = event->pos();
        qDebug() << "KnownPos" << knownPos << endl;
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

void Editor::newProject(int type, int width, int height, int dpi)
{
    mIndex.clear();
    int dpm = dpi/0.0254;
    switch(type)
    {
    case 0:
        //create Standard Image
        mIndex.append(new Layer(Layer::Bitmap, currentIndex, width, height));
        mIndex.at(0)->getImage()->getImage()->setDotsPerMeterX(dpm);
        mIndex.at(0)->getImage()->getImage()->setDotsPerMeterY(dpm);
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
    update();
}
