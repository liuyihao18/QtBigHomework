#ifndef ARROWTRAP_H
#define ARROWTRAP_H

#include "terrain.h"

class ArrowTerrain : public Terrain
{
    Q_OBJECT
public:
    ArrowTerrain(QObject* parent = nullptr);
    ArrowTerrain(int x,int y,int width,int height,QObject* parent = nullptr);
};

#endif // ARROWTRAP_H
