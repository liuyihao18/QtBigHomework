#include "flowerbuff.h"

FlowerBuff::FlowerBuff(QObject *parent) :Buff(parent)
{

}

FlowerBuff::FlowerBuff(int x, int y, int width, int height, QObject *parent)
    :Buff(x,y,width,height,":/images/buff/images/buff/flowerBuff.png",parent)
{

}
