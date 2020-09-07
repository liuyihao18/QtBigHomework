#include "flyingbrick.h"

FlyingBrick::FlyingBrick(QObject* parent) :Terrain(parent)
{

}

FlyingBrick::FlyingBrick(int x, int y, int width,int height, QObject *parent)
    :Terrain(x,y, width, height,":/images/terrain/images/terrain/flyingBrick.jpg",parent),MoveThing(x,y,width,height,200)
{

}

void FlyingBrick::returnOrigin()
{
    moveRect(originX(),originY());
}
