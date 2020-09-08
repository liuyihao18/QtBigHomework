#include "magicbullet.h"

MagicBullet::MagicBullet(QObject* parent): FlyingProp(parent)
{

}

MagicBullet::MagicBullet(int x, int y, int width, int height, int direction, QObject *parent)
    :FlyingProp(x,y,width,height,":/images/flyingprop/images/flyingprop/magicbullet.png",direction,1000,1,parent)
{

}
