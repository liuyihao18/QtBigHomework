#include "goal.h"

Goal::Goal(QObject* parent): BaseObject(parent)
{

}

Goal::Goal(int x, int y, int width, int height, QObject *parent)
    :BaseObject(x,y,width,height,":/images/goal/images/goal/goal.png",parent)
{

}
