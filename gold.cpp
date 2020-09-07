#include "gold.h"

Gold::Gold(QObject* parent):Values(parent)
{

}

Gold::Gold(int x, int y, int width, int height, QObject *parent)
    :Values(x,y,width,height,":/images/gold/images/gold/gold.png",1,parent)
{

}
