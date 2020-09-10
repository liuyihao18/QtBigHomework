#ifndef FIREBALL_H
#define FIREBALL_H

#include "flyingprop.h"

class FireBall : public FlyingProp {
    Q_OBJECT

public:

    FireBall(QObject *parent = nullptr);
    FireBall(int      x,
             int      y,
             int      width,
             int      height,
             int      directio_n,
             QObject *parent = nullptr);
};

#endif // FIREBALL_H
