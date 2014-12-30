#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QString>

class Object
{
public:
    Object();
    Object(QString name, int index);

    void setModified(bool val){ modified = val; }
    void setName(QString name){ this->name = name; }
    void setIndex(int index){ this->index = index; }

    bool isModified(){ return modified; }
    QString getName(){ return name; }
    int getIndex(){ return index; }

private:
    bool modified;
    QString name;
    int index;
};

#endif // OBJECT_H
