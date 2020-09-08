#include "fireball.h"

FireBall::FireBall(QObject* parent):FlyingProp(parent)
{

}

FireBall::FireBall(int x, int y, int width, int height, QObject *parent)
    :FlyingProp(x,y,width,height,":/images/flyingprop/images/flyingprop/fireball.png",1000,1,parent)
{

}
