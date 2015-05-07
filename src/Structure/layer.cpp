#include "layer.h"

Layer::Layer()
{

}

Layer::Layer(LayerType type, int index)
{
    m_LayerType = type;
    m_currentIndex = index;

    object = new Object();

    if(type==Bitmap)
    {
        QRect temp(0, 0, 10000, 10000);
        QColor color(255, 255, 255, 255);
    }
    setFocus(true);
}

Layer::Layer(LayerType type, int index, int width, int height)
{
    m_LayerType = type;
    m_currentIndex = index;
    if(m_LayerType == Bitmap)
    {
        mWidth = width;
        mHeight = height;
    }
    setFocus(true);
}

Layer::Layer(LayerType type, int width, int height)
{
    m_LayerType = type;
    if(m_LayerType == Bitmap)
    {
        QRect size(0, 0, width, height);
        QColor color;
        if(frame.size() == 0){
            color = QColor(Qt::white);
        }else{
            color = QColor(Qt::transparent);
        }
        frame.push_back(new BitmapImage(size, color));
    }else if(m_LayerType == Bitmap_Blank){
        QRect size(0, 0, width, height);
        QColor color(Qt::transparent);
        frame.push_back(new BitmapImage(size, color));
    }else{
        qDebug() << "Invalid Type!";
    }
}

void Layer::createFrame()
{
    QRect size(0, 0, mWidth, mHeight);
    QColor color;
    if(frame.size() == 0){
        color = QColor(Qt::white);
    }else{
        color = QColor(Qt::transparent);
    }
    frame.push_back(new BitmapImage(size, color));
    qDebug() << "Status of Image" << frame.at(0) << endl;
}

void Layer::setOpacity(int o){
    m_Opacity = o;
}

void Layer::setCompositionMode(int comp){
    m_CompositionMode = comp;
}
