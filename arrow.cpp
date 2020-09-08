#include "arrow.h"

Arrow::Arrow(QObject* parent):FlyingProp(parent)
{

}

Arrow::Arrow(int x, int y, int width, int height, int direction, QObject *parent)
    :FlyingProp(x,y,width,height,":/images/flyingprop/images/flyingprop/arrow.png",direction,1000,1,parent)
{

}
