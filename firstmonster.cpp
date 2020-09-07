#include "firstmonster.h"

FirstMonster::FirstMonster(QObject*parent):Monster(parent)
{

}

FirstMonster::FirstMonster(int x, int y, int width, int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster1.jpg", parent)
{

}
