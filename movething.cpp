#include "movething.h"

MoveThing::MoveThing()
{

}

MoveThing::MoveThing(int x,int y, int width, int height, int moveSpeed)
    :move_speed(moveSpeed),tempPos(x,y,width,height)
{

}


void MoveThing::returnOrigin()
{

}

void MoveThing::updatePos(int)
{

}

void MoveThing::confirmPos()
{

}

void MoveThing::cancelPos()
{

}

const QRect &MoveThing::getTempPos()
{
    return tempPos;
}

int MoveThing::getMoveSpeed() const
{
    return move_speed;
}
