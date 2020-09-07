#include "player.h"
#include <QSet>
#include <QDebug>

Player::Player(QObject* parent) :Role(parent)
{

}

Player::Player(int x, int y, int width,int height, QObject* parent)
    :Role(x,y,width,height,":/images/player/images/player/mario.png",500,3,parent),
    points(0),downSpeed(500), upSpeed(500), jumpTime(300), fallDownHPReduce(1), canAttack(false)
{

}

int Player::getPoints() const
{
    return points;
}

void Player::addPoins(int point)
{
    points+=point;
}

void Player::reducePoints(int point)
{
    points-=point;
}

void Player::addBuff(const QString &buffName)
{
    if(buffName==QString("MushroomBuff")){
        addHP(1);
    }else if(buffName==QString("FlowerBuff")){
        addHP(1);
        canAttack = true;
    }
}

int Player::getFallDownHPReduce() const
{
    return fallDownHPReduce;
}

int Player::getJumpTime() const
{
    return jumpTime;
}

int Player::getDownSpeed() const
{
    return downSpeed;
}

int Player::getUpSpeed() const
{
    return upSpeed;
}

void Player::updatePos(bool jumping,int judge_unit)
{
    if(jumping){
        tempPos.moveTo(x(),y()-judge_unit*upSpeed/move_speed);
    }else{
        tempPos.moveTo(x(),y()+judge_unit*downSpeed/move_speed);
    }
}

void Player::confirmPos()
{
    rect = tempPos;
}

void Player::cancelPos()
{
    tempPos = rect;
}

void Player::initialize()
{
    Role::initialize();
    points = 0;
    canAttack = false;
}



