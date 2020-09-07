#include "floorgrass.h"

FloorGrass::FloorGrass(QObject* parent) :Ground(parent)
{

}

FloorGrass::FloorGrass(int x, int y, int width, int height, QObject* parent)
    :Ground(x,y,width,height,":/images/terrain/ground/images/terrain/ground/floor_grass.jpg",parent)
{

}
