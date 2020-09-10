#include "fireball.h"

FireBall::FireBall(QObject *parent) : FlyingProp(parent)
{}

FireBall::FireBall(int      x,
                   int      y,
                   int      width,
                   int      height,
                   int      direction,
                   QObject *parent)
    : FlyingProp(x,
                 y,
                 width,
                 height,
                 ":/images/flyingprop/images/flyingprop/fireBall.png",
                 direction,
                 750,
                 1,
                 parent)
{}
