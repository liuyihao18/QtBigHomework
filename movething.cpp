#include "movething.h"

MoveThing::MoveThing()
{

}

MoveThing::MoveThing(int x,int y, int width, int height, int direction, int moveSpeed)
    :direction(direction),originDirection(direction), move_speed(moveSpeed),tempPos(x,y,width,height)
{

}


void MoveThing::initialize()
{
    direction = originDirection;
}

void MoveThing::returnOriginPos()
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

void MoveThing::needToChangeMove()
{

}

const QRect &MoveThing::getTempPos()
{
    return tempPos;
}

int MoveThing::getDirection() const
{
    return direction;
}

int MoveThing::getMoveSpeed() const
{
    switch (direction) {
    case Up:
    case Right:
    case Down:
    case Left:
        return move_speed;
    case UpRight:
    case DownRight:
    case DownLeft:
    case UpLeft:
        return move_speed/1.414;
    default:
        return move_speed;
    }
}
