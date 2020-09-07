#include "thirdmonster.h"

ThirdMonster::ThirdMonster(QObject* parent):Monster(parent)
{

}

ThirdMonster::ThirdMonster(int x, int y, int width,int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster3.jpg",1,1,parent)
{

}
