#include "firstmonster.h"

FirstMonster::FirstMonster(QObject *parent) : Monster(parent)
{}

FirstMonster::FirstMonster(int x, int y, int width, int height, QObject *parent)
    : Monster(x,
              y,
              width,
              height,
              ":/images/monster/images/monster/monster1.png",
              1,
              Right,
              1,
              parent),
    _reverse(false)
{}

void FirstMonster::updatePos(int judgeUnit)
{
    if (!_reverse) {
        _tempPos.moveTo(x() + judgeUnit, y());
    } else {
        _tempPos.moveTo(x() - judgeUnit, y());
    }
}

void FirstMonster::needToChangeMove()
{
    _reverse = !_reverse;
    directio_n = _reverse ? Left : Right;
}
