#include "layer.h"

Layer::Layer()
{

}

Layer::Layer(LayerType type, int index)
{
    m_LayerType = type;
    m_currentIndex = index;
    m_Opacity = 100;
    m_Visible = true;

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
    m_Opacity = 100;
    m_LayerType = type;
    m_currentIndex = index;
    m_Visible = true;
    if(m_LayerType == Bitmap)
    {
        m_Width = width;
        m_Height = height;
    }
    setFocus(true);
}

Layer::Layer(LayerType type, int width, int height)
{
    m_LayerType = type;
    m_Opacity = 100;
    m_Visible = true;
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

Layer::Layer(LayerType type, int width, int height, QColor col){
    m_LayerType = type;
    m_Opacity = 100;
    m_Visible = true;
    if(m_LayerType == Bitmap)
    {
        QRect size(0, 0, width, height);
        QColor color;
        if(frame.size() == 0){
            color = col;
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
    QRect size(0, 0, m_Width, m_Height);
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
