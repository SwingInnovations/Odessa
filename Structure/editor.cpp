#include "editor.h"

Editor::Editor(QWidget *parent): QWidget(parent), currentFrame(0), currentIndex(0), numOfFramesPerSecond(24)
{
    deviceDown = false;
    setAutoFillBackground(true);
    brush = Brush();
    brush.setBrush(QBrush(Qt::SolidLine));
    brush.setColor(Qt::red);
    brush.getPen().setWidth(20);
    brush.getPen().setColor(brush.getColor());

    qDebug() << "KnownPos" << knownPos << endl;
}

void Editor::paintEvent(QPaintEvent *event)
{
    qDebug() << "Painting" << endl;
    QPainter painter(this);
    if(!mIndex.isEmpty())
    {
        mIndex.at(currentIndex-1)->getImage()->paintImage(painter);
    }

    if(!rIndex.isEmpty())
    {
        rIndex.at(currentFrame-1)->getImage()->paintImage(painter);
    }

}

void Editor::mousePressEvent(QMouseEvent *event)
{
    if(!mIndex.isEmpty() || !rIndex.isEmpty())
    {
        deviceDown = true;
        drawPath[0] = drawPath[1] = drawPath[2] = event->pos();
    }
    qDebug() << "Mouse Pressed" << endl;
    update();
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    if(deviceDown)
    {
        deviceDown = false;
    }
    update();
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{
    QPixmap tempPixMap = mIndex.at(0)->getImage()->getPixmap();

    QPainter painter(&tempPixMap);

    drawPath[2] = drawPath[1];
    drawPath[1] = drawPath[0];
    drawPath[0] = event->pos();
    knownPos = event->pos();

    if(deviceDown)
    {
        mIndex.at(0)->getImage()->paintImage(event, brush, drawPath);
    }
    update();
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
            //qDebug() << "KnownPos" << knownPos << endl;
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

        if(deviceDown)
        {
            mIndex.at(currentIndex-1)->getImage()->paintImage(event, brush, drawPath);
        }

        qDebug() << "KnownPos" << knownPos << endl;
    default:
        break;
        qDebug() << "Nothing Happening" << endl;
    }

    if(event->type() == QEvent::TabletEnterProximity)
    {
        qDebug() << "Entered Proximity" << endl;
    }
    update();
    qDebug() << "currentFrame"<< currentIndex << endl;
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
    switch(type)
    {
    case 0:
        //create Standard Image
        mIndex.append(new Layer(Layer::Bitmap, currentIndex, width, height));
        currentIndex++;
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
