#include "arrow.h"

Arrow::Arrow(QObject* parent):FlyingProp(parent)
{

}

Arrow::Arrow(int x, int y, int width, int height, QObject *parent)
    :FlyingProp(x,y,width,height,":/images/flyingprop/images/flyingprop/arrow.png",1000,1,parent)
{

}
