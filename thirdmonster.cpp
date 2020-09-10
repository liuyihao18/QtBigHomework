#include "thirdmonster.h"
#include <cmath>
#include <ctime>

int ThirdMonster::Num = 0;

ThirdMonster::ThirdMonster(QObject *parent) : Monster(parent)
{}

ThirdMonster::ThirdMonster(int x, int y, int width, int height, QObject *parent)
    : Monster(x,
              y,
              width,
              height,
              ":/images/monster/images/monster/monster3.png",
              1,
              Up,
              1,
              parent),
    Launcher(1500 + rand() % 1000), _num(Num++), _originMoveSpeed(_moveSpeed),
    _launchTimer(this)
{
    connect(&_launchTimer, SIGNAL(timeout()), this, SLOT(launchOver()));
}

void ThirdMonster::updatePos(int judge_unit)
{
    srand(time(nullptr) + _num);
    directio_n = rand() % 8;
    _moveSpeed = _originMoveSpeed - 75 + rand() % 150;
    _launchInteval = 1500 + rand() % 1000;

    switch (directio_n) {
    case Up:
        _tempPos.moveTo(x(), y() - judge_unit);
        break;

    case UpRight:
        _tempPos.moveTo(x() + judge_unit, y() - judge_unit);
        break;

    case Right:
        _tempPos.moveTo(x() + judge_unit, y());
        break;

    case DownRight:
        _tempPos.moveTo(x() + judge_unit, y() + judge_unit);
        break;

    case Down:
        _tempPos.moveTo(x(), y() + judge_unit);
        break;

    case DownLeft:
        _tempPos.moveTo(x() - judge_unit, y() + judge_unit);
        break;

    case Left:
        _tempPos.moveTo(x() - judge_unit, y());
        break;

    case UpLeft:
        _tempPos.moveTo(x() - judge_unit, y() - judge_unit - judge_unit);
        break;

    default:
        break;
    }
}

FlyingProp * ThirdMonster::launchFlyingProp()
{
    if (!canLaunch() || !isShow()) {
        return nullptr;
    }
    launch();
    _launchTimer.setInterval(_launchInteval);
    _launchTimer.start();
    int flyingPropWidth = 0.6 * width();
    int flyingPropHeight = 0.6 * width();
    int posX = 0;
    int posY = 0;

    switch (directio_n) {
    case Up:
        posX = x() + width() / 2 - flyingPropWidth / 2;
        posY = y() - flyingPropHeight;
        break;

    case UpRight:
        posX = x() + width();
        posY = y() - flyingPropHeight;
        break;

    case Right:
        posX = x() + width();
        posY = y() + height() / 2 - flyingPropHeight / 2;
        break;

    case DownRight:
        posX = x() + width();
        posY = y() + height();
        break;

    case Down:
        posX = x() + width() / 2 - flyingPropWidth / 2;
        posY = y() + height();
        break;

    case DownLeft:
        posX = x() - flyingPropWidth;
        posY = y() + height();
        break;

    case Left:
        posX = x() - flyingPropWidth;
        posY = y() + height() / 2 - flyingPropHeight / 2;
        break;

    case UpLeft:
        posX = x() - flyingPropWidth;
        posY = y() - flyingPropHeight;
        break;

    default:
        break;
    }
    return new FireBall(posX,
                        posY,
                        flyingPropWidth,
                        flyingPropHeight,
                        directio_n,
                        this);
}

void ThirdMonster::launchOver()
{
    ready();
    _launchTimer.stop();
}
