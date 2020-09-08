#include "flyingprop.h"

FlyingProp::FlyingProp(QObject* parent) :BaseObject(parent)
{

}

FlyingProp::FlyingProp(int x, int y, int width, int height, const QString &imgPath, QObject *parent)
    :BaseObject(x,y,width,height,imgPath,parent)
{

}
