#include "flyingprop.h"

FlyingProp::FlyingProp(QObject *parent) : BaseObject(parent)
{}

FlyingProp::FlyingProp(int            x,
                       int            y,
                       int            width,
                       int            height,
                       const QString& imgPath,
                       int            direction,
                       int            moveSpeed,
                       int            HPReduce,
                       QObject       *parent)
    : BaseObject(x, y, width, height, imgPath, parent), HPReducer(HPReduce),
    MoveThing(x, y, width, height, direction, moveSpeed)
{}

void FlyingProp::updatePos(int judge_unit)
{
    int newX = x();
    int newY = y();

    switch (directio_n) {
    case Up:
        newY -= judge_unit;
        break;

    case UpRight:
        newX += judge_unit;
        newY -= judge_unit;
        break;

    case Right:
        newX += judge_unit;
        break;

    case DownRight:
        newX += judge_unit;
        newY += judge_unit;
        break;

    case Down:
        newY += judge_unit;
        break;

    case DownLeft:
        newX -= judge_unit;
        newY += judge_unit;
        break;

    case Left:
        newX -= judge_unit;
        break;

    case UpLeft:
        newX -= judge_unit;
        newY -= judge_unit;
        break;

    default:
        break;
    }
    _tempPos.moveTo(newX, newY);
}

void FlyingProp::confirmPos()
{
    _rect = _tempPos;
}

void FlyingProp::cancelPos()
{
    _tempPos = _rect;
}
