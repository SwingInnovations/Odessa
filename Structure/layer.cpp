#include "layer.h"

Layer::Layer()
{

}

Layer::Layer(LayerType type, int index)
{
    m_LayerType = type;
    m_currentIndex = index;

    if(type==Bitmap)
    {
        m_Image = new BitmapImage();
    }
}
