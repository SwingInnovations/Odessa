#ifndef OVERLOADS_H
#define OVERLOADS_H

#include "Structure/brush.h"
#include <QtCore>
#include <QDataStream>


inline QDataStream &operator <<(QDataStream &out, const Brush &brush){
    out << brush.GetSWidth() << brush.GetSHeight() << brush.getHardness() << brush.getRotate() << brush.GetSpacing();
    return out;
}

inline QDataStream &operator >>(QDataStream &in, Brush &brush){
    brush = Brush();
    in >> brush.sWidth >> brush.sHeight >> brush.mHardness >> brush.mRotate >> brush.mSpacing;
    return in;
}

#endif // OVERLOADS_H
