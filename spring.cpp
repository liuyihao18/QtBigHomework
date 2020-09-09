#include "spring.h"

Spring::Spring(QObject* parent) :Terrain(parent)
{

}

Spring::Spring(int x, int y, int width,int height, QObject *parent)
    :Terrain(x,y,width,height,":/images/terrain/images/terrain/spring.png",parent)
{

}
