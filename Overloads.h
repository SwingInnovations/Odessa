#ifndef OVERLOADS_H
#define OVERLOADS_H

#include <QVariant>
#include <QtCore>
#include <QDataStream>

Q_DECLARE_METATYPE(Brush)

#include "Structure/brush.h"

inline QDataStream &operator <<(QDataStream &out, const Brush &brush);
inline QDataStream &operator >>(QDataStream &in, Brush &brush);


inline QDataStream &operator <<(QDataStream &out, const Brush &brush){
    out << brush.getSWidth() << brush.getSHeight() << brush.getHardness() << brush.getRotate() << brush.getSpacing() << brush.getStencil() << brush.getName();
    return out;
}

inline QDataStream &operator >>(QDataStream &in, Brush &brush){
    brush = Brush();
    in >> brush.sWidth >> brush.sHeight >> brush.mHardness >> brush.mRotate >> brush.mSpacing >> brush.mStencil >> brush.mName;
    return in;
}

#endif // OVERLOADS_H
