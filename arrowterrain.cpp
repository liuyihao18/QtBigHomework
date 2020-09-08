#include "arrowterrain.h"

ArrowTerrain::ArrowTerrain(QObject* parent): Terrain(parent)
{

}

ArrowTerrain::ArrowTerrain(int x, int y, int width, int height, QObject *parent)
    :Terrain(x,y,width,height,":/images/trap/images/trap/arrowTrap.jpg",parent)
{

}
