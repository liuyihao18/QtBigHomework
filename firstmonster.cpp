#include "firstmonster.h"

FirstMonster::FirstMonster(QObject*parent):Monster(parent)
{

}

FirstMonster::FirstMonster(int x, int y, int width, int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster1.png",1,Right,1,parent),reverse(false)
{

}

void FirstMonster::updatePos(int judge_unit)
{
    if(!reverse){
        tempPos.moveTo(x()+judge_unit,y());
    }else{
        tempPos.moveTo(x()-judge_unit,y());
    }
}

void FirstMonster::needToChangeMove()
{
    reverse = !reverse;
    direction = reverse?Left:Right;
}
