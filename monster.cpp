#include "monster.h"

Monster::Monster(QObject* parent) :Role(parent)
{

}

Monster::Monster(int x, int y, int width,int height, const QString& imgPath, QObject* parent)
    :Role(x,y,width,height,imgPath,250,1,parent)
{

}
