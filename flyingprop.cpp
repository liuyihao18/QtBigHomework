#include "flyingprop.h"

FlyingProp::FlyingProp(QObject* parent) :BaseObject(parent), moveSpeed(0)
{

}

FlyingProp::FlyingProp(int x, int y, int width, int height, const QString &imgPath, int moveSpeed, int HPReduce, QObject *parent)
    :BaseObject(x,y,width,height,imgPath,parent),HPReducer(HPReduce),moveSpeed(moveSpeed)
{

}

int FlyingProp::getMoveSpeed() const
{
    return moveSpeed;
}
