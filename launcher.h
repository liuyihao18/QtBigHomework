#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "flyingprop.h"

class Launcher
{
public:
    Launcher();
    virtual FlyingProp* emitFlyingProp() = 0;
};

#endif // LAUNCHER_H
