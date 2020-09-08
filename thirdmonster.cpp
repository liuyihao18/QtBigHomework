#include "thirdmonster.h"
#include <cmath>
#include <ctime>

int ThirdMonster::num = 0;

ThirdMonster::ThirdMonster(QObject* parent):Monster(parent)
{

}

ThirdMonster::ThirdMonster(int x, int y, int width,int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster3.jpg",1,Up,1,parent),m_num(num++)
{

}

void ThirdMonster::updatePos(int judge_unit)
{
    srand(time(nullptr)+m_num);
    direction = rand()%8;
    switch (direction) {
    case Up:
        tempPos.moveTo(x(),y()-judge_unit);
        break;
    case UpRight:
        tempPos.moveTo(x()+judge_unit,y()-judge_unit);
        break;
    case Right:
        tempPos.moveTo(x()+judge_unit,y());
        break;
    case DownRight:
        tempPos.moveTo(x()+judge_unit,y()+judge_unit);
        break;
    case Down:
        tempPos.moveTo(x(),y()+judge_unit);
        break;
    case DownLeft:
        tempPos.moveTo(x()-judge_unit,y()+judge_unit);
        break;
    case Left:
        tempPos.moveTo(x()-judge_unit,y());
        break;
    case UpLeft:
        tempPos.moveTo(x()-judge_unit,y()-judge_unit-judge_unit);
        break;
    default:
        break;
    }
}
