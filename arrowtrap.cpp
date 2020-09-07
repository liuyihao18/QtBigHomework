#include "arrowtrap.h"

ArrowTrap::ArrowTrap(QObject* parent): Trap(parent)
{

}

ArrowTrap::ArrowTrap(int x, int y, int width, int height, QObject *parent)
    :Trap(x,y,width,height,":/images/trap/images/trap/arrowTrap.jpg",parent), MoveThing(x,y,width,height,500)
{

}
