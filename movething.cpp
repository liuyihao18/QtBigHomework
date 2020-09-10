#include "movething.h"

MoveThing::MoveThing()
{}

MoveThing::MoveThing(int x,
                     int y,
                     int width,
                     int height,
                     int direction,
                     int moveSpeed)
    : directio_n(direction), _originDirection(direction), _moveSpeed(moveSpeed),
    _tempPos(x, y, width, height)
{}

void MoveThing::initialize()
{
    directio_n = _originDirection;
}

void         MoveThing::returnOriginPos()
{}

void         MoveThing::updatePos(int)
{}

void         MoveThing::confirmPos()
{}

void         MoveThing::cancelPos()
{}

void         MoveThing::needToChangeMove()
{}

const QRect& MoveThing::getTempPos()
{
    return _tempPos;
}

int MoveThing::getDirection() const
{
    return directio_n;
}

void MoveThing::setDirection(int direction)
{
    this->directio_n = direction;
}

int MoveThing::getMoveSpeed() const
{
    switch (directio_n) {
    case Up:
    case Right:
    case Down:
    case Left:
        return _moveSpeed;

    case UpRight:
    case DownRight:
    case DownLeft:
    case UpLeft:
        return _moveSpeed / 1.414;

    default:
        return _moveSpeed;
    }
}
