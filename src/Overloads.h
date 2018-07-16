#ifndef OVERLOADS_H
#define OVERLOADS_H

#include <QVariant>
#include <QtCore>
#include <QDataStream>
#include <QPoint>

#include "Structure/brush.h"
#include "Interface/dialogwindows.h"

Q_DECLARE_METATYPE(Brush)

inline QDataStream &operator <<(QDataStream &out, const Brush &brush);
inline QDataStream &operator >>(QDataStream &in, Brush &brush);
inline QDataStream &operator <<(QDataStream &out, const ProjectInfo &info);
inline QDataStream &operator >>(QDataStream &in, ProjectInfo &info);
inline QPoint &operator *(QPoint p, int scaleFactor);

inline QDataStream &operator <<(QDataStream &out, const Brush &brush){
    out << brush.getSWidth() << brush.getSHeight() << brush.getHardness() << brush.getRotate() << brush.getSpacing() << brush.getStencil() << brush.getName();
    return out;
}

inline QDataStream &operator >>(QDataStream &in, Brush &brush){
    brush = Brush();
    in >> brush.s_Width >> brush.s_Height >> brush.m_hardness >> brush.m_rotate >> brush.m_Spacing >> brush.m_Stencil >> brush.m_Name;
    return in;
}

inline QDataStream &operator <<(QDataStream &out, const ProjectInfo &info){
    out << info.getWidth() << info.getHeight() << info.getDPI() << info.getType() << info.getFrameCount() << info.getFPS() << info.getSpriteCount_Row() << info.getSpriteCount_Col();
}

inline QDataStream &operator >>(QDataStream &in, ProjectInfo &info){
    info = ProjectInfo();
    int w, h, d, t, fc, f, sr, sc;
    in >> w >> h >> d >> t >> fc >> f >> sr >> sc;
    info.setWidth(w);
    info.setHeight(h);
    info.setDPI(d);
    info.setType(t);
    info.setFrameCount(fc);
    info.setFPS(f);
    info.setSpriteCount_Row(sr);
    info.setSpriteCount_Col(sc);
    return in;
}

inline QPoint &operator *(QPoint p, int scaleFactor){
    int _x = p.x() * scaleFactor;
    int _y = p.y() * scaleFactor;
    p.setX(_x);
    p.setY(_y);
    return p;
}


#endif // OVERLOADS_H
