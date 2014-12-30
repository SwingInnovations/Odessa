#include "object.h"

Object::Object()
{

}

Object::Object(QString name, int index){
    this->name = name;
    this->index = index;
    setModified(true);
}
