#include "role.h"

Role::Role(QObject* parent) :BaseObject(parent), HP(3)
{

}

Role::Role(int x, int y, int width,int height, const QString &imgPath, int speed,int HP, QObject* parent)
    :BaseObject(x,y,width,height,imgPath, parent), MoveThing(x,y,width,height,speed) ,
      HP(HP), originHP(HP), invincible(false),invincibleTimer(this)
{
    invincibleTimer.setInterval(1000);
    connect(&invincibleTimer,SIGNAL(timeout()),this,SLOT(invincibleOver()));
}

void Role::initialize()
{
    moveRect(originX(),originY());
    HP = originHP;
}

void Role::returnOriginPos()
{
    moveRect(originX(),originY());
}

int Role::getHP() const
{
    return HP;
}

void Role::addHP(int x)
{
    HP+=x;
}

void Role::reduceHP(int x)
{
    if(!invincible){
        HP-=x;
        if(HP<=0){
            hide();
        }
        invincible = true;
        invincibleTimer.start();
    }
}

void Role::invincibleOver()
{
    invincible = false;
    invincibleTimer.stop();
}


