#include "secondmonster.h"

SecondMonster::SecondMonster(QObject* parent):Monster(parent)
{

}

SecondMonster::SecondMonster(int x, int y, int width, int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster2.jpg",parent)
{

}
