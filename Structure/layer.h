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
    Layer(LayerType type, int index, int width, int height);
    int getIndex(){ return m_currentIndex; }
    bool getFocusStatus()const{ return isFocus; }

    void setIndex(int indexVal){ m_currentIndex = indexVal; }
    void setFocus(bool val){ isFocus = val; }

    BitmapImage* getImage(){return m_Image;}
protected:
    Object *object;

private:
    bool isFocus;
    BitmapImage* m_Image;
    LayerType m_LayerType;
    int m_currentIndex;
};

#endif // LAYER_H
