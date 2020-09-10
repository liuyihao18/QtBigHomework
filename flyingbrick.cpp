#include "flyingbrick.h"

FlyingBrick::FlyingBrick(QObject *parent) : Terrain(parent)
{}

FlyingBrick::FlyingBrick(int x, int y, int width, int height, QObject *parent)
    : Terrain(x,
              y,
              width,
              height,
              ":/images/terrain/images/terrain/flyingBrick.png",
              parent), MoveThing(x, y, width, height, Right, 200), _reverse(false)
{}

bool FlyingBrick::isReverse() const
{
    return _reverse;
}

void FlyingBrick::updatePos(int judgeUnit)
{
    if (!_reverse) {
        _tempPos.moveTo(x() + judgeUnit, y());
    } else {
        _tempPos.moveTo(x() - judgeUnit, y());
    }
}

void FlyingBrick::confirmPos()
{
    MoveThing::confirmPos();
    _rect = _tempPos;
}

void FlyingBrick::cancelPos()
{
    MoveThing::cancelPos();
    _tempPos = _rect;
}

void FlyingBrick::returnOriginPos()
{
    MoveThing::returnOriginPos();
    moveRect(_originX, _originY);
}

void FlyingBrick::needToChangeMove()
{
    MoveThing::needToChangeMove();
    _reverse = !_reverse;
    directio_n = _reverse ? Left : Right;
}

void FlyingBrick::initialize()
{
    MoveThing::initialize();
    returnOriginPos();
}
