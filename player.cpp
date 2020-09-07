#include "player.h"
#include <QSet>
#include <QDebug>

Player::Player(QObject* parent) :Role(parent)
{

}

Player::Player(int x, int y, int width,int height, QObject* parent)
    :Role(x,y,width,height,":/images/player/images/player/mario.png",500,3,parent)
    ,down_speed(500), up_speed(500), jump_time(300)
{

}

int Player::getJumpTime() const
{
    return jump_time;
}

int Player::getDownSpeed() const
{
    return down_speed;
}

int Player::getUpSpeed() const
{
    return up_speed;
}

void Player::updatePos(bool jumping,int judge_unit)
{
    if(jumping){
        tempPos.moveTo(x(),y()-judge_unit*up_speed/move_speed);
    }else{
        tempPos.moveTo(x(),y()+judge_unit*down_speed/move_speed);
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



