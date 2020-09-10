#include "secondmonster.h"

SecondMonster::SecondMonster(QObject *parent) : Monster(parent)
{}

SecondMonster::SecondMonster(int x, int y, int width, int height, QObject *parent)
    : Monster(x,
              y,
              width,
              height,
              ":/images/monster/images/monster/monster2.png",
              1,
              Up,
              1,
              parent),
    _reverse(false), _upHeight(0), _maxUpHeight(300)
{}

bool SecondMonster::isUpToMaxUpHeight() const
{
    return _upHeight == _maxUpHeight;
}

void SecondMonster::updatePos(int judgeUnit)
{
    if (!_reverse) {
        _tempPos.moveTo(x(), y() - judgeUnit);
    } else {
        _tempPos.moveTo(x(), y() + judgeUnit);
    }
    _upHeight++;
}

void SecondMonster::needToChangeMove()
{
    _reverse = !_reverse;
    directio_n = _reverse ? Down : Up;
    _upHeight = 0;
}
