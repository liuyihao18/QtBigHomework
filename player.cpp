#include "player.h"
#include <QSet>
#include <QDebug>

Player::Player(QObject* parent) :Role(parent)
{

}

Player::Player(int x, int y, int width,int height, QObject* parent)
    :Role(x,y,width,height,":/images/player/images/player/mario.png",400,3,Right,parent),
    points(0),downSpeed(400), upSpeed(400), jumpTime(400), fallDownHPReduce(1), canAttack(false), jumping(false),
    jumpTimer(this)
{
    connect(&jumpTimer,SIGNAL(timeout()),this,SLOT(jumpOver()));
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
        jumpTime = 450;
        addPoins(10);
    }else if(buffName==QString("FlowerBuff")){
        addHP(1);
        jumpTime = 450;
        canAttack = true;
        addPoins(20);
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

void Player::jump(bool springJump)
{
    if(!jumping){
        jumping = true;
        if(!springJump){
            jumpTimer.setInterval(jumpTime);
        }else{
            jumpTimer.setInterval(2*jumpTime);
        }
        jumpTimer.start();
    }
}

void Player::updatePos(int judge_unit)
{
    if(jumping){
        tempPos.moveTo(x(),y()-judge_unit*upSpeed/move_speed);
    }else{
        tempPos.moveTo(x(),y()+judge_unit*downSpeed/move_speed);
    }
}

void Player::initialize()
{
    Role::initialize();
    points = 0;
    canAttack = false;
}

FlyingProp *Player::emitFlyingProp()
{
    return nullptr;
}

void Player::jumpOver()
{
    jumping = false;
    jumpTimer.stop();
}



