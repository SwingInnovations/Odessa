#include "editor.h"

Editor::Editor(QWidget *parent): QWidget(parent), currentFrame(0), currentIndex(0), numOfFramesPerSecond(24)
{
    addLayer();
}

void Editor::paintEvent(QPaintEvent *event)
{
    qDebug() << "Painting" << endl;
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse Pressed" << endl;
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{

}

void Editor::addLayer()
{
    mIndex.append(new Layer(Layer::Bitmap, currentIndex));
    currentIndex++;
    qDebug() << "Image Drawn!" << endl;
}
