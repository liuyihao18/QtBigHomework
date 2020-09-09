#include "arrowterrain.h"

ArrowTerrain::ArrowTerrain(QObject* parent): Terrain(parent)
{

}

ArrowTerrain::ArrowTerrain(int x, int y, int width, int height, QObject *parent)
    :Terrain(x,y,width,height,":/images/terrain/images/terrain/arrowTerrain.png",parent),Launcher(1500),launchTimer(this)
{
    connect(&launchTimer,SIGNAL(timeout()),this,SLOT(launchOver()));
}

FlyingProp *ArrowTerrain::launchFlyingProp()
{
    if(!canLaunch()||!isShow()){
        return nullptr;
    }
    launch();
    launchTimer.setInterval(launchInteval);
    launchTimer.start();
    int flyingPropWidth = width();
    int flyingPropHeight = 0.25*height();
    return new Arrow(x()-flyingPropWidth,y()+height()/2-flyingPropHeight/2,flyingPropWidth,flyingPropHeight,Left,this);
}

void ArrowTerrain::launchOver()
{
    ready();
    launchTimer.stop();
}

