#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "flyingprop.h"

class Launcher
{
public:
    Launcher(int launchInteval = 100);
    virtual FlyingProp* emitFlyingProp() = 0;
    bool canLaunch() const;
    void launch();
    void ready();

protected:
    int launchInteval;
    bool launched;

};

#endif // LAUNCHER_H
