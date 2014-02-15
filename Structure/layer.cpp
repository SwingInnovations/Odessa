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
        QColor color(255, 0, 0, 255);
        m_Image = new BitmapImage(temp, color);
    }
}

Layer::Layer(LayerType type, int index, int width, int height)
{
    m_LayerType = type;
    m_currentIndex = index;
    if(m_LayerType == Bitmap)
    {
        QRect size(0, 0, width, height);
        QColor color(0, 0, 0, 255);
        m_Image = new BitmapImage(size, color);
    }
}
