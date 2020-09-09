#include "passivetrap.h"

PassiveTrap::PassiveTrap(QObject* parent) :Trap(parent)
{

}

PassiveTrap::PassiveTrap(int x, int y, int width, int height, QObject *parent)
    :Trap(x,y,width, height,":/images/trap/images/trap/passiveTrap.png",1,parent)
{

}
