#include "role.h"

Role::Role(QObject *parent) : BaseObject(parent), _HP(3)
{}

Role::Role(int            x,
           int            y,
           int            width,
           int            height,
           const QString& imgPath,
           int            speed,
           int            HP,
           int            direction,
           QObject       *parent)
    : BaseObject(x, y, width, height, imgPath, parent), MoveThing(x,
                                                                  y,
                                                                  width,
                                                                  height,
                                                                  direction,
                                                                  speed),
    _HP(HP), _originHP(HP), _invincible(false), _invincibleTimer(this)
{
    _invincibleTimer.setInterval(1000);
    connect(&_invincibleTimer, SIGNAL(timeout()), this, SLOT(invincibleOver()));
}

void Role::initialize()
{
    MoveThing::initialize();
    returnOriginPos();
    _HP = _originHP;
}

void Role::returnOriginPos()
{
    MoveThing::returnOriginPos();
    moveRect(_originX, _originY);
}

void Role::confirmPos()
{
    MoveThing::confirmPos();
    _rect = _tempPos;
}

void Role::cancelPos()
{
    MoveThing::cancelPos();
    _tempPos = _rect;
}

int Role::getHP() const
{
    return _HP;
}

void Role::addHP(int x)
{
    _HP += x;
}

void Role::reduceHP(int x)
{
    if (!_invincible) {
        _HP -= x;

        if (_HP <= 0) {
            hide();
        }
        _invincible = true;
        _invincibleTimer.start();
    }
}

void Role::invincibleOver()
{
    _invincible = false;
    _invincibleTimer.stop();
}
