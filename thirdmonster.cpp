#include "thirdmonster.h"
#include <cmath>
#include <ctime>

int ThirdMonster::num = 0;

ThirdMonster::ThirdMonster(QObject* parent):Monster(parent)
{

}

ThirdMonster::ThirdMonster(int x, int y, int width,int height, QObject *parent)
    :Monster(x,y,width,height,":/images/monster/images/monster/monster3.png",1,Up,1,parent),
      Launcher(1500+rand()%1000), m_num(num++),originMoveSpeed(move_speed),launchTimer(this)
{
    connect(&launchTimer,SIGNAL(timeout()),this,SLOT(launchOver()));
}

void ThirdMonster::updatePos(int judge_unit)
{
    srand(time(nullptr)+m_num);
    direction = rand()%8;
    move_speed = originMoveSpeed-75+rand()%150;
    launchInteval = 1500+rand()%1000;
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

FlyingProp *ThirdMonster::launchFlyingProp()
{
    if(!canLaunch()||!isShow()){
        return nullptr;
    }
    launch();
    launchTimer.setInterval(launchInteval);
    launchTimer.start();
    int flyingPropWidth = 0.6*width();
    int flyingPropHeight = 0.6*width();
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
    return new FireBall(posX,posY,flyingPropWidth,flyingPropHeight,direction,this);
}

void ThirdMonster::launchOver()
{
    ready();
    launchTimer.stop();
}
