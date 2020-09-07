#include "rock.h"

Rock::Rock(QObject* parent) :Ground(parent)
{

}

Rock::Rock(int x, int y, int width, int height, QObject *parent)
    :Ground(x,y,width,height,":/images/terrain/ground/images/terrain/ground/rock.jpg",parent)
{

}
