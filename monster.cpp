#include "monster.h"

Monster::Monster(QObject* parent) :Role(parent)
{

}

Monster::Monster(int x, int y, int width,int height, const QString& imgPath, int HP, int HPReduce, QObject* parent)
    :Role(x,y,width,height,imgPath,250,HP,parent),HPReduce(HPReduce)
{

}

int Monster::getHPReduce() const
{
    return HPReduce;
}
