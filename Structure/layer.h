#ifndef LAYER_H
#define LAYER_H

#include "object.h"
#include "Graphics/Bitmap/bitmapimage.h"

enum LayerType{Bitmap, Sound};

class Layer
{
public:
    Layer();
    Layer(LayerType type){m_LayerType = type;}
    Layer(LayerType type, int index){ m_LayerType = type; m_currentIndex = index; }
    int getIndex(){ return m_currentIndex; }

    void setIndex(int indexVal){ m_currentIndex = indexVal; }

private:
    BitmapImage* m_Image;
    LayerType m_LayerType;
    int m_currentIndex;
};

#endif // LAYER_H
