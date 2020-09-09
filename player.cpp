#include "player.h"
#include <QSet>
#include <QDebug>

Player::Player(QObject* parent) :Role(parent)
{

}

Player::Player(int x, int y, int width,int height, QObject* parent)
    :Role(x,y,width,height,":/images/player/images/player/player.png",400,3,Right,parent),Launcher(100),
      points(0),downSpeed(400),originDownSpeed(downSpeed), upSpeed(400),originUpSpeed(upSpeed), jumpTime(400), fallDownHPReduce(1), canAttack(false), jumping(false),
      jumpTimer(this),launchTimer(this)
{
    connect(&jumpTimer,SIGNAL(timeout()),this,SLOT(jumpOver()));
    connect(&launchTimer,SIGNAL(timeout()),this,SLOT(launchOver()));
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

void Player::setFallDownHPReduce(int fallDownHPReduce)
{
    this->fallDownHPReduce = fallDownHPReduce;
}

int Player::getJumpTime() const
{
    return jumpTime;
}

void Player::setJumpTime(int jumpTime)
{
    this->jumpTime = jumpTime;
}

void Player::refreshUpSpeed()
{
    upSpeed = originUpSpeed;
}

int Player::getDownSpeed() const
{
    return downSpeed;
}

int Player::getOriginDownSpeed() const
{
    return originDownSpeed;
}

void Player::setDownSpeed(int downSpeed)
{
    this->downSpeed = downSpeed;
}

void Player::refreshDownSpeed()
{
    downSpeed = originDownSpeed;
}

int Player::getUpSpeed() const
{
    return upSpeed;
}

int Player::getOriginUpSpeed() const
{
    return originUpSpeed;
}

void Player::setUpSpeed(int upSpeed)
{
    this->upSpeed = upSpeed;
}

void Player::jump(bool springJump)
{
    if(!jumping){
        jumping = true;
        if(!springJump){
            jumpTimer.setInterval(jumpTime);
        }else{
            upSpeed = 2*originUpSpeed;
            jumpTimer.setInterval(jumpTime);
        }
        jumpTimer.start();
    }
}

bool Player::ifCanAttack() const
{
    return canAttack;
}

int Player::getMoveSpeed() const
{
    return move_speed;
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
    jumping = false;
}

FlyingProp *Player::launchFlyingProp()
{
    if(!canLaunch()||!canAttack||!isShow()){
        return nullptr;
    }
    launch();
    launchTimer.setInterval(launchInteval);
    launchTimer.start();
    int flyingPropWidth = 0.4*width()*0.6666667;
    int flyingPropHeight = 0.4*height();
    int posX = 0;
    int posY = 0;
    switch(direction){
    case Up:
        posX = x()+width()/2-flyingPropWidth/2;
        posY = y()-flyingPropHeight;
        break;
    case UpRight:
        posX = x()+width();
        posY = y()-flyingPropHeight;
        break;
    case Right:
        posX = x()+width();
        posY = y()+height()/2-flyingPropHeight/2;
        break;
    case DownRight:
        posX = x()+width();
        posY = y()+height();
        break;
    case Down:
        posX = x()+width()/2-flyingPropWidth/2;
        posY = y()+height();
        break;
    case DownLeft:
        posX = x()-flyingPropWidth;
        posY = y()+height();
        break;
    case Left:
        posX = x()-flyingPropWidth;
        posY = y()+height()/2-flyingPropHeight/2;
        break;
    case UpLeft:
        posX = x()-flyingPropWidth;
        posY = y()-flyingPropHeight;
        break;
    default:
        break;
    }
    return new MagicBullet(posX,posY,flyingPropWidth,flyingPropHeight,direction,this);
}

void Player::jumpOver()
{
    upSpeed = originUpSpeed;
    jumping = false;
    jumpTimer.stop();
}

void Player::launchOver()
{
    ready();
    launchTimer.stop();
}



