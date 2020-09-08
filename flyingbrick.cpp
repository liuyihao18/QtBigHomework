#include "flyingbrick.h"

FlyingBrick::FlyingBrick(QObject* parent) :Terrain(parent)
{

}

FlyingBrick::FlyingBrick(int x, int y, int width,int height, QObject *parent)
    :Terrain(x,y, width, height,":/images/terrain/images/terrain/flyingBrick.jpg",parent),MoveThing(x,y,width,height,Right,200),reverse(false)
{

}

bool FlyingBrick::isReverse() const
{
    return reverse;
}

void FlyingBrick::updatePos(int judge_unit)
{
    if(!reverse){
        tempPos.moveTo(x()+judge_unit,y());
    }else{
        tempPos.moveTo(x()-judge_unit,y());
    }
}

void FlyingBrick::confirmPos()
{
    MoveThing::confirmPos();
    rect = tempPos;
}

void FlyingBrick::cancelPos()
{
    MoveThing::cancelPos();
    tempPos = rect;
}

void FlyingBrick::returnOriginPos()
{
    MoveThing::returnOriginPos();
    moveRect(originX(),originY());
}

void FlyingBrick::needToChangeMove()
{
    MoveThing::needToChangeMove();
    reverse = !reverse;
    direction = reverse?Left:Right;
}

void FlyingBrick::initialize()
{
    MoveThing::initialize();
    returnOriginPos();
}
