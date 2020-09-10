#include "launcher.h"

Launcher::Launcher(int launchInteval) : _launchInteval(launchInteval), _launched(
        false)
{}

bool Launcher::canLaunch() const
{
    return !_launched;
}

void Launcher::launch()
{
    _launched = true;
}

void Launcher::ready()
{
    _launched = false;
}
