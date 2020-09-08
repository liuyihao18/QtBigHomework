#include "arrowterrain.h"

ArrowTerrain::ArrowTerrain(QObject* parent): Terrain(parent)
{

}

ArrowTerrain::ArrowTerrain(int x, int y, int width, int height, QObject *parent)
    :Terrain(x,y,width,height,":/images/trap/images/trap/arrowTrap.jpg",parent),Launcher(500),launchTimer(this)
{
    connect(&launchTimer,SIGNAL(timeout()),this,SLOT(launchOver()));
}

FlyingProp *ArrowTerrain::emitFlyingProp()
{
    if(!canLaunch()){
        return nullptr;
    }
    launch();
    launchTimer.setInterval(launchInteval);
    launchTimer.start();
    int flyingPropWidth = 20;
    int flyingPropHeight = 20;
    int posX = 0;
    int posY = 0;

}

void ArrowTerrain::launchOver()
{
    ready();
    launchTimer.stop();
}

