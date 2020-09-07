#include "trap.h"

Trap::Trap(QObject* parent) :BaseObject(parent)
{

}

Trap::Trap(int x, int y, int width,int height, const QString &imgPath, int HPReduce,QObject *parent)
    :BaseObject(x,y,width,height,imgPath,parent), HPReduce(HPReduce)
{

}

int Trap::getHPReduce() const
{
    return HPReduce;
}
