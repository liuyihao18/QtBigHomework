#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "flyingprop.h"

class Launcher {
public:

    Launcher(int _launchInteval = 100);
    virtual FlyingProp* launchFlyingProp() = 0;
    bool                canLaunch() const;
    void                launch();
    void                ready();

protected:

    int _launchInteval;
    bool _launched;
};

#endif // LAUNCHER_H
