#ifndef LAYER_H
#define LAYER_H

#include "object.h"
#include "Graphics/Bitmap/bitmapimage.h"


class Layer : public Object
{
public:
    enum LayerType{Bitmap, Sound};

    Layer();
    Layer(LayerType type){m_LayerType = type;}
    Layer(LayerType type, int index);
    int getIndex(){ return m_currentIndex; }

    void setIndex(int indexVal){ m_currentIndex = indexVal; }

protected:
    Object object;

private:
    BitmapImage* m_Image;
    LayerType m_LayerType;
    int m_currentIndex;
};

#endif // LAYER_H
