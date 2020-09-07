#include "role.h"

Role::Role(QObject* parent) :BaseObject(parent), HP(3)
{

}

Role::Role(int x, int y, int width,int height, const QString &imgPath, int speed,int HP, QObject* parent)
    :BaseObject(x,y,width,height,imgPath, parent), MoveThing(x,y,width,height,speed) , HP(HP)
{

}

void Role::returnOrigin()
{
    moveRect(originX(),originY());
}
