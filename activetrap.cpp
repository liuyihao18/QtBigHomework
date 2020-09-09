#include "activetrap.h"

ActiveTrap::ActiveTrap(QObject* parent) :Trap(parent)
{

}

ActiveTrap::ActiveTrap(int x, int y, int width, int height, QObject *parent)
    :Trap(x,y,width,height,":/images/trap/images/trap/activeTrap.png",1,parent)
{

}
