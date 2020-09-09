#include "secondmonster.h"

SecondMonster::SecondMonster(QObject* parent):Monster(parent)
{

}

SecondMonster::SecondMonster(int x, int y, int width, int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster2.png",1,Up,1,parent),
      reverse(false),upHeight(0),maxUpHeight(300)
{

}

bool SecondMonster::isUpToMaxUpHeight() const
{
    return upHeight == maxUpHeight;
}

void SecondMonster::updatePos(int judge_unit)
{
    if(!reverse){
        tempPos.moveTo(x(),y()-judge_unit);
    }else{
        tempPos.moveTo(x(),y()+judge_unit);
    }
    upHeight++;
}

void SecondMonster::needToChangeMove()
{
    reverse = !reverse;
    direction = reverse?Down:Up;
    upHeight = 0;
}
