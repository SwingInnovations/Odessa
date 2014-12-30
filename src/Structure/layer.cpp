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
        //m_Image = new BitmapImage(temp, color);
    }
    setFocus(true);
}

Layer::Layer(LayerType type, int index, int width, int height)
{
    m_LayerType = type;
    m_currentIndex = index;
    if(m_LayerType == Bitmap)
    {
//        QRect size(0, 0, width, height);
//        QColor color(255, 255, 255, 255);
//        m_Image = new BitmapImage(size, color);
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
        QColor color(Qt::white);
        frame.push_back(new BitmapImage(size, color));
    }else if(m_LayerType == Bitmap_Blank){
        QRect size(0, 0, width, height);
        QColor color(Qt::transparent);
        m_Image = new BitmapImage(size, color);
    }else{
        qDebug() << "Invalid Type!";
    }
}

void Layer::createFrame()
{
    QRect size(0, 0, mWidth, mHeight);
    QColor color(Qt::white);
    m_Image = new BitmapImage(size, color);
    frame.push_back(m_Image);
    qDebug() << "Status of Image" << frame.at(0) << endl;
}
