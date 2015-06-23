#ifndef LAYER_H
#define LAYER_H

#include<QVector>
#include "object.h"
#include "../Graphics/Bitmap/bitmapimage.h"


class Layer : public Object
{
public:
    enum LayerType{Bitmap, Sound, Bitmap_Blank};

    Layer();
    Layer(LayerType type){m_LayerType = type;}
    Layer(LayerType type, int index);
    Layer(LayerType type, int width, int height);
    Layer(LayerType type, int width, int height, QColor col);
    Layer(LayerType type, int index, int width, int height);

    int getIndex(){ return m_currentIndex; }
    int getOpacity(){ return m_Opacity;}
    int getCompositionMode()const{ return m_CompositionMode; }
    int getFrameIndeX(){ return mFrameIndex; }
    int getFrameListSize(){return frame.size();}
    bool isVisible(){ return m_Visible; }
    BitmapImage *getFrame(int frameIndex){return frame.at(frameIndex);}
    bool getFocusStatus()const{ return isFocus; }

    void setIndex(int indexVal){ m_currentIndex = indexVal; }
    void setFocus(bool val){ isFocus = val; }

    void setOpacity(int);
    void setCompositionMode(int);
    void setVisible(bool val){ m_Visible = val; }

    void createFrame();
    void createFrameB();

    BitmapImage* getImage(){return m_Image;}
protected:
    Object *object;

private:
    bool isFocus;
    BitmapImage* m_Image;
    LayerType m_LayerType;
    int m_currentIndex;
    int mFrameIndex;
    int mWidth, mHeight;
    int m_Opacity;
    int m_CompositionMode;
    bool m_Visible;

    QVector<BitmapImage*> frame;
};

#endif // LAYER_H
