#include "launcher.h"

Launcher::Launcher(int launchInteval):launchInteval(launchInteval),launched(false)
{

}

bool Launcher::canLaunch() const
{
    return !launched;
}

void Launcher::launch()
{
    launched = true;
}

void Launcher::ready()
{
    launched = false;
}

